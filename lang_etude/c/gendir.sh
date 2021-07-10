#/bin/bash

name=$(basename $1)
if [ -z "$name" ]; then
    echo "Usage: $0 プロジェクト名"
    exit 1
fi

is_exe=1
if [ "$2" = "lib" ]; then
    is_exe=0
fi

mkdir -p $name
cd $name
mkdir -p src bin include
touch src/${name}.c include/${name}.h
cd bin

if [ "$is_exe" = "1" ]; then
cat <<EOF > Makefile
TARGET  := ${name}
OBJS    := ${name}.o

include ../../makefiles/dir.mk
include \$(MAKEFILE_DIR)/exe.mk
EOF
else
cat <<EOF > Makefile
TARGET  := lib${name}.a
OBJS    := ${name}.o

include ../../makefiles/dir.mk
include \$(MAKEFILE_DIR)/lib.mk
EOF
fi

cat <<EOF >> Makefile

T_DEPLIB :=
test: \$(SRC_DIR)/${name}.c
	\$(CC) \$(DFLAGS)                        \\
	    \$(INCL_DIR:%=-I%) \$(LIB_DIR:%=-L%) \\
	    -DTEST \$^ -o \$@                    \\
	    \$(T_DEPLIB:%=-l%)
EOF

