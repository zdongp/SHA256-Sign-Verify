#!/bin/bash
g++ -D SIGN -o sign sign2.cpp -L /home/dong/work/tmp/1/usr/local/ssl/lib -lcrypto
g++ -o verify sign2.cpp -L /home/dong/work/tmp/1/usr/local/ssl/lib -lcrypto
