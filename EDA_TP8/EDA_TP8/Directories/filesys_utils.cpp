#include "filesystem_header.h"
int check_existance(const char* file)
{
	path p(file); //Constructor de path. lleva un const char.
	if (exists(p))
	{
		if (is_regular_file(p))
			cout << p << " existe y su tamaño es " << file_size(p) << '\n';
		else if (is_directory(p))
			cout << p << " Es un directorio!\n";
		else
			cout << p << "Es un dispositivo Pipe o un Socket. En windows, capaz la lectora de CDs\n";
		return 1;
	}
	else
		cout << p << " No existe\n";
	return 0;
}

vector<string> listall(path p, bool mode_) {
	directory_iterator end_itr;
	vector<string> found;
	// cycle through the directory
	for (directory_iterator itr(p); itr != end_itr; ++itr) {
		// If it's not a directory, list it. If you want to list directories too, just remove this check.
		if (is_regular_file(itr->path())) {
			// assign current file name to current_file and echo it out to the console.
			string current_file = itr->path().string();
			if (current_file.size() >= 5) {
				if (!strcmp(&current_file[current_file.size() - 4], mode_ == COMPRESS ? DECOMPEXTENSION : COMPEXTENSION)) {
					found.push_back(current_file);
					path aux(current_file);
				}
			}
		}
	}
	return found;
}