#include <stdlib.h>
#include <stdio.h>

#include "dlist.h"

struct DList_ {
    struct DList_ *prev;
    struct DList_ *next;
    void *data;
};

DList* dl_create_node(int data)
{
    DList *ret = calloc(1, sizeof(DList));
    if ( ret == NULL )
        return NULL;
    ret->data = malloc(sizeof(int));
    if ( ret->data == NULL )
    {
        free(ret);
        return NULL;
    }

    *(int*)(ret->data) = data;
    return ret;
}

DList* dl_append(DList *tail, DList *node)
{
    // assert(tail->next == NULL);
    tail->next = node;
    node->prev = tail;
    node->next = NULL;

    return node;
}

void dl_dump(DList *head)
{
    for ( DList *cur = head; cur != NULL; cur = cur->next )
    {
        printf("%d\n", *(int*)(cur->data));
    }
}
void dl_dump_from_to(DList *head, DList *tail)
{
    for ( DList *cur = head; cur != tail->next; cur = cur->next )
    {
        fprintf(stderr, "%d\t", *(int*)(cur->data));
    }
    fprintf(stderr, "\n");
}

// 同じ二重リストに所属する node 同士の入れ替え
void dl_swap(DList **l_p, DList **r_p)
{
    DList *l = *l_p;
    DList *r = *r_p;

    if ( l == r )
        return;

#ifdef DEBUG
    fprintf(stderr, "swap %d : %d\n", *(int*)(l->data), *(int*)(r->data));
#endif

    // l は必ず r よりも右にある状態で呼び出すこと！

    DList *l_prev = l->prev;
    DList *r_prev = r->prev;
    DList *l_next = l->next;
    DList *r_next = r->next;
    if ( l_next == r )
    {
        //  l, r が隣接しているケース
        //
        //           l     r    r_next
        //     +     +     +    +
        //     l_prev
        //

        // 右向きの矢印を繋ぐ
        if ( l_prev != NULL )
            l_prev->next = r;
        r->         next = l;
        l->         next = r_next;
        // 左向きの矢印を繋ぐ
        if ( r_next != NULL )
            r_next->prev = l;
        l->         prev = r;
        r->         prev = l_prev;
    }
    else
    {
        //  l, r が隣接していないケース
        //
        //           l          r_prev    r_next
        //     +     +    +     +    +    +
        //     l_prev     l_next     r
        //

        // 右向きの矢印を繋ぐ
        if ( l_prev != NULL )
            l_prev->next = r;
        r->         next = l_next;
        r_prev->    next = l;
        l->         next = r_next;
        // 左向きの矢印を繋ぐ
        if ( r_next != NULL )
            r_next->prev = l;
        l->         prev = r_prev;
        l_next->    prev = r;
        r->         prev = l_prev;
    }

    *l_p = r;
    *r_p = l;
}

void
dl_pop(DList *node)
{
    // node をリストからはずす
    //
    // l    node   r
    //
    DList *l = node->prev;
    DList *r = node->next;
    if ( l != NULL )
        l->next = r;
    if ( r != NULL )
        r->prev = l;

    node->prev = NULL;
    node->next = NULL;
}
void
dl_insert_right(DList *list, DList *node)
{
    // list の右に node を挿入
    //
    //  node
    //
    //  list  r
    //
    DList *r = list->next;
    list->next = node;
    if ( r != NULL )
        r->prev = node;
    node->prev = list;
    node->next = r;
}

int cmp_node(DList *a, DList *b)
{
    return *(int*)(a->data) - *(int*)(b->data);
}

// head, tail 間から適当に 1 つ node を選び、pivot とする。
// head, tail 間の node を
//   pivot 以下のものは pivot より左へ、
//   そうでないものは   pivot より右へ振り分ける。
DList* partition(DList **head, DList **tail)
{
    if ( *head == *tail )
        return NULL;

#ifdef DEBUG
    printf("Start partition this list.\n");
    dl_dump_from_to(*head, *tail);
#endif

    // head, tail 間の長さが 2 のとき
    if ( (*head)->next == *tail )
    {
        if ( cmp_node(*head, *tail) > 0 )
            dl_swap(head, tail);
        return NULL;
    }

    // head を pivot とする
    DList *pivot = *head;
    // head が更新される
    *head = (*head)->next;

    // head が入れ替わってしまうケースなら先に処理しておく
    if ( cmp_node(pivot, *head) < 0 )
        dl_swap(&pivot, head);

#ifdef DEBUG
    printf("pivot is %d\n", *(int*)(pivot)->data);
#endif

    DList *l = pivot->next;
    DList *r = *tail;

    while ( 1 )
    {
        while ( l != r && cmp_node(l, pivot) <= 0 )
            l = l->next;
        while ( r != l && cmp_node(pivot, r) <= 0 )
            r = r->prev;

        // l と r が出会った
        if ( l == r )
            break;

        if ( cmp_node(l, r) > 0 )
        {
            // tail が入れ替わるケースがある。
            // そのときは呼び出しもとにそれを伝える必要があるので。
            if ( r == *tail )
            {
                dl_swap(&l, tail);
                r = *tail;
            }
            else
            {
                dl_swap(&l, &r);
            }
        }
    }

    // pivot をどっちに入れるか。
    if ( cmp_node(r, pivot) <= 0 )
    {
        // assert(r == *tail);
        dl_pop(pivot);
        dl_insert_right(r, pivot);
        *tail = pivot;
    }
    else
    {
        dl_pop(pivot);
        dl_insert_right(l->prev, pivot);
    }
    return pivot;
}

void quick_sort(DList **head, DList **tail)
{
    DList *pivot = partition(head, tail);
    if ( pivot == NULL )
        return;

#ifdef DEBUG
    printf("partition finished\n");
    dl_dump_from_to(*head, *tail);
#endif

    if ( pivot != *head )
        quick_sort(head, &pivot->prev);
    if ( pivot != *tail )
        quick_sort(&pivot->next, tail);
}

#ifdef TEST
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
#endif
