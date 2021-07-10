#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "msgbuf.h"

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

static MsgRet
_msg_recv(MsgBuf *msg)
{
    int i;
    for ( i = msg->start; i < msg->end; i++ )
    {
        if ( msg->buf[i] == '\n' )
        {
            return MSGBUF_PEER_ALIVE;
        }
    }
    if ( i == msg->end )
    {
        int size = msg->end - msg->start;
        // If bufsize is big enough, overlap doesn't occur...
        // memmove(msg->buf, msg->buf + msg->start, size);
        memcpy(msg->buf, msg->buf + msg->start, size);
        msg->start = 0;
        msg->end = size;

        size = recv(msg->fd, msg->buf + msg->end, msg->buflen - size, 0);
        if ( size < 0 )
        {
            perror("send");
            return MSGBUF_ERR;
        }
        else if ( size == 0 )
        {
            return MSGBUF_PEER_DEAD;
        }

        msg->end += size;
    }
    return MSGBUF_PEER_ALIVE;
}

MsgRet
msg_send_key_value(MsgBuf *msg,
                   char   *key,    /* [i] */
                   char   *value)  /* [i] */
{
    MsgRet ret = MSGBUF_PEER_ALIVE;
    if ( strcmp(key, "\n") == 0 )
    {
        msg->buf[msg->end++] = '\n';
        return _msg_send(msg);
    }

    int capacity = msg->buflen - msg->end;
    int written = snprintf(msg->buf + msg->end, capacity,
                            "%s:%s\n", key, value);

    // Buffer is full. Send buffer and retry appending
    if ( capacity < written )
    {
        ret = _msg_send(msg);
        if ( ret != MSGBUF_PEER_ALIVE )
        {
            return ret;
        }
        return msg_send_key_value(msg, key, value);
    }
    else
    {
        msg->end += written;
        return MSGBUF_PEER_ALIVE;
    }
}
MsgRet
msg_recv_key_value(MsgBuf *msg,
                   char *key,    /* [o] */
                   char *value)  /* [o] */
{
    MsgRet ret = MSGBUF_PEER_ALIVE;
    if ( (ret = _msg_recv(msg)) != MSGBUF_PEER_ALIVE )
    {
        return ret;
    }

    // End of Frame
    if ( msg->buf[msg->start] == '\n' )
    {
        msg->start++;
        strcpy(key, "\n");
        value[0] = '\0';
        return MSGBUF_PEER_ALIVE;
    }

    // NOTE: If line contains multiple colons (:) , the last one is
    //       treat as a delimiter.
    // e.g.
    //   When line is "foo:bar:baz", key is "foo:bar" and value is "baz".
    char *key_pos = msg->buf + msg->start;
    char *line_end = split_str(key_pos, '\n'); // "\n"'s pos + 1.
    char *value_pos = rsplit_str(key_pos, ':');
    strcpy(key, key_pos);
    strcpy(value, value_pos);
    msg->start = line_end - msg->buf;

    return ret;
}

#ifdef TEST
#include <stdlib.h>
int main(int argc, char *argv[])
{
#if 1
    //
    // Bank
    //
    int sock = establish_tcp_connection("127.0.0.1", atoi(argv[1]));
    if ( sock == -1 )
    {
        return 1;
    }

    int buflen = 8092;

    char send_buf[buflen];
    MsgBuf req;
    msg_init(&req, send_buf, buflen, sock);
    msg_send_key_value(&req, "OPEN_ACCOUNT", "bank_1");
    msg_send_key_value(&req, "name", "kob");
    msg_send_key_value(&req, "\n", NULL);

    int num = 0;
    char recv_buf[buflen];
    MsgBuf res;
    msg_init(&res, recv_buf, buflen, sock);
    while ( 1 )
    {
        char key[128] = { '\0' };
        char value[1024] = { '\0' };
        switch ( msg_recv_key_value(&res, key, value) )
        {
            case MSGBUF_PEER_ALIVE:
                break;
            case MSGBUF_PEER_DEAD:
                goto END;
                break;
            case MSGBUF_ERR:
                return 1;
                break;
        }

        if ( strcmp(key, "\n") == 0 )
        {
            printf("------------------------------------------------------\n");
            printf("num: %d\n", num);
        }
        else
        {
            printf("key  : %s\n", key);
            printf("value: %s\n", value);
            num++;
        }
    }

#else
    //
    // Store
    //
    int listen = socket_bind_listen(atoi(argv[2]));
    int store = accept_tcp_connection(listen);
    if ( store == -1 )
    {
        return 1;
    }
    MsgBuf req2;
    msg_init(&req2, buf, buflen, store);

    int num = 0;
    while ( 1 )
    {
        char key[128] = { '\0' };
        char value[1024] = { '\0' };
        switch ( msg_recv_key_value(&req2, key, value) )
        {
            case MSGBUF_PEER_ALIVE:
                break;
            case MSGBUF_PEER_DEAD:
                goto END;
                break;
            case MSGBUF_ERR:
                return 1;
                break;
        }

        if ( strcmp(key, "\n") == 0 )
        {
            printf("------------------------------------------------------\n");
            printf("num: %d\n", num);
        }
        else
        {
            printf("key  : %s\n", key);
            printf("value: %s\n", value);
            num++;
        }
    }
#endif
END:

    return 0;
}
#endif

