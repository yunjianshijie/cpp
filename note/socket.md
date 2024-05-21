socket 系统调用
关键的 socket 系统调用包括以下几种。
1. socket()系统调用创建一个新 socket。
2. bind()系统调用将一个 socket 绑定到一个地址上。通常，服务器需要使用这个调用来将其 socket 绑定到一个众所周知的地址上使得客户端能够定位到该 socket 上。
3. listen()系统调用允许一个流 socket 接受来自其他 socket 的接入连接。
4. accept()系统调用 在一个监听流 socket 上接受来自一个对等应用序的连接，并可选地返回对等 socket 的地址。
5. connect()系统调用建立与另一个 socket 之间的连接

##  we
~~~ c
#include< sys/socket.h>
int socket(int domain ,int type ,int protocol); //回-1 
~~~
1. type 参数指定了 socket 类型
2. domain 参数指定了 socket 的通信 domain。
3. otocol 参数在本书描述的 socket 类型中总会被指定为 0。
4. 返回int socket文件描述符

## bind
~~~ c
#include<sys/socket.h>
int bind(int sofkfd,const struct sockaddr *addr,socklen_t addrlen);
~~~

1. sockfd是上个socket()返回的
2. addr是指针，它指向了一个指定该socket绑定到的地址结构。
3. addrlen 参数指定了地址结构的大小。addrlen 参数使用的 socklen_t 数据类型在 SUSv3 被规定为一个整数类型。
这个要么提前知道，要么用listen() 不用bind()


## 通用 socket 地址结构：struct sockaddr 

bind()的第二个参数
~~~c
struct sockaddr{
    sa_family_t sa_family;
    char sa_data[14];
};
~~~

为了所有的结构都可以
所以。。
## 主动和被动 socket

服务端被动接听



## 监听接入连接：listen() 

listen()系统调用将文件描述符 sockfd 引用的流 socket 标记为被动。这个 socket 后面会被用来接受来自其他（主动的）socket 的连接。


~~~ c

#include<sys/socket.h>
int listen(int sockfd,int backlog);
~~~

backlog 参数的用途首先需要注意到客户端可能会在服务器调用 accept()之前调用connect()。这种情况是有可能会发生的，如服务器可能正忙于处理其他客户端





# 

如 ssh（安全的 shell）daemon 使用众所周知的端口 22，HTTP（Web 服务器和浏览器之间通信时所采用的协议）使用众所周知的端口 80。
 