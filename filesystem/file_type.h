#ifndef FILE_TYPE_H
#define FILE_TYPE_H
#include "filesystem_wrapper.h"
#include "filesystem_entry.h"
#include <iostream>

class FileType:public FilesystemEntry{
	public:
		FileType(FilesystemManagement::FILESYSTEM_ENTRY_TYPE *e);
		FileType(std::string path);
		~FileType();
		virtual void copy(std::string destination);
		virtual void move(std::string destination);
		virtual void del();
};


#endif
