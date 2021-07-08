#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "dlist.h"

int main(int argc, char *argv[])
{
    (void)argc, (void)argv;
    Logger *logger = logger_create();

    logger_start(logger);

    DList *head = dl_create_node(1);
    DList *tail = head;

    //int n;
    //scanf("%d\n", &n);
    //for ( int i = 0; i < n; i++ )
    //{
    //    int d;
    //    scanf("%d\n", &d);
    //    tail = append(tail, dl_create_node(d));
    //}

    DList *node1 = dl_append(tail,  dl_create_node(3));
    DList *node2 = dl_append(node1, dl_create_node(5));
    DList *node3 = dl_append(node2, dl_create_node(8));
    DList *node4 = dl_append(node3, dl_create_node(9));
    DList *node5 = dl_append(node4, dl_create_node(2));
    DList *node6 = dl_append(node5, dl_create_node(6));
    DList *node7 = dl_append(node6, dl_create_node(1));
    tail = node7;
    dl_dump(head);

    logger_end(logger);

#if 0
    // swap のテスト
    printf("node1 と node6 を入れ替え\n");
    swap  (&node1,  &node6);
    dump(node1);
    printf("node1 と node2 を入れ替え\n");
    swap  (&node1,  &node2);
    dump(node1);
    printf("node3 と node4 を入れ替え\n");
    swap  (&node3,  &node4);
    dump(node1);
    printf("node1 と node2 を入れ替え\n");
    swap  (&node1,  &node2);
    dump(node1);
    printf("node1 と node7 を入れ替え\n");
    swap  (&node1,  &node7);
    dump(node1);
    printf("node6 と node7 を入れ替え\n");
    swap  (&node6,  &node7);
    dump(node1);
#endif

    quick_sort(&head, &tail);
    dl_dump(head);

    return 0;
}
