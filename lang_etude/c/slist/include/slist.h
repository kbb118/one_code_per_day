#ifndef __SLIST_H__
#define __SLIST_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct SList_ SList;

//
// callback
//
typedef void (SListFreeFunc)(void *data);
typedef void (SListPrintFunc)(void *data);
typedef int (SListCmpFunc)(void *a, void *b);

//
// アクセサ
//
size_t slist_len(SList *s);
void*  slist_head(SList *s);
void*  slist_tail(SList *s);

//
// 生成/破棄
//
SList *slist_new_(SListFreeFunc *free_func);
void slist_delete(SList *s);
#define slist_new(f) slist_new_((SListFreeFunc*)f)

//
// 追加/削除/検索/整列
//
ssize_t slist_append_(SList *s, void *data);
ssize_t slist_prepend_(SList *s, void *data);
bool    slist_remove_(SList *s, void *data, SListCmpFunc *cmp_func);
void*   slist_find_  (SList *s, void *data, SListCmpFunc *cmp_func);
void    slist_sort_  (SList *s, SListCmpFunc *cmp_func);
#define slist_append(s, d)    slist_append_(s, (void*)d)
#define slist_prepend(s, d)   slist_prepend_(s, (void*)d)
#define slist_remove(s, d, f) slist_remove_(s, (void*)d, (SListCmpFunc*)f)
#define slist_find(s, d, f)   slist_find_(s, (void*)d, (SListCmpFunc*)f)
#define slist_sort(s, f)      slist_sort_(s, (SListCmpFunc*)f)

//
// 出力
//
void slist_print_(SList *s, SListPrintFunc *print_func);
#define slist_print(s, f) slist_print_(s, (SListPrintFunc*)f)

//
// その他
//
SList** slist_groupby(SList *s, SListCmpFunc *cmp_func);

#endif /* ifndef __SLIST_H__ */
