#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <cstring>
constexpr int MAX_EVENTS = 10;

int main() {
    // 创建 socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // 绑定 socket
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8085);
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        return 1;
    }

    // 监听 socket
    if (listen(server_fd, 10) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return 1;
    }

    // 创建 epoll 实例
    int epoll_fd = epoll_create1(0);
    if (epoll_fd < 0) {
        std::cerr << "Failed to create epoll instance" << std::endl;
        return 1;
    }

    // 注册 server_fd 到 epoll 实例
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) < 0) {
        std::cerr << "Failed to add server socket to epoll" << std::endl;
        return 1;
    }

    std::vector<struct epoll_event> events(MAX_EVENTS);

    // 处理事件
    while (true) {
        int num_events = epoll_wait(epoll_fd, events.data(), MAX_EVENTS, -1);
        if (num_events < 0) {
            std::cerr << "Failed to wait for epoll events" << std::endl;
            return 1;
        }

        for (int i = 0; i < num_events; i++) {
            if (events[i].data.fd == server_fd) {
                // 接受新的连接
                int client_fd = accept(server_fd, nullptr, nullptr);
                if (client_fd < 0) {
                    std::cerr << "Failed to accept connection" << std::endl;
                    continue;
                }

                // 将新的客户端 socket 注册到 epoll 实例
                event.events = EPOLLIN;
                event.data.fd = client_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) < 0) {
                    std::cerr << "Failed to add client socket to epoll" << std::endl;
                    close(client_fd);
                    continue;
                }

                std::cout << "Accepted new connection on fd " << client_fd << std::endl;
            } else {
                // 处理客户端 socket 上的事件
                int client_fd = events[i].data.fd;
                char buffer[1024];
                ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer));
                if (bytes_read < 0) {
                    std::cerr << "Failed to read from client socket" << std::endl;
                    close(client_fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, nullptr);
                } else if (bytes_read == 0) {
                    std::cout << "Client disconnected on fd " << client_fd << std::endl;
                    close(client_fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, nullptr);
                } else {
                    std::cout << "Received " << bytes_read << " bytes on fd " << client_fd << ": " << std::string(buffer, static_cast<size_t>(bytes_read)) << std::endl;
                }
            }
        }
    }

    return 0;
}