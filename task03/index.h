#pragma once
#include <string>
#include <map>
#include <memory>
#include <dirent.h>
#include <sstream>
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
typedef pair <string, shared_ptr<file_info>> PAIR;




class FileIndexer
{
public:
    explicit FileIndexer(const string &rootPath):
    root (rootPath),
    number (0)
    {};
    ~FileIndexer();

    /*
     * Build deep file index starting from root dir.
     * Put info about files into map: "Full path" -> file_info.
     * Store file_info as shared_ptr. Do not use pure pointers inside this class.
     * Return number of files found.
     */
    unsigned Build();
    unsigned Build(const string &Path);

    enum SortingType {
        Name,
        Size,
        Time,
    };

    static bool cmp_Size (const PAIR &T1, const PAIR &T2){
        return T1.second->size < T2.second->size;
    }
    static bool cmp_Time (const PAIR &T1, const PAIR &T2){
        return T1.second->mtime > T2.second->mtime;

    }

    /*
     * Print file list to cout unsorted/sorted.
     * Use table-view to print all info about files.
     */
    void PrintFiles();
    void PrintFilesSorted(SortingType type);

    /*
     * Find file paths by pattern and print them unsorted.
     * Return number of found files.
     */
    unsigned FindFiles(const std::string &pattern);

    /* 
     * Move file selected by path.
     * Return status: success or fail.
     */
    bool MoveFile(const std::string &path, const std::string &new_path);

    /* 
     * Delete file selected by path.
     * Return status: success or fail.
     */
    bool DeleteFile(const std::string &path);

    void print_one (shared_ptr<file_info> el);


private:
    map<string, shared_ptr<file_info> > Index;
    const string root;
    unsigned number;
};

