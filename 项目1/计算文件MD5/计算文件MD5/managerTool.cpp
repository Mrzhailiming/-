#include "managerTool.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;

void managerTool::scannerFiles(){
	cout << "������·�� : " << endl;
	string path;
	getline(cin, path);
	manager.scannerFile(path);
	showAllFiles();
}
void managerTool::showAllFiles(){
	manager.showAllFiles();
}
void managerTool::showSameFiles(){
	manager.showSameFilesList();
}

void managerTool::showMD5_File(){
	manager.showMD5_File();
}
void managerTool::showFile_MD5(){
	manager.showFile_MD5();
}
void managerTool::delFileByName(){
	cout << "�������ļ��� : " << endl;
	string name;
	getline(cin, name);
	manager.delFileByName(name);
}
void managerTool::delFileByMd5(){
	cout << "������Md5 : " << endl;
	string md5;
	getline(cin, md5);
	manager.delFileByMd5(md5);
}
void managerTool::delSameFile(){
	manager.delFileBySame();
}