#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>


#define CHUNK_SIZE 16
#define CHUNK_BYTE 64
typedef unsigned int un_int;


class getMd5{
public:
	getMd5(){
		init();
	}
	//��ʼ��
	void init();
	//����
	void reset();

	//ѭ������
	un_int shift(un_int src, un_int num);

	//
	void dealChunk();

	//���������Ϣ
	void fillChunk();

	//����ת��Ϊ�ַ���
	std::string turnStr(un_int src);

	//��ȡ�ַ�����MD5
	std::string getStrMd5(std::string str);
	//��ȡ�ļ���MD5
	std::string getFileMd5(std::string str);
private:
	static int _s[64];
	int _k[64];
	
	//һ�����ݿ�
	char _chunk[CHUNK_BYTE];
	un_int _a, _b, _c, _d;
	un_int totalByte, lastChunkByte;
};
