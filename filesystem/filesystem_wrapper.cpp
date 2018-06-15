/*
	Copyright 2018 Kacper Gawroński.

	This file, and all files created by Kacper Gawroński in project
	File-Manager, are licensed under GNU General Public License.

    File-Manager is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    File-Manager is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with File-Manager.  If not, see <http://www.gnu.org/licenses/>.
*/


/*version for linux using struct stat*/
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include "filesystem_wrapper.h"

namespace FilesystemManagement{
#ifdef __linux__
	FILESYSTEM_ENTRY_TYPE::FILESYSTEM_ENTRY_TYPE(std::string path,struct stat *OS_info){
		this->OS_info=OS_info;
			this->path=path;
			this->name=basename((char*)path.c_str());
			this->parent_path=dirname((char*)path.c_str());
	}
	FILESYSTEM_ENTRY_TYPE::FILESYSTEM_ENTRY_TYPE(std::string path){
		this->OS_info=new struct stat;
		if(stat(path.c_str(),this->OS_info)!=-1){
			this->path=path;
			
			this->name=basename((char*)path.c_str());
			this->parent_path=dirname((char*)path.c_str());
		}else{
			this->path="";
			this->name="";
			this->parent_path="";
			this->parent=(FILESYSTEM_ENTRY_TYPE*)0;					
		}
	}
	FILESYSTEM_ENTRY_TYPE::FILESYSTEM_ENTRY_TYPE(FILESYSTEM_ENTRY_TYPE *parent,std::string name){
		this->OS_info=new struct stat;
		this->parent=parent;
		this->name=name;
		this->parent_path=parent->get_path();
		this->path=this->parent_path+"/"+this->name;
		//std::cout<<this->path<<std::endl<<this->name<<std::endl<<std::endl;
		stat(this->path.c_str(),this->OS_info);
	}
	
	
	FILESYSTEM_ENTRY_TYPE::~FILESYSTEM_ENTRY_TYPE(){
		delete OS_info;
	}
	
	std::string FILESYSTEM_ENTRY_TYPE::get_filesystem_entry_type(){
		switch((int)(((this->OS_info->st_mode)&0170000)>>12)){
			case 2:
				return "chardev";
			case 4:
				return "directory";
			case 6:
				return "blockdev";
			case 8:
				return "file";
		}
		return std::to_string((int)(((this->OS_info->st_mode)&0170000)>>12));
	}
	
	int FILESYSTEM_ENTRY_TYPE::get_gid(){
		return this->OS_info->st_gid;
	}
	int FILESYSTEM_ENTRY_TYPE::get_uid(){
		return this->OS_info->st_uid;
	}
	
	int FILESYSTEM_ENTRY_TYPE::get_nlinks(){
		return this->OS_info->st_nlink;
	}
	
	std::string FILESYSTEM_ENTRY_TYPE::get_modification_time(){
		return std::string(ctime(&this->OS_info->st_mtime));
	}
	
	unsigned long long FILESYSTEM_ENTRY_TYPE::get_size(){
		return this->OS_info->st_size;
	}
	       int open(const char *pathname, int flags, mode_t mode);
	std::string FILESYSTEM_ENTRY_TYPE::get_permissions(){
		
		char perm[]={ 
			(this->OS_info->st_mode & S_IRUSR) ? 'r' : '-',
			(this->OS_info->st_mode & S_IWUSR) ? 'w' : '-',
			(this->OS_info->st_mode & S_IXUSR) ? 'x' : '-',
			(this->OS_info->st_mode & S_IRGRP) ? 'r' : '-',
			(this->OS_info->st_mode & S_IWGRP) ? 'w' : '-',
			(this->OS_info->st_mode & S_IXGRP) ? 'x' : '-',
			(this->OS_info->st_mode & S_IROTH) ? 'r' : '-',
			(this->OS_info->st_mode & S_IWOTH) ? 'w' : '-',
			(this->OS_info->st_mode & S_IXOTH) ? 'x' : '-',
			'\0'				
		};
		return std::string(perm);
	}
#else
#error Not implemented
#endif
	
	
	std::string FILESYSTEM_ENTRY_TYPE::get_path(){
		return this->path;
	}
	void* FILESYSTEM_ENTRY_TYPE::get_parent(){
		return reinterpret_cast<void*>(this->parent);
	}
	std::string FILESYSTEM_ENTRY_TYPE::get_parent_path(){
		return this->parent_path;
	}
	std::string FILESYSTEM_ENTRY_TYPE::get_name(){
		return this->name;
	}
	
	
	std::vector<FILESYSTEM_ENTRY_TYPE*>* FILESYSTEM_ENTRY_TYPE::get_children(){
		std::vector<FILESYSTEM_ENTRY_TYPE*> *returned= new std::vector<FILESYSTEM_ENTRY_TYPE*>;
		DIR *dir;
		struct dirent *entry;
		if((dir=opendir(this->path.c_str()))!=0){
			while((entry=readdir(dir))!=(void*)0){
				if(strcmp(entry->d_name,".")&&strcmp(entry->d_name,"..")){
					returned->push_back(new FILESYSTEM_ENTRY_TYPE(this,std::string(entry->d_name)));
				
				}
			}
		}
		return returned;
	}
	
}

