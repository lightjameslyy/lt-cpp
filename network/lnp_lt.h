#ifndef LNP_LT_H_
#define LNP_LT_H_

/*
 * Linux Network Programming header file by liutao.
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#include <sys/un.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <netdb.h>
#include <poll.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <algorithm>

namespace lt {

bool isHostBigEndian();

template<size_t N>
struct EchoPacket {
    int len;
    char buf[N];
};

ssize_t readn(int fd, void* buf, size_t count);
ssize_t writen(int fd, const void* buf, size_t count);

ssize_t recvpeek(int sockfd, void* buf, size_t len);

ssize_t readline(int sockfd, void* buf, size_t maxlen);

void activate_nonblock(int fd);
void deactivate_nonblock(int fd);

int read_timeout(int fd, unsigned int wait_seconds);
int write_timeout(int fd, unsigned int wait_seconds);
int accept_timeout(int fd, struct sockaddr_in* addr, unsigned int wait_seconds);
int connect_timeout(int fd, struct sockaddr_in* addr, unsigned int wait_seconds);

void send_fd(int sockfd, int sendfd);
int recv_fd(int sockfd);

// epoll
namespace epoll {

typedef std::vector<struct epoll_event> EventList;

}   // namespace epoll

// info
namespace info {

// 获取本机IP地址，默认返回第一个IP地址
inline int getlocalip(char* ip) {
    char host[100] = {0};
    if (gethostname(host, sizeof(host)) < 0)
        return -1;
    struct hostent* hp;
    if ((hp = gethostbyname(host)) == NULL)
        return -1;
    strcpy(ip, inet_ntoa(*(struct in_addr*)hp->h_addr_list[0]));
    return 0;
}

}   // namespace info

// errors
namespace err {

inline void Exit(const char* fmt) {
    perror(fmt);
    exit(EXIT_FAILURE);
}

}   // namespace err

namespace sem {

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds* buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short*  array;  /* Array for GETALL, SETALL */
    struct seminfo*  __buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

inline int sem_create(key_t key) {
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid == -1)
        err::Exit("semget");

    return semid;
}

inline int sem_open(key_t key) {
    int semid = semget(key, 0, 0);
    if (semid == -1)
        err::Exit("semget");

    return semid;
}

inline int sem_setval(int semid, int val) {
    semun su;
    su.val = val;
    int ret = semctl(semid, 0, SETVAL, su);
    if (ret == -1)
        err::Exit("sem_setval");
    return ret;
}

inline int sem_getval(int semid) {
    int ret = semctl(semid, 0, GETVAL, 0);
    if (ret == -1)
        err::Exit("sem_getval");
    return ret;
}

inline int sem_rmid(int semid) {
    int ret = semctl(semid, 0, IPC_RMID, 0);
    if (ret == -1)
        err::Exit("sem_rmid");
    return ret;
}

inline int sem_p(int semid) {
    struct sembuf sops = {0, -1, 0};
    int ret = semop(semid, &sops, 1);
    if (ret == -1)
        err::Exit("semop");
    return ret;
}

inline int sem_v(int semid) {
    struct sembuf sops = {0, 1, 0};
    int ret = semop(semid, &sops, 1);
    if (ret == -1)
        err::Exit("semop");
    return ret;
}

inline int sem_p(int semid, int no) {
    struct sembuf sops = {no, -1, 0};
    int ret = semop(semid, &sops, 1);
    if (ret == -1)
        err::Exit("semop");
    return ret;
}

inline int sem_v(int semid, int no) {
    struct sembuf sops = {no, 1, 0};
    int ret = semop(semid, &sops, 1);
    if (ret == -1)
        err::Exit("semop");
    return ret;
}
}   // namespace sem

namespace shm {

struct shmhead {
    unsigned int blksize;   // 块大小
    unsigned int blocks;    // 总块数
    unsigned int rd_index;  // 读索引
    unsigned int wr_index;  // 写索引
};

struct shmfifo {
    shmhead* p_shm;     // 共享内存头部指针
    char* p_payload;    // 有效负载的起始地址

    int shmid;          // 共享内存ID
    int sem_mutex;      // 用于互斥的信号量
    int sem_full;       // 用于控制共享内存是否满的信号量
    int sem_empty;      // 用于控制共享内存是否空的信号量

};

shmfifo* shmfifo_init(int key, int blksize, int blocks);
void shmfifo_put(shmfifo* fifo, const void* buf);
void shmfifo_get(shmfifo* fifo, void* buf);
void shmfifo_destroy(shmfifo* fifo);

}   // namespace shm

}   // namespace lt

#endif  // LNP_LT_H_
