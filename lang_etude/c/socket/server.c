#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    int ret = 0;
    int sock_listen = -1;
    int sock_client = -1;

    sock_listen = socket(AF_INET, SOCK_STREAM, 0);
    if ( sock_listen == -1 )
    {
        perror("socket");
        goto ERR;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(30000);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ( bind(sock_listen, (struct sockaddr*)&addr, sizeof(addr)) == -1  )
    {
        perror("bind");
        goto ERR;
    }

    if ( listen(sock_listen, 10) == -1 )
    {
        perror("listen");
        goto ERR;
    }

    sock_client = accept(sock_listen, NULL, NULL);
    if ( sock_client == -1 )
    {
        perror("accept");
        goto ERR;
    }

    while ( 1 )
    {
        char buf[32];
        ssize_t recv_size = recv(sock_client, buf, 32, 0);
        if ( recv_size == -1 )
        {
            perror("recv");
            goto ERR;
        }
        else if ( recv_size == 0 )
        {
            fprintf(stderr, "Client disconnected.\n");
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

        fprintf(stderr, "Server recv: %s\n", buf);

        if ( strcmp(buf, "kill") == 0 )
            goto END;

        ssize_t send_size = send(sock_client, buf, strlen(buf), 0);
        if ( send_size == -1 )
        {
            perror("send");
            goto ERR;
        }
        fprintf(stderr, "Server send: %s\n", buf);
    }

END:
    if ( sock_listen != -1 )
        close(sock_listen);
    if ( sock_client != -1 )
    {
#if 0
        /* I want to linger on close */
        // https://www.ibm.com/docs/ja/zos/2.3.0?topic=functions-setsockopt-set-options-associated-socket
        struct linger l;
        l.l_onoff  = 1;
        l.l_linger = 0;
        setsockopt(sock_client, SOL_SOCKET, SO_LINGER,
                (char *) &l, sizeof(l));
#endif

        close(sock_client);
    }
    return ret;
ERR:
    ret = 1;
    goto END;
}
