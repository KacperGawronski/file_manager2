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


#ifndef FILESYSTEM_ABSTRACT_CLASS_H
#define FILESYSTEM_ABSTRACT_CLASS_H
#include <string>
#include <vector>
namespace AbstractClasses{
	class FilesystemEntry{
		protected:
			std::string name;
			std::string path;
			FilesystemEntry *parent;
			std::string parent_path;
		public:
			virtual std::string get_filesystem_entry_type()=0;
			virtual int get_gid()=0;
			virtual int get_uid()=0;
			virtual int get_nlinks()=0;
			virtual std::string get_modification_time()=0;
			
			virtual unsigned long long get_size()=0;
			
			virtual std::string get_permissions()=0;
			virtual std::string get_path()=0;
			virtual void* get_parent()=0;
			virtual std::string get_parent_path()=0;
			virtual std::string get_name()=0;
						
			virtual void *get_children()=0;			
	};
}


#endif
