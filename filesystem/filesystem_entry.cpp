#include "filesystem_wrapper.h"
#include "filesystem_entry.h"

FilesystemEntry::FilesystemEntry(FilesystemManagement::FILESYSTEM_ENTRY_TYPE *e){
		name=e->get_name();
		path=e->get_path();
		parent_path=e->get_parent_path();
		n_links=e->get_nlinks();
		gid=e->get_gid();
		uid=e->get_uid();
		size=e->get_size();
		permissions=e->get_permissions();
		modification_time=e->get_modification_time();
		filesystem_entry_type=e->get_filesystem_entry_type();
}

FilesystemEntry::FilesystemEntry(std::string path){
		FilesystemManagement::FILESYSTEM_ENTRY_TYPE e(path);
		name=e.get_name();
		this->path=e.get_path();
		parent_path=e.get_parent_path();
		n_links=e.get_nlinks();
		gid=e.get_gid();
		uid=e.get_uid();
		size=e.get_size();
		permissions=e.get_permissions();
		modification_time=e.get_modification_time();
		filesystem_entry_type=e.get_filesystem_entry_type();
}

FilesystemEntry::~FilesystemEntry(){}
