#include "outNumber.h"


void menu(){
	cout << "**********************��ħ��ֿ��뿪***************************" << endl;
	cout << "******************����Щɷ�ʿ���뿪����***********************" << endl;
	cout << "*****************˵�ľ����� --> yangShaBi**********************" << endl;
	cout << "*************���� 1 ���ɿ�ʼ��ѯShaBi�ĵ绰����****************" << endl;
	cout << "**************��ʼ��!�������ռ�ShaBi�����һ��*****************" << endl;
	cout << "******************�������µ���ȥ��, ������!********************" << endl;
	cout << "***************************************************************" << endl;
}

void testOutNumber(){
	outNumber out;
	int choice = 1;
	std::string gar;
	while (choice){
		menu();
		cin >> choice;
		//ˢ�»�����
		getline(cin, gar);
		switch (choice)
		{
		case 1:
			out.init();
			break;
		case 0:
			cout << "�˳��ɹ�!" << endl;
			break;
		default:
			break;
		}
	}
}


int main(){

	testOutNumber();
	return 0;
}