fname := dir.mk
$(info $(fname):ディレクトリ構成に関わる変数を定義します。)

# ./
# ├── makefiles
# │   ├── common.mk # コンパイラやフラグなどの定義
# │   ├── dir.mk    # ディレクトリ構成の定義
# │   ├── exe.mk    # 実行体作成に関する定義
# │   └── lib.mk    # ライブラリ作成に関する定義
# │
# ├── symlink.sh    # 下記ディレクトリに symlink を作る
# ├── bin
# │   └── sample_exe -> ../sample_exe/bin/sample_exe
# ├── lib
# │   ├── sample_lib.h  -> ../sample_lib/include/sample_lib.h
# │   └── libsample.a  -> ../sample_lib/bin/libsample.a
# │
# ├── sample_lib
# │   ├── bin
# │   │   └── Makefile
# │   ├── include
# │   │   └── sample_lib.h
# │   └── src
# │       └── sample_lib.c
# │
# └── sample_exe
#     ├── bin
#     │   └── Makefile
#     ├── include
#     │   └── sample_exe.h
#     └── src
#         └── sample_exe.c

# path は全て bin ディレクトリからの相対パス
MAKEFILE_DIR := ../../makefiles
SRC_DIR      := ../src
INCL_DIR     := ../../lib ../include
LIB_DIR      := ../../lib

$(info $(fname):  共通 Makefile のディレクトリは $(MAKEFILE_DIR))
$(info $(fname):  ソースファイルのディレクトリは $(SRC_DIR))
$(info $(fname):  ヘッダのインクルードディレクトリは $(INCL_DIR))
$(info $(fname):  ライブラリのインクルードディレクトリは $(LIB_DIR))
