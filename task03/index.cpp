#include "index.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#define LENGHT_OF_NAME 20
#define LENGHT_OF_PATH 50
#ifdef __linux__

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#elif defined(_WIN32)
#include <Windows.h>
#endif

using namespace std;
#ifdef __linux__

vector<file_info *> read_directory(const string &path) {
    DIR *dirp = opendir(path.c_str());
    if (!dirp)
        return vector<file_info *>();

    vector<file_info *> vec;
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
        inf->path = fullpath;
        inf->name = name;
        inf->type = entry->d_type == DT_DIR ? ft_dir : ft_reg;
        inf->size = st.st_size;
        inf->mtime = st.st_mtim.tv_sec;
        vec.push_back(inf);
    }
    closedir(dirp);
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

inline void FileIndexer::print_one(const shared_ptr<file_info> el) {
    time_t lt = el->mtime;
    cout << setw(LENGHT_OF_NAME) << left << \
        (el->name.length() < LENGHT_OF_NAME? el->name : (el->name.substr(0, LENGHT_OF_NAME - 3) + "...")) << \
            setw(10) << el->size << setw(LENGHT_OF_PATH) << \
                (el->path.length() < LENGHT_OF_PATH? el->path : (el->path.substr(0, LENGHT_OF_PATH - 3) + "...")) << \
                    setw(5) << right << (el->type == ft_dir ? "dir" : "reg") << \
                        setw(30) << ctime(&lt);
}


unsigned FileIndexer::Build(const string &Path) {
    unsigned num = 0;
    auto current_dir = read_directory(Path);
    for (auto &d: current_dir) {
        auto new_one = make_shared<file_info>(*d);
        Index.insert(make_pair(Path + "/" + d->name, new_one));
        num++;
        if (d->type == ft_dir)
            Build(Path + "/" + d->name);
        delete d;
    }
    return num;
}

unsigned FileIndexer::Build() { return number = Build(root); }

FileIndexer::~FileIndexer() { Index.clear(); }

bool FileIndexer::MoveFile(const std::string &path, const std::string &new_path) {
    if (Index.find(path) == Index.end())
        return false;
    else
        Index[new_path] = Index[path];
    Index.erase(path);
    return true;
}

bool FileIndexer::DeleteFile(const std::string &path) {
    if (number == 0 || Index.find(path) == Index.end())
        return false;
    else
        Index.erase(path);
    return true;
}

unsigned FileIndexer::FindFiles(const std::string &pattern) {
    unsigned num = 0;
    for (auto &it: Index)
        if (it.first.find(pattern) <= it.first.length()) {
            num++;
            print_one(it.second);
        }
    cout << "matches found: " << num << endl;
    return num;
}

void FileIndexer::PrintFiles() {
    for (auto &it: Index)
        print_one(it.second);
}

void FileIndexer::PrintFilesSorted(FileIndexer::SortingType type) {
    if (type == Name)
        PrintFiles();
    else {
        vector<PAIR> sorting_map;
        for (auto &it: Index)
            sorting_map.push_back(it);
        if (type == Size)
            sort(sorting_map.begin(), sorting_map.end(), cmp_Size);
        else
            sort(sorting_map.begin(), sorting_map.end(), cmp_Time);
        for (auto &it: sorting_map)
            print_one(it.second);
    }
}