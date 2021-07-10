#ifndef _DLIST_H_
#define _DLIST_H_

typedef struct DList_ DList;

/* ../src/dlist.c */
extern DList *dl_create_node(int data);
extern DList *dl_append(DList *tail, DList *node);
extern void dl_dump(DList *head);
extern void dl_dump_from_to(DList *head, DList *tail);
extern void dl_swap(DList **l_p, DList **r_p);
extern void dl_pop(DList *node);
extern void dl_insert_right(DList *list, DList *node);
extern int cmp_node(DList *a, DList *b);
extern DList *partition(DList **head, DList **tail);
extern void quick_sort(DList **head, DList **tail);

#endif /* ifndef _DLIST_H_ */
