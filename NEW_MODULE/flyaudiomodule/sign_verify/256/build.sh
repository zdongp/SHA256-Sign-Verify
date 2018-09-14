#!/bin/bash
gcc -o ./out/sha ./256/*.c

tag="sha"
tmp=$(ls out | grep $tag)
if [ "$tmp" == "$tag" ];then
echo "*** build "$tag" OK!"
else
echo "*** build "$tag" Failed!"
fi