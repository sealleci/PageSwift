#include "play_uti.h"
#include <iostream>
#include <vector>
#include <algorithm>

puti::TimeFrame::TimeFrame(){}
puti::TimeFrame::TimeFrame(const TimeFrame& a){
    this->threadId=a.threadId;
    this->timePoint=a.timePoint;
    this->actionType=a.actionType;
    this->row=a.row;
    this->block=a.block;
    this->newPage=a.newPage;
    this->oldPage=a.oldPage;
}
puti::TimeFrame::TimeFrame(
        int _id,
        unsigned long long _time):
        threadId(_id),
        timePoint(_time){}
puti::TimeFrame::TimeFrame(
        int _id,
        unsigned long long _time,
        int _act):
        threadId(_id),
        timePoint(_time),
        actionType(_act){}
void puti::TimeFrame::setAct(int _act){
    this->actionType=_act;
}

void puti::TimeFrame::setAddOrAcc(int _row,int _block,int _new){
    this->row=_row;
    this->block=_block;
    this->newPage=_new;
}
void puti::TimeFrame::setReplace(int _row,int _block,int _new,int _old){
    this->row=_row;
    this->block=_block;
    this->newPage=_new;
    this->oldPage=_old;
}
bool puti::TimeFrame::operator < (const puti::TimeFrame& a){
    if(this->timePoint!=a.timePoint){
        return this->timePoint<a.timePoint;
    }else{
          return this->threadId<a.threadId;
    }
}

puti::TimeAxis::TimeAxis(){}
void puti::TimeAxis::setId(int id){
    this->threadId=id;
}
void puti::TimeAxis::addFrame(const TimeFrame& frame){
    this->frames.push_back(frame);
}
void puti::TimeAxis::merge(const puti::TimeAxis& a){
    this->frames.resize(a.frames.size()+this->frames.size());
    std::merge(a.frames.begin(),a.frames.end(),
               this->frames.begin(),this->frames.end(),
               this->frames.begin());
}

std::ostream& puti::operator << (std::ostream& out, puti::TimeAxis& a) {
    for(auto e:a.frames){
        out<<"["<<
             "tid:"<<e.threadId<<
             ", "<<
             "time_p:"<<e.timePoint<<
             ", ";

        switch (e.actionType) {
        case 0:
            out<<"acs tlb:("<<
                 e.newPage<<
                 ", "<<
                 e.block<<
                 ")";
            break;
        case 1:
            out<<"acs_err tlb:("<<
                 e.newPage<<
                 ", -"<<
                 ")";
            break;
        case 2:
            out<<"acs page_tbl:("<<
                 e.newPage<<
                 ", "<<
                 e.block<<
                 ")";
            break;
        case 3:
            out<<"acs_err page_tbl:("<<
                 e.newPage<<
                 ", -"<<
                 ")";
            break;
        case 4:
            out<<"intprt";
            break;
        case 5:
            out<<"acs mem:("<<
                 e.newPage<<
                 ", "<<
                 e.block<<
                 ")";
            break;
        default:
            break;
        }
        out<<"]"<<std::endl;
    }
    return out;
}
