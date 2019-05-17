#include <iostream>
#include <string>
#include <vector>
#include "index.h"



#ifdef __linux__

vector<file_info*> read_directory(string path)
{
	DIR* dirp = opendir(path.c_str());
	if (!dirp)
		return vector<file_info*>();

	vector<file_info*> vec;
	dirent* entry;
	while (entry = readdir(dirp)) {
		string name = entry->d_name;
		if (name == "." || name == "..")
			continue;
		struct stat st;
		string fullpath = path + "/" + name;
		if (stat(fullpath.c_str(), &st))
			continue; // err

		file_info * inf = new file_info;
		inf->name = name;
		inf->type = entry->d_type == DT_DIR ? ft_dir : ft_reg;
		inf->size = st.st_size;
		inf->mtime = st.st_mtim.tv_sec;
		vec.push_back(inf);
	}
	return vec;
}

#elif defined(_WIN32)

vector<file_info*> read_directory(string path)
{
	path += "/*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(path.c_str(), &fd);
	if (hFind == INVALID_HANDLE_VALUE)
		return vector<file_info*>();

	vector<file_info*> vec;
	do {
		file_info* info = new file_info;
		string name = fd.cFileName;
		if (name == "." || name == "..")
			continue;

		info->name = name;
		info->mtime = fd.ftLastWriteTime.dwLowDateTime;
		info->size = fd.nFileSizeLow | fd.nFileSizeHigh << 32;
		info->type = (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? ft_dir : ft_reg;
		vec.push_back(info);
	} while (FindNextFile(hFind, &fd));

	FindClose(hFind);
	return vec;
}


#endif



FileIndexer::FileIndexer(const std::string& rootPath) :
	_root(rootPath),
	_size_name(0),
	_size_path(0) {};

