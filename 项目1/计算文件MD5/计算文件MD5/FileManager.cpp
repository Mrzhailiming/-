#include "FileManager.h"
#include "SearchDelFile.h"


//ɨ��
void FileManager::scannerFile(const std::string& path){
	//ɨ��֮ǰ��files���
	files.clear();

	std::cout << "All files" << std::endl;
	searchFile(path, files);
	showAllFiles();

	std::cout << "MD5 -- fileName" << std::endl;
	getMd5_Files();
	showMd5Files();

	std::cout << "samelist" << std::endl;
	sameFilesList();
	showSameFilesList();
}

//���ļ���md5 -- file ӳ��
void FileManager::getMd5_Files(){
	//���ԭ����MD5_FILE
	md5_file.clear();
	for (const auto& e : files){
		//����ÿ���ļ�md5֮ǰҪ����ABCD
		md.reset();
		md5_file.insert(make_pair(md.getFileMd5(e.c_str()), e));
	}
}

//ֻ�����ظ��ļ�,ӳ���ϵΪmd5 -- file
void FileManager::sameFilesList(){
	file_md5.clear();
	auto it = md5_file.begin();
	while (it != md5_file.end()){
		//������������ϵ��ļ�MD5ֵ��ͬ,�����
		if (md5_file.count(it->first) > 1){
			auto pair = md5_file.equal_range(it->first);
			auto begin = pair.first;
			while (begin != pair.second){
				file_md5.insert(make_pair(begin->second, begin->first));
				++begin;
			}
			it = pair.second;
		}
		else{
			files.erase(it->second);
			it = md5_file.erase(it);
		}
	}
}
//��ֻ֤����ͬ�ļ�ֻ����һ��
void FileManager::delFileByName(const std::string& fileName){
	

}
void FileManager::delFileByMd5(const std::string& fileMd5){

}
void FileManager::delFileBySame(){

}
//ģ��ɾ��
void FileManager::delFileByMatch(const std::string& Match){

}

void FileManager::showAllFiles(){
	for (const auto& e : files){
		std::cout << e << std::endl;
	}
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
	std::cout << md5_file.size() << std::endl;
}
void FileManager::showMd5Files(){
	for (const auto& e : md5_file){
		std::cout << e.first << "---" << e.second << std::endl;
	}
}