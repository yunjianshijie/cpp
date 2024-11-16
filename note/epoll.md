


# epoll 多路复用

3个函数原型

~~~ cpp
#include <sys/epoll.h>
//创建epoll实例
int epoll_create(int size);
//管理红黑树上文件描述符（添加，修改，删除）
int epoll_ctl(int epfd,int op,int fd,struct epoll_event *event);
 // EPOLL_CTL_ADD：注册新的fd到epfd中
    // EPOLL_CTL_MOD：修改已经注册的fd的监听事件
    // EPOLL_CTL_DEL：从epfd中删除一个fd
//检测epoll树上有没有就绪的文件描述符
int epoll_wait(int epfd,struct eppll_event * events,int maxevents,int timeout);
~~~

创建 epoll 实例
注册需要监控的文件描述符及其事件类型
在 epoll_wait 中等待事件发生
处理发生的事件
如有需要,可以修改已注册的文件描述符

在cpp中 events.data() (使用vector容器)


``` 


