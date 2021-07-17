#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include "Common.h"

using namespace std;
const char diskFileName[] = "myDisk.img";  //���̾����ļ���

class DiskDriver {
public:
	FILE* diskPointer;                     //�����ļ�ָ��

public:
	DiskDriver() 
	{
		diskPointer = fopen(diskFileName, "rb+");
	}
	~DiskDriver() 
	{
		if (diskPointer != NULL) {
			fclose(diskPointer);
		}
	}
	void Reset() 
	{
		if (diskPointer != NULL)
			fclose(diskPointer);
		diskPointer = fopen(diskFileName, "rb+");
	}
	//д���̺���
	void write(const uint8* in_buffer, uint32 in_size, int offset = -1, uint32 origin = SEEK_SET) {
		if (offset >= 0)
			fseek(diskPointer, offset, origin);
		fwrite(in_buffer, in_size, 1, diskPointer);
		return;
	}
	//�����̺���
	void read(uint8* out_buffer, uint32 out_size, int offset = -1, uint32 origin = SEEK_SET) {
		if (offset >= 0)
			fseek(diskPointer, offset, origin);
		fread(out_buffer, out_size, 1, diskPointer);
		return;
	}

	//��龵���ļ��Ƿ����
	bool Exists() 
	{
		return diskPointer != NULL;
	}
	//�򿪾����ļ�
	void Construct() 
	{
		diskPointer = fopen(diskFileName, "wb+");
		if (diskPointer == NULL)
			printf("Disk Construct Error!\n");
	}
};