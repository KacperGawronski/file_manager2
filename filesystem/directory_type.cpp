#include "directory_type.h"
#include "file_type.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <unistd.h>

#include <vector>

DirectoryType::DirectoryType(FilesystemManagement::FILESYSTEM_ENTRY_TYPE *e):FilesystemEntry(e){this->content=new FilesystemManagement::FILESYSTEM_ENTRY_TYPE(e->get_path());}
DirectoryType::DirectoryType(std::string path):FilesystemEntry(path){this->content=new FilesystemManagement::FILESYSTEM_ENTRY_TYPE(path);}
DirectoryType::~DirectoryType(){delete this->content;}

void DirectoryType::copy(std::string destination){

	struct stat st = {0};
	if(stat(destination.c_str(), &st) == -1) {
		mkdir(destination.c_str(), 0700);
	}
	auto children=this->content->get_children();
	/*here is polymorphism*/
	FilesystemEntry *current;
	for(FilesystemManagement::FILESYSTEM_ENTRY_TYPE* child:*children){
		if (child->get_filesystem_entry_type()=="directory"){
			current=new DirectoryType(child);
		}else if(child->get_filesystem_entry_type()=="file"){
			current=new FileType(child);
		}
		if(destination.at(destination.length()-1)!='/'){
			current->copy(destination+'/'+current->path.substr(this->path.length()+1,current->path.length()-this->path.length()-1));
		}else{
			current->copy(destination+current->path.substr(this->path.length(),current->path.length()-this->path.length()));
		}
		delete current;
		delete child;
	}
	delete children;
}

void DirectoryType::del(){
	std::remove(this->path.c_str());
};
void DirectoryType::move(std::string destination){
	std::rename(this->path.c_str(),destination.c_str());
}