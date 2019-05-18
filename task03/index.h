#include <string>
#include <map>
#include <memory>
#include <utility>
#include <map>

enum file_type {
    ft_dir,
    ft_reg,
};

struct file_info {
    std::string name;
    std::string path;
    file_type type;
    uint64_t size;
    uint64_t mtime;
};

#define MAX_NAME_LENGTH 70
#define MAX_PATH_LENGTH 120
#define TYPE_LENGTH 9
#define SIZE_LENGTH 7
//#define TIME_LENGTH 25

static std::map<int, char> SIPrefix = {{0, ' '}, {1, 'K'}, {2, 'M'}, {3, 'G'}, {4, 'T'}, {5, 'P'}, {6, 'E'}};

class FileIndexer {
public:
    FileIndexer(const std::string &rootPath);
    ~FileIndexer() = default;

    unsigned Build();

    enum SortingType {
        Name,
        Size,
        Time,
    };

    void PrintFiles() const;
    void PrintFilesSorted(SortingType type) const;
    unsigned FindFiles(const std::string &pattern) const;
    bool MoveFile(const std::string &path, const std::string &new_path);
    bool DeleteFile(const std::string &path);

private:
    const std::string root_path_;
    std::map<std::string, std::shared_ptr<file_info>> indices_;
    unsigned long name_length_ = 0;
    unsigned long path_length_ = 0;

    unsigned BuildIndex(const std::string& dir);
    void UpdateNameLength ();
    void UpdatePathLength ();
    void PrintElement (const std::shared_ptr<file_info> file) const;
};
