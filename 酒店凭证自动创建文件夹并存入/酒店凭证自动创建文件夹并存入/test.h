#ifndef FIRST
#define FIRST

//ͷ�ļ�
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <map>

#include <windows.h>
#include <stdio.h>
#include <io.h>
using namespace std;

#define DEFAULT_PATH "D:\\"


class myWork{
public:
	myWork(string pt = NULL){
		path = pt;
	}

	//��ȡ�ļ����������ļ�
	void getAllFile(const string& path){
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
				if (strcmp(fileData.name, ".") != 0 && strcmp(fileData.name, "..") != 0){
					getAllFile(path + "\\" + fileData.name);
				}
			}
			else{
				pfileVec.push_back(path + "\\" + fileData.name);
			}
		} while (_findnext(handle, &fileData) == 0);
		_findclose(handle);
	}
	//�����-�ļ���ӳ�䣬 multimap
	void num_fimeName(){
		//����vector, ����ź��ļ���ӳ��
		
		for (const auto& e : pfileVec){
			int i = 0;
			int num = 0;
			while (i < e.size() && (e[i] < '0' || e[i] > '9')){
				++i;
			}
			while (i < e.size() && (e[i] >= '0' && e[i] <= '9')){
				num = num * 10 + e[i] - '0';
				++i;
			}
			if (num != 0){
				pMulMap.insert(make_pair(num, path + e));
			}
			
		}
	}

	//����multimap �����ļ��в������ļ�
	void create_moveFile(){
		multimap<int, string>::iterator it = pMulMap.begin();
		while (it != pMulMap.end()){
			//����
			int num = it->first;
			string dirName = num + "";
			string dirPath_Name = DEFAULT_PATH + dirName;
			//�����µ��ļ���
			createNewDir(dirPath_Name);
			//�����ļ�
			string oldPath = path + dirName;
			string newPath = dirPath_Name;
			moveFile(oldPath, newPath);
			++it;
			if (it->first == num){
				oldPath = path + it->second;
				moveFile(oldPath, newPath);
				++it;
			}
		}
	}

	//������Ӧ��˾/�˵��ļ��У�����Ŵ��棩
	void createNewDir(const string& dirPath_name){
		string sh = "md ";
		string tmp = sh + dirPath_name;
		system(tmp.c_str());
	}
	//�ƶ��ļ�
	void moveFile(const string& oldPath, const string& newPath){
			MoveFile((LPCWSTR)oldPath.c_str(), (LPCWSTR)newPath.c_str());
	}
private:
	string path;
	vector<string> pfileVec;
	multimap<int, string> pMulMap;
};



#endif