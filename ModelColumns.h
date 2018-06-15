
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    {
		add(entry_type);
		add(entry_name);
		add(permissions);
		add(modification_time);
		add(nlinks);
		add(uid);
		add(gid);
    }

    Gtk::TreeModelColumn<Glib::ustring> entry_type;
    Gtk::TreeModelColumn<Glib::ustring> entry_name;
    Gtk::TreeModelColumn<Glib::ustring> permissions;
    Gtk::TreeModelColumn<Glib::ustring> modification_time;
    Gtk::TreeModelColumn<int> nlinks;
    Gtk::TreeModelColumn<int> uid;
    Gtk::TreeModelColumn<int> gid;
  };
