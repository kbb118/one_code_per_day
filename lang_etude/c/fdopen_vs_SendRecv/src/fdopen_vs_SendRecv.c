#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include "logger.h"

typedef struct {
    char *buf;        // buffer must be passed from outside.
    int buflen;

    int  start;        // data is read/write but not processed part of buffer.
    int  end;          // end of data

    int  fd;
} MsgBuf;

typedef enum {
    MSGBUF_ERR = 0,
    MSGBUF_PEER_ALIVE,
    MSGBUF_PEER_DEAD
} MsgRet;

void
msg_init(MsgBuf *msg, char *buf, int buflen, int fd)
{
    msg->buf = buf;
    msg->buflen = buflen;
    msg->start = 0;
    msg->end = 0;
    msg->fd = fd;
}

static MsgRet
_msg_send(MsgBuf *msg)
{
    if ( send(msg->fd, msg->buf, msg->end, MSG_NOSIGNAL) != msg->end )
    {
        perror("send");
        return (errno == EPIPE) ? MSGBUF_PEER_DEAD : MSGBUF_ERR;
    }

    msg->start = 0;
    msg->end = 0;
    return MSGBUF_PEER_ALIVE;
}

Logger *gLogger;

static inline MsgRet
_msg_recv(MsgBuf *msg,
          char *line,    /* [o] */
          int *_len)      /* [o] */
{
    (void)_len;
    int len = 0;
    int i;
    for ( i = msg->start; i < msg->end; i++ )
    {
        line[len++] = msg->buf[i];
        if ( msg->buf[i] == '\n' )
        {
            line[len] = '\0';
            msg->start = i+1;
            return MSGBUF_PEER_ALIVE;
        }
    }
    if ( i == msg->end )
    {
        int size = msg->buflen;
        msg->start = 0;
        msg->end = size;

        //logger_start(gLogger);
        size = recv(msg->fd, msg->buf, msg->buflen, 0);
        //logger_end(gLogger);
        if ( size < 0 )
        {
            perror("recv");
            return MSGBUF_ERR;
        }
        else if ( size == 0 )
        {
            return MSGBUF_PEER_DEAD;
        }

        for ( i = msg->start; i < msg->end; i++ )
        {
            line[len++] = msg->buf[i];
            if ( msg->buf[i] == '\n' )
            {
                line[len] = '\0';
                msg->start = i+1;
                return MSGBUF_PEER_ALIVE;
            }
        }
    }
    return MSGBUF_PEER_ALIVE;
}

MsgRet
msg_send_line(MsgBuf *msg,
              char   *line,
              int    len)    /* [i] */
{
    MsgRet ret = MSGBUF_PEER_ALIVE;
    if ( strcmp(line, "\n") == 0 )
    {
        msg->buf[msg->end++] = '\n';
        return _msg_send(msg);
    }

    int capacity = msg->buflen - msg->end;

    // Buffer is full. Send buffer and retry appending
    if ( capacity < len )
    {
        ret = _msg_send(msg);
        if ( ret != MSGBUF_PEER_ALIVE )
        {
            return ret;
        }
        return msg_send_line(msg, line, len);
    }
    else
    {
        memcpy(msg->buf + msg->end, line, len);
        msg->end += len;
        return MSGBUF_PEER_ALIVE;
    }
}
MsgRet
msg_recv_line(MsgBuf *msg,
              char *line,    /* [o] */
              int *len)      /* [o] */
{
    return _msg_recv(msg, line, len);
}

int
establish_tcp_connection(char *ip, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if ( sock == -1 )
    {
        perror("socket");
        goto ERR;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if ( inet_aton(ip, &addr.sin_addr) == 0 )
    {
        fprintf(stderr, "inet_aton: Invalid ipv4 address form.\n");
        goto ERR;
    }

    if ( connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1 )
    {
        perror("connect");
        goto ERR;
    }
END:
    return sock;
ERR:
    if ( sock != -1 )
    {
        close(sock);
    }
    sock = -1;
    goto END;
}

int
socket_bind_listen(int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if ( sock == -1 )
    {
        perror("socket");
        goto ERR;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ( bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1  )
    {
        perror("bind");
        goto ERR;
    }

    if ( listen(sock, 10000) == -1 )
    {
        perror("listen");
        goto ERR;
    }

END:
    return sock;
ERR:
    if ( sock != -1 )
    {
        close(sock);
    }
    sock = -1;
    goto END;
}

int
accept_tcp_connection(int sock_listen)
{
    int sock_client = accept(sock_listen, NULL, NULL);
    if ( sock_client == -1 )
    {
        perror("accept");
        goto ERR;
    }
END:
    return sock_client;
ERR:
    goto END;
}

#define LINE_256 "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234\n"

//#define SEND_NUM (1024*1024*1024/256)
#define SEND_NUM (100*1024*1024/256)
//#define SEND_NUM (5)


#ifdef SENDRECV
int main(int argc, char *argv[])
{
    gLogger = logger_create();

    (void)argc;
    int sock = establish_tcp_connection("127.0.0.1", atoi(argv[1]));
    if ( sock == -1 )
    {
        return 1;
    }

    int buflen = 4096;

    logger_start(gLogger);

    char send_buf[buflen];
    MsgBuf req;
    msg_init(&req, send_buf, buflen, sock);
    for ( int i = 0; i < SEND_NUM; i++ ) {
        msg_send_line(&req, LINE_256, 256);
    }
    msg_send_line(&req, "\n", 1);
    logger_end(gLogger);


    logger_start(gLogger);

    char recved[512] = { 0 };
    int line_len;


    char recv_buf[buflen];
    MsgBuf res;
    msg_init(&res, recv_buf, buflen, sock);
    for ( int i = 0; i < SEND_NUM; i++ ) {
        msg_recv_line(&req, recved, &line_len);
        printf("%s\n", recved);
    }
    logger_end(gLogger);
    return 0;
}
#endif
#ifdef FDOPEN
int main(int argc, char *argv[])
{
    gLogger = logger_create();

    (void)argc;
    int sock = establish_tcp_connection("127.0.0.1", atoi(argv[1]));
    if ( sock == -1 )
    {
        return 1;
    }

    logger_start(gLogger);
    FILE *fp = fdopen(sock, "r+");

    for ( int i = 0; i < SEND_NUM; i++ ) {
        fputs(LINE_256, fp);
    }
    fputs("\n", fp);
    fflush(fp);

    logger_end(gLogger);

    logger_start(gLogger);

    char recved[512];
    for ( int i = 0; i < SEND_NUM; i++ ) {
        fgets(recved, 512, fp);
        printf("%s\n",recved);
    }
    logger_end(gLogger);
    return 0;
}
#endif
#ifdef PEER
#define PEER_MSG "abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcde\n"

int main(int argc, char *argv[])
{
    (void)argc;
    int listen = socket_bind_listen(atoi(argv[1]));
    int sock = accept_tcp_connection(listen);

    FILE *fp = fdopen(sock, "r+");

    char recved[512] = { 0 };
    while ( fgets(recved, 512, fp) ) {
        printf("%s\n",recved);
        if ( strcmp(recved, "\n") == 0 )
            break;
    }
    fflush(fp);

    for ( int i = 0; i < SEND_NUM; i++ ) {
        //send(sock, PEER_MSG, 256, 0);
        fputs(PEER_MSG, fp);
    }
    fflush(fp);

    while( 1 ) {
        fgets(recved, 512, fp);
        //printf("%s\n",recved);
    }
    fflush(fp);

    return 0;
}
#endif
