#pragma once
#include "MD5.h"
#include "SearchDelFile.h"
#include "FileManager.h"
#include "managerTool.h"
using namespace std;;



void testTurnStr(){
	uint num = 0x12345678;
	md5 m;
	cout << m.turnStr(num).c_str() << endl;
}

void testgetStringMd5(){
	md5 m;
	std::string s = "abcdefgi";
	cout << m.getStringMd5(s).c_str() << endl;
}

void testGetFileMd5(){
	md5 m;
	cout << m.getFileMd5("test1.txt").c_str() << endl;
	m.reset();
	cout << m.getFileMd5("test2.txt").c_str() << endl;
}

void testSearchFile(){
	const string path = ".";
	unordered_set<string> files;
	searchFile(path, files);
	for (const auto& e : files){
		cout << e << endl;
	}
}

void testFileManager(){
	FileManager fm;
	string path = ".";
	fm.scannerFile(path);
	//fm.delFileByMd5();
}
enum {
	EXIT,
	SCANNERFILE,
	SHOWALLFILES,
	SHOWSAMEFILES,
	DELFILEBYNAME,
	DEFILEBYMD5,
	DELSNAMEFILE,
	SHOWMD5FILE,
	SHOWFILEMD5
};

void menu(){
	std::cout << "****************************************************" << std::endl;
	std::cout << "***1 ɨ�� 2 ��ʾ�����ļ� 3 ��ʾ�����ظ��ļ�*********" << std::endl;
	std::cout << "***4 ���ļ���ɾ�� 5 ��MD5ɾ�� 6 ɾ���ظ��ļ� *******" << std::endl;
	std::cout << "***7 md5-file 8 file- md5***************************" << std::endl;
	std::cout << "****************************************************" << std::endl;

}
void testTool(){
	managerTool tool;
	int choice;
	string gar;
	do{
		menu();
		std::cout << "������ѡ�� :" << std::endl;
		std::cin >> choice;
		getline(std::cin, gar);
		switch (choice){
		case SCANNERFILE:
			tool.scannerFiles();
			break;
		case SHOWALLFILES:
			tool.showAllFiles();
			break;
		case SHOWSAMEFILES:
			tool.showSameFiles();
			break;
		case DELFILEBYNAME:
			tool.delFileByName();
			break;
		case DEFILEBYMD5:
			tool.delFileByMd5();
			break;
		case DELSNAMEFILE:
			tool.delSameFile();
			break;
		case SHOWMD5FILE:
			tool.showMD5_File();
			break;
		case SHOWFILEMD5:
			tool.showFile_MD5();
			break;
		case EXIT:
			std::cout << "�˳��ɹ�" << std::endl;
			break;
		default:
			break;
		}
	} while (choice != EXIT);
}
int main(){
	//testTurnStr();
	//testgetStringMd5();
	//testGetFileMd5();
	//testSearchFile();
	//testFileManager();
	testTool();
	return 0;
}