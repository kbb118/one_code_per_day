#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

//
// 標準入力から最大 size - 1 バイト読み取る。
//
// buf の末尾に改行があった場合はヌル文字に置き換える
// buf の末尾はヌル終端される
//
int read_line(char* buf, int size)
{
    ssize_t stdin_size = read(0, buf, size);
    if ( stdin_size == -1 )
    {
        perror("read");
        goto ERR;
    }
    else if ( stdin_size == 0 )
    {
        fprintf(stderr, "EOF.\n");
        goto ONLY_EOF;
    }
    else if ( stdin_size == size )
    {
        fprintf(stderr, "Input too long.\n");
        // FIXME 
        // ここは fflush じゃなく
        // 次の改行まで読み捨てるべきな気がする
        fflush(stdin);
        goto TOO_LONG_LINE;
    }
    else
    {
        if ( buf[stdin_size-1] == '\n' )
            buf[stdin_size-1] = '\0';
        else
            buf[stdin_size] = '\0';
    }

    return 1;
ERR:
    return -1;
ONLY_EOF:
    return 0;
TOO_LONG_LINE:
    return 2;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    int ret = 0;
    int sock = -1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if ( sock == -1 )
    {
        perror("socket");
        goto ERR;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(30000);
    if ( inet_aton("127.0.0.1", &addr.sin_addr) == 0 )
    {
        fprintf(stderr, "inet_aton: Invalid ipv4 address form.\n");
        goto ERR;
    }

    if ( connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1 )
    {
        perror("connect");
        goto ERR;
    }

    while ( 1 )
    {
        char buf[10];

        int status = read_line(buf, 10);
        if ( status == -1 )
        {
            goto ERR;
        }
        else if ( status == 0 )
        {
            goto END;
        }
        else if ( status == 2 )
        {
            continue;
        }

        if ( strcmp(buf, "end") == 0 )
        {
            goto END;
        }

        fprintf(stderr, "Client send: %s\n", buf);
        ssize_t send_size = send(sock, buf, strlen(buf), 0);
        if ( send_size == -1 )
        {
            perror("send");
            goto ERR;
        }

        ssize_t recv_size = recv(sock, buf, 32, 0);
        if ( recv_size == -1 )
        {
            perror("recv");
            goto ERR;
        }
        else if ( recv_size == 0 )
        {
            fprintf(stderr, "Server disconnected.\n");
            goto END;
        }
        else if ( recv_size == 32 )
        {
            fprintf(stderr, "Too long data.\n");
        }
        else
        {
            buf[recv_size] = '\0';
        }
        fprintf(stderr, "Client recv: %s\n", buf);
    }

END:
    if ( sock != -1 )
    {
#if 0
        /* I want to linger on close */
        // https://www.ibm.com/docs/ja/zos/2.3.0?topic=functions-setsockopt-set-options-associated-socket
        struct linger l;
        l.l_onoff  = 1;
        l.l_linger = 0;
        setsockopt(sock, SOL_SOCKET, SO_LINGER,
                (char *) &l, sizeof(l));
#endif
        close(sock);
    }
    return ret;
ERR:
    ret = 1;
    goto END;
}
