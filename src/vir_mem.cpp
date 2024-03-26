#include "vir_mem.h"
#include "play_uti.h"
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <bitset>
#include <algorithm>
#include <chrono>
#include <random>
#include <thread>
#include <mutex>

virm::LogicalAddr::LogicalAddr() {}
virm::LogicalAddr::LogicalAddr(int _page, int _offset) {
	this->page = _page;
	this->offset = _offset;
}
unsigned virm::LogicalAddr::getFullAddr() {
	unsigned addr = 0;
	addr += this->page;
	addr <<= offsetDigits;
	addr += this->offset;
	return addr;
}
std::vector<virm::LogicalAddr> virm::LogicalAddr::genAddrs(int count,unsigned lower,unsigned upper){
    std::vector<virm::LogicalAddr> addrs;
    if(count>0){
        if(lower>upper){
            unsigned swapTmp=lower;
            lower=upper;
            upper=swapTmp;
        }
        addrs.resize(count);
        long long seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::default_random_engine e;
        e.seed(seed);
        std::uniform_int_distribution<unsigned> u(lower, upper);
        unsigned tmpVal=0;
        for(int i=0;i<count;++i){
            tmpVal=u(e);
            addrs[i]=virm::LogicalAddr(
                                tmpVal>>(virm::LogicalAddr::offsetDigits),
                                tmpVal&((unsigned)(1<<virm::LogicalAddr::offsetDigits)-1)
                                );
        }
    }
    return addrs;
}

virm::TableItem::TableItem() {}
virm::TableItem::TableItem(int _page, int _block) {
	this->page = _page;
	this->block = _block;
}
virm::TableItem::TableItem(int _page) {
	this->page = _page;
}
virm::TableItem::TableItem(const TableItem& _item) {
	this->page = _item.page;
	this->block = _item.block;
	this->recency = _item.recency;
	this->usage = _item.usage;
	this->order = _item.order;
}
bool virm::TableItem::isInMem() {
	return this->isInMemFlag;
}
void virm::TableItem::loadIn() {
	this->isInMemFlag = true;
}
void virm::TableItem::swapOut() {
	this->isInMemFlag = false;
}
void virm::TableItem::clear() {
    //this->page=-1;
	this->block = -1;
	this->recency = 0;
	this->usage = 0;
	this->order = 0;
}
bool virm::TableItem::operator == (int num) {
	return this->page == num;
}

virm::PageTable::PageTable() {}
void virm::PageTable::setSize(int _size) {
	this->size = _size;
}
void virm::PageTable::initTable() {
	this->items.resize(this->size);
	for (int i = 0; i < this->size; ++i) {
		this->items[i] = TableItem(i);
	}
}
void virm::PageTable::setAlgoType(int _type) {
	if (_type >= 0 && _type <= 4) {
		this->replAlgoType = _type;
	} else {
		this->replAlgoType = 0;
	}
}
void virm::PageTable::setResidentSize(int _size) {
	this->residentSize = _size;
}
// void setResidentSet(std::vector<int>& _blocks){
// 	this->blocks.assign(_blocks.begin(), _blocks.end());
// }
void virm::PageTable::shift() {
	switch (this->replAlgoType) {
    case 1://LRU
		for (int i = 0; i < this->size; ++i) {
			if (this->items[i].isInMem()) {
				this->items[i].recency >>= 1;
			}
		}
		break;
    case 2://LFU
		for (int i = 0; i < this->size; ++i) {
			if (this->items[i].isInMem()) {
				this->items[i].usage >>= 1;
			}
		}
		break;
	default: break;
	}
}
int virm::PageTable::access(int page, int offset) {
	std::vector<TableItem>::iterator pi = std::find(this->items.begin(), this->items.end(), page);
    //unsigned physicalAddr = 0;
    int tmpBlock=-1;
    offset+=0;
	if (pi != this->items.end() && pi->isInMem()) {
        tmpBlock=pi->block;
//		physicalAddr = pi->block;
//		physicalAddr <<= virm::LogicalAddr::offsetDigits;
        switch (this->replAlgoType) { //更改置换用参数
        case 1://LRU
            pi->recency += 0x80000000;
            break;
        case 2://LFU
            pi->usage += 0x80000000;
            break;
        default: break;
        }
	}
    //physicalAddr += offset;
    return tmpBlock;
}
bool virm::PageTable::search(int page) {
	std::vector<TableItem>::iterator pi = std::find(this->items.begin(), this->items.end(), page);
	if (pi != this->items.end() && pi->isInMem()) {
		return true;
	}
	return false;
}
int virm::PageTable::getBlock(int page) {
	std::vector<TableItem>::iterator pi = std::find(this->items.begin(), this->items.end(), page);
	if (pi != this->items.end() && pi->isInMem()) {
		return pi->block;
	}
	return -1;
}
int virm::PageTable::getPage(int block){
    for(int i=0;i<(int)this->items.size();++i){
        if(this->items[i].block==block){
            return this->items[i].page;
        }
    }
    return -1;
}

int virm::PageTable::update(int page, int step, std::vector<LogicalAddr>& seq, std::vector<int>& blocks) {
    if (this->curLoads < this->residentSize) { //添加
		this->load(page, step, blocks);
		return -1;
    } else { //置换
		return this->replace(page, step, seq);
	}
}
void virm::PageTable::load(int page, int step, std::vector<int>& blocks) {
	std::vector<TableItem>::iterator pi = std::find(this->items.begin(), this->items.end(), page);
	if (pi != this->items.end()) {
		pi->block = blocks[this->curLoads++];
		pi->page = page;
        pi->loadIn();
        switch (this->replAlgoType) { //为新添的页初始化置换用参数
        case 0://FIFO
			pi->order = step;
			break;
        case 1://LRU
			pi->recency = 0;
			break;
        case 2://LFU
			pi->usage = 0;
			break;
		default: break;
		}
	}
}
int virm::PageTable::replace(int page, int step, std::vector<LogicalAddr>& seq) {
	int replPage = 0;
	switch (this->replAlgoType) {
	case 0:
		replPage = this->FIFO(page, step);
		break;
	case 1:
		replPage = this->LRU(page);
		break;
	case 2:
		replPage = this->LFU(page);
		break;
	case 3:
		replPage = this->OPT(page, step, seq);
		break;
	default: break;
	}
	return replPage;
}
int virm::PageTable::FIFO(int page, int step) {
	int minOrd = 0x7fffffff;
	int replIndex = 0;

	for (int i = 0; i < this->size; ++i) {
		if (this->items[i].isInMem()) {
			if (this->items[i].order < minOrd) {
				minOrd = this->items[i].order;
				replIndex = i;
			}
		}
	}

	int replPage = this->items[replIndex].page;
	int curBlock = this->items[replIndex].block;
	this->items[replIndex].swapOut();
	this->items[replIndex].clear();
	std::vector<TableItem>::iterator pi = std::find(this->items.begin(), this->items.end(), page);
    //std::cout<<page<<":"<<(pi!=this->items.end()?"true":"false")<<std::endl;
	if (pi != this->items.end()) {
		pi->page = page;
		pi->block = curBlock;
		pi->loadIn();
		pi->order = step;
	}
	return replPage;
}

int virm::PageTable::LRU(int page) {
	unsigned minRec = 0xffffffff;
	int replIndex = 0;

	for (int i = 0; i < this->size; ++i) {
		if (this->items[i].isInMem()) {
			if (this->items[i].recency < minRec) {
				minRec = this->items[i].recency;
                //std::cout<<this->items[i].page<<":"<<this->items[i].recency<<std::endl;
				replIndex = i;
			}
		}
	}

	int replPage = this->items[replIndex].page;
	int curBlock = this->items[replIndex].block;
	this->items[replIndex].swapOut();
	this->items[replIndex].clear();
	std::vector<TableItem>::iterator pi = std::find(this->items.begin(), this->items.end(), page);
	if (pi != this->items.end()) {
		pi->page = page;
		pi->block = curBlock;
		pi->loadIn();
		pi->recency = 0;
	}
	return replPage;
}

int virm::PageTable::LFU(int page) {
	int min1Cnt = 9;
	unsigned curUsg = 0xffffffff;
	int replIndex = 0;

	unsigned tmpUsg = 0;
	int tmp1Cnt = 0;

	for (int i = 0; i < this->size; ++i) {
		if (this->items[i].isInMem()) {
			tmpUsg = this->items[i].usage;
			tmp1Cnt = 0;
			while (tmpUsg != 0) {
				if (tmpUsg & 1) {
					tmp1Cnt++;
				}
				tmpUsg >>= 1;
			}
            //std::cout<<this->items[i].page<<":"<<std::bitset<32>(this->items[i].usage)<<":"<<tmp1Cnt<<std::endl;
			if (tmp1Cnt < min1Cnt || (tmp1Cnt == min1Cnt && this->items[i].usage < curUsg)) {
				min1Cnt = tmp1Cnt;
				replIndex = i;
				curUsg = this->items[i].usage;
			}
		}
	}

	int replPage = this->items[replIndex].page;
	int curBlock = this->items[replIndex].block;
	this->items[replIndex].swapOut();
	this->items[replIndex].clear();
	std::vector<TableItem>::iterator pi = std::find(this->items.begin(), this->items.end(), page);
	if (pi != this->items.end()) {
		pi->page = page;
		pi->block = curBlock;
		pi->loadIn();
		pi->usage = 0;
	}
	return replPage;
}

int virm::PageTable::OPT(int page, int step, std::vector<LogicalAddr>& seq) {
	typedef struct Triplet {
		int index;
		int page;
		int interval;
		Triplet() {}
		Triplet(int _index, int _page, int _interval) {
			this->index = _index;
			this->page = _page;
			this->interval = _interval;
		}
	} OPTTriplet;
	std::vector<OPTTriplet> tris;
	int tmpInterv = (int)seq.size() + 1;

	for (int i = 0; i < this->size; ++i) {
		if (this->items[i].isInMem()) {
			tmpInterv = (int)seq.size() + 1;
			for (int j = step; j < (int)seq.size(); ++j) {
				if (seq[j].page == this->items[i].page) {
					tmpInterv = j - step;
					break;
				}
			}
			tris.push_back(OPTTriplet(i, this->items[i].page, tmpInterv));
		}
	}
    //从大到小排序
	std::sort(tris.begin(), tris.end(),
	[](OPTTriplet & a, OPTTriplet & b) {
		return a.interval > b.interval;
	});

	int replPage = this->items[tris[0].index].page;
	int curBlock = this->items[tris[0].index].block;
	this->items[tris[0].index].swapOut();
	this->items[tris[0].index].clear();
	std::vector<TableItem>::iterator pi = std::find(this->items.begin(), this->items.end(), page);
	if (pi != this->items.end()) {
		pi->page = page;
		pi->block = curBlock;
		pi->loadIn();
	}
	return replPage;
}
std::string virm::PageTable::toString() {
	typedef std::pair<int, int> OutPair;
	std::vector<OutPair> arr;
	for (int i = 0; i < this->size; ++i) {
		if (this->items[i].isInMem()) {
			arr.push_back(OutPair(this->items[i].page, this->items[i].block));
		}
	}
	sort(arr.begin(), arr.end(),
	[](OutPair & a, OutPair & b) {
		return a.second < b.second;
	});
	std::string s = "[";
	for (int i = 0; i < (int)arr.size(); ++i) {
		if (i != 0) {
			s.append(", ");
		}
		s.append(std::to_string(arr[i].first));
		s.append("-");
		s.append(std::to_string(arr[i].second));
	}
	s.append("]");
	return s;
}

std::ostream& virm::operator << (std::ostream& out, virm::PageTable& p) {
	typedef std::pair<int, int> OutPair;
	std::vector<OutPair> arr;
	for (int i = 0; i < p.size; ++i) {
		if (p.items[i].isInMem()) {
			arr.push_back(OutPair(p.items[i].page, p.items[i].block));
		}
	}
	sort(arr.begin(), arr.end(),
	[](OutPair & a, OutPair & b) {
		return a.second < b.second;
	});
	out << "[";
	for (int i = 0; i < (int)arr.size(); ++i) {
		if (i != 0) {
			out << ", ";
		}
		out << arr[i].first << "-" << arr[i].second;
	}
	out << "]";
	return out;
}

virm::TLB::TLB() {}
virm::TLB::TLB(int _size) {
	this->size = _size;
}
void virm::TLB::setSize(int _size) {
	this->size = _size;
}
void virm::TLB::initTLB() {
	this->items.resize(this->size);
}
int virm::TLB::access(int page, int offset) {
	std::vector<TableItem>::iterator pi = std::find(this->items.begin(), this->items.end(), page);
    //unsigned physicalAddr = 0;
    int block=-1;
    offset+=0;
	if (pi != this->items.end() && pi->isInMem()) {
        block=pi->block;
//		physicalAddr = pi->block;
//		physicalAddr <<= virm::LogicalAddr::offsetDigits;
        pi->recency += 0x80000000;
	}
    //physicalAddr += offset;
    return block;
}
bool virm::TLB::search(int page) {
    std::vector<TableItem>::iterator pi = std::find(this->items.begin(), this->items.end(), page);
    if (pi != this->items.end()) {
        return true;
    }
//    for(auto e:this->items){
//        if(e.page==page){
//            return true;
//        }
//    }
	return false;
}
void virm::TLB::shift() {
	for (int i = 0; i < this->curLoads; ++i) {
		this->items[i].recency >>= 1;
	}
}
int virm::TLB::update(int page, int block) {
    if (this->curLoads < this->size) { //添加
		this->load(page, block);
		return -1;
    } else { //置换
		return this->replace(page, block);
	}
}
void virm::TLB::load(int page, int block) {
    for(int i=0;i<this->curLoads;++i){
        if(this->items[i].block==block){
            this->items[i].page=page;
            return;
        }
    }
	int curIndex = this->curLoads++;
	this->items[curIndex].loadIn();
	this->items[curIndex].page = page;
	this->items[curIndex].block = block;
	this->items[curIndex].recency = 0;
}
int virm::TLB::replace(int page, int block) { //LRU
    for(int i=0;i<this->curLoads;++i){
        if(this->items[i].block==block){
            int tpage=this->items[i].page;
            this->items[i].page=page;
            return tpage;
        }
    }
	unsigned minRec = 0xffffffff;
	int replIndex = 0;

	for (int i = 0; i < this->size; ++i) {
		if (this->items[i].recency < minRec) {
			minRec = this->items[i].recency;
			replIndex = i;
		}
	}

	int replPage = this->items[replIndex].page;
	this->items[replIndex].clear();
	this->items[replIndex].loadIn();
	this->items[replIndex].page = page;
	this->items[replIndex].block = block;
	this->items[replIndex].recency = 0;
	return replPage;
}
std::string virm::TLB::toString() {
	typedef std::pair<int, int> OutPair;
	std::vector<OutPair> arr;
	for (int i = 0; i < this->size; ++i) {
		if (this->items[i].isInMem()) {
			arr.push_back(OutPair(this->items[i].page, this->items[i].block));
		}
	}
	sort(arr.begin(), arr.end(),
	[](OutPair & a, OutPair & b) {
		return a.second < b.second;
	});
	std::string s = "[";
	for (int i = 0; i < (int)arr.size(); ++i) {
		if (i != 0) {
			s.append(", ");
		}
		s.append(std::to_string(arr[i].first));
		s.append("-");
		s.append(std::to_string(arr[i].second));
	}
	s.append("]");
	return s;
}

std::ostream& virm::operator << (std::ostream& out, virm::TLB& tlb) {
	typedef std::pair<int, int> OutPair;
	std::vector<OutPair> arr;
	for (int i = 0; i < tlb.curLoads; ++i) {
		arr.push_back(OutPair(tlb.items[i].page, tlb.items[i].block));
	}
	sort(arr.begin(), arr.end(),
	[](OutPair & a, OutPair & b) {
		return a.second < b.second;
	});
	out << "[";
	for (int i = 0; i < (int)arr.size(); ++i) {
		if (i != 0) {
			out << ", ";
		}
		out << arr[i].first << "-" << arr[i].second;
	}
	out << "]";
	return out;
}


virm::Memory::Memory() {}
void virm::Memory::setSize(int _size) {
	this->size = _size;
}
void virm::Memory::initBlocks() {
	for (int i = 0; i < this->size; ++i) {
		blocks.insert(block_type::value_type(i, 1));
	}
}
bool virm::Memory::isBlockUsable(int block) {
	if (block >= this->size || block < 0)return false;
	block_type::iterator bi = this->blocks.find(block);
	if (bi == blocks.end())return false;
	if (bi->second == 1)return true;
	return false;
}
std::vector<int> virm::Memory::distribute(int count) {
	long long seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine e;
	e.seed(seed);
	std::uniform_int_distribution<int> u(0, this->size - 1);
	std::vector<int> distributed;
	int tmpBlock = 0;

	for (int i = 0; i < count; ++i) {
		while (true) {
			tmpBlock = u(e);
			block_type::iterator bi = this->blocks.find(tmpBlock);
			if (bi != blocks.end() && bi->second == 1) {
				bi->second = 0;
				distributed.push_back(tmpBlock);
				break;
			}
		};
	}
	std::sort(distributed.begin(), distributed.end(), std::less<int>());
	return distributed;
}

virm::SwapSpace::SwapSpace() {}
void virm::SwapSpace::setSize(int _size) {
	this->size = _size;
}
void virm::SwapSpace::initBlocks() {
	for (int i = 0; i < this->size; ++i) {
		blocks.insert(block_type::value_type(i, 1));
	}
}
bool virm::SwapSpace::isBlockUsable(int block) {
	if (block >= this->size || block < 0)return false;
	block_type::iterator bi = this->blocks.find(block);
	if (bi == blocks.end())return false;
	if (bi->second == 1)return true;
	return false;
}
std::vector<int> virm::SwapSpace::distribute(int count) {
	long long seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine e;
	e.seed(seed);
	std::uniform_int_distribution<int> u(0, this->size - 1);
	std::vector<int> distributed;
	int tmpBlock = 0;

	for (int i = 0; i < count; ++i) {
		while (true) {
			tmpBlock = u(e);
			block_type::iterator bi = this->blocks.find(tmpBlock);
			if (bi != blocks.end() && bi->second == 1) {
				bi->second = 0;
				distributed.push_back(tmpBlock);
				break;
			}
		};
	}
	std::sort(distributed.begin(), distributed.end(), std::less<int>());
	return distributed;
}

virm::PCB::PCB() {}
void virm::PCB::setResidentSize(int _size) {
	this->residentSize = _size;
}
void virm::PCB::setResidentSet(std::vector<int> _blocks) {
	this->blocks.assign(_blocks.begin(), _blocks.end());
    this->loadedPages.resize(this->residentSize);
    std::fill(this->loadedPages.begin(),this->loadedPages.end(),-1);
}
void virm::PCB::setPageTable(int _size, int _type) {
	this->pageTable.setSize(_size);
	this->pageTable.setResidentSize(this->residentSize);
	this->pageTable.setAlgoType(_type);
	this->pageTable.initTable();
}
void virm::PCB::setTLB(int _size) {
	this->tlb.setSize(_size);
	this->tlb.initTLB();
}
void virm::PCB::activeTLB() {
	this->isUsingTLBFlag = true;
}
void virm::PCB::deactiveTLB() {
	this->isUsingTLBFlag = false;
}
bool virm::PCB::isUsingTLB() {
	return this->isUsingTLBFlag;
}
int virm::PCB::getRow(int block){
    int row=-1;
    for(int i=0;i<(int)this->blocks.size();++i){
        if(this->blocks[i]==block){
            row=i;
            break;
        }
    }
    return row;
}

virm::VirtualMem::VirtualMem() {}
void virm::VirtualMem::setAccessMemTime(long long _time) {
	this->accessMemTime = nanos(_time);
}
void virm::VirtualMem::setInterruptTime(long long _time) {
	this->interruptTime = nanos(_time);
}
void virm::VirtualMem::setAccessTLBTime(long long _time) {
	this->accessTLBTime = nanos(_time);
}
void virm::VirtualMem::initMem(int count) {
	this->memory.setSize(count);
	this->memory.initBlocks();
}
void virm::VirtualMem::initSwap(int count) {
	this->swapSpace.setSize(count);
	this->swapSpace.initBlocks();
}
std::vector<int> virm::VirtualMem::getDistribMem(int count) {
	return this->memory.distribute(count);
}
std::vector<int> virm::VirtualMem::getDistribSwap(int count) {
	return this->swapSpace.distribute(count);
}

std::mutex virm::ThreadProperty::writeLock;
virm::ThreadProperty::ThreadProperty() {}
void virm::ThreadProperty::setId(int _id) {
	this->id = _id;
}
void virm::ThreadProperty::setSequence(std::vector<LogicalAddr> _seq) {
	this->seq.assign(_seq.begin(), _seq.end());
}
void virm::ThreadProperty::mutexWrite(std::string s) {
    ThreadProperty::writeLock.lock();
	std::cout << s << std::endl;
    ThreadProperty::writeLock.unlock();
}
void virm::ThreadProperty::execute() {
	/*
	快表->页表->缺页->快表->页表
	页表->缺页->页表
	 */
#define prc this->process
#define vms this->virMemSys
#define log(x) std::cout<<x<<std::endl

	for (int i = 0; i < (int)seq.size(); ++i) {
		while (true) {
            //log(i);
            if (prc.isUsingTLB()) { //访问快表
                //std::cout<<prc.tlb<<std::endl;
                puti::TimeFrame tlbf(this->id,this->elapsedTime.count());
                this->elapsedTime += vms.accessTLBTime; //访问快表时间
                //std::cout<<prc.tlb.search(seq[i].page)<<std::endl;
                if (prc.tlb.search(seq[i].page)) { //在快表中访问到
                    tlbf.setAct(0);
                    int tmpBlock=-1;

					prc.tlb.shift();
                    tmpBlock=prc.tlb.access(seq[i].page, seq[i].offset);

                    prc.pageTable.shift();
                    prc.pageTable.access(seq[i].page, seq[i].offset);


                    tlbf.setAddOrAcc(prc.getRow(tmpBlock),tmpBlock,seq[i].page);
                    puti::TimeFrame acm1(this->id,this->elapsedTime.count(),5);
                    acm1.setAddOrAcc(prc.getRow(tmpBlock),tmpBlock,seq[i].page);
                    //this->axis.addFrame(tlbf);
                    //std::cout<<i<<"-"<<"tlb:"<<prc.getRow(tmpBlock)<<","<<tmpBlock<<std::endl;
                    this->axis.addFrame(acm1);

                    this->elapsedTime += vms.accessMemTime; //访问内容时间
					break;
                }else{
                    tlbf.setAct(1);
                    //this->axis.addFrame(tlbf);
                }
			}
            //访问页表
            //std::cout<<prc.pageTable<<std::endl;
            puti::TimeFrame ptbf(this->id,this->elapsedTime.count());
            this->elapsedTime += vms.accessMemTime; //访问页表时间
            if (prc.pageTable.search(seq[i].page)) { //在页表中访问到
                ptbf.setAct(2);
                int tmpBlock2=-1;

				prc.pageTable.shift();
                tmpBlock2=prc.pageTable.access(seq[i].page, seq[i].offset);

                ptbf.setAddOrAcc(prc.getRow(tmpBlock2),tmpBlock2,seq[i].page);
                puti::TimeFrame acm2(this->id,this->elapsedTime.count(),5);
                acm2.setAddOrAcc(prc.getRow(tmpBlock2),tmpBlock2,seq[i].page);
                //this->axis.addFrame(ptbf);
                //std::cout<<i<<"-"<<"pb:"<<prc.getRow(tmpBlock2)<<","<<tmpBlock2<<std::endl;
                this->axis.addFrame(acm2);

                this->elapsedTime += vms.accessMemTime; //访问内容时间
                //this->mutexWrite("t"+std::to_string(this->id)+": "+prc.pageTable.toString());

                if (prc.isUsingTLB()) { //更新快表
					prc.tlb.update(seq[i].page, prc.pageTable.getBlock(seq[i].page));
				}
				break;
            }else{
                ptbf.setAct(3);
                //this->axis.addFrame(ptbf);
            }
            //缺页处理
            puti::TimeFrame intf(this->id,this->elapsedTime.count(),4);
            prc.pageTable.update(seq[i].page, i, seq, prc.blocks); //更新页表

            if (prc.isUsingTLB()) { //更新快表
                prc.tlb.update(seq[i].page, prc.pageTable.getBlock(seq[i].page));
			}
            this->elapsedTime += vms.interruptTime; //缺页处理时间
		}
	}
}
