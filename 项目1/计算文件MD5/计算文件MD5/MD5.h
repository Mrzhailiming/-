#ifndef __MD5_H__
#define  __MD5_H__

typedef unsigned int uint;
#define CHUNK_BYTE 64//һ��chunk���ֽ���
#define CHUNK_SIZE 16//һ��chunk�ĳ���, uint[16]
//�ĸ�λ���㺯��
#define  F(a,b,c) (((a) & (b))|((~a) & (c)))
#define  G(a,b,c) (((a) & (c))|((b) & (~c)))
#define  H(a,b,c) ((a) ^ (b) ^ (c))
#define  I(a,b,c) ((b) ^ ((a) | (~c)))
//ABCD��ʼֵ
#define _atemp  0x67452301;
#define _btemp  0xefcdab89;
#define _ctemp  0x98badcfe;
#define _dtemp  0x10325476;

//k[64] K[i] = floor(2^(32) * abs(sin(i + 1))) 
//s[64] ѭ�����Ƶ�λ�� s[64] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7,12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10,15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };
//uint s[64];
uint k[64];

//���ֽ�Ϊ��λ
uint totalByte;//�ܹ����ֽ���
uint lastByte;//���һ�����ݿ���ֽ���
uint A;
uint B;
uint C;
uint D;
//16 * 4 �ֽ�
uint chunk[CHUNK_SIZE];

//�ַ�����MD5


//�ļ���MD5


//��ʼ�� : k[64] ABCD �ļ����� ���һ�����ݿ�ĳ���
void init();

//ѭ����λ
uint shift(uint tmp, uint shiftNumber);

//��ȡ�ļ��ĳ���


//��ȡ���һ�����ݵĳ���


//һ��chunk�Ĵ���
void chunkMD5(uint* chunk);

//���������Ϣ 
void fillChunk(uint* chunk);


//����ת�ַ���,����MD5���
//��ȡÿһ���ֽڵ�����


#endif __MD5_H__