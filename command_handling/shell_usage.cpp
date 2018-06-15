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

#include "shell_usage.h"
#include <cstdlib>
#include <cstdio>
#include <string>
void shell_usage::run_command(std::string command,Glib::RefPtr<Gtk::TextBuffer> output,std::string path){
	FILE *shell;
	
	shell=popen((std::string("/bin/sh -c \"cd ")+path+std::string(";")+command+std::string("\"")).c_str(),"r");
	char buffer[256];
	while (fgets(buffer, 256, shell) != NULL) {
		output->insert_at_cursor(std::string(buffer));
    }
    pclose(shell);
}
