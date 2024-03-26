#ifndef PLAY_UTI_H
#define PLAY_UTI_H
#include <iostream>
#include <vector>
namespace  puti{
struct TimeFrame{
    int threadId=0;//线程编号
    unsigned long long timePoint=0;//时间点
    /*
     * 0:访问快表存在, 1:访问快表存在不存在
     * 2:访问页表存在, 3:访问页表不存在
     * 4:缺页
     * 5:访问内存
    */
    int actionType=0;
    int row=0;//替换、增加或访问时，table对应的行数
    int block=0;//对应物理块
    int newPage=0;//新增的页号或访问的页号
    int oldPage=0;//被替换的旧页号

    TimeFrame();
    TimeFrame(const TimeFrame& a);
    TimeFrame(int _id,unsigned long long _time);
    TimeFrame(int _id,unsigned long long _time,int _act);
    void setAct(int _act);
    void setAddOrAcc(int _row,int _block,int _new);
    void setReplace(int _row,int _block,int _new,int _old);
    bool operator < (const TimeFrame& a);
};

struct TimeAxis {
    int threadId;
    std::vector<TimeFrame> frames;

    TimeAxis();
    void setId(int id);
    void addFrame(const TimeFrame& frame);
    void merge(const TimeAxis& a);

    friend std::ostream& operator << (std::ostream& out, TimeAxis& ax);
};
std::ostream& operator << (std::ostream& out, TimeAxis& a);
}

#endif // PLAY_UTI_H
