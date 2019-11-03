FROM ubuntu:bionic

# smlsharp のビルド&実行環境コンテナを作成
#
# install following tools and libraries
# - GNU Multiple Precision Arithmetic Library
# - MassiveThreads
# - LLVM 3.7.1
# - YAJL 2.x
#
# smlsharp の make がコケるので
# https://github.com/smlsharp/smlsharp/issues/51 を参考に Makefile をいじっている


RUN apt update && apt install -y build-essential curl m4 python cmake
    && curl -SLO https://gmplib.org/download/gmp/gmp-6.1.2.tar.xz \
    && tar xvf gmp-6.1.2.tar.xz && cd gmp-6.1.2 \
    && ./configure && make && make install \
    && cd ../ \
    && curl -SLO https://github.com/massivethreads/massivethreads/archive/v0.99.tar.gz \
    && tar xzvf v0.99.tar.gz && cd massivethreads-0.99 \
    && ./configure && make && make install \
    && cd ../ \
    && curl -SLO http://releases.llvm.org/3.7.1/llvm-3.7.1.src.tar.xz \
    && tar xvf llvm-3.7.1.src.tar.xz && cd llvm-3.7.1.src && mkdir build && cd build \
    && ../configure --enable-shared --enable-optimized --disable-bindings \
    && make && make install \
    && cd ../ \
    && curl -SLO https://github.com/lloyd/yajl/archive/2.1.0.tar.gz \
    && tar xzvf 2.1.0.tar.gz && cd 2.1.0 \
    && ./configure && make && make install \
    && cd ..\
    && curl -SLO http://www.pllab.riec.tohoku.ac.jp/smlsharp/download/smlsharp-3.4.0.tar.gz \
    && tar xzvf smlsharp-3.4.0.tar.gz && cd smlsharp-3.4.0 \
    && ./configure \
    && sed -i -e 's/\\$/-relocation-model=pic ./Makefile \\/' \
    && make && make install \
    && cd ../ 

