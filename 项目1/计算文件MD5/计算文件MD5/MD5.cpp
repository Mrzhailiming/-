#include "MD5.h"
#include <math.h>
#include <iostream>

uint s[64] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14,
20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23,
4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10,
15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };
void init(){
	//��ʼ��ABCD
	A = _atemp;
	B = _btemp;
	C = _ctemp;
	D = _dtemp;
	//����
	totalByte = lastByte = 0;
	//��ʼ��s[i],k[i]
	
	for (int i = 0; i < 64; ++i){
		k[i] = (uint)(abs(sin(i + 1.0)) * pow(2.0, 32));
	}

}

//ѭ����λ
uint shift(uint tmp, uint shiftNumber){
	return (tmp << shiftNumber) | (tmp >> (32 - shiftNumber));
}

//һ��chunk�Ĵ���
void chunkMD5(uint* chunk){
	uint a = A;
	uint b = B;
	uint c = C;
	uint d = D;
	int f, g;
	for (int i = 0; i < 64; ++i){
		if (i >= 0 && i < 16){
			f = F(b, c, d);
			g = i;
		}
		else if (i >= 16 && i < 32){
			f = G(b, c, d);
			g = (5 * i + 1) % 16;
		}
		else if (i >= 32 && i < 48){
			f = H(b, c, d);
			g = (3 * i + 5) % 16;
		}
		else{
			f = I(b, c, d);
			g = (7 * i) % 16;
		}
		uint tmp = d;
		c = b;
		b = b + shift((a + f + k[i] + chunk[g]), s[i]);
		a = d;
	}
	//����ABCD
	A += a;
	B += b;
	C += c;
	D += d;
}

//���������Ϣ 
void fillChunk(uint* chunk){
	//����һ���ֽ�,���ʣ��Ĳ���64bit(8�ֽ�)
	//���������Ϣ��,����ǰ��chunk
	//�򹹽�һ��512bit(64�ֽ�)�����ݿ�

	//�����ĵ�һ���ֽڵ�λ��
	char* p = (char*)chunk + lastByte;
	*p = (char)0x80;
	++p;
	int remainNum = CHUNK_BYTE - lastByte - 1;
	//ʣ�಻��64bit
	if (remainNum < 8){
		memset(p, 0, remainNum * 8);
		chunkMD5(chunk);
		memset(chunk, 0, CHUNK_BYTE * 8);
	}
	else{
		memset(p, 0, remainNum * 4);
	}

}
