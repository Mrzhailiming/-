#include "MD5.h"


uint md5::s[64] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23,
4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

void md5::init(){
	//��ʼ��ABCD
	A = _atemp;
	B = _btemp;
	C = _ctemp;
	D = _dtemp;
	//����
	_totalByte = _lastByte = 0;
	//��ʼ��s[i],k[i]
	
	for (int i = 0; i < 64; ++i){
		k[i] = (uint)(abs(sin(i + 1.0)) * pow(2.0, 32));
	}
	
}

//����
void md5::reset(){
	A = _atemp;
	B = _btemp;
	C = _ctemp;
	D = _dtemp;
	//����
	_totalByte = _lastByte = 0;
}

//ѭ����λ
uint md5::shift(uint tmp, uint shiftNumber){
	return (tmp << shiftNumber) | (tmp >> (32 - shiftNumber));
}

//һ��chunk�Ĵ���
void md5::dealChunk(uint* chunk){
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
void md5::fillChunk(uint* chunk){
	//����һ���ֽ�,���ʣ��Ĳ���64bit(8�ֽ�)
	//���������Ϣ��,����ǰ��chunk
	//�򹹽�һ��512bit(64�ֽ�)�����ݿ�

	//�����ĵ�һ���ֽڵ�λ��
	char* p = (char*)chunk + _lastByte;
	*p = (char)0x80;
	++p;
	//���1�ֽں�,ʣ����ֽ���
	int remainNum = CHUNK_BYTE - _lastByte - 1;
	//ʣ�಻��64bit
	if (remainNum < 8){
		//��ʣ�����0
		memset(p, 0, remainNum);
		//����chunk
		dealChunk(chunk);
		//�ѵ�ǰchunkȫ����Ϊ0,�����¿���chunk
		memset(chunk, 0, CHUNK_BYTE);
	}
	else{
		memset(p, 0, remainNum);
	}
	//��ԭʼ���ȸ�ֵ�����64bit
	unsigned long long totalBit = _totalByte;
	totalBit *= 8;
	((unsigned long long*)chunk)[7] = totalBit;
	dealChunk(chunk);
}

//����ת�ַ���,����MD5���
std::string md5::turnStr(uint src){
	static std::string map = "0123456789abcdef";
	std::string ret;
	//��ȡÿ���ֽڵ�����
	for (int i = 0; i < 4; ++i){
		int cur = (src >> (i * 8)) & 0xff;
		ret += map[cur / 16];
		ret += map[cur % 16];
	}
	return ret;
}

//�����ַ�����md5
std::string md5::getStringMd5(const std::string& str){
	uint len = str.size();
	const char* Cstr = str.c_str();
	int chunkNum = len / CHUNK_BYTE;
	for (int i = 0; i < chunkNum; ++i){
		memcpy(_chunk, Cstr + i * CHUNK_BYTE, CHUNK_BYTE);
		dealChunk(_chunk);
	}
	_totalByte = len;
	_lastByte = len - chunkNum * CHUNK_BYTE;
	memcpy(_chunk, Cstr + chunkNum * CHUNK_BYTE, _lastByte);
	//�������һ�����ݿ�
	fillChunk(_chunk);
	return turnStr(A).append(turnStr(B)).append(turnStr(C)).append(turnStr(D));
}

//�����ļ���md5
std::string md5::getFileMd5(const char* file){
	//1.ȫ��������,�ռ任ʱ��  
	//f.read(char*,num)
	//f.eof()
	//f.end
	//f.beg
	//F.seekg(0,f.end)
	//f.tellg()
	std::ifstream f(file, std::ifstream::binary);
	if (!f.is_open()){
		std::cout << file;
		perror("error");
		return "";
	}
	if (!f.eof()){
		//��ȡ�ļ����ֽ���
		f.seekg(0, f.end);
		uint len = f.tellg();
		f.seekg(0, f.beg);
		//���ļ�����str
		char* str = new char[len];
		f.read(str, len);
		int chunkNum = len / CHUNK_BYTE;
		for (int i = 0; i < chunkNum; ++i){
			memcpy(_chunk, str + i * CHUNK_BYTE, CHUNK_BYTE);
			dealChunk(_chunk);
		}
		_totalByte = len;
		_lastByte = len - chunkNum * CHUNK_BYTE;
		memcpy(_chunk, str + chunkNum * CHUNK_BYTE, _lastByte);
		//�������һ�����ݿ�
		fillChunk(_chunk);
		delete str;
	}
	return turnStr(A).append(turnStr(B)).append(turnStr(C)).append(turnStr(D));

	
	//2.ÿ��ֻ��һ������, ʱ�任�ռ�
	//f.gcount() //�ϴζ�ȡ���ֽڸ���
	/*while (!f.eof()){
		f.read((char*)_chunk, CHUNK_BYTE);
		if (f.gcount() != CHUNK_BYTE){
		_lastByte = f.gcount();
		break;
		}
		dealChunk(_chunk);
		_totalByte += CHUNK_BYTE;
		}
		_totalByte += _lastByte;
		fillChunk(_chunk);
		return turnStr(A).append(turnStr(B)).append(turnStr(C)).append(turnStr(D));*/
}