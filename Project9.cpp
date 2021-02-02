#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>
#include <ctime>

int main(int argc, const char** argv)
{	
	using std::chrono::system_clock;
	std::string path = argv[1];
	std::filesystem::path directoryPath(path);
	uint32_t counter = 0;
	uintmax_t totalSize = 0;

	std::cout << "Directory of " << path << std::endl << std::endl;

	for (auto& p : std::filesystem::directory_iterator(directoryPath)) {

		const auto& ftime = std::filesystem::last_write_time(p);
		auto stime = std::chrono::time_point_cast<system_clock::duration>(ftime - std::filesystem::file_time_type::clock::now()
			+ system_clock::now());
		std::time_t cftime = std::chrono::system_clock::to_time_t(stime);

		if (std::filesystem::is_directory(p)) {			 
			 std::cout << std::asctime(std::localtime(&cftime)) << " " << std::filesystem::file_size(p) 
				 << " " << "<DIR> " << p.path().filename().string() << std::endl;
		}

		else {
			++counter;
			totalSize += std::filesystem::file_size(p);
			std::cout << std::asctime(std::localtime(&cftime)) << " " << std::filesystem::file_size(p) 
				<< " " << p.path().filename().string() << std::endl;
		}
	}
	std::cout << counter << " File(s)" << "   " << totalSize << " bytes" << std::endl;
}