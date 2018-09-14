/*
 *filename:barcode_access.h
 *author:hujian
 *date:2012/6/18 14:23
 *@GuangZhou flyaudio Ltd.,corp.
 *
 */
#ifndef BARCODE_ACCESS_H
#define BARCODE_ACCESS_H

/*
 *准备barcode，可访问返回1，否则返回0
 */
int prepare_BarCode(void);//0��ʾʧ�� 1��ʾ����

/*
 *读取所有的barcode
 *参数：BarCode，传入的缓冲区，最好大于与等于512字节，每一个有效条目以0x55标识开始，即有效标识0x55+50个字节有效数据
 *参数：len，说明缓冲区大小
 *返回值：成功则返回读取的数据长度；失败返回负数，通常是-1。
 */
int read_AllBarCode(char *BarCode,int len);

/*
 *读取一条barcode
 *参数：BarCode，传入的缓冲区，最好大于或是等于50个字节，所有都是有效数据
 *参数：len，说明缓冲区大小
 *返回值：成功则返回读取的数据长度；失败返回负数，通常是-1。
 */
int read_BarCode(char *BarCode,int len);

#endif//#ifndef BARCODE_ACCESS_H
