#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // 创建 TCP 套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // 设置服务器地址和端口
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12346); //h to n

    // 绑定套接字到地址和端口
    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(sockfd);
        return 1;
    }

    // 开始监听连接请求
    if (listen(sockfd, 5) == -1) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Server is listening on port 12345..." << std::endl;

    // 接受客户端连接
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSockfd == -1) {
        std::cerr << "Failed to accept client connection" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Accepted connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

    // 接收客户端发送的数据
    char buffer[1024];
    ssize_t bytesReceived = recv(clientSockfd, buffer, sizeof(buffer), 0);
    if (bytesReceived == -1) {
        std::cerr << "Failed to receive data" << std::endl;
        close(clientSockfd);
        close(sockfd);
        return 1;
    }

    std::cout << "Received " << bytesReceived << " bytes from the client" << std::endl;
    std::cout << "Message: " << buffer << std::endl;

    // 向客户端发送响应
    
    const char* response = "Hello, client!";
    ssize_t bytesSent = send(clientSockfd, response, strlen(response), 0);
    if (bytesSent == -1) {
        std::cerr << "Failed to send data" << std::endl;
        close(clientSockfd);
        close(sockfd);
        return 1;
    }

    std::cout << "Sent " << bytesSent << " bytes to the client" << std::endl;

    close(clientSockfd);
    close(sockfd);
    return 0;
}