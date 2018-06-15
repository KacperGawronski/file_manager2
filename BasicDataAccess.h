#ifndef BASIC_DATA_ACCESS_H
#define BASIC_DATA_ACCESS_H
#include <gtkmm.h>
#include <iostream>
#include "BasicWidgetsAccess.h"
#include "filesystem/filesystem_entry.h"
#include <map>

class BasicDataAccess{
	private:
		BasicWidgetsAccess *widgets;
	public:		
		std::map<std::string, FilesystemEntry*> left_entries,right_entries;
		BasicDataAccess(BasicWidgetsAccess *w);
		~BasicDataAccess();
		std::string get_left_path();
		std::string get_right_path();
		std::string get_left_command();
		std::string get_right_command();
};
#endif
