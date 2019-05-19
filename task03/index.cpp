
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

#ifdef __linux__
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#elif defined(_WIN32)

#include <Windows.h>

#endif

#include "index.h"

using namespace std;

#ifdef __linux__

vector<file_info*> read_directory(string path)
{
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

vector<file_info *> read_directory(string basePath)
{
    string path = basePath + "/*";
    WIN32_FIND_DATA fd;
    HANDLE hFind = FindFirstFile(path.c_str(), &fd);
    if (hFind == INVALID_HANDLE_VALUE)
        return vector<file_info *>();

    vector<file_info *> vec;
    do {
        file_info *info = new file_info;
        string name = fd.cFileName;
        if (name == "." || name == "..")
            continue;

        info->path = basePath + "/" + name;
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

FileIndexer::FileIndexer(const std::string &rootPath)
{
    m_FileInfoMap.clear();
    m_sRootPath = rootPath;
}

FileIndexer::~FileIndexer() {}

unsigned FileIndexer::Build()
{
    BuildInternal(m_sRootPath);
    return m_FileInfoMap.size();
}

void FileIndexer::PrintFiles()
{
    for (auto it = m_FileInfoMap.begin(); it != m_FileInfoMap.end(); ++it)
    {
        PrintFileInfo(it->second);
    }
}

void FileIndexer::PrintFilesSorted(SortingType type)
{
    std::vector<FileInfoPointer> vec;
    for (auto it = m_FileInfoMap.begin(); it != m_FileInfoMap.end(); ++it)
    {
        vec.push_back(it->second);
    }

    switch (type)
    {
        case Name:
            std::sort(vec.begin(), vec.end(), SortByName);
            break;
        case Size:
            std::sort(vec.begin(), vec.end(), SortBySize);
            break;
        case Time:
            std::sort(vec.begin(), vec.end(), SortByTime);
            break;
        default:
            break;
    }

    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        PrintFileInfo(*it);
    }
}

unsigned FileIndexer::FindFiles(const std::string &pattern)
{
    for (auto it = m_FileInfoMap.begin(); it != m_FileInfoMap.end(); ++it)
    {
        if (IsStringContains(it->first, pattern))
        {
            PrintFileInfo(it->second);
        }
    }

    return 0;
}

bool FileIndexer::MoveFileFi(const std::string &path, const std::string &new_path)
{
    if (m_FileInfoMap.find(path) == m_FileInfoMap.end())
    {
        return false;
    }

    if (std::rename(path.c_str(), new_path.c_str()))
    {
        return false;
    }

    auto it = m_FileInfoMap.find(path);
    it->second.get()->path = new_path;
    m_FileInfoMap[new_path] = it->second;
    m_FileInfoMap.erase(path);
    return true;
}

bool FileIndexer::DeleteFileFi(const std::string &path)
{
    if (m_FileInfoMap.find(path) == m_FileInfoMap.end())
    {
        return false;
    }

    if (std::remove(path.c_str()))
    {
        return false;
    }

    m_FileInfoMap.erase(path);
    return true;
}

bool FileIndexer::SortByName(FileInfoPointer const &a, FileInfoPointer const &b)
{
    return (a.get()->type == ft_dir && b.get()->type == ft_reg)
           || a.get()->name < b.get()->name;
}

bool FileIndexer::SortBySize(FileInfoPointer const &a, FileInfoPointer const &b)
{
    return (a.get()->type == ft_dir && b.get()->type == ft_reg)
           || a.get()->size < b.get()->size;
}

bool FileIndexer::SortByTime(FileInfoPointer const &a, FileInfoPointer const &b)
{
    return (a.get()->type == ft_dir && b.get()->type == ft_reg)
           || a.get()->mtime < b.get()->mtime;
}

bool FileIndexer::IsStringContains(const std::string &str, const std::string &pattern)
{
    return str.find(pattern) != std::string::npos;
}

void FileIndexer::BuildInternal(const std::string &path)
{
    vector<file_info *> vFileInfo = read_directory(path);
    for (int i = 0; i < vFileInfo.size(); ++i)
    {
        FileInfoPointer fileInfo(vFileInfo[i]);
        m_FileInfoMap[fileInfo.get()->path] = fileInfo;
        if (fileInfo.get()->type == ft_dir)
        {
            BuildInternal(fileInfo.get()->path);
        }
    }
}

void FileIndexer::PrintFileInfo(const FileInfoPointer info)
{
    file_info *fi = info.get();

    cout << left << setw(nameWidth) << setfill(separator) << fi->path;
    cout << left << setw(nameWidth) << setfill(separator) << fi->name;
    cout << left << setw(numWidth) << setfill(separator) << (fi->type == ft_dir ? "D" : "F");
    cout << left << setw(numWidth) << setfill(separator) << fi->size;
    cout << left << setw(nameWidth) << setfill(separator) << fi->mtime << endl;
}