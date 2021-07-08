#/bin/bash

libs="stack logger"

for l in $libs; do
    (cd lib
    for h in $(\ls ../$l/include/*.h 2>/dev/null); do
        ln -s $h .
    done
    for h in $(\ls ../$l/bin/*.a 2>/dev/null); do
        ln -s $h .
    done)
done
