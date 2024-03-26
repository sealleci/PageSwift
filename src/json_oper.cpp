#include "json_oper.h"
#include <vector>
#include <string>
#include <fstream>
#include "tinyjson.hpp"

std::string jsop::readFileAsStr(const std::string filePath) {
	std::fstream file;
	file.open(filePath, std::ios::in);

	std::string content = "",line = "";

	while (getline(file, line)) {
		content.append(line);
	}

	file.close();

	return content;
}

std::vector<std::string> jsop::read(const std::string filePath) {
	std::vector<std::string> res;

	tiny::TinyJson json;
	json.ReadJson(readFileAsStr(filePath));

	tiny::xarray seq = json.Get<tiny::xarray>("seq");

	for (int i = 0; i < (int)seq.Count(); ++i) {
		seq.Enter(i);
		res.push_back(seq.Get<std::string>());
	}

	return res;
}
