#pragma once
#include "getMD5.h"
#include <unordered_set>
#include <unordered_map>
class FileManager{
public:
	void init();
	//ɨ��
	void scannerFile(const std::string& path);

	//����ÿһ���ļ���md5,�������Ӧ��������
	void getAllFilesMd5();
	void getSameFiles();

	//�����ļ�MD5
	void getFILEmd5();
	void getSTRINGmd5();

	//չʾ
	void showAllFile();
	void showSameFile();
	void showName_Md5();
	void showMd5_Name();

	//ɾ��
	void delFileByName();
	void delFileByMd5();
	void delSameFile();
private:
	getMd5 _gMd5;
	//��������ļ�
	std::unordered_set<std::string> _allFiles;

	//����ļ���ӳ��md5
	std::unordered_map<std::string, std::string> _name_md5;
	//����ظ��ļ�,md5ӳ���ļ���
	std::unordered_multimap<std::string, std::string> _md5_name;
};