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
//
//int not_sort_directories(const char* dir)
//{
//	path p(dir);   // p se crea a partir de un const char
//	if (exists(p))
//	{
//		if (is_regular_file(p))
//			cout << p << " size is " << file_size(p) << '\n';
//		else if (is_directory(p))
//		{
//			cout << p << " is a directory containing:\n";
//
//			for (directory_iterator itr(p); itr != directory_iterator(); itr++)
//				cout << itr->path().filename() << endl;
//		}
//	}
//	else
//		cout << p << "No existe\n";
//	getchar();
//	return 0;
//}

//int see_dirContent(const char* dir)
//{
//	path p(dir);
//	if (exists(p))
//	{
//		if (is_regular_file(p))
//			cout << p << "Es un archivo de tamaño " << file_size(p) << '\n';
//		else if (is_directory(p))     // is p a directory?
//		{
//			cout << p << " Es un directorio, que tiene :\n \n";
//			for (directory_iterator itr(p); itr != directory_iterator(); itr++)
//				cout << itr->path().filename() << endl;
//		}
//	}
//	else
//		cout << p << " No existe\n";
//	getchar();
//	return 0;
//}
/*
La funcion copy mueve todos los elementos comprendidos entre directory_iterator() (que devuelve un ITERATOR END)
y directory_iterator(p) que devuelve la carpeta raiz a  ostream_iterator, que se ocupa de transformar a la clase
especificada en <> (TEMPLATE) en algo legible para cout.
*/


//int returnCurrentPath() {
//	cout << "\n";
//	cout << current_path().string();
//	cout << "\n";
//	return 1;
//}

//int copyFile(const char* base, const char* targ) {
//	copy_file(base, targ);
//	return 1;
//}

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

//int createDir(const char* dir) {
//	return create_directory(dir);
//}
#define _CRT_SECURE_NO_WARNINGS
//int seeLastWritten(const char* dir) {
//	char storeDate[32];
//
//	time_t lastTime = last_write_time(dir);
//	tm *readable = localtime(&lastTime);
//
//	strftime(storeDate, 32, "%a, %d.%m.%Y %H:%M:%S", readable);
//	cout << storeDate;
//	return 1;
//}