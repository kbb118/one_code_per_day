fname := common.mk
$(info $(fname):C ソースファイルのビルドに関わる変数とレシピを定義します。)

CC     := gcc
CFLAGS := -Wall -Wextra -std=gnu99
DFLAGS := -Wall -Wextra -std=gnu99 -g

ifeq "$(OBJS)" "undefined"
    $(error OBJSが定義されていません)
endif
DOBJS := $(OBJS:%.o=%.do)

$(info $(fname):  コンパイラは $(CC))
$(info $(fname):  コンパイルフラグは $(CFLAGS))
$(info $(fname):  デバッグ用のコンパイルフラグは $(DFLAGS))
$(info $(fname):  コンパイルターゲットは $(OBJS))
$(info $(fname):  デバッグ用コンパイルターゲットは $(DOBJS))

%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCL_DIR:%=-I%) -c $^ -o $@
%.do: $(SRC_DIR)/%.c
	$(CC) $(DFLAGS) $(INCL_DIR:%=-I%) -c $^ -o $@
d: $(DTARGET)

clean:
	rm -f $(TARGET) $(DTARGET) $(OBJS) $(DOBJS)

