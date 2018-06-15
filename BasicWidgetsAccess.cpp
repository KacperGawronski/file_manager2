#include "BasicWidgetsAccess.h"
BasicWidgetsAccess::BasicWidgetsAccess(Glib::RefPtr<Gtk::Builder> &builder){
	builder->get_widget("left_command_button",left_command_button);
	builder->get_widget("right_command_button",right_command_button);
	builder->get_widget("left_path_entry",left_path_entry);
	builder->get_widget("right_path_entry",right_path_entry);
	builder->get_widget("left_command_entry",left_command_entry);
	builder->get_widget("right_command_entry",right_command_entry);
	builder->get_widget("left_tree_view",left_tree_view);
	builder->get_widget("right_tree_view",right_tree_view);
	builder->get_widget("left_command_view",left_command_view);
	builder->get_widget("right_command_view",right_command_view);
	builder->get_widget("copy_button",copy_button);
	builder->get_widget("move_button",move_button);
	builder->get_widget("delete_button",delete_button);
	left_tree_model= Gtk::ListStore::create(model_columns_left);
	right_tree_model= Gtk::ListStore::create(model_columns_right);
	left_tree_view->set_model(left_tree_model);
	right_tree_view->set_model(right_tree_model);
	
	left_tree_view->append_column("Type", model_columns_left.entry_type);
	left_tree_view->append_column("Name", model_columns_left.entry_name);
	left_tree_view->append_column("Permissions", model_columns_left.permissions);
	left_tree_view->append_column("Modification", model_columns_left.modification_time);
	left_tree_view->append_column("nlinks", model_columns_left.nlinks);
	left_tree_view->append_column("uid", model_columns_left.uid);
	left_tree_view->append_column("gid", model_columns_left.gid);
	
	right_tree_view->append_column("Type", model_columns_right.entry_type);
	right_tree_view->append_column("Name", model_columns_right.entry_name);
	right_tree_view->append_column("Permissions", model_columns_right.permissions);
	right_tree_view->append_column("Modification", model_columns_right.modification_time);
	right_tree_view->append_column_numeric("nlinks", model_columns_right.nlinks,"%d");
	right_tree_view->append_column_numeric("uid", model_columns_right.uid,"%d");
	right_tree_view->append_column_numeric("gid", model_columns_right.gid,"%d");
}

BasicWidgetsAccess::~BasicWidgetsAccess(){
	delete left_path_entry;
	delete right_path_entry;
	delete left_command_entry;
	delete right_command_entry;
	delete left_tree_view;
	delete right_tree_view;
	delete left_command_view;
	delete right_command_view;
//	delete left_tree_model;
//	delete right_tree_model;
}
