fname := lib.mk
$(info $(fname):ライブラリのビルドに関わる変数とレシピを定義します。)

ifeq "$(TARGET)" "undefined"
    $(error TARGETが定義されていません)
endif

DTARGET := $(TARGET:%.a=%_d.a)
$(info $(fname):  ビルドターゲットは $(TARGET))
$(info $(fname):  デバッグ用ビルドターゲットは $(DTARGET))

$(TARGET): $(OBJS)
	ar r $@ $^
$(DTARGET): $(DOBJS)
	ar r $@ $^

include $(MAKEFILE_DIR)/common.mk
