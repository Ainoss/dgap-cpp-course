#pragma once

#include <map>
#include <vector>
#include <Windows.h>
#include <fileapi.h>
#include <sys/stat.h>
#include <memory>
#include <string>

using namespace std;

enum file_type
{
	ft_dir,
	ft_reg,
};

struct file_info
{
	string name;
	string path;
	file_type type;
	uint64_t size;
	uint64_t mtime;
};

vector<file_info*> read_directory(string path);

class FileIndexer
{
public:
	FileIndexer(const std::string& rootPath);
	~FileIndexer() { _base.clear(); }

	unsigned Build();

	enum SortingType {
		Name,
		Size,
		Time,
	};

	void PrintFiles();
	void PrintFilesSorted(SortingType type);

	unsigned FindFiles(const std::string& pattern);

	bool MoveFile_(const std::string& path, const std::string& new_path);

	bool DeleteFile_(const std::string& path);

	void BuildIn(const string& root, int& count);
private:
	map<string, shared_ptr<file_info>> _base;
	string _root;
	int _size_name, _size_path;
};

