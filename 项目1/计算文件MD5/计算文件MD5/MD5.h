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
class md5{
public:
	//��ʼ��
	void init();
	//��ȡ�ļ�����
	uint totalByte();
	//��ȡ�ļ����һ�����ݿ�ĳ���
	uint lastByte();

	//���������Ϣ
	void fillChunk(uint* chunk);
	//����һ��chunk
	void dealChunk(uint* chunk);
	//ѭ������
	uint shift(uint tmp, uint shiftNumber);

	///����ת�ַ���,����MD5���
	void turnStr(uint src);
private:
	uint _totalByte;
	uint _lastByte;
	static uint s[64];
	static uint k[64];

	uint _chunk[CHUNK_SIZE];
	uint A, B, C, D;
};


//�ַ�����MD5
//�ļ���MD5


#endif __MD5_H__