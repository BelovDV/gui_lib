#include "settings.hpp"

#include <fstream>

Settings::Settings(std::string&& temppath, std::string&& datapath) :
	path_temp_(std::move(temppath)),
	path_data_(std::move(datapath)) {
	std::ifstream in(path_temp_);
	in.read((char*)&data_, sizeof(data_));
}

Settings::~Settings() {
	std::ofstream out(path_temp_);
	out.write((char*)&data_, sizeof(data_));
}
