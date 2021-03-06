#!/bin/bash

FILES=`git ls-tree -r --name-only HEAD .`
MAXLEN=0
for f in $FILES; do
    if [ ${#f} -gt $MAXLEN ]; then
        MAXLEN=${#f}
    fi
done
for f in $FILES; do
    str=$(git log -1 --decorate --pretty=format:"%C(green)%cr%Creset" $f)
    str2=$(git log -1 --decorate --pretty=format:"%C(cyan)%h%Creset %s %C(yellow)(%cn)%Creset" $f)
    printf "%-${MAXLEN}s -- %s \t %s\n" "$f" "$str" "$str2"
done
