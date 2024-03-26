#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QButtonGroup>
#include <QTableWidget>
#include <QFileDialog>
#include <QGraphicsOpacityEffect>
#include <QCheckBox>
#include <QComboBox>
#include <QColor>
#include <QTime>
#include <QEventLoop>
#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <math.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <time.h>
#include "vir_mem.h"
#include "str_tools.h"
#include "tinyjson.hpp"
#include "json_oper.h"
#define log(x) std::cout<<x<<std::endl

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("PageSwift");

    dps.resize(thCount+1);
    thLookupTbl.resize(thCount+1);
    rdyThs.resize(thCount+1);

    mainTP.setId(-1);
    mainTP.virMemSys.setAccessMemTime(50);
    mainTP.virMemSys.setAccessTLBTime(5);
    mainTP.virMemSys.setInterruptTime(10000);
    mainTP.virMemSys.initMem(20);
    mainTP.virMemSys.initSwap(20);
    mainTP.process.setResidentSize(3);
    mainTP.process.setResidentSet(mainTP.virMemSys.getDistribMem(mainTP.process.residentSize));

    thBtnGrp=new QButtonGroup();
    thBtnGrp->addButton(ui->addThreadBtn_1,1);
    thBtnGrp->addButton(ui->addThreadBtn_2,2);
    thBtnGrp->addButton(ui->addThreadBtn_3,3);
    thBtnGrp->addButton(ui->addThreadBtn_4,4);
    connect(thBtnGrp,SIGNAL(buttonClicked(int)),this,SLOT(addThreadBtnClicked(int)));

    thCnfBtnGrp=new QButtonGroup();
    connect(thCnfBtnGrp,SIGNAL(buttonClicked(int)),this,SLOT(confirmThreadBtnClicked(int)));
    thStepBtnGrp=new QButtonGroup();
    connect(thStepBtnGrp,SIGNAL(buttonClicked(int)),this,SLOT(stepThreadBtnClicked(int)));
    thPauseBtnGrp=new QButtonGroup();
    connect(thPauseBtnGrp,SIGNAL(buttonClicked(int)),this,SLOT(pauseThreadBtnClicked(int)));
    thPlayBtnGrp=new QButtonGroup();
    connect(thPlayBtnGrp,SIGNAL(buttonClicked(int)),this,SLOT(playThreadBtnClicked(int)));

    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete thBtnGrp;
}

int MainWindow::thLookupBtnId(int thId){
    for(int i=1;i<(int)thLookupTbl.size();++i){
        if(thLookupTbl[i]==thId){
            return i;
        }
    }
    return 0;
}

//std::mutex qmutex;
void MainWindow::DisplayProperty::deal(){
    this->tp.execute();
    //log("comp");
}

void MainWindow::on_residentTxt_editingFinished()
{
    if(mainTP.process.residentSize!=ui->residentTxt->value()){
        std::cout<<ui->residentTxt->value()<<std::endl;
        mainTP.process.setResidentSize(ui->residentTxt->value());
        mainTP.virMemSys.initMem(mainTP.process.residentSize*3/2);
        mainTP.virMemSys.initSwap(mainTP.process.residentSize*3/2);
        mainTP.process.setResidentSet(mainTP.virMemSys.memory.distribute(mainTP.process.residentSize));
    }
}

void MainWindow::on_acMemTimeTxt_editingFinished()
{
    QString text=ui->acMemTimeTxt->text();
    if(!text.isNull()&&!text.isEmpty()){
        mainTP.virMemSys.setAccessMemTime((long long)text.toDouble());
        //std::cout<<mainTP.virMemSys.accessMemTime.count()<<std::endl;
    }
}

void MainWindow::on_acTLBTimeTxt_editingFinished()
{
    QString text=ui->acTLBTimeTxt->text();
    if(!text.isNull()&&!text.isEmpty()){
        mainTP.virMemSys.setAccessTLBTime((long long)text.toDouble());
    }

}

void MainWindow::on_intrptTimeTxt_editingFinished()
{
    QString text=ui->intrptTimeTxt->text();
    if(!text.isNull()&&!text.isEmpty()){
        mainTP.virMemSys.setInterruptTime((long long)text.toDouble());
    }
}


void MainWindow::on_addrManuTxt_textChanged()
{

     std::vector<std::string> strSeq=stool::split(ui->addrManuTxt->toPlainText().toStdString(),",");
     std::vector<virm::LogicalAddr> seq;
     unsigned tmpVal=0;
     for(auto e:strSeq){
        e=stool::trim(e);
        if(stool::isLegalPattern(e)){
            tmpVal=stool::hex2Dec(e);

            seq.push_back(virm::LogicalAddr(
                                tmpVal>>(virm::LogicalAddr::offsetDigits),
                                tmpVal&((unsigned)(1<<virm::LogicalAddr::offsetDigits)-1)
                              )
                          );
        }
     }
     if(seq.size()!=0){
        mainTP.setSequence(seq);
     }
//     std::cout<<"edit"<<std::endl;
//     for(auto e:seq){
//         std::cout<<e.page<<std::endl;
//     }
}

void MainWindow::on_addrCntTxt_editingFinished()
{
    genAddtAttrs.count=ui->addrCntTxt->text().toInt();
}

void MainWindow::on_addrLowLimTxt_editingFinished()
{
    QString text=ui->addrLowLimTxt->text();
    if(!text.isNull()&&!text.isEmpty()){
        if(stool::isLegalPattern(text.toStdString())){
            genAddtAttrs.lower=stool::getMatchAddr(text.toStdString());
        }
    }
}

void MainWindow::on_addrGreatLimTxt_editingFinished()
{
    QString text=ui->addrGreatLimTxt->text();
    if(!text.isNull()&&!text.isEmpty()){
        if(stool::isLegalPattern(text.toStdString())){
            genAddtAttrs.upper=stool::getMatchAddr(text.toStdString());
        }
    }
}

void MainWindow::on_addrGenerBtn_clicked()
{
    if(genAddtAttrs.count>0){
        std::vector<virm::LogicalAddr> addrs =
                virm::LogicalAddr::genAddrs(
                    genAddtAttrs.count,
                    stool::hex2Dec(genAddtAttrs.lower),
                    stool::hex2Dec(genAddtAttrs.upper)
                    );
        mainTP.setSequence(addrs);

        QString text;
        for(int i=0;i<(int)addrs.size();++i){
           if(i!=0){
               text.append(", ");
           }
           text.append(QString::fromStdString(stool::dec2Hex(addrs[i].getFullAddr())));
        }
        ui->addrManuTxt->setText(text);
    }
}

void MainWindow::on_loadFileBtn_clicked()
{
    //生成文件对话框
    QFileDialog* fileDialog=new QFileDialog();
    fileDialog->setWindowTitle(tr("选择文件"));
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(tr("Json(*.json)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    QString fileName;
    if(fileDialog->exec()){
        fileName = fileDialog->selectedFiles()[0];
    }
    //读取.json
    if(!fileName.isEmpty()&&!fileName.isNull()){
        std::vector<std::string> vs=jsop::read(fileName.toStdString());
        QString text;
        for(int i=0;i<(int)vs.size();++i){
           if(i!=0){
               text.append(", ");
           }
           text.append(QString::fromStdString(vs[i]));
        }
        ui->addrManuTxt->setText(text);
//        std::vector<std::string> vs=jsop::read(fileName.toStdString());
//        std::vector<virm::LogicalAddr> seq;
//        unsigned val=0;
//        for(auto e:vs){
//          if(stool::isLegalPattern(e)){
//            val=stool::hex2Dec(stool::getMatchAddr(e));
//            seq.push_back(virm::LogicalAddr(
//                              val>>virm::LogicalAddr::offsetDigits,
//                              val&((unsigned)(1<<virm::LogicalAddr::offsetDigits)-1)
//                              )
//                          );
//          }
//        }
//        //设置
//        if(seq.size()!=0){
//           mainTP.setSequence(seq);
//           QString text;
//           for(int i=0;i<(int)seq.size();++i){
//               if(i!=0){
//                   text.append(",");
//               }
//               text.append(QString::fromStdString(stool::dec2Hex(seq[i].getFullAddr())+"H"));
//           }
//           ui->addrManuTxt->setText(text);
//        }
    }
}

void MainWindow::addThreadBtnClicked(int bid)
{
    if(mainTP.seq.size()<=0)return;
    if(curThCnt<thCount){
        curThCnt++;
        thLookupTbl[bid]=curThCnt;
        int id=thLookupTbl[bid];

        QGroupBox* box1=new QGroupBox(ui->addThreadGrp);
        box1->setObjectName("threadSetGrp_"+QString::number(id));
        box1->setGeometry(
                    thBtnGrp->button(bid)->geometry().x(),
                    thBtnGrp->button(bid)->geometry().y(),
                    thBtnGrp->button(bid)->geometry().width(),
                    thBtnGrp->button(bid)->geometry().height()
                    );

        QGroupBox* box2=new QGroupBox(box1);
        box2->setObjectName("thSetTLBGrp_"+QString::number(id));
        QLabel* label1=new QLabel(box2);
        label1->setText("启用TLB");
        label1->setAlignment(Qt::AlignCenter);
        QCheckBox* chkBox=new QCheckBox(box2);
        chkBox->setObjectName("tlbChkBox_"+QString::number(id));
        chkBox->setChecked(false);
        QHBoxLayout* b2HbLyt=new QHBoxLayout();
        b2HbLyt->addWidget(label1);
        b2HbLyt->addWidget(chkBox);
        box2->setLayout(b2HbLyt);
        box2->setAlignment(Qt::AlignCenter);


        QGroupBox* box3=new QGroupBox(box1);
        box3->setObjectName("thSetAlgGrp_"+QString::number(id));
        QLabel* label2=new QLabel(box3);
        label2->setText("置换算法");
        label2->setAlignment(Qt::AlignCenter);

        QComboBox* cmbBox=new QComboBox(box3);
        cmbBox->setObjectName("algCmbBox_"+QString::number(id));
        cmbBox->addItem("FIFO",0);
        cmbBox->addItem("LRU",1);
        cmbBox->addItem("LFU",2);
        cmbBox->addItem("OPT",3);
        cmbBox->setCurrentIndex(0);
        QHBoxLayout* b3HbLyt=new QHBoxLayout();
        b3HbLyt->addWidget(label2);
        b3HbLyt->addWidget(cmbBox);
        box3->setLayout(b3HbLyt);
        box3->setAlignment(Qt::AlignHCenter);

        QPushButton* button=new QPushButton(box1);
        button->setObjectName("thCnfBtn_"+QString::number(id));
        button->setText("确认");
        thCnfBtnGrp->addButton(button,id);

        QLabel* label3=new QLabel(box1);
        label3->setText("线程"+QString::number(id));
        label3->setObjectName("setThrdName_"+QString::number(id));

        QVBoxLayout* b1VbLyt=new QVBoxLayout();
        b1VbLyt->addWidget(label3);
        b1VbLyt->addWidget(box2);
        b1VbLyt->addWidget(box3);
        b1VbLyt->addWidget(button);
        b1VbLyt->setStretch(0,1);
        b1VbLyt->setStretch(1,3);
        b1VbLyt->setStretch(2,3);
        b1VbLyt->setStretch(3,3);
        box1->setLayout(b1VbLyt);

        box1->show();

        QGraphicsOpacityEffect* opefct=new QGraphicsOpacityEffect;
        opefct->setOpacity(0.0);
        thBtnGrp->button(bid)->setGraphicsEffect(opefct);
        thBtnGrp->button(bid)->setEnabled(false);
    }
}

void MainWindow::confirmThreadBtnClicked(int id){
    rdyThCnt++;
    rdyThs[id]=1;
    this->findChild<QLabel*>("setThrdName_"+QString::number(id))->setText("线程"+QString::number(id)+" - Ready");

    int bid=thLookupBtnId(id);
    int cmbIndex=this->findChild<QComboBox*>("algCmbBox_"+QString::number(id))->currentIndex();
    bool chkStat=this->findChild<QCheckBox*>("tlbChkBox_"+QString::number(id))->isChecked();
    //std::cout<<cmbIndex<<","<<chkStat<<std::endl;

    QGroupBox* box=new QGroupBox(ui->addThreadGrp);
    box->setObjectName("threadShowGrp_"+QString::number(id));
    box->setGeometry(
                thBtnGrp->button(bid)->geometry().x(),
                thBtnGrp->button(bid)->geometry().y(),
                thBtnGrp->button(bid)->geometry().width(),
                thBtnGrp->button(bid)->geometry().height()
                );
    QLabel* label=new QLabel(box);
    label->setText("线程"+QString::number(id));

    QTableWidget* table=new QTableWidget(box);
    table->setObjectName("threadShowTbl_"+QString::number(id));
    table->setRowCount(mainTP.process.residentSize);
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels(QStringList()<<"页号"<<"块号");
    table->verticalHeader()->setHidden(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //table->setItem(0,0,new QTableWidgetItem("2"));

//    QGroupBox* box2=new QGroupBox(box);
//    box2->setObjectName("threadShowBtnGrp_"+QString::number(id));
//    QPushButton* button1=new QPushButton(box2);
//    button1->setObjectName("thPlayBtn_"+QString::number(id));
//    button1->setText("play");
//    thPlayBtnGrp->addButton(button1,id);
//    QPushButton* button2=new QPushButton(box2);
//    button2->setObjectName("thPauseoBtn_"+QString::number(id));
//    button2->setText("pause");
//    thPauseBtnGrp->addButton(button2,id);
//    QPushButton* button3=new QPushButton(box2);
//    button3->setObjectName("thStepBtn_"+QString::number(id));
//    button3->setText("step");
//    thStepBtnGrp->addButton(button3,id);
//    QHBoxLayout* btnHbLyt=new QHBoxLayout();
//    btnHbLyt->addWidget(button1);
//    btnHbLyt->addWidget(button2);
//    btnHbLyt->addWidget(button3);
    //box2->setLayout(btnHbLyt);
    QLabel* label2=new QLabel();
    label2->setObjectName("curPhy_"+QString::number(id));
    label->setText("");
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* vbLyt=new QVBoxLayout();
    vbLyt->addWidget(label);
    vbLyt->addWidget(table);
    vbLyt->addWidget(label2);
    //vbLyt->addWidget(box2);
    box->setLayout(vbLyt);

    int maxPage=0;
    for(int i=0;i<(int)mainTP.seq.size();++i){
        maxPage=std::max(maxPage,mainTP.seq[i].page);
    }

    dps[id].tp.setId(id);
    dps[id].tp.setSequence(mainTP.seq);

    dps[id].tp.process.setResidentSize(mainTP.process.residentSize);
    dps[id].tp.process.setResidentSet(mainTP.process.blocks);
    dps[id].tp.process.setPageTable(maxPage+1,cmbIndex);
    //log(dps[id].tp.process.pageTable.size);
    if(chkStat){
        dps[id].tp.process.activeTLB();
        dps[id].tp.process.setTLB(mainTP.process.residentSize/2+1);
    }else{
        dps[id].tp.process.deactiveTLB();
    }

    dps[id].tp.virMemSys.setAccessMemTime(mainTP.virMemSys.accessMemTime.count());
    dps[id].tp.virMemSys.setAccessTLBTime(mainTP.virMemSys.accessTLBTime.count());
    dps[id].tp.virMemSys.setInterruptTime(mainTP.virMemSys.interruptTime.count());

    dps[id].tp.virMemSys.initMem(mainTP.process.residentSize*3/2);
    dps[id].tp.virMemSys.initSwap(mainTP.process.residentSize*3/2);
}

void MainWindow::stepThreadBtnClicked(int id){
    if(dps[id].curStep<(int)dps[id].tp.axis.frames.size()){
        QTableWidget* table=this->findChild<QTableWidget*>("threadShowTbl_"+QString::number(id));
        int step=dps[id].curStep++;
        //std::cout<<"id:"<<id<<", page:"<<dps[id].tp.axis.frames[step].row<<std::endl;
        for(int i=0;i<mainTP.process.residentSize;++i){
            table->item(i,0)->setBackgroundColor(QColor("#ffffff"));
            table->item(i,0)->setTextColor(QColor("#000000"));
            table->item(i,1)->setBackgroundColor(QColor("#ffffff"));
            table->item(i,1)->setTextColor(QColor("#000000"));
        }
        table->setItem(dps[id].tp.axis.frames[step].row,0,
                       new QTableWidgetItem(
                           QString::number(
                               dps[id].tp.axis.frames[step].newPage
                               )
                           )
                       );
        table->item(dps[id].tp.axis.frames[step].row,0)->setBackgroundColor(QColor("#4D9900"));
        table->item(dps[id].tp.axis.frames[step].row,0)->setTextColor(QColor("#ffffff"));
        table->item(dps[id].tp.axis.frames[step].row,1)->setBackgroundColor(QColor("#4D9900"));
        table->item(dps[id].tp.axis.frames[step].row,1)->setTextColor(QColor("#ffffff"));
    }
}

void MainWindow::pauseThreadBtnClicked(int id){

}

void MainWindow::playThreadBtnClicked(int id){

}

void MainWindow::on_startBtn_clicked(){
    QGroupBox* lbox=this->findChild<QGroupBox*>("settingGrp");
    lbox->setEnabled(false);

    int realCnt=0;
    for(int i=1;i<=thCount;++i){
        if(rdyThs[i]==1){
            realCnt++;
        }
    }
    std::vector<std::thread> threads(realCnt);

    int realIndex=0;
    for(int i=1;i<=thCount;++i){
        if(rdyThs[i]==1){
            //threads[realIndex]=std::thread(&virm::ThreadProperty::execute,dps[i].tp);
            dps[i].tp.execute();

            this->findChild<QGroupBox*>("threadShowGrp_"+QString::number(i))->show();

            QGraphicsOpacityEffect* opefct=new QGraphicsOpacityEffect;
            opefct->setOpacity(0.0);
            QGroupBox* tsgGrpBox=this->findChild<QGroupBox*>("threadSetGrp_"+QString::number(i));
            tsgGrpBox->setGraphicsEffect(opefct);
            tsgGrpBox->setEnabled(false);
            realIndex++;
        }else{
        }
    }

    for(int i=0;i<realCnt;++i){
       //threads[i].join();
    }


    for(int i=1;i<=thCount;++i){
        if(rdyThs[i]==1){
            for(int j=0;j<(int)dps[i].tp.process.blocks.size();++j){
                QTableWidget* table=this->findChild<QTableWidget*>("threadShowTbl_"+QString::number(i));
                table->setItem(j,0,new QTableWidgetItem("--"));
                table->setItem(j,1,
                               new QTableWidgetItem(
                                   QString::number(
                                       dps[i].tp.process.blocks[j]
                                       )
                                   )
                               );
            }
        }
    }

    int finished=0;
    while(finished<realCnt){
        //log("?");
        for(int i=1;i<=thCount;++i){
            if(rdyThs[i]==1){
                //log(dps[i].tp.axis.frames.size());
                if(dps[i].curStep<(int)dps[i].tp.axis.frames.size()){
                    //log("!");
                    QTableWidget* table=this->findChild<QTableWidget*>("threadShowTbl_"+QString::number(i));
                    for(int j=0;j<dps[i].tp.process.residentSize;++j){
                        table->item(j,0)->setBackgroundColor(QColor("#ffffff"));
                        table->item(j,0)->setTextColor(QColor("#000000"));
                        table->item(j,1)->setBackgroundColor(QColor("#ffffff"));
                        table->item(j,1)->setTextColor(QColor("#000000"));
                    }
                    table->setItem(dps[i].tp.axis.frames[dps[i].curStep].row,0,
                                   new QTableWidgetItem(
                                       QString::number(
                                           dps[i].tp.axis.frames[dps[i].curStep].newPage
                                           )
                                       )
                                   );

                    table->item(dps[i].tp.axis.frames[dps[i].curStep].row,0)->setBackgroundColor(QColor("#4D9900"));
                    table->item(dps[i].tp.axis.frames[dps[i].curStep].row,0)->setTextColor(QColor("#ffffff"));
                    table->item(dps[i].tp.axis.frames[dps[i].curStep].row,1)->setBackgroundColor(QColor("#4D9900"));
                    table->item(dps[i].tp.axis.frames[dps[i].curStep].row,1)->setTextColor(QColor("#ffffff"));

                    QLabel* label=this->findChild<QLabel*>("curPhy_"+QString::number(i));
                    label->setText(
                                "物理地址:"+
                                QString::fromStdString(
                                    stool::dec2Hex(
                                        (unsigned)(dps[i].tp.axis.frames[dps[i].curStep].block<<virm::LogicalAddr::offsetDigits)+
                                        (unsigned)dps[i].tp.seq[dps[i].curStep].offset
                                    )
                                )
                            );
                    //log(stool::dec2Hex((unsigned)dps[i].tp.axis.frames[dps[i].curStep].block<<virm::LogicalAddr::offsetDigits+(unsigned)dps[i].tp.seq[dps[i].curStep].offset));
                    label->setAlignment(Qt::AlignCenter);
                    //std::this_thread::sleep_for(std::chrono::seconds(2));
                    dps[i].curStep++;
                }else{
                    finished++;
                }
            }
        }
        QTime dtime=QTime::currentTime().addMSecs(700);
        while(QTime::currentTime()<dtime){
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        }
    }
}

void MainWindow::on_restartBtn_clicked(){
    qApp->exit(114);
}
