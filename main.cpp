#include <gtkmm.h>
#include <iostream>
#include "BasicDataAccess.h"
#include "BasicWidgetsAccess.h"
#include "BasicSignalsAccess.h"

int main (int argc, char **argv)
{
  auto app = Gtk::Application::create(argc, argv, "File manager");

  auto refBuilder = Gtk::Builder::create();
 
  try
  {
    refBuilder->add_from_file("./GUI/main.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }
  Gtk::Window *main_window;
  refBuilder->get_widget("main_window", main_window);
  BasicWidgetsAccess widgets_wrapper(refBuilder);
  BasicDataAccess data_wrapper(&widgets_wrapper);
  BasicSignalsAccess signals_wrapper(&widgets_wrapper,&data_wrapper);
  app->run(*main_window);
 
  delete main_window;
 
  return 0;
}
