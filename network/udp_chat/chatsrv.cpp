/*
 * echo server using UDP
 */

#include "lnp_lt.h"
#include "pub.h"

using namespace lt;

// 聊天室成员列表
static USER_LIST client_list;

static void do_sendlist(char* username, int sock, struct sockaddr_in* cliaddr) {
    // 发送在线人数
    int count = htonl((int)client_list.size());
    sendto(sock, &count, sizeof(int), 0, (struct sockaddr*)cliaddr, sizeof(*cliaddr));

    // 发送在线用户列表
    printf("sending user list to: %s <-> %s:%d\n", username, inet_ntoa(cliaddr->sin_addr), ntohs(cliaddr->sin_port));
    for (auto it = client_list.begin(); it != client_list.end(); ++it) {
        sendto(sock, &*it, sizeof(USER_INFO), 0, (struct sockaddr*)cliaddr, sizeof(*cliaddr));
    }
}

static void do_logout(MESSAGE& msg, int sock, struct sockaddr_in* cliaddr) {
    // msg.body: username
    MESSAGE m;
    m.cmd = htonl(S2C_SOMEONE_LOGOUT);
    struct sockaddr_in peeraddr;
    memset(&peeraddr, 0, sizeof(peeraddr));
    peeraddr.sin_family = AF_INET;

    auto delit = client_list.begin();
    for (auto it = client_list.begin(); it != client_list.end(); ++it) {
        if (strcmp(it->username, msg.body) == 0) {
            delit = it;
        } else {
            peeraddr.sin_addr.s_addr = it->ip;
            peeraddr.sin_port = it->port;
            memcpy(m.body, msg.body, strlen(msg.body));
            if (sendto(sock, &m, sizeof(m), 0, (struct sockaddr*)&peeraddr, sizeof(peeraddr)) < 0)
                err::Exit("sendto");
        }
    }
    client_list.erase(delit);
    printf("user %s has logout server\n", msg.body);
}

static void do_login(MESSAGE& msg, int sock, struct sockaddr_in* cliaddr) {
    USER_INFO user;
    strcpy(user.username, msg.body);
    user.ip = cliaddr->sin_addr.s_addr;
    user.port = cliaddr->sin_port;

    // 查找用户
    auto it = client_list.begin();
    for (; it != client_list.end(); ++it) {
        if (strcmp(it->username, msg.body) == 0)
            break;
    }

    MESSAGE reply_msg;
    memset(&reply_msg, 0, sizeof(reply_msg));
    if (it == client_list.end()) {  // 用户不存在，新添加
        printf("has a user login: %s <-> %s:%d\n", user.username, inet_ntoa(cliaddr->sin_addr), ntohs(user.port));
        client_list.push_back(user);

        // 登录成功应答
        reply_msg.cmd = htonl(S2C_LOGIN_OK);
        sendto(sock, &reply_msg, sizeof(reply_msg), 0, (struct sockaddr*)cliaddr, sizeof(*cliaddr));

        do_sendlist(user.username, sock, cliaddr);

        // 向其他用户通知有新用户登录
        for (it = client_list.begin(); it != client_list.end(); ++it) {
            if (strcmp(it->username, user.username) == 0)
                continue;
            struct sockaddr_in peeraddr;
            memset(&peeraddr, 0, sizeof(peeraddr));
            peeraddr.sin_family = AF_INET;
            peeraddr.sin_addr.s_addr = it->ip;
            peeraddr.sin_port = it->port;

            msg.cmd = htonl(S2C_SOMEONE_LOGIN);
            memcpy(msg.body, &user, sizeof(user));
            if (sendto(sock, &msg, sizeof(msg), 0, (struct sockaddr*)&peeraddr, sizeof(peeraddr)) < 0)
                err::Exit("sendto");
        }

    } else {    // 用户已登录
        printf("user %s has already logined\n", msg.body);

        reply_msg.cmd = htonl(S2C_ALREADY_LOGINED);
        sendto(sock, &reply_msg, sizeof(reply_msg), 0, (struct sockaddr*)cliaddr, sizeof(*cliaddr));
    }

}
static void chat_server(int sock) {
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    MESSAGE msg;
    while(1) {
        memset(&msg, 0, sizeof(msg));
        int ret = recvfrom(sock, &msg, sizeof(msg), 0, (struct sockaddr*)&cliaddr, &clilen);
        if (ret == -1) {
            if (errno == EINTR)
                continue;
            err::Exit("recvfrom");
        }
        if (ret == 0) {
            printf("client close\n");
            break;
        }
        int cmd = ntohl(msg.cmd);
        switch (cmd) {
        case C2S_LOGIN:
            do_login(msg, sock, &cliaddr);
            break;
        case C2S_LOGOUT:
            do_logout(msg, sock, &cliaddr);
            break;
        case C2S_ONLINE_USER:
            msg.cmd = htonl(S2C_ONLINE_USER);
            sendto(sock, &msg, sizeof(msg), 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
            do_sendlist(msg.body, sock, &cliaddr);
            break;
        default:
            break;
        }
    }
    close(sock);
}

int main(int argc, char* argv[]) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        err::Exit("socket");

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   // 0.0.0.0, for server

    if (bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        err::Exit("bind");

    chat_server(sock);

    return 0;
}
