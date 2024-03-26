#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QButtonGroup>
#include <QMainWindow>
#include <QTableWidget>
#include <QProcess>
#include <string>
#include <vector>
#include "vir_mem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    struct GenAddrAttrs{
        int count=0;
        std::string lower="00000000";
        std::string upper="0000F000";
    };
    struct DisplayProperty{
        virm::ThreadProperty tp;
        int curStep=0;
        void deal();
    };

private slots:
    void on_residentTxt_editingFinished();
    void on_acMemTimeTxt_editingFinished();
    void on_acTLBTimeTxt_editingFinished();
    void on_intrptTimeTxt_editingFinished();
    void on_addrManuTxt_textChanged();
    void on_addrCntTxt_editingFinished();
    void on_addrLowLimTxt_editingFinished();
    void on_addrGreatLimTxt_editingFinished();
    void on_addrGenerBtn_clicked();
    void addThreadBtnClicked(int bid);
    void confirmThreadBtnClicked(int id);
    void stepThreadBtnClicked(int id);
    void pauseThreadBtnClicked(int id);
    void playThreadBtnClicked(int id);
    void on_loadFileBtn_clicked();
    int thLookupBtnId(int thId);

    void on_startBtn_clicked();

    void on_restartBtn_clicked();

private:
    Ui::MainWindow *ui;
    virm::ThreadProperty mainTP;
    GenAddrAttrs genAddtAttrs;
    int thCount=4;
    int curThCnt=0;
    int rdyThCnt=0;
    std::vector<DisplayProperty> dps;
    std::vector<int> thLookupTbl;//<按钮id,线程序号>
    std::vector<int> rdyThs;//<按钮id,线程序号>
    QButtonGroup* thBtnGrp;
    QButtonGroup* thCnfBtnGrp;
    QButtonGroup* thStepBtnGrp;
    QButtonGroup* thPlayBtnGrp;
    QButtonGroup* thPauseBtnGrp;

};

#endif // MAINWINDOW_H
