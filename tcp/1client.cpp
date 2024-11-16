#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
int main() {
    // 创建 socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // 连接服务器
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
     if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0) {
        std::cerr << "Invalid address" << std::endl;
        return 1;
    }
    addr.sin_port = htons(8085);
    if (connect(client_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        close(client_fd);
        return 1;
    }

    // 发送数据
    const char* message = "Hello, server!";
    if (write(client_fd, message, strlen(message)) < 0) {
        std::cerr << "Failed to send data to server" << std::endl;
        close(client_fd);
        return 1;
    }

    // 读取响应
    char buffer[1024];
    ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer));
    if (bytes_read < 0) {
        std::cerr << "Failed to read from server" << std::endl;
        close(client_fd);
        return 1;
    } else if (bytes_read == 0) {
        std::cout << "Server closed the connection" << std::endl;
    } else {
        std::cout << "Received from server: " << std::string(buffer, static_cast<size_t>(bytes_read)) << std::endl;
    }

    // 关闭 socket
    close(client_fd);

    return 0;
}