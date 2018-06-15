#include "BasicSignalsAccess.h"
#include "filesystem/filesystem_wrapper.h"
#include <sstream>

#include "filesystem/file_type.h"
#include "filesystem/directory_type.h"
#include "filesystem/other_type.h"

#include "command_handling/shell_usage.h"

	BasicSignalsAccess::BasicSignalsAccess(BasicWidgetsAccess *w,BasicDataAccess *d){
		widgets=w;
		data=d;
		
		widgets->left_path_entry->signal_activate().connect(sigc::mem_fun(*this, &BasicSignalsAccess::on_activate_left_path_entry));
		widgets->right_path_entry->signal_activate().connect(sigc::mem_fun(*this, &BasicSignalsAccess::on_activate_right_path_entry));
		widgets->copy_button->signal_clicked().connect(sigc::mem_fun(*this,&BasicSignalsAccess::on_clicked_copy_button));
		widgets->move_button->signal_clicked().connect(sigc::mem_fun(*this,&BasicSignalsAccess::on_clicked_move_button));
		widgets->delete_button->signal_clicked().connect(sigc::mem_fun(*this,&BasicSignalsAccess::on_clicked_delete_button));
		widgets->left_command_button->signal_clicked().connect(sigc::mem_fun(*this,&BasicSignalsAccess::on_clicked_left_command_button));
		widgets->right_command_button->signal_clicked().connect(sigc::mem_fun(*this,&BasicSignalsAccess::on_clicked_right_command_button));
		
	}
	

	void BasicSignalsAccess::on_clicked_left_command_button(){
		shell_usage::run_command(widgets->left_command_entry->get_text(),widgets->left_command_view->get_buffer(),widgets->left_path_entry->get_text());
		on_activate_left_path_entry();
	};
	void BasicSignalsAccess::on_clicked_right_command_button(){
		shell_usage::run_command(widgets->right_command_entry->get_text(),widgets->right_command_view->get_buffer(),widgets->right_path_entry->get_text());
		on_activate_right_path_entry();
	};
	
	
	
	BasicSignalsAccess::~BasicSignalsAccess(){
		
	}
	
	void BasicSignalsAccess::create_new_left_tree_model(){
		widgets->left_tree_model= Gtk::ListStore::create(widgets->model_columns_left);
		widgets->left_tree_view->set_model(widgets->left_tree_model);
		
		widgets->left_tree_view->append_column("Type", widgets->model_columns_left.entry_type);
		widgets->left_tree_view->append_column("Name", widgets->model_columns_left.entry_name);
		widgets->left_tree_view->append_column("Permissions", widgets->model_columns_left.permissions);
		widgets->left_tree_view->append_column("Modification", widgets->model_columns_left.modification_time);
		widgets->left_tree_view->append_column("nlinks", widgets->model_columns_left.nlinks);
		widgets->left_tree_view->append_column("uid", widgets->model_columns_left.uid);
		widgets->left_tree_view->append_column("gid", widgets->model_columns_left.gid);
		Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->widgets->left_tree_view->get_selection();
		refTreeSelection->set_mode(Gtk::SELECTION_MULTIPLE);
		Gtk::TreeView::Column* column = this->widgets->left_tree_view->get_column(1);
		if(column){
			column->set_sort_column(this->widgets->model_columns_left.entry_type);
			column->set_sort_column(this->widgets->model_columns_left.entry_name);
		}
	}
	
	void BasicSignalsAccess::on_activate_left_path_entry(){
		for(auto i:data->left_entries){
			delete i.second;
			i.second=nullptr;
		}
		data->left_entries.clear();
		create_new_left_tree_model();
		FilesystemManagement::FILESYSTEM_ENTRY_TYPE *list=new FilesystemManagement::FILESYSTEM_ENTRY_TYPE(static_cast<std::string>(data->get_left_path()));
		for(FilesystemManagement::FILESYSTEM_ENTRY_TYPE* child:*list->get_children()){
			Gtk::TreeModel::Row row = *(this->widgets->left_tree_model->append());
			row[this->widgets->model_columns_left.entry_type] = child->get_filesystem_entry_type();
			row[this->widgets->model_columns_left.entry_name] = child->get_name();
			row[this->widgets->model_columns_left.permissions] = child->get_permissions();
			row[this->widgets->model_columns_left.modification_time] = child->get_modification_time();
			row[this->widgets->model_columns_left.nlinks]= child->get_nlinks();
			row[this->widgets->model_columns_left.uid]= child->get_uid();
			row[this->widgets->model_columns_left.gid]= child->get_gid();
			this->widgets->left_tree_view->show_all();
			
			
			std::string filesystem_entry_type=child->get_filesystem_entry_type();
			if(filesystem_entry_type=="file"){
				data->left_entries.insert(std::pair<std::string,FilesystemEntry*>(child->get_name(),new FileType(child)));
			}else if(filesystem_entry_type=="directory"){
				data->left_entries.insert(std::pair<std::string,FilesystemEntry*>(child->get_name(),new DirectoryType(child)));
			}else{
				data->left_entries.insert(std::pair<std::string,FilesystemEntry*>(child->get_name(),new OtherType(child)));
			}
			
			delete child;
		}
		delete list;
	}

	void BasicSignalsAccess::create_new_right_tree_model(){
		widgets->right_tree_model= Gtk::ListStore::create(widgets->model_columns_right);
		widgets->right_tree_view->set_model(widgets->right_tree_model);
		
		widgets->right_tree_view->append_column("Type", widgets->model_columns_right.entry_type);
		widgets->right_tree_view->append_column("Name", widgets->model_columns_right.entry_name);
		widgets->right_tree_view->append_column("Permissions", widgets->model_columns_right.permissions);
		widgets->right_tree_view->append_column("Modification", widgets->model_columns_right.modification_time);
		widgets->right_tree_view->append_column("nlinks", widgets->model_columns_right.nlinks);
		widgets->right_tree_view->append_column("uid", widgets->model_columns_right.uid);
		widgets->right_tree_view->append_column("gid", widgets->model_columns_right.gid);
		Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->widgets->right_tree_view->get_selection();
		refTreeSelection->set_mode(Gtk::SELECTION_MULTIPLE);
		Gtk::TreeView::Column* column = this->widgets->right_tree_view->get_column(1);
		if(column){
			column->set_sort_column(this->widgets->model_columns_right.entry_type);
			column->set_sort_column(this->widgets->model_columns_right.entry_name);
		}
	}
	
	void BasicSignalsAccess::on_activate_right_path_entry(){
		for(auto i:data->right_entries){
			delete i.second;
			i.second=nullptr;
		}
		data->right_entries.clear();
		create_new_right_tree_model();
		FilesystemManagement::FILESYSTEM_ENTRY_TYPE *list=new FilesystemManagement::FILESYSTEM_ENTRY_TYPE(static_cast<std::string>(data->get_right_path()));
		for(FilesystemManagement::FILESYSTEM_ENTRY_TYPE* child:*list->get_children()){
			Gtk::TreeModel::Row row = *(this->widgets->right_tree_model->append());
			row[this->widgets->model_columns_right.entry_type] = child->get_filesystem_entry_type();
			row[this->widgets->model_columns_right.entry_name] = child->get_name();
			row[this->widgets->model_columns_right.permissions] = child->get_permissions();
			row[this->widgets->model_columns_right.modification_time] = child->get_modification_time();
			row[this->widgets->model_columns_right.nlinks]= child->get_nlinks();
			row[this->widgets->model_columns_right.uid]= child->get_uid();
			row[this->widgets->model_columns_right.gid]= child->get_gid();

			std::string filesystem_entry_type=child->get_filesystem_entry_type();
			if(filesystem_entry_type=="file"){
				data->right_entries.insert(std::pair<std::string,FilesystemEntry*>(child->get_name(),new FileType(child)));
			}else if(filesystem_entry_type=="directory"){
				data->right_entries.insert(std::pair<std::string,FilesystemEntry*>(child->get_name(),new DirectoryType(child)));
			}else{
				data->right_entries.insert(std::pair<std::string,FilesystemEntry*>(child->get_name(),new OtherType(child)));
			}
			
			delete child;
		}
		delete list;
		this->widgets->right_tree_view->show_all();
	}

	void BasicSignalsAccess::on_clicked_copy_button(){
		Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->widgets->right_tree_view->get_selection();
		refTreeSelection->selected_foreach_iter(sigc::mem_fun(*this, &BasicSignalsAccess::copy_from_right) );
		refTreeSelection = this->widgets->left_tree_view->get_selection();
		refTreeSelection->selected_foreach_iter(sigc::mem_fun(*this, &BasicSignalsAccess::copy_from_left) );
		on_activate_right_path_entry();
		on_activate_left_path_entry();
	
	}
	void BasicSignalsAccess::copy_from_left(const Gtk::TreeModel::iterator& iter){
		Gtk::TreeModel::Row row = *iter;
		std::string dir = data->get_right_path();
		
		std::stringstream id;
		id<<row[widgets->model_columns_right.entry_name];
		data->left_entries[id.str()]->copy(data->get_right_path());
		//system(("cp "+dir+(dir.at(dir.length()-1)=='/'?"":"/")+row[widgets->model_columns_right.entry_name]+" "+data->get_right_path()).c_str());
	}
	void BasicSignalsAccess::copy_from_right(const Gtk::TreeModel::iterator& iter){
		Gtk::TreeModel::Row row = *iter;
		std::stringstream id;
		id<<row[widgets->model_columns_right.entry_name];
		data->right_entries[id.str()]->copy(data->get_left_path());
		//system(("cp "+dir+(dir.at(dir.length()-1)=='/'?"":"/")+row[widgets->model_columns_right.entry_name]+" "+data->get_left_path()).c_str());
	}
	




	void BasicSignalsAccess::on_clicked_move_button(){
		Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->widgets->right_tree_view->get_selection();
		refTreeSelection->selected_foreach_iter(sigc::mem_fun(*this, &BasicSignalsAccess::move_from_right) );
		refTreeSelection = this->widgets->left_tree_view->get_selection();
		refTreeSelection->selected_foreach_iter(sigc::mem_fun(*this, &BasicSignalsAccess::move_from_left) );
		on_activate_right_path_entry();
		on_activate_left_path_entry();
	}
	void BasicSignalsAccess::move_from_left(const Gtk::TreeModel::iterator& iter){
		Gtk::TreeModel::Row row = *iter;
		//std::string dir = data->get_left_path();
		
		std::stringstream id;
		id<<row[widgets->model_columns_right.entry_name];
		data->left_entries[id.str()]->move(data->get_right_path());
		
		//system(("mv "+dir+(dir.at(dir.length()-1)=='/'?"":"/")+row[widgets->model_columns_left.entry_name]+" "+data->get_right_path()).c_str());
	}
	void BasicSignalsAccess::move_from_right(const Gtk::TreeModel::iterator& iter){
		Gtk::TreeModel::Row row = *iter;
		//std::string dir = data->get_right_path();
		
		std::stringstream id;
		id<<row[widgets->model_columns_right.entry_name];
		data->right_entries[id.str()]->move(data->get_left_path());
		//system(("mv "+dir+(dir.at(dir.length()-1)=='/'?"":"/")+row[widgets->model_columns_right.entry_name]+" "+data->get_left_path()).c_str());

	}




	void BasicSignalsAccess::on_clicked_delete_button(){
		Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->widgets->right_tree_view->get_selection();
		refTreeSelection->selected_foreach_iter(sigc::mem_fun(*this, &BasicSignalsAccess::delete_from_right) );
		refTreeSelection = this->widgets->left_tree_view->get_selection();
		refTreeSelection->selected_foreach_iter(sigc::mem_fun(*this, &BasicSignalsAccess::delete_from_left) );
		on_activate_right_path_entry();
		on_activate_left_path_entry();
	}
	void BasicSignalsAccess::delete_from_left(const Gtk::TreeModel::iterator& iter){
		Gtk::TreeModel::Row row = *iter;
		
		std::stringstream id;
		id<<row[widgets->model_columns_left.entry_name];
		data->left_entries[id.str()]->del();
		
		/*std::stringstream buffer;
		std::string dir = data->get_left_path();
		buffer<<"rm "<<dir<<(dir.at(dir.length()-1)=='/'?"":"/")<<row[widgets->model_columns_left.entry_name];
		system(buffer.str().c_str());*/
	}
	void BasicSignalsAccess::delete_from_right(const Gtk::TreeModel::iterator& iter){
		Gtk::TreeModel::Row row = *iter;
		
		std::stringstream id;
		id<<row[widgets->model_columns_right.entry_name];
		data->right_entries[id.str()]->del();
		
		/*std::stringstream buffer;
		std::string dir = data->get_right_path();
		buffer<<"rm "<<dir<<(dir.at(dir.length()-1)=='/'?"":"/")<<row[widgets->model_columns_right.entry_name];
		system(buffer.str().c_str());*/
	}
