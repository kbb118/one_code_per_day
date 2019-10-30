#!/bin/sh
set -u # 未定義の変数読み出しチェック機能を on
### 環境変数等を一般的な内容に初期化 ###
umask 0022
PATH='/usr/bin:/bin'
IFS=$(printf '\t\n_');IFS=${IFS%_}
export PATH IFS LC_ALL=C LANG=C 

# sedで改行を扱うための定義
LF=$(printf '\\\n_');LF=${LF%_} 

# ps の結果は実行するごとに毎回変わるので
# 乱数の種として使用できる
(ps -Ao pid,etime,pcpu,vsz; date) |
# od で数値化
od -A n -t d4 -v |
   # -A n  アドレス表示を出さない
   # -t d4 10進で4バイトずつ出す
   # -v    省略記号(*)を出さない
sed 's/[^0-9]\{1,\}/'"$LF"'/g' | # 4列 -> 1列化
grep '[0-9]' | # 数字の列のみにする
# <1億の数値を42個足して<2^32を作る
tail -n 42 |
sed 's/.*\(.\{8\}\)$/\1/g' |
awk 'BEGIN{a=-2147483648;}
     {a+=$1;}
     END{srand(a);print rand();}
    '
    

