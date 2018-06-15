#ifndef OTHER_TYPE_H
#define OTHER_TYPE_H
#include "filesystem_wrapper.h"
#include "filesystem_entry.h"
#include <iostream>

class OtherType:public FilesystemEntry{
	public:
		OtherType(FilesystemManagement::FILESYSTEM_ENTRY_TYPE *e);
		OtherType(std::string path);
		~OtherType();
		virtual void copy(std::string destination);
		virtual void move(std::string destination);
		virtual void del();
};


#endif
