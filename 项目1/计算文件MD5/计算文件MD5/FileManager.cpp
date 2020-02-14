#include "FileManager.h"
#include "SearchDelFile.h"


//ɨ��
void FileManager::scannerFile(const std::string& path){
	//ɨ��֮ǰ��files���
	files.clear();

	//�������ļ����洢��files��
	searchFile(path, files);

	//�õ������ļ���file --- md5
	getMd5_Files();

	//�õ���ͬ�ļ���MD5 -- files
	sameFilesList();
}

//�������ļ����洢������ӳ�䷽����
void FileManager::getMd5_Files(){
	//���ԭ����MD5_FILE
	file_md5.clear();
	md5_file.clear();
	for (const auto& e : files){
		//����ÿ���ļ�md5֮ǰҪ����ABCD
		md.reset();
		md5_file.insert(make_pair(md.getFileMd5(e.c_str()), e));
		file_md5.insert(make_pair(e, md.getFileMd5(e.c_str())));
	}

}

//���ظ����ļ��洢��ӳ���ϵΪmd5 -- file��
void FileManager::sameFilesList(){
	auto it = md5_file.begin();
	while (it != md5_file.end()){
		if (md5_file.count(it->first) == 1){
			it = md5_file.erase(it);
		}
		else{
			++it;
		}
	}
}
//��֤��ͬ�ļ�ֻ����һ��,���µ�ǰ���ļ�
void FileManager::delFileByName(const std::string& fileName){
	//�ļ�������
	if (file_md5.count(fileName) == 0){
		perror("�ļ������� :");
		return;
	}
	//��ȡ�ļ�md5
	std::string md5 = file_md5[fileName];
	//�ж����ͬ�ļ�����
	if (md5_file.count(md5) > 1){
		int count = 0;
		auto pair = md5_file.equal_range(md5);
		auto begin = pair.first;
		//ɾ��ͬ�����ļ�,ע�ⲻɾ��������ļ�������Ӧ���ļ�
		while (begin != pair.second){
			if (begin->second != fileName){
				//ɾ����������ļ�
				RemoveFile(begin->second.c_str());
				file_md5.erase(begin->second);
				files.erase(begin->second);
				begin = md5_file.erase(begin);
				++count;
			}
			else{
				++begin;
			}
		}
		std::cout << "���ļ���ɾ���ɹ� :" << count << "��" << std::endl;
	}
	else{
		std::cout << fileName << " : ֻ��һ��" << std::endl;
	}
}

//��֤��ͬ���ļ�ֻ����һ��
void FileManager::delFileByMd5(const std::string& fileMd5){
	//���fileMD5��Ӧ���ļ�����
	//md5_file ֻ����ظ��ļ�
	int count = 0;
	if (md5_file.count(fileMd5) > 1){
		auto pair = md5_file.equal_range(fileMd5);
		auto begin = pair.first;
		++begin;
		//�ӵڶ�����ʼɾ��,files��file_md5
		while (begin != pair.second){
			//ɾ����������ļ�
			RemoveFile(begin->second.c_str());
			files.erase(begin->second);
			file_md5.erase(begin->second);
			++count;
			++begin;
		}

		auto it = md5_file.find(fileMd5);
		++it;
		while (it != md5_file.end() && it->first == fileMd5){
			it = md5_file.erase(it);
		}
		std::cout << "��MD5ɾ���ɹ� :" << count << "��" << std::endl;
	}
}

//ɾ���ظ����ļ�,�ظ����ļ�����MD5_file���
void FileManager::delFileBySame(){
	if (md5_file.size() == 0){
		std::cout << "û���ظ����ļ�" << std::endl;
		return;
	}
	else{
		int count = 0;
		std::string md5;
		//�õ���Ԫ�ص�md5
		auto it = md5_file.begin();
		md5 = it->first;
		++it;
		while (it != md5_file.end()){
			
			if (it->first == md5){
				//ɾ����������ļ�
				RemoveFile(it->second.c_str());
				files.erase(it->second);
				file_md5.erase(it->second);
				//ɾ��MD5_file�е�,�����е���������
				it = md5_file.erase(it);
				++count;//ɾ���ļ��ĸ���
			}
			else{
				md5 = it->first;
				++it;
			}
		}
		std::cout << "�ظ��ļ�ɾ�� :" << count << "�� " << std::endl;
	}
	
}
//ģ��ɾ��
void FileManager::delFileByMatch(const std::string& Match){
	//str.find(str) != npos;
}

void FileManager::RemoveFile(const char* name){
	delFile(name);
}

void FileManager::showAllFiles(){
	std::cout << "�����ļ� : " << std::endl;
	for (const auto& e : files){
		std::cout << e << std::endl;
	}
	std::cout << "�ļ����� :" << files.size() << std::endl;
}
void FileManager::showSameFilesList(){
	auto it = md5_file.begin();
	while (it != md5_file.end()){
		auto pair = md5_file.equal_range(it->first);
		auto begin = pair.first;
		while (begin != pair.second){
			std::cout << begin->first << "---" << begin->second << std::endl;
			++begin;
		}
		it = pair.second;
	}
	std::cout << "�ظ��ļ�����: " <<  md5_file.size() << std::endl;
}
void FileManager::showMd5Files(){
	for (const auto& e : md5_file){
		std::cout << e.first << "---" << e.second << std::endl;
	}
	std::cout << "�ļ�����: " << md5_file.size() << std::endl;
}

void FileManager::showMD5_File(){
	std::cout << "\tmd5" << "\t---" << "Filename" << std::endl;
	for (const auto& e : file_md5){
		std::cout << e.second << e.first << std::endl;
	}
	std::cout << "�ļ�����: " << md5_file.size() << std::endl;
}
void FileManager::showFile_MD5(){
	std::cout << "\tFilename" << "\t---" << "md5" << std::endl;
	for (const auto& e : file_md5){
		std::cout << e.first << e.second << std::endl;
	}
	std::cout << "�ļ�����: " << md5_file.size() << std::endl;
}