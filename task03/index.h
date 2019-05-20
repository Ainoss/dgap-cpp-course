
#include <string>
#include <map>
#include <memory>

enum file_type
{
    ft_dir,
    ft_reg,
};

struct file_info
{
    std::string name;
    std::string path;
    file_type type;
    uint64_t size;
    uint64_t mtime;
};
typedef std::shared_ptr<file_info> FileInfoPointer;
typedef std::map<std::string, FileInfoPointer> FileInfoMap;

class FileIndexer
{
public:
    FileIndexer(const std::string &rootPath);

    ~FileIndexer();

    /*
     * Build deep file index starting from root dir.
     * Put info about files into map: "Full path" -> file_info.
     * Store file_info as shared_ptr. Do not use pure pointers inside this class.
     * Return number of files found.
     */
    unsigned Build();

    enum SortingType
    {
        Name,
        Size,
        Time,
    };

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
    bool MoveFileFi(const std::string &path, const std::string &new_path);

    /*
     * Delete file selected by path.
     * Return status: success or fail.
     */
    bool DeleteFileFi(const std::string &path);

private:
    static bool SortByName(FileInfoPointer const &a, FileInfoPointer const &b);

    static bool SortBySize(FileInfoPointer const &a, FileInfoPointer const &b);

    static bool SortByTime(FileInfoPointer const &a, FileInfoPointer const &b);

    static bool IsStringContains(const std::string &str, const std::string &pattern);

    void PrintFileInfo(const FileInfoPointer info);

    void BuildInternal(const std::string &path);

    const char separator = ' ';
    const int nameWidth = 80;
    const int numWidth = 8;

    std::string m_sRootPath;
    FileInfoMap m_FileInfoMap;
};