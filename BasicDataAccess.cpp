#include "BasicDataAccess.h" 
BasicDataAccess::BasicDataAccess(BasicWidgetsAccess *w){
	widgets=w;
}

BasicDataAccess::~BasicDataAccess(){
	for(auto i:left_entries){
		delete i.second;
	}
	for(auto i:right_entries){
		delete i.second;
	}
}

std::string BasicDataAccess::get_left_path(){
	return widgets->left_path_entry->get_text();
}
std::string BasicDataAccess::get_right_path(){
	return widgets->right_path_entry->get_text();
}

std::string BasicDataAccess::get_left_command(){
	return widgets->left_command_entry->get_text();
}
std::string BasicDataAccess::get_right_command(){
	return widgets->right_command_entry->get_text();
}
