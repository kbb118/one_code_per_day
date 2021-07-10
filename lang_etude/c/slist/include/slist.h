#ifndef __SLIST_H__
#define __SLIST_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct SList_ SList;

//
// callback
//
typedef void (SListFreeFunc)(void *p);
typedef int  (SListCmpFunc)(void *a, void *b);

//
// アクセサ
//
size_t slist_len(SList *s);
void*  slist_head(SList *s);
void*  slist_tail(SList *s);

//
// 生成/破棄
//
SList *slist_new(SListFreeFunc *free_func);
void slist_delete(SList *s);

//
// 追加/削除/検索/整列
//
ssize_t slist_append (SList *s, void *data);
ssize_t slist_prepend(SList *s, void *data);
bool slist_remove (SList *s, void *data, SListCmpFunc *cmp_func);
void*   slist_find   (SList *s, void *data, SListCmpFunc *cmp_func);
void    slist_sort   (SList *s, SListCmpFunc *cmp_func);

//
// その他
//
SList** slist_groupby(SList *s, SListCmpFunc *cmp_func);

#endif /* ifndef __SLIST_H__ */
