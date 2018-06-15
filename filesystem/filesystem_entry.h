#ifndef FILESYSTEMENTRY_H
#define FILESYSTEMENTRY_H
#include "filesystem_wrapper.h"
#include <iostream>
#include <sys/sendfile.h>

class FilesystemEntry{
	public:
		FilesystemEntry(FilesystemManagement::FILESYSTEM_ENTRY_TYPE *e);
		FilesystemEntry(std::string path);
		~FilesystemEntry();
		std::string name;
		std::string path;
		std::string parent_path;
		std::string permissions;
		std::string modification_time;
		int n_links,gid,uid;
		std::string filesystem_entry_type;
		unsigned long long size;
		virtual void copy(std::string destination)=0;
		virtual void move(std::string destination)=0;
		virtual void del()=0;
};


#endif
