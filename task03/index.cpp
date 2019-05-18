#include "index.h"

#include <iostream>
#include <string>
#include <vector>

#ifdef __linux__
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#elif defined(_WIN32)
#include <Windows.h>
#endif

#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

#ifdef __linux__

vector<file_info*> read_directory(const string& path) {
    DIR *dirp = opendir(path.c_str());
    if (!dirp)
        return vector<file_info*>();

    vector<file_info*> vec;
    dirent *entry;
    while (entry = readdir(dirp)) {
        string name = entry->d_name;
        if (name == "." || name == "..")
            continue;
        struct stat st;
        string fullpath = path + "/" + name;
        if (stat(fullpath.c_str(), &st))
            continue; // err

        file_info *inf = new file_info;
        inf->name = name;
        inf->path = fullpath;
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
		file_info *info = new file_info;
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

FileIndexer::FileIndexer(const string& rootPath) :
    root_path_(rootPath) {};

unsigned FileIndexer::BuildIndex (const string& dir) {
    auto raw = read_directory(dir);

    for (const auto& file : raw) {
        indices_[file->path] = shared_ptr<file_info>(file);

        if (file->type == file_type::ft_dir)
            BuildIndex(file->path);
    }
}

void FileIndexer::UpdatePathLength() {
    auto it = max_element(indices_.begin(), indices_.end(),
            [] (const auto& lhs, const auto& rhs){
                return lhs.second->path.size() < rhs.second->path.size();
    });
    path_length_ = it->second->path.size();

    if (path_length_ > MAX_PATH_LENGTH)
        path_length_ = MAX_PATH_LENGTH;
}

void FileIndexer::UpdateNameLength() {
    auto it = max_element(indices_.begin(), indices_.end(),
            [] (const auto& lhs, const auto& rhs){
                return lhs.second->name.size() < rhs.second->name.size();
    });
    name_length_ = it->second->name.size();

    if (name_length_ > MAX_NAME_LENGTH)
        name_length_ = MAX_NAME_LENGTH;
}

unsigned FileIndexer::Build() {
    BuildIndex(root_path_);
    UpdateNameLength();
    UpdatePathLength();
    return static_cast<unsigned int>(indices_.size());
}

void FileIndexer::PrintElement(const shared_ptr<file_info> file) const {
    cout.setf(ios::left);

    cout << setw(static_cast<int>(name_length_));
    if (file->name.size() > MAX_NAME_LENGTH) {
        cout << (file->name.substr(0, MAX_NAME_LENGTH - 3) + "...");
    }
    else {
        cout << file->name;
    }
    cout << " ";

    cout << setw(static_cast<int>(path_length_));
    if (file->path.size() > MAX_PATH_LENGTH) {
        cout << file->path.substr(0, MAX_PATH_LENGTH - 3) + "...";
    }
    else {
        cout << file->path;
    }
    cout << " ";

    cout << setw(TYPE_LENGTH);
    switch(file->type) {
        case file_type::ft_dir :
            cout << "Directory";
            break;
        case file_type::ft_reg :
            cout << "Regular";
            break;
    }
    cout << " ";

    cout << setw(SIZE_LENGTH);
    if (file->type == file_type::ft_reg) {
        ostringstream nice_size("");
        int prefix = 0;
        uint64_t new_size = file->size;

        while (new_size >= 1024) {
            new_size = (new_size >> 10);
            ++prefix;
        }

        if (prefix == 0)
            nice_size << file->size << " ";
        else {
            double value = static_cast<double>(file->size >> (10 * prefix - 10)) / 1024;
            nice_size << fixed << showpoint << setprecision(1) << value << " ";
        }

        nice_size << SIPrefix[prefix];

        cout << nice_size.str();
    }
    else {    // file->type == file_type::ft_dir
        cout << " ";
    }
    cout << " ";

    time_t time = file->mtime;
    cout << ctime(&time);
}

void FileIndexer::PrintFiles() const {
    for (const auto& [path, file] : indices_)
        PrintElement(file);
}

void FileIndexer::PrintFilesSorted(SortingType type) const {
    vector<shared_ptr<file_info>> buffer(indices_.size());
    auto mit = indices_.begin();
    auto vit = buffer.begin();
    while (mit != indices_.end()) {
        *vit = mit->second;
        ++vit;
        ++mit;
    }

    sort(buffer.begin(), buffer.end(),
            [type] (const auto& lhs, const auto& rhs) {
                switch(type) {
                    case SortingType::Name :
                        return lhs->name < rhs->name;
                    case SortingType::Size :
                        return lhs->size < rhs->size;
                    case SortingType::Time :
                        return lhs->mtime < rhs->mtime;
                }
    });

    for (const auto& file : buffer)
        PrintElement(file);
}

unsigned FileIndexer::FindFiles(const string& pattern) const {
    unsigned res = 0u;
    for (const auto& [path, file] : indices_) {
        if (file->path.find(pattern) == string::npos)
            continue;
        ++res;
        PrintElement(file);
    }
    return res;
}

bool FileIndexer::MoveFile(const string& path, const string& new_path) {

    if (indices_.count(path) == 0)
        return false;

    // Проверим, есть ли вообще папка, в которую пытаются отправить файл.
    // Заодно считаем новое название файла (в том же Linux файл переименовывается именно таким образом, с помощью команды mv)
    auto rev_it = find(new_path.rbegin(), new_path.rend(), '/');

    if (rev_it == new_path.rend())
        throw invalid_argument("There must be a slash in the path, at least before the new name of the file");

    auto it = rev_it.base();
    string new_name(it, new_path.end());
    string new_dir(new_path.begin(), prev(it));

    if (indices_.count(new_dir) == 0 && new_dir != ".") // функция read_directory не возвращает в векторе директорию ".", да и в большинстве функций её пришлось бы игонорировать, но здесь не стоит
        return false;
    if (indices_[new_dir]->type != file_type::ft_dir)
        return false;

    indices_[new_path] = indices_[path];
    indices_[new_path]->name = new_name;
    indices_[new_path]->path = new_path;
    indices_.erase(path);
    return true;
}

bool FileIndexer::DeleteFile(const string& path) {
    if (indices_.count(path) == 0)
        return false;
    else {
        switch (indices_[path]->type) {
            case file_type::ft_dir : { // удаляем папку со всем содержимым (папку "." я по понятным причинам удалять не разрешил, так что удаление для неё просто не реализовано
                auto it1 = indices_.lower_bound(path);
                string next_path = path; // далее идёт немного модифицированный upper_bound для нахождения строк по префиксу
                ++next_path[next_path.size() - 1];
                auto it2 = indices_.lower_bound(next_path);
                indices_.erase(it1, it2);
            }
            case file_type::ft_reg :
                indices_.erase(path);
                break;
        }

        UpdateNameLength();
        UpdatePathLength();
        return true;
    }
}