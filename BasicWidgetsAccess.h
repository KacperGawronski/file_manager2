#ifndef BASIC_WIDGETS_ACCESS_H
#define BASIC_WIDGETS_ACCESS_H
#include <gtkmm.h>
#include <iostream>
#include "ModelColumns.h"
class BasicWidgetsAccess{
	
	private:
	public:
		Gtk::Entry *left_path_entry,*right_path_entry,*left_command_entry,*right_command_entry;
		Gtk::TreeView *left_tree_view,*right_tree_view;
		Gtk::TextView *left_command_view,*right_command_view;
		Glib::RefPtr<Gtk::ListStore> left_tree_model;
		Glib::RefPtr<Gtk::ListStore> right_tree_model;
		Gtk::Button *copy_button,*move_button,*delete_button;
		Gtk::Button *left_command_button,*right_command_button;
		ModelColumns model_columns_left, model_columns_right;
	BasicWidgetsAccess(Glib::RefPtr<Gtk::Builder> &builder);
	~BasicWidgetsAccess();
	
};



#endif
