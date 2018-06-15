#ifndef BASIC_SIGNALS_ACCESS_H
#define BASIC_SIGNALS_ACCESS_H
#include <gtkmm.h>
#include <iostream>
#include "BasicWidgetsAccess.h"
#include "BasicDataAccess.h"

class BasicSignalsAccess{
	private:
		BasicWidgetsAccess *widgets;
		BasicDataAccess *data;
		void create_new_left_tree_model();
		void create_new_right_tree_model();
		void copy_from_right(const Gtk::TreeModel::iterator& iter);
		void copy_from_left(const Gtk::TreeModel::iterator& iter);
		void move_from_right(const Gtk::TreeModel::iterator& iter);
		void move_from_left(const Gtk::TreeModel::iterator& iter);
		void delete_from_right(const Gtk::TreeModel::iterator& iter);
		void delete_from_left(const Gtk::TreeModel::iterator& iter);
	public:
		BasicSignalsAccess(BasicWidgetsAccess *w, BasicDataAccess *d);
		~BasicSignalsAccess();
		void on_activate_left_path_entry();
		void on_activate_right_path_entry();
		void on_clicked_copy_button();
		void on_clicked_move_button();
		void on_clicked_delete_button();
		
		void on_clicked_left_command_button();
		void on_clicked_right_command_button();
};
#endif
