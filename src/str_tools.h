#ifndef STR_TOOLS_H
#define STR_TOOLS_H
#include <string>
#include <vector>
namespace stool{
    std::string trim(std::string str);
	std::vector<std::string> split(const std::string& s,const std::string &sep);
    bool isLegalPattern(std::string str);
    std::string getMatchAddr(std::string str);
    unsigned hex2Dec(std::string str);
    std::string dec2Hex(unsigned num);
    std::string getCurSysDate();
    std::string dec2Bin(unsigned num);
}
#endif
