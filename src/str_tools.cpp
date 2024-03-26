#include "str_tools.h"
#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include <chrono>
#include <algorithm>
#include <bitset>

std::string stool::trim(std::string str){
	std::string::size_type head=0,tail=str.length()-1;

	for(int i=0;i<(int)str.length();++i){
		if(str[i]!=' '&&str[i]!='\t'){
			head=i;
			break;
		}
	}

	for(int i=(int)str.length()-1;i>=0;--i){
		if(str[i]!=' '&&str[i]!='\t'){
			tail=i;
			break;
		}
	}

	return str.substr(head,tail-head+1);
}

std::vector<std::string> stool::split(const std::string& s,const std::string &sep)
{
	std::vector<std::string> result;
	std::string::size_type pos1,pos2;
	pos2=s.find(sep);
	pos1=0;
	while(std::string::npos!=pos2)
	{
		result.push_back(s.substr(pos1,pos2-pos1));
		pos1=pos2+sep.size();
		pos2=s.find(sep,pos1);
	}
	if(pos1!=s.length())
		result.push_back(s.substr(pos1));
	return result;
}

bool stool::isLegalPattern(std::string str){
    std::regex addrReg("([0-9A-Fa-f]+)[Hh]?");
    return std::regex_match(str,addrReg);
}

std::string stool::getMatchAddr(std::string str){
  std::regex addrReg("([0-9A-Fa-f]+)[Hh]?");
  std::smatch addrMatch;
  if(std::regex_match(str,addrMatch,addrReg)){
  	return addrMatch.str(1);
  }
  else{
  	return "";
  }
}

unsigned stool::hex2Dec(std::string str){
    unsigned res=0;
    std::transform(str.begin(),str.end(),str.begin(),::toupper);
	for(int i=0;i<(int)str.length();++i){
		res<<=4;
		if(str[i]>='0'&&str[i]<='9'){
			res+=str[i]-'0';
		}else{
			res+=str[i]-'A'+10;
		}
	}
	return res;
}

std::string stool::dec2Hex(unsigned num){
	std::string res="00000000";
	unsigned digit=0;
	int index=7;
	while(num!=0){
		digit=num&0xf;
		if(digit<=9){
			res[index]='0'+digit;
		}else{
			res[index]='A'+digit-10;
		}
		index--;
		num>>=4;
	}
	return res;
}

std::string stool::getCurSysDate(){
  time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  struct tm* ptm = localtime(&tt);
  char date[60] = {0};
  sprintf(date, "%02d_%02d",(int)ptm->tm_mon + 1, (int)ptm->tm_mday);
  return std::string(date);
}

std::string stool::dec2Bin(unsigned num){
	return std::bitset<32>(num).to_string();
}
