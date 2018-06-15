#include "file_type.h"
#include "fstream"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>

FileType::FileType(FilesystemManagement::FILESYSTEM_ENTRY_TYPE *e):FilesystemEntry(e){}
FileType::FileType(std::string path):FilesystemEntry(path){}
FileType::~FileType(){}

void FileType::copy(std::string destination){
	int source_fd=open(this->path.c_str(),O_RDONLY);
	int dest_fd=creat(destination.c_str(),O_WRONLY);
	if(source_fd>=0&&dest_fd>=0){
		sendfile(dest_fd,source_fd,NULL,size);
	}else{
		std::cout<<"Error in copying file."<<std::endl;
	}
}

void FileType::del(){
	std::remove(this->path.c_str());
};
void FileType::move(std::string destination){
	std::rename(this->path.c_str(),destination.c_str());
}
