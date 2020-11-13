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
	myWork(string path = NULL){;
	}

	//��ȡ�ļ����������ļ�
	void getAllFile(){
		_finddata_t findData;
		long fHandle;
		fHandle = _findfirst("D:\\test\\*.*", &findData);
		if (fHandle != -1){
			do {
				if (findData.name == "." || findData.name == ".."){
					continue;
				}
				
				pfileVec.push_back(findData.name);
				
			} while (!_findnext(fHandle, &findData));
		}
	}
	//�����-�ļ���ӳ�䣬 multimap
	void num_fimeName(){
		//����vector, ����ź��ļ���ӳ��
		int num = 0;
		for (const auto& e : pfileVec){
			int i = 0;
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

			}
		}
	}

	//������Ӧ��˾/�˵��ļ��У�����Ŵ��棩
	void createNewDir(string& dirPath_name){
		string sh = "md ";
		string tmp = sh + dirPath_name;
		system(tmp.c_str());
	}
	//�ƶ��ļ�
	void moveFile(string& oldPath, string& newPath){
			MoveFile((LPCWSTR)oldPath.c_str(), (LPCWSTR)newPath.c_str());
	}
private:
	string path;
	vector<string> pfileVec;
	multimap<int, string> pMulMap;
};



#endif