#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "MD5.h"
class FileManager{
public:
	void scannerFile(const std::string& path);
	void getMd5_Files();
	void sameFilesList();

	void showAllFiles();
	void showSameFilesList();
	void showMd5Files();
	void showMD5_File();
	void showFile_MD5();
	//ɾ������:��ֻ֤����ͬ�ļ�ֻ����һ��
	void delFileByName(const std::string& fileName);
	void delFileByMd5(const std::string& fileMd5);
	void delFileBySame();
	//ģ��ɾ��
	void delFileByMatch(const std::string& Match);
	//����ɾ����������ļ�
	void RemoveFile(const char* name);
private:
	//���������ļ�
	std::unordered_set<std::string> files;
	//md-file,
	std::unordered_multimap<std::string, std::string> md5_file;
	//file-md
	std::unordered_map<std::string, std::string> file_md5;
	md5 md;
};