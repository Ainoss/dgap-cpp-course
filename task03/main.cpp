#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include "index.h"

#pragma warning (disable : 4996)

using namespace std;

vector<string> split(const string& s, char delim) {
	vector<string> elems;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
		elems.push_back(item);
	return elems;
}

int main(int argc, char* argv[])
{
	string root;
	if (argc == 1)
		root = ".";
	else
		root = argv[1];

	FileIndexer index(root);
	index.Build();

	while (1) {
		cout << "> ";
		string line;
		if (!getline(cin, line))
			break;

		vector<string> cmd = split(line, ' ');
		if (cmd.size() == 0)
			continue;
		else if (cmd[0] == "print") {
			if (cmd.size() == 1)
				index.PrintFiles();
			else if (cmd[1] == "name")
				index.PrintFilesSorted(FileIndexer::SortingType::Name);
			else if (cmd[1] == "size")
				index.PrintFilesSorted(FileIndexer::SortingType::Size);
			else if (cmd[1] == "time")
				index.PrintFilesSorted(FileIndexer::SortingType::Time);
		}
		else if (cmd[0] == "find" && cmd.size() == 2) {
			index.FindFiles(cmd[1]);
		}
		else if (cmd[0] == "move" && cmd.size() == 3) {
			if (!index.MoveFile_(cmd[1], cmd[2]))
				cout << "File not found" << endl;
		}
		else if (cmd[0] == "del" && cmd.size() == 2) {
			if (!index.DeleteFile_(cmd[1]))
				cout << "File not found" << endl;
		}
		else if (cmd[0] == "exit")
			break;
		else
			cout << "Incorrect command!" << endl;
	}

	return 0;
}


void FileIndexer::BuildIn(const string& root, int& count) {
	vector<file_info*> buf;
	buf = read_directory(root);
	if (buf.size() == 0)
		return;
	count += buf.size();
	for (auto& i : buf) {
		_base[root + "/" + i->name] = make_shared<file_info>(*i);
		if (i->type == ft_dir)
			BuildIn(root + "/" + i->name, count);
		delete i;
		count++;
	}
}

inline unsigned FileIndexer::Build()
{
	int count = 0;
	BuildIn(_root, count);
	return count;
}

inline void FileIndexer::PrintFiles()
{
	for (auto& i : _base) {
		__time64_t r = i.second->mtime;
		struct tm* t;
		t = gmtime(&r);
		printf("%-50s %-50I64u", i.second->name.c_str(), i.second->size);
		printf("%04i/%02i/%02i %02i:%02i:%02i \n", (t->tm_year), t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	}
}

inline bool FileIndexer::MoveFile_(const std::string & path, const std::string & new_path)
{
	if (_base.find(path) == _base.end())
		return false;
	else
		_base[new_path] = _base[path];
	_base.erase(path);
	return true;
}

inline bool FileIndexer::DeleteFile_(const std::string & path)
{
	if (_base.find(path) == _base.end())
		return false;
	else
		_base.erase(path);
	return true;
}

inline unsigned FileIndexer::FindFiles(const std::string & pattern)
{
	int x = 0;
	for (auto i : _base) {
		if (i.first == pattern) {
			x++;
			cout << i.second->path;
		}
	}
	return x;
}

inline void FileIndexer::PrintFilesSorted(SortingType type)
{
	cout << "dsn" << endl;
	vector <shared_ptr<file_info>> buf;
	for (auto i : _base) {
		buf.push_back(i.second);
	}
	if (type == Name){
		sort(buf.begin(), buf.end(), [](const auto i, const auto j) {
			return (i->name > j->name) ? true : false;
			});
	}
	else if (type == Size) {
		sort(buf.begin(), buf.end(), [](const auto i, const auto j) {
			return (i->size > j->size) ? true : false;
			});
	}
	else if (type == Time) {
		sort(buf.begin(), buf.end(), [](const auto i, const auto j) {
			return (i->mtime > j->mtime) ? true : false;
			});
	}
	for (auto& i : buf) {
		printf("%-50s %-50I64u %I64u\n", i->name.c_str(), i->size, i->mtime);
	}
}