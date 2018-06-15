#include "file_type.h"
#include "fstream"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <errno.h>

FileType::FileType(FilesystemManagement::FILESYSTEM_ENTRY_TYPE *e):FilesystemEntry(e){this->mode=e->get_mode();}
FileType::FileType(std::string path):FilesystemEntry(path){}
FileType::~FileType(){}

void FileType::copy(std::string destination){
	if(destination.at(destination.length()-1)!='/')destination+="/";
	std::cout<<destination<<std::endl;
	int source_fd=open(this->path.c_str(),O_RDONLY);
	int dest_fd=open((destination+this->name).c_str(),O_WRONLY|O_CREAT|O_TRUNC,this->mode);
	if(source_fd>=0&&dest_fd>=0){
		sendfile(dest_fd,source_fd,NULL,size);
	}else{
		std::perror("Error:\n");
		std::cerr<<"Error in copying file:"<<errno<<std::endl;
	}
}

void FileType::del(){
	std::remove(this->path.c_str());
};
void FileType::move(std::string destination){
	if(destination.at(destination.length()-1)!='/')destination+="/";
	std::rename(this->path.c_str(),(destination+this->name).c_str());
}
