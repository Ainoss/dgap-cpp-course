#include <string>
#include <map>
#include <memory>

enum file_type
{
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

class FileIndexer
{
public:
	FileIndexer(const std::string &rootPath) : m_root(rootPath),
		m_pathLength(0),
		m_nameLength(0) {

	}

	~FileIndexer() = default;

	unsigned Build();

	enum SortingType {
		Name,
		Size,
		Time,
	};

	void PrintFiles();
	void PrintFilesSorted(SortingType type);

	unsigned FindFiles(const std::string &pattern);

	bool MoveFile_(const std::string &path, const std::string &new_path);

	bool DeleteFile_(const std::string &path);

private:
	std::string m_root;
	std::map<std::string, std::shared_ptr<file_info>> m_index;
	unsigned m_pathLength;
	unsigned m_nameLength;
};