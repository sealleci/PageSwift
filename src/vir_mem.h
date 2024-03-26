#ifndef VIR_MEM_H
#define VIR_MEM_H
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <mutex>
#include "play_uti.h"
namespace virm {
struct LogicalAddr {
	int page;
	int offset;
	const static int pageDigits = 20;
	const static int offsetDigits = 12;
	LogicalAddr();
	LogicalAddr(int _page, int _offset);
	unsigned getFullAddr();
    static std::vector<LogicalAddr> genAddrs(int count,unsigned lower,unsigned upper);
};

struct TableItem {
    int page=-1;
    int block=-1;
    unsigned recency = 0; //访问频率，比总大小
    unsigned usage = 0; //访问次数，比1的多少
    int order = 0; //到来先后
    bool isInMemFlag = false; //是否在内存里
	TableItem();
	TableItem(int _page, int _block);
    TableItem(int _page);
	TableItem(const TableItem& _item);
	bool isInMem();
	void loadIn();
	void swapOut();
	void clear();
	bool operator == (int num);
};

struct PageTable {
	int size = 100;
	int residentSize = 3;
	int curLoads = 0;
    int replAlgoType = 0; //置换算法类型
	std::vector<TableItem> items;
    //std::vector<int> blocks;//驻留集

	PageTable();
	void setSize(int _size);
	void initTable();
	void setAlgoType(int _type);
	void setResidentSize(int _size);
    // void setResidentSet(std::vector<int>& _blocks){
    // 	this->blocks.assign(_blocks.begin(), _blocks.end());
    // }
	void shift();
    int access(int page, int offset);
	bool search(int page);
	int getBlock(int page);
    int getPage(int block);
	int update(int page, int step, std::vector<LogicalAddr>& seq, std::vector<int>& blocks);
	void load(int page, int step, std::vector<int>& blocks);
	int replace(int page, int step, std::vector<LogicalAddr>& seq);
	int FIFO(int page, int step);
	int LRU(int page);
	int LFU(int page);
	int OPT(int page, int step, std::vector<LogicalAddr>& seq);
    std::string toString();
	friend std::ostream& operator << (std::ostream& out, PageTable& p);
};
std::ostream& operator << (std::ostream& out, PageTable& p);

struct TLB {
	int size = 4;
	int curLoads = 0;
	std::vector<TableItem> items;

	TLB();
	TLB(int _size);
	void setSize(int _size);
	void initTLB();
    int access(int page, int offset);
	bool search(int page);
	void shift();
	int update(int page, int block);
	void load(int page, int block);
	int replace(int page, int block);
    std::string toString();
	friend std::ostream& operator << (std::ostream& out, TLB& tlb);
};
std::ostream& operator << (std::ostream& out, TLB& tlb);

struct Memory {
	int size = 50;
	int blockSize = 1 << 12;
	typedef std::map<int, int> block_type;
    block_type blocks;//1空闲，0占用
	Memory();
	void setSize(int _size);
	void initBlocks();
	bool isBlockUsable(int block);
	std::vector<int> distribute(int count);
};

struct SwapSpace {
	int size = 50;
	int blockSize = 1 << 12;
	typedef std::map<int, int> block_type;
    block_type blocks;//1空闲，0占用
	SwapSpace();
	void setSize(int _size);
	void initBlocks();
	bool isBlockUsable(int block);
	std::vector<int> distribute(int count);
};

struct PCB
{
	int residentSize = 4;
    bool isUsingTLBFlag = true; //是否启用快表
	TLB tlb;
	PageTable pageTable;
    std::vector<int> blocks;//驻留集
    std::vector<int> loadedPages;
	PCB();
	void setResidentSize(int _size);
	void setResidentSet(std::vector<int> _blocks);
	void setPageTable(int _size, int _type);
	void setTLB(int _size);
	void activeTLB();
	void deactiveTLB();
	bool isUsingTLB();
    int getRow(int block);
};

struct VirtualMem {
	typedef std::chrono::nanoseconds nanos;
    nanos accessMemTime = nanos(50); //访问内存时间
    nanos interruptTime = nanos(10000); //中断处理时间
    nanos accessTLBTime = nanos(5); //访问快表时间
    nanos shiftDuration = nanos(100); //位移寄存器的位移间隔
	Memory memory;
	SwapSpace swapSpace;

	VirtualMem();
	void setAccessMemTime(long long _time);
	void setInterruptTime(long long _time);
	void setAccessTLBTime(long long _time);
	void initMem(int count);
	void initSwap(int count);
	std::vector<int> getDistribMem(int count);
	std::vector<int> getDistribSwap(int count);
};

struct ThreadProperty {
	static std::mutex writeLock;
	int id;
	VirtualMem virMemSys;
	PCB process;
    puti::TimeAxis axis;

	typedef std::chrono::nanoseconds nanos;
	nanos elapsedTime = nanos(0);
	std::vector<LogicalAddr> seq;

	ThreadProperty();
	void setId(int _id);
	void setSequence(std::vector<LogicalAddr> _seq);
	void mutexWrite(std::string s);
	void execute();
};
}
#endif
