#include "test.h"
#define BEGIN 1
#define END 2


void bg(){
	cout << "������·����";
	char path[40] = { 0 };
	myWork w(path);
	//�õ������ļ�
	w.getAllFile(path);
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
	m.getAllFile("D:\\test");

	m.num_fimeName();
	wchar_t old = "D:\\test\\����Ӧ���� 216 217 ����89 (2).zip";
	LPCWSTR* old = new LPCWSTR();
	LPCWSTR* newPath = new LPCWSTR("D:\\");
	MoveFile(*old, *newPath);
	//m.create_moveFile();
	//m.createNewDir("D:\\aa");
}



int main(){
	//menu();
	testGetAllFile();
	//testNumFile();
	return 0;
}