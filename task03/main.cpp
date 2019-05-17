#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "index.h"

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
	for (auto i : _base) {
		cout << i.second->name << endl;
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
	//vector <string, shared_ptr<file_info>> buf;
}