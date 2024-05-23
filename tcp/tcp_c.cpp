#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    // 创建 TCP 套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // 设置服务器地址和端口
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(12346);

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Failed to connect to server" << std::endl;
        close(sockfd);
        return 1;
    }

    // 发送数据到服务器
    char message[50];
    std::cout << "发一句话吧\n";
    std::cin >> message;
    std::cout << " 即将发送  " << message << "size " << sizeof(message) << std::endl;
    //= "Hello, TCP server!";
    ssize_t bytesSent = send(sockfd, message, sizeof(message), 0);
    // free(message);
    if (bytesSent == -1)
    {
        std::cerr << "Failed to send data" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Sent " << bytesSent << " bytes to the server" << std::endl;

    // 接收服务器的响应
    char buffer[1024];
    ssize_t bytesReceived = recv(sockfd, buffer, sizeof(buffer), 0);
    if (bytesReceived == -1)
    {
        std::cerr << "Failed to receive data" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Received " << bytesReceived << " bytes from the server" << std::endl;
    std::cout << "Message: " << buffer << std::endl;

    close(sockfd);
    return 0;
}