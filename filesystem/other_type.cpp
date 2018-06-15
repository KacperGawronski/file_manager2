#include "other_type.h"


OtherType::OtherType(FilesystemManagement::FILESYSTEM_ENTRY_TYPE *e):FilesystemEntry(e){}
OtherType::OtherType(std::string path):FilesystemEntry(path){}
OtherType::~OtherType(){}
void OtherType::copy(std::string destination){}
void OtherType::move(std::string destination){}
void OtherType::del(){}
