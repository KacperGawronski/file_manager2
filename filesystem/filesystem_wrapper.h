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



#ifndef FILESYSTEM_MANAGEMENT_H
#define FILESYSTEM_MANAGEMENT_H
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include "filesystem_abstract_class.h"
#ifdef __linux__
	#include "linux_includes.h"
	#define OS_INFO_TYPE struct stat
	#define OS_SPECIFIC_FILESYSTEM_ENTRY_TYPE FilesystemManagement::LinuxFilesystemEntry
namespace FilesystemManagement{
	
	#define FILESYSTEM_ENTRY_TYPE LinuxFilesystemEntry
	class FILESYSTEM_ENTRY_TYPE:public AbstractClasses::FilesystemEntry{
		
		private:
			std::string name;
			std::string path;
			FILESYSTEM_ENTRY_TYPE *parent;
			std::string parent_path;
			struct stat *OS_info;
		public:
			FILESYSTEM_ENTRY_TYPE(std::string path,struct stat *OS_info);
			FILESYSTEM_ENTRY_TYPE(std::string path);
			FILESYSTEM_ENTRY_TYPE(FILESYSTEM_ENTRY_TYPE *parent,std::string name);
			
			
			~FILESYSTEM_ENTRY_TYPE();

			std::string get_filesystem_entry_type();

			int get_gid();
			int get_uid();
			int get_nlinks();
			mode_t get_mode();
			std::string get_modification_time();

			unsigned long long get_size();

			std::string get_permissions();
			std::string get_path();
			/*LinuxFilesystemEntry*/void* get_parent();
			std::string get_parent_path();
			std::string get_name();
			std::vector<FILESYSTEM_ENTRY_TYPE*>* get_children();			
		
	};
}
#endif
#endif
