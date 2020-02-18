
#include "getMD5.h"
#include <stdio.h>
int getMd5::_s[64] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7,
12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10,
15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

//��ʼ��
void getMd5::init(){
	_a = 0x67452301;
	_b = 0xefcdab89;
	_c = 0x98badcfe;
	_d = 0x10325476;
	totalByte = lastChunkByte = 0;
	for (int i = 0; i < 64; i++)
	{
		_k[i] = (int)(abs(sin(i + 1)) * pow(2, 32));
	}
}
//����
void getMd5::reset(){
	_a = 0x67452301;
	_b = 0xefcdab89;
	_c = 0x98badcfe;
	_d = 0x10325476;
	totalByte = lastChunkByte = 0;
}

//ѭ������
un_int getMd5::shift(un_int src, un_int num){
	return (src << num) | (src << (32 - num));
}

void getMd5::dealChunk(){
	/*
	F(x,y,z) = (x & y) | ((~x) & z)
	G(x,y,z) = (x & z) | ( y & (~z))
	H(x,y,z) = x ^ y ^ z
	I(x,y,z) = y ^ (x | (~z))
	*/
	int a = _a;
	int b = _b;
	int c = _c;
	int d = _d;
	int ret;
	int g;
	//����64��
	for (int i = 0; i < 64; ++i){
		if (i >= 0 && i < 16){
			ret = (b & c) | ((~b) & d);
			g = i;
		}
		else if (i >= 16 && i < 32){
			ret = (b & d) | (c & (~d));
			g = (5 * i + 1) % 16;
		}
		else if (i >= 32 && i < 48){
			ret = b ^ c ^ d;
			g = (3 * i + 5) % 16;
		}
		else{
			ret = c ^ (b | (~d));
			g = (7 * i) % 16;
		}
		int tmp = d;
		d = c;
		c = b;
		b = b + shift((a + ret + _k[i] + _chunk[g]), _s[i]);
	}
	_a += a;
	_b += b;
	_c += c;
	_d += d;
}

//���������Ϣ
void getMd5::fillChunk(){
	//�����һ���ֽ�
	char* p = (char*)_chunk + lastChunkByte;
	*p = (char)0x80;
	int remainNum = CHUNK_BYTE - lastChunkByte - 1;
	//���ʣ�಻��8���ֽ�
	if (remainNum < 8){
		//�Ȱ�ʣ��Ķ����0
		memset(p + 1, 0, remainNum);
		dealChunk();
		//���������һ��chunkȻ���ٰ�chunk����Ϊ0,�൱���¿���һ��chunk
		memset(_chunk, 0, CHUNK_BYTE);
	}
	else{
		memset(p + 1, 0, remainNum);
	}
	unsigned long long totalBit = totalByte;
	totalBit *= 8;
	((unsigned long long*)_chunk)[7] = totalBit;
	dealChunk();
}

//����ת��Ϊ�ַ���
std::string getMd5::turnStr(un_int src){
	std::string map = "0123456789abcdef";
	std::string ret;
	for (int i = 0; i < 4; ++i){
		int cur = (src >> i * 8) & 0xff;
		ret += map[cur / 16];
		ret += map[cur % 16];
	}
	return ret;
}


//��ȡ�ַ�����MD5
std::string getMd5::getStrMd5(std::string str){
	reset();
	totalByte = str.size();
	lastChunkByte = totalByte % 64;
	int chunkNum = totalByte / 64;
	for (int i = 0; i < chunkNum; ++i){
		memcpy(_chunk, str.c_str(), CHUNK_BYTE);
		dealChunk();
	}
	memcpy(_chunk, str.c_str(), lastChunkByte);
	fillChunk();
	return turnStr(_a).append(turnStr(_b)).append(turnStr(_c)).append(turnStr(_d));

}
//��ȡ�ļ���MD5
std::string getMd5::getFileMd5(std::string str){
	//ÿ�ε���������
	reset();
	FILE* f = fopen(str.c_str(), "rb");
	if (f == nullptr){
		perror("���ļ�ʧ�� :");
		return "";
	}
	fseek(f, 0, SEEK_END);
	un_int totalByte = ftell(f);
	rewind(f);
	int chunkNum = totalByte / CHUNK_BYTE;
	lastChunkByte = totalByte % CHUNK_BYTE;
	char* src = new char[totalByte];
	fread(src, 1, totalByte, f);
	for (int i = 0; i < chunkNum; ++i){
		memcpy(_chunk, src + i * CHUNK_BYTE, CHUNK_BYTE);
		dealChunk();
	}
	memcpy(_chunk, src + chunkNum * CHUNK_BYTE, lastChunkByte);
	fillChunk();
	fclose(f);
	return turnStr(_a).append(turnStr(_b)).append(turnStr(_c)).append(turnStr(_d));
}