#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
//#include <ostream>

using std::cout;
using std::cin;
using std::endl;


class outNumber{
public:

	//����ǰ����������
	void init();

	//�����м� n λ
	void getMidNum();
	//����
	void getAllNum(int len, FILE* f);
private:
	std::string beginNum;
	std::string endNum;
	std::string midNum;
	std::string retNum;
};