#pragma once
#include "FileManager.h"


class managerTool{
public:
	void scannerFiles();
	void showAllFiles();
	void showSameFiles();
	void showMD5_File();
	void showFile_MD5();
	//ɾ��
	void delFileByName();
	void delFileByMd5();
	void delSameFile();
private:
	FileManager manager;
};