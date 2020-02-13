#include "SearchDelFile.h"


void search(const std::string& path, std::vector<std::string>& files){
	std::string  s = path + "\\" + "*.*";
	_finddata_t filedata;
	long handle = _findfirst(s.c_str(), &filedata);
	//�ҵ�,���� 0;
	if (handle == -1){
		//û�ҵ�
		std::cout << s << std::endl;
		perror("findfirst error :");
		_findclose(handle);
		return;
	}
	do {
		//��ǰΪĿ¼,��������
		if (filedata.attrib & _A_SUBDIR){
			if (strcmp(filedata.name, ".") != 0 && strcmp(filedata.name, "..") != 0)
			search(path + "\\" + filedata.name, files);
		}
		else{
			files.push_back(path +"\\" + filedata.name);
		}
	} while (_findnext(handle, &filedata) == 0);
	_findclose(handle);
}