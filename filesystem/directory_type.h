#ifndef DIRECTORY_TYPE_H
#define DIRECTORY_TYPE_H
#include "filesystem_wrapper.h"
#include "filesystem_entry.h"
#include <iostream>

class DirectoryType:public FilesystemEntry{
	private:
		FilesystemManagement::FILESYSTEM_ENTRY_TYPE *content;
	public:
		DirectoryType(FilesystemManagement::FILESYSTEM_ENTRY_TYPE *e);
		DirectoryType(std::string path);
		~DirectoryType();
		
		virtual void copy(std::string destination);
		virtual void move(std::string destination);
		virtual void del();
};


#endif
