/*
 * chat client using UDP
 */

#include "lnp_lt.h"
#include "pub.h"

using namespace lt;

// 当前用户名
static char username[16];

// 聊天室成员列表
static USER_LIST client_list;

static void usage() {
    printf("\nCommands:\n");
    printf("send <username> <msg>\n");
    printf("list\n");
    printf("exit\n\n");
}

static bool sendmsgto(int sock, char* peername, char* msg) {
    if (strcmp(peername, username) == 0) {
        printf("can't send message to self\n");
        return false;
    }

    // 查找用户
    auto it = client_list.begin();
    for (; it != client_list.end(); ++it) {
        if (strcmp(it->username, peername) == 0)
            break;
    }

    if (it == client_list.end()) {
        printf("user %s has not logined server\n", peername);
        return false;
    }

    MESSAGE m;
    memset(&m, 0, sizeof(m));
    m.cmd = htonl(C2C_CHAT);

    CHAT_MSG cm;
    strcpy(cm.username, username);
    strcpy(cm.msg, msg);

    memcpy(m.body, &cm, sizeof(cm));

    struct sockaddr_in peeraddr;
    memset(&peeraddr, 0, sizeof(peeraddr));
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_addr.s_addr = it->ip;
    peeraddr.sin_port = it->port;

    in_addr tmp;
    tmp.s_addr = it->ip;
    printf("sending message [%s] to user [%s] <-> %s:%d\n", msg, peername, inet_ntoa(tmp), ntohs(it->port));

    sendto(sock, &m, sizeof(m), 0, (struct sockaddr*)&peeraddr, sizeof(peeraddr));
    return true;
}

static void parse_cmd(char* cmdline, int sock, struct sockaddr_in* servaddr) {
    char cmd[10] = {0};
    char* p = strchr(cmdline, ' ');
    if (p != NULL)
        *p = '\0';

    strcpy(cmd, cmdline);
    cmd[9] = '\0';
    if (strcmp(cmd, "exit") == 0) {
        MESSAGE msg;
        memset(&msg, 0, sizeof(msg));
        msg.cmd = htonl(C2S_LOGOUT);
        strcpy(msg.body, username);

        if (sendto(sock, &msg, sizeof(msg), 0, (struct sockaddr*)servaddr, sizeof(*servaddr)) < 0)
            err::Exit("sendto");
        printf("user %s has logout server\n", username);
        exit(EXIT_SUCCESS);
    } else if (strcmp(cmd, "send") == 0) {
        char peername[16] = {0};
        char msg[MSG_LEN] = {0};
        /*
         * send     user    msg
         *          p       p2
         */
        while (*p++ == ' ');
        char* p2 = strchr(p, ' ');
        if (p2 == NULL) {
            printf("%s: command not found\n", cmd);
            usage();
            return;
        }
        *p2 = '\0';
        strcpy(peername, p);

        while (*p2++ == ' ');
        strcpy(msg, p2);
        sendmsgto(sock, peername, msg);
    } else if (strcmp(cmd, "list") == 0) {
        MESSAGE msg;
        memset(&msg, 0, sizeof(msg));
        msg.cmd = htonl(C2S_ONLINE_USER);
        memcpy(msg.body, username, sizeof(username));
        if (sendto(sock, &msg, sizeof(msg), 0, (struct sockaddr*)servaddr, sizeof(*servaddr)) < 0)
            err::Exit("sendto");
    } else {
        printf("%s: command not found\n", cmd);
        usage();
    }
}

static void do_someone_login(MESSAGE& msg) {
    USER_INFO* user = (USER_INFO*)msg.body;
    in_addr tmp;
    tmp.s_addr = user->ip;
    printf("%s <-> %s:%d has logined server\n", user->username, inet_ntoa(tmp), ntohs(user->port));
    client_list.push_back(*user);
}

static void do_someone_logout(MESSAGE& msg) {
    for (auto it = client_list.begin(); it != client_list.end(); ++it) {
        if (strcmp(it->username, msg.body) == 0) {
            client_list.erase(it);
            break;
        }
    }

    printf("user %s has logout server\n", msg.body);
}

static void do_getlist(int sock) {
    int count;
    recvfrom(sock, &count, sizeof(int), 0, NULL, NULL);
    count = ntohl(count);
    printf("has %d users logined server\n", count);
    client_list.clear();

    // 获取当前登录用户列表
    for (int i = 0; i < count; ++i) {
        USER_INFO user;
        recvfrom(sock, &user, sizeof(user), 0, NULL, NULL);
        client_list.push_back(user);
        in_addr tmp;
        tmp.s_addr = user.ip;

        printf("%d %s <-> %s:%d\n", i, user.username, inet_ntoa(tmp), ntohs(user.port));
    }
}

static void do_chat(MESSAGE& msg) {
    CHAT_MSG* cm = (CHAT_MSG*)msg.body;
    printf("receive message [%s] from [%s]\n", cm->msg, cm->username);
}

static void chat_client(int sock) {
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    MESSAGE msg;
    while(1) {
        memset(username, 0, sizeof(username));
        printf("please input your name: ");
        fflush(stdout);
        scanf("%s", username);

        memset(&msg, 0, sizeof(msg));
        msg.cmd = htonl(C2S_LOGIN);
        strcpy(msg.body, username);

        sendto(sock, &msg, sizeof(msg), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

        memset(&msg, 0, sizeof(msg));
        recvfrom(sock, &msg, sizeof(msg), 0, NULL, NULL);
        int cmd = ntohl(msg.cmd);
        if (cmd == S2C_ALREADY_LOGINED)
            printf("user %s has already logined server\n", username);
        else if (cmd == S2C_LOGIN_OK) {
            printf("user %s has logined server\n", username);
            break;
        }
    }
    // 至此，已经登录成功

    do_getlist(sock);

    usage();

    struct sockaddr_in peeraddr;
    socklen_t peerlen = sizeof(peeraddr);

    fd_set rset;
    FD_ZERO(&rset);
    while(1) {
        FD_SET(STDIN_FILENO, &rset);
        FD_SET(sock, &rset);

        int nReady = select(sock + 1, &rset, NULL, NULL, NULL);
        if (nReady == -1) {
            if (errno == EINTR)
                continue;
            err::Exit("select");
        }
        if (nReady == 0)
            continue;

        if (FD_ISSET(sock, &rset)) {
            memset(&msg, 0, sizeof(msg));
            recvfrom(sock, &msg, sizeof(msg), 0, (struct sockaddr*)&peeraddr, &peerlen);
            int cmd = ntohl(msg.cmd);
            switch(cmd) {
            case S2C_SOMEONE_LOGIN:
                do_someone_login(msg);
                break;
            case S2C_SOMEONE_LOGOUT:
                do_someone_logout(msg);
                break;
            case S2C_ONLINE_USER:
                do_getlist(sock);
                break;
            case C2C_CHAT:
                do_chat(msg);
                break;
            default:
                break;
            }

        }
        if (FD_ISSET(STDIN_FILENO, &rset)) {
            char cmdline[100] = {0};
            if (fgets(cmdline, sizeof(cmdline), stdin) == NULL)
                break;
            if (cmdline[0] == '\n')
                continue;
            cmdline[strlen(cmdline) - 1] = '\0';
            parse_cmd(cmdline, sock, &servaddr);
        }
    }

    memset(&msg, 0, sizeof(msg));
    msg.cmd = htonl(C2S_LOGOUT);
    memcpy(msg.body, username, sizeof(username));
    sendto(sock, &msg, sizeof(msg), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
}

int main(int argc, char* argv[]) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        err::Exit("socket");

    chat_client(sock);

    return 0;
}
