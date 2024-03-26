#ifndef JSON_OPER_H
#define JSON_OPER_H
#include <vector>
#include <string>
namespace jsop{
    std::string readFileAsStr(const std::string filePath);
	std::vector<std::string> read(const std::string filePath);
}
#endif
