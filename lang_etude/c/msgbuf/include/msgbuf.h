#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <string.h>
#include <stdbool.h>

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

static inline char *
split_str(char *str, char c)
{
    // c must exist in str!
    char *ret = strchr(str, c);
    *ret = '\0';
    return ret + 1;
}
static inline char *
rsplit_str(char *str, char c)
{
    // str must be null terminated!
    char *ret = strrchr(str, c);
    *ret = '\0';
    return ret + 1;
}


/* ../src/message.c */
extern void msg_init(MsgBuf *msg, char *buf, int buflen, int fd);
extern MsgRet msg_send_key_value(MsgBuf *msg, char *key, char *value);
extern MsgRet msg_recv_key_value(MsgBuf *msg, char *key, char *value);

#endif /* ifndef __MESSAGE_H__ */
