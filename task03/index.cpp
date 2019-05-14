
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iterator>
#include <ctime>

#include "index.h"

#ifdef __linux__
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#elif defined(_WIN32)
#include <Windows.h>
#endif

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

#ifdef __linux__

vector<file_info*> read_directory(string path)
{
    DIR *dirp = opendir(path.c_str());
    if (!dirp)
    {    
        closedir(dirp);
        return vector<file_info*>();
    }

    vector<file_info*> vec;
    dirent *entry;
    while (entry = readdir(dirp))
    {
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

        if (!inf->type)
        {
            vector<file_info*> vec1 = read_directory(inf->path);
            for(auto &i: vec1)
                vec.push_back(i); 
        }
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

        info->path = path + "/" + name;
        info->name = name;
        info->mtime = fd.ftLastWriteTime.dwLowDateTime;
        info->size = fd.nFileSizeLow | fd.nFileSizeHigh << 32;
        info->type = (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? ft_dir : ft_reg;
        vec.push_back(info);
        
        if (!info->type)
        {
            vector<file_info*> vec1 = read_directory(inf->path);
            for(auto &i: vec1)
                vec.push_back(i); 
        }
    } while (FindNextFile(hFind, &fd));

    FindClose(hFind);
    return vec;
}


#endif

FileIndexer::FileIndexer(const std::string &rootPath): 
    m_root(rootPath)
{}


FileIndexer::~FileIndexer()
{}

unsigned FileIndexer::Build()
{
    vector<file_info*> vec = read_directory(m_root);
    for(auto &i: vec)
    {
        mp[i->path] = shared_ptr<file_info>(i);
    }
    return mp.size();
}

template<typename T>
void PrintMap(T map_to_print)
{    
    unsigned s_size = 0, s_path = 0, s_name = 0, s_time = 24, s_type = 0; 
    for(auto &i: map_to_print)
    {
        string type = to_string(i.second->type);
        string size = to_string(i.second->size);
        if (i.second->path.size() > s_path) s_path = i.second->path.size();
        if (i.second->name.size() > s_name) s_name = i.second->name.size();
        if (size.size() > s_size) s_size = size.size();
        if (type.size() > s_type) s_type = type.size();
    }
    cout << setw(s_name + 4) << "NAME" << setw(s_path + 4) << "PATH" << setw(s_size + 4) << "SIZE" << setw(s_type + 4) << "TYPE" << setw(s_time + 4) << "TIME" << endl;
    cout << endl;
    for(auto &i: map_to_print)
    {
        time_t time = (time_t)i.second->mtime;
        cout << setw(s_name + 4) << i.second->name << setw(s_path + 4) << i.second->path << setw(s_size + 4) << i.second->size << setw(s_type + 4) << i.second->type << setw(s_time + 4) << asctime(localtime(&time));
    }
    cout << endl;
}



void FileIndexer::PrintFiles()
{
    PrintMap<map<string, shared_ptr<file_info>>>(mp);
}

void FileIndexer::PrintFilesSorted(SortingType type)
{
    
    if (type == SortingType::Name)
    {
        multimap<string, shared_ptr<file_info>> mp1;
        for(auto &i: mp)
            mp1.insert(pair<string, shared_ptr<file_info>>(i.second->name, i.second));
        PrintMap<multimap<string, shared_ptr<file_info>>>(mp1);
    }
    else if (type == SortingType::Size)
    {
        multimap<uint64_t, shared_ptr<file_info>> mp1;
        for(auto &i: mp)
            mp1.insert(pair<uint64_t, shared_ptr<file_info>>(i.second->size, i.second));
        PrintMap<multimap<uint64_t, shared_ptr<file_info>>>(mp1);
    }
    else if (type == SortingType::Time)
    {
              multimap<uint64_t, shared_ptr<file_info>> mp1;
        for(auto &i: mp)
            mp1.insert(pair<uint64_t, shared_ptr<file_info>>(i.second->mtime, i.second));
        PrintMap<multimap<uint64_t, shared_ptr<file_info>>>(mp1);
    }

}


unsigned FileIndexer::FindFiles(const string &pattern)
{
    map<string, shared_ptr<file_info>> mp1;
    unsigned counter = 0;

    for (auto &i: mp)
    {
        if (i.second->name.find(pattern) != string::npos)
        {
            mp1[i.second->path] = i.second;
            counter++;
        }
    }

    cout << "Found " << counter << " file(s):\n" << endl;

    if (counter)
        PrintMap<map<string, shared_ptr<file_info>>>(mp1);

    return counter;
}


bool FileIndexer::MoveFile(const string &path, const string &new_path)
{
    if (mp.find(path) != mp.end())
    {
        string fullpath = new_path + "/" + mp[path]->name;
        if ((mp.find(path) != mp.end()) && (mp.find(fullpath) == mp.end()) && (mp.find(new_path) != mp.end()))
        {
            if (mp[new_path]->type)
                return false;
            if (!mp[path]->type)
            {    
                if (!fullpath.find(path))
                    return false;

                mp[fullpath] = mp[path];
                mp[fullpath]->path = fullpath;

                for (auto &i: mp)
                {
                    if (!i.first.find(path))
                        MoveFile(path + "/" + i.second->name, fullpath);
                }

                mp.erase(path);
            }
            else
            {
                mp[fullpath] = mp[path];
                mp[fullpath]->path = fullpath;
    
                mp.erase(path);
            }

            return true;
        }
    }
    return false;
}

bool FileIndexer::DeleteFile(const string &path)
{
    if (mp.find(path) != mp.end())
    {
        if (!mp[path]->type)
        {
            for (auto &i: mp)
            {
                if (!i.first.find(path))
                    mp.erase(i.first);
            }
        }
        else
            mp.erase(path);
        return true;
    }
    return false;
}
