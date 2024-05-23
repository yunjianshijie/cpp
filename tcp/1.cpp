#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // 创建 UDP 套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);  //因为SOCK_DGRAM只有UDP所以最后可以填0
    if (sockfd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // 设置服务器地址和端口
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(65432);

    // 绑定套接字到服务器地址和端口
    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "UDP server is listening on 0.0.0.0:65432" << std::endl;

    // 接收和发送数据包
    char buffer[1024];
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    while (true) {
        // 接收来自客户端的数据
        ssize_t bytesReceived = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (bytesReceived == -1) {
            std::cerr << "Failed to receive data" << std::endl;
            continue;
        }

        std::cout << "Received " << bytesReceived << " bytes from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

        // 将数据原封不动地发回给客户端
        ssize_t bytesSent = sendto(sockfd, buffer, bytesReceived, 0, (struct sockaddr*)&clientAddr, clientAddrLen);
        if (bytesSent == -1) {
            std::cerr << "Failed to send data" << std::endl;
            continue;
        }

        std::cout << "Sent " << bytesSent << " bytes back to " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;
    }

    close(sockfd);
    return 0;
}