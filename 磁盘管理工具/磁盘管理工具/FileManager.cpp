#include "FileManager.h"
#include <io.h>

void FileManager::init(){
	std::cout << "������·�� :";
	std::string path;
	getline(std::cin, path);
	//����ɨ��
	scannerFile(path);
	//����ÿһ���ļ���md5
	getAllFilesMd5();
	//��MD5_file�������и���,�Ѳ��ظ����ļ�ɾ����
	getSameFiles();
}

//ɨ��
void FileManager::scannerFile(const std::string& path){
	//Ҫƥ����ļ���ʽ
	const std::string tar = path + "\\" + "*.*";
	_finddata_t fileData;
	long handle = _findfirst(tar.c_str(), &fileData);
	if (handle == -1){
		perror("find file Error : ");
		_findclose(handle);
		return;
	}
	do{
		if (fileData.attrib & _A_SUBDIR){
			if (strcmp(fileData.name, ".") != 0 && strcmp(fileData.name, "..") !=  0){
				scannerFile(path + "\\" + fileData.name);
			}
		}
		else{
			_allFiles.insert(path + "\\" + fileData.name);
		}
	} while (_findnext(handle, &fileData) == 0);
	_findclose(handle);
}

//����ÿһ���ļ���md5,�������Ӧ��������
void FileManager::getAllFilesMd5(){
	//���
	_name_md5.clear();
	_md5_name.clear();
	std::string md5;
	for (const auto& e : _allFiles){
		md5 = _gMd5.getFileMd5(e.c_str()).c_str();
		_name_md5.insert(make_pair(e,md5));
		_md5_name.insert(make_pair(md5, e));
	}
}

void FileManager::getSameFiles(){
	std::string md5;
	auto it = _md5_name.begin();
	while (it != _md5_name.end()){
		md5 = it->first;
		if (_md5_name.count(md5) == 1){
			it = _md5_name.erase(it);
		}
		else{
			++it;
		}
	}
}

//չʾ
void FileManager::showAllFile(){
	std::cout << "\t�ļ��� :" << _name_md5.size() << std::endl;
	for (const auto& e : _name_md5){
		std::cout << e.first << "\t--\t" << e.second << std::endl;
	}
}
void FileManager::showSameFile(){
	std::cout << "\t�ļ��� :" << _md5_name.size() << std::endl;
	for (const auto& e : _md5_name){
		std::cout << e.first << "--" << e.second << std::endl;
	}
}
void FileManager::showName_Md5(){
	std::cout << "\t�ļ��� :" << _name_md5.size() << std::endl;
	for (const auto& e : _name_md5){
		std::cout << e.first << "\t--\t" << e.second << std::endl;
	}
}
void FileManager::showMd5_Name(){
	std::cout << "\t�ļ��� :" << _name_md5.size() << std::endl;
	for (const auto& e : _name_md5){
		std::cout << e.second << "\t--\t" << e.first << std::endl;
	}
}

//ɾ��,ȥ��
void FileManager::delFileByName(){
	std::cout << "������ȥ�ص��ļ����� :";
	std::string name;
	std::cin >> name;
	//std::cout << _allFiles.count(name) << std::endl;
	if (_allFiles.count(name) < 1){
		perror("file not found :");
		return;
	}
	//ɾ�����ļ�����
	int count = 0;
	std::string md5 = _name_md5[name];
	auto pair = _md5_name.equal_range(md5);
	auto beginIt = pair.first;
	while (beginIt != pair.second){
		if (strcmp(beginIt->second.c_str(), name.c_str()) != 0){
			++count;
			//remove(beginIt->second.c_str());
			_allFiles.erase(beginIt->second);
			_name_md5.erase(beginIt->second);
			beginIt = _md5_name.erase(beginIt);
			//���»�ȡ����
			pair = _md5_name.equal_range(md5);
			beginIt = pair.first;
			++beginIt;
		}
	}
	std::cout << "\tɾ���ļ��� :" << count << std::endl;
}

//
void FileManager::delFileByMd5(){
	std::cout << "������ȥ�ص��ļ���MD5 :";
	std::string md5;
	std::cin >> md5;
	//�ڴ���ظ��ļ��������в���
	if (_md5_name.count(md5) < 1){
		perror("file only one :");
		return;
	}
	//ɾ�����ļ�����
	int count = 0;
	auto pair = _md5_name.equal_range(md5);
	auto beginIt = pair.first;
	++beginIt;
	while (beginIt != pair.second){
		++count;
		//remove(beginIt->second.c_str());
		_name_md5.erase(beginIt->second);
		_allFiles.erase(beginIt->second);
		_md5_name.erase(beginIt);
		//���µ�����
		pair = _md5_name.equal_range(md5);
		beginIt = pair.first;
		++beginIt;
	}
	std::cout << "\tɾ���ļ��� :" << count << std::endl;
}
void FileManager::delSameFile(){
	int count = 0;
	std::string curMd5;
	auto it = _md5_name.begin();
	while (it != _md5_name.end()){
		curMd5 = it->first;
		++it;
		while(it != _md5_name.end() && strcmp(it->first.c_str(), curMd5.c_str()) == 0){
			++count;
			//remove(beginIt->second.c_str());
			_name_md5.erase(it->second);
			_allFiles.erase(it->second);
			//���µ�����
			it = _md5_name.erase(it);
		}
	}
	std::cout << "\tɾ���ļ��� :" << count << std::endl;
}

void FileManager::getFILEmd5(){
	std::cout << "�������ļ�����(����·��) :";
	std::string name, str;
	std::cin >> name;
	str = _gMd5.getFileMd5(name);
	std::cout << "�ļ���md5Ϊ : " << str << std::endl;
	FILE* f = fopen("Filemd5.txt", "a");
	fwrite((name + " <-> " + str + " --- ").c_str(), 1, name.size() + str.size() + 10, f);
	fclose(f);
}
void FileManager::getSTRINGmd5(){
	std::cout << "�������ַ��� :";
	std::string name, str;
	std::cin >> name;
	str = _gMd5.getStrMd5(name);
	std::cout <<"�ַ�����md5Ϊ : " << str << std::endl;
	FILE* f = fopen("Strmd5.txt", "a");
	fwrite((name + " <-> " + str + " --- ").c_str(), 1, name.size() + str.size() + 10, f);
	fclose(f);
}