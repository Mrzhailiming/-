#include "test.h"
#define BEGIN 1
#define END 2


void bg(){
	cout << "������·����";
	char path[40] = { 0 };
	myWork w(path);
	//�õ������ļ�
	w.getAllFile();
	//����
	w.create_moveFile();
	cout << "********chuli�ɹ�*******" << endl;
}


void ex(){
	cout << "********�˳��ɹ�*******" << endl;
}
void menu(){
	cout << "**********************" << endl;
	cout << "********1. ��ʼ*******" << endl;
	cout << "********2. �˳�*******" << endl;
	cout << "**********************" << endl;
	int flag = 1;
	int sw = 0;
	while (flag){
		
		cin >> sw;
		switch (sw){
			case BEGIN:
				bg();
			case END:
				flag = 0;
				ex();
			default:
				cout << "ѡ���������������" << endl;
				continue;
		}
	}
	
}
void testGetAllFile(){
	myWork m("D:\\test");
	m.getAllFile();

	m.num_fimeName();
}



int main(){
	//menu();
	testGetAllFile();
	//testNumFile();
	return 0;
}