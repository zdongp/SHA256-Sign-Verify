#!/bin/bash

#build out dir
tmp=$(ls | grep "out")
if [ "$tmp" != "out" ];then
	mkdir out
fi

#build sign
gcc -D SIGN -o ./out/sign ./src/SignVerify.cpp ./src/libcrypto.so

tag="sign"
tmp=$(ls out | grep $tag)
if [ "$tmp" == "$tag" ];then
echo "*** build "$tag" OK!"
else
echo "*** build "$tag" Failed!"
fi

#build sha
./256/build.sh

#build cer pfx
./out/openssl genrsa -out ./out/openssl.key 1024
./out/openssl req -new -x509 -key ./out/openssl.key -out ./out/openssl.cer -days 3650 -subj /CN=cn
./out/openssl pkcs12 -export -out ./out/openssl.pfx -inkey ./out/openssl.key -in ./out/openssl.cer

rm ./out/openssl.key

tag="openssl.cer"
tmp=$(ls out | grep $tag)
if [ "$tmp" == "$tag" ];then
echo "*** build "$tag" OK!"
else
echo "*** build "$tag" Failed!"
fi

tag="openssl.pfx"
tmp=$(ls out | grep $tag)
if [ "$tmp" == "$tag" ];then
echo "*** build "$tag" OK!"
else
echo "*** build "$tag" Failed!"
fi