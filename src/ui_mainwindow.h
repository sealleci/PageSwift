/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *leftBar;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *settingGrp;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *residentGrp;
    QHBoxLayout *horizontalLayout_5;
    QLabel *residentLbl;
    QSpinBox *residentTxt;
    QGroupBox *timeSet;
    QVBoxLayout *verticalLayout;
    QGroupBox *acMemTimeGrp;
    QHBoxLayout *horizontalLayout_2;
    QLabel *acMemTimeLbl;
    QLineEdit *acMemTimeTxt;
    QLabel *nsLbl_1;
    QGroupBox *acTLBTimeGrp;
    QHBoxLayout *horizontalLayout_3;
    QLabel *acTLBTimeLbl;
    QLineEdit *acTLBTimeTxt;
    QLabel *nsLbl_2;
    QGroupBox *intrptTimeGrp;
    QHBoxLayout *horizontalLayout_4;
    QLabel *intrptTimeLbl;
    QLineEdit *intrptTimeTxt;
    QLabel *nsLbl_3;
    QGroupBox *addrGrp;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *addrManuGrp;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *addrManuHeaderGrp;
    QHBoxLayout *horizontalLayout_6;
    QLabel *addrManuLbl;
    QPushButton *loadFileBtn;
    QTextEdit *addrManuTxt;
    QGroupBox *addrAutoGrp;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *addrCntGrp;
    QHBoxLayout *horizontalLayout_7;
    QLabel *addrCntLbl;
    QSpinBox *addrCntTxt;
    QGroupBox *addrLimGrp;
    QGridLayout *gridLayout_3;
    QLabel *addrLimLbl;
    QLineEdit *addrLowLimTxt;
    QLabel *connectSymbLbl;
    QLineEdit *addrGreatLimTxt;
    QPushButton *addrGenerBtn;
    QPushButton *restartBtn;
    QGroupBox *centralSec;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *actionGrp;
    QHBoxLayout *horizontalLayout;
    QPushButton *startBtn;
    QGroupBox *addThreadGrp;
    QGridLayout *gridLayout;
    QPushButton *addThreadBtn_2;
    QPushButton *addThreadBtn_3;
    QPushButton *addThreadBtn_4;
    QPushButton *addThreadBtn_1;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1237, 940);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_8 = new QHBoxLayout(centralWidget);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        leftBar = new QGroupBox(centralWidget);
        leftBar->setObjectName(QStringLiteral("leftBar"));
        verticalLayout_5 = new QVBoxLayout(leftBar);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        settingGrp = new QGroupBox(leftBar);
        settingGrp->setObjectName(QStringLiteral("settingGrp"));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(10);
        settingGrp->setFont(font);
        verticalLayout_6 = new QVBoxLayout(settingGrp);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        residentGrp = new QGroupBox(settingGrp);
        residentGrp->setObjectName(QStringLiteral("residentGrp"));
        residentGrp->setMaximumSize(QSize(253, 247));
        horizontalLayout_5 = new QHBoxLayout(residentGrp);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        residentLbl = new QLabel(residentGrp);
        residentLbl->setObjectName(QStringLiteral("residentLbl"));
        residentLbl->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(residentLbl);

        residentTxt = new QSpinBox(residentGrp);
        residentTxt->setObjectName(QStringLiteral("residentTxt"));
        residentTxt->setMinimum(1);
        residentTxt->setValue(3);

        horizontalLayout_5->addWidget(residentTxt);


        verticalLayout_6->addWidget(residentGrp);

        timeSet = new QGroupBox(settingGrp);
        timeSet->setObjectName(QStringLiteral("timeSet"));
        verticalLayout = new QVBoxLayout(timeSet);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        acMemTimeGrp = new QGroupBox(timeSet);
        acMemTimeGrp->setObjectName(QStringLiteral("acMemTimeGrp"));
        horizontalLayout_2 = new QHBoxLayout(acMemTimeGrp);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        acMemTimeLbl = new QLabel(acMemTimeGrp);
        acMemTimeLbl->setObjectName(QStringLiteral("acMemTimeLbl"));

        horizontalLayout_2->addWidget(acMemTimeLbl);

        acMemTimeTxt = new QLineEdit(acMemTimeGrp);
        acMemTimeTxt->setObjectName(QStringLiteral("acMemTimeTxt"));

        horizontalLayout_2->addWidget(acMemTimeTxt);

        nsLbl_1 = new QLabel(acMemTimeGrp);
        nsLbl_1->setObjectName(QStringLiteral("nsLbl_1"));

        horizontalLayout_2->addWidget(nsLbl_1);


        verticalLayout->addWidget(acMemTimeGrp);

        acTLBTimeGrp = new QGroupBox(timeSet);
        acTLBTimeGrp->setObjectName(QStringLiteral("acTLBTimeGrp"));
        horizontalLayout_3 = new QHBoxLayout(acTLBTimeGrp);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        acTLBTimeLbl = new QLabel(acTLBTimeGrp);
        acTLBTimeLbl->setObjectName(QStringLiteral("acTLBTimeLbl"));

        horizontalLayout_3->addWidget(acTLBTimeLbl);

        acTLBTimeTxt = new QLineEdit(acTLBTimeGrp);
        acTLBTimeTxt->setObjectName(QStringLiteral("acTLBTimeTxt"));

        horizontalLayout_3->addWidget(acTLBTimeTxt);

        nsLbl_2 = new QLabel(acTLBTimeGrp);
        nsLbl_2->setObjectName(QStringLiteral("nsLbl_2"));

        horizontalLayout_3->addWidget(nsLbl_2);


        verticalLayout->addWidget(acTLBTimeGrp);

        intrptTimeGrp = new QGroupBox(timeSet);
        intrptTimeGrp->setObjectName(QStringLiteral("intrptTimeGrp"));
        horizontalLayout_4 = new QHBoxLayout(intrptTimeGrp);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        intrptTimeLbl = new QLabel(intrptTimeGrp);
        intrptTimeLbl->setObjectName(QStringLiteral("intrptTimeLbl"));

        horizontalLayout_4->addWidget(intrptTimeLbl);

        intrptTimeTxt = new QLineEdit(intrptTimeGrp);
        intrptTimeTxt->setObjectName(QStringLiteral("intrptTimeTxt"));

        horizontalLayout_4->addWidget(intrptTimeTxt);

        nsLbl_3 = new QLabel(intrptTimeGrp);
        nsLbl_3->setObjectName(QStringLiteral("nsLbl_3"));

        horizontalLayout_4->addWidget(nsLbl_3);


        verticalLayout->addWidget(intrptTimeGrp);


        verticalLayout_6->addWidget(timeSet);

        addrGrp = new QGroupBox(settingGrp);
        addrGrp->setObjectName(QStringLiteral("addrGrp"));
        verticalLayout_3 = new QVBoxLayout(addrGrp);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        addrManuGrp = new QGroupBox(addrGrp);
        addrManuGrp->setObjectName(QStringLiteral("addrManuGrp"));
        verticalLayout_7 = new QVBoxLayout(addrManuGrp);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        addrManuHeaderGrp = new QGroupBox(addrManuGrp);
        addrManuHeaderGrp->setObjectName(QStringLiteral("addrManuHeaderGrp"));
        horizontalLayout_6 = new QHBoxLayout(addrManuHeaderGrp);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        addrManuLbl = new QLabel(addrManuHeaderGrp);
        addrManuLbl->setObjectName(QStringLiteral("addrManuLbl"));
        addrManuLbl->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(addrManuLbl);

        loadFileBtn = new QPushButton(addrManuHeaderGrp);
        loadFileBtn->setObjectName(QStringLiteral("loadFileBtn"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/res/icon/file.svg"), QSize(), QIcon::Normal, QIcon::Off);
        loadFileBtn->setIcon(icon);
        loadFileBtn->setIconSize(QSize(30, 30));

        horizontalLayout_6->addWidget(loadFileBtn);

        horizontalLayout_6->setStretch(0, 5);
        horizontalLayout_6->setStretch(1, 1);

        verticalLayout_7->addWidget(addrManuHeaderGrp);

        addrManuTxt = new QTextEdit(addrManuGrp);
        addrManuTxt->setObjectName(QStringLiteral("addrManuTxt"));

        verticalLayout_7->addWidget(addrManuTxt);

        verticalLayout_7->setStretch(0, 1);
        verticalLayout_7->setStretch(1, 5);

        verticalLayout_3->addWidget(addrManuGrp);

        addrAutoGrp = new QGroupBox(addrGrp);
        addrAutoGrp->setObjectName(QStringLiteral("addrAutoGrp"));
        verticalLayout_2 = new QVBoxLayout(addrAutoGrp);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        addrCntGrp = new QGroupBox(addrAutoGrp);
        addrCntGrp->setObjectName(QStringLiteral("addrCntGrp"));
        horizontalLayout_7 = new QHBoxLayout(addrCntGrp);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        addrCntLbl = new QLabel(addrCntGrp);
        addrCntLbl->setObjectName(QStringLiteral("addrCntLbl"));
        addrCntLbl->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(addrCntLbl);

        addrCntTxt = new QSpinBox(addrCntGrp);
        addrCntTxt->setObjectName(QStringLiteral("addrCntTxt"));
        addrCntTxt->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        addrCntTxt->setMaximum(255);

        horizontalLayout_7->addWidget(addrCntTxt);


        verticalLayout_2->addWidget(addrCntGrp);

        addrLimGrp = new QGroupBox(addrAutoGrp);
        addrLimGrp->setObjectName(QStringLiteral("addrLimGrp"));
        gridLayout_3 = new QGridLayout(addrLimGrp);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        addrLimLbl = new QLabel(addrLimGrp);
        addrLimLbl->setObjectName(QStringLiteral("addrLimLbl"));

        gridLayout_3->addWidget(addrLimLbl, 0, 0, 1, 1);

        addrLowLimTxt = new QLineEdit(addrLimGrp);
        addrLowLimTxt->setObjectName(QStringLiteral("addrLowLimTxt"));
        addrLowLimTxt->setMaxLength(9);
        addrLowLimTxt->setDragEnabled(false);

        gridLayout_3->addWidget(addrLowLimTxt, 0, 1, 1, 1);

        connectSymbLbl = new QLabel(addrLimGrp);
        connectSymbLbl->setObjectName(QStringLiteral("connectSymbLbl"));

        gridLayout_3->addWidget(connectSymbLbl, 0, 2, 1, 1);

        addrGreatLimTxt = new QLineEdit(addrLimGrp);
        addrGreatLimTxt->setObjectName(QStringLiteral("addrGreatLimTxt"));
        addrGreatLimTxt->setMaxLength(9);

        gridLayout_3->addWidget(addrGreatLimTxt, 0, 3, 1, 1);

        gridLayout_3->setColumnMinimumWidth(0, 1);
        gridLayout_3->setColumnMinimumWidth(1, 3);
        gridLayout_3->setColumnMinimumWidth(2, 1);
        gridLayout_3->setColumnMinimumWidth(3, 3);

        verticalLayout_2->addWidget(addrLimGrp);

        addrGenerBtn = new QPushButton(addrAutoGrp);
        addrGenerBtn->setObjectName(QStringLiteral("addrGenerBtn"));

        verticalLayout_2->addWidget(addrGenerBtn);

        verticalLayout_2->setStretch(2, 2);

        verticalLayout_3->addWidget(addrAutoGrp);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 1);

        verticalLayout_6->addWidget(addrGrp);

        verticalLayout_6->setStretch(0, 1);
        verticalLayout_6->setStretch(1, 3);
        verticalLayout_6->setStretch(2, 6);

        verticalLayout_5->addWidget(settingGrp);

        restartBtn = new QPushButton(leftBar);
        restartBtn->setObjectName(QStringLiteral("restartBtn"));

        verticalLayout_5->addWidget(restartBtn);

        verticalLayout_5->setStretch(0, 10);
        verticalLayout_5->setStretch(1, 1);

        horizontalLayout_8->addWidget(leftBar);

        centralSec = new QGroupBox(centralWidget);
        centralSec->setObjectName(QStringLiteral("centralSec"));
        centralSec->setFont(font);
        centralSec->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        verticalLayout_4 = new QVBoxLayout(centralSec);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetFixedSize);
        actionGrp = new QGroupBox(centralSec);
        actionGrp->setObjectName(QStringLiteral("actionGrp"));
        horizontalLayout = new QHBoxLayout(actionGrp);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        startBtn = new QPushButton(actionGrp);
        startBtn->setObjectName(QStringLiteral("startBtn"));

        horizontalLayout->addWidget(startBtn);


        verticalLayout_4->addWidget(actionGrp);

        addThreadGrp = new QGroupBox(centralSec);
        addThreadGrp->setObjectName(QStringLiteral("addThreadGrp"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addThreadGrp->sizePolicy().hasHeightForWidth());
        addThreadGrp->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(addThreadGrp);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        addThreadBtn_2 = new QPushButton(addThreadGrp);
        addThreadBtn_2->setObjectName(QStringLiteral("addThreadBtn_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/res/icon/addThrdBtnIcon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        addThreadBtn_2->setIcon(icon1);
        addThreadBtn_2->setIconSize(QSize(350, 350));

        gridLayout->addWidget(addThreadBtn_2, 0, 1, 1, 1);

        addThreadBtn_3 = new QPushButton(addThreadGrp);
        addThreadBtn_3->setObjectName(QStringLiteral("addThreadBtn_3"));
        addThreadBtn_3->setIcon(icon1);
        addThreadBtn_3->setIconSize(QSize(350, 350));

        gridLayout->addWidget(addThreadBtn_3, 1, 0, 1, 1);

        addThreadBtn_4 = new QPushButton(addThreadGrp);
        addThreadBtn_4->setObjectName(QStringLiteral("addThreadBtn_4"));
        addThreadBtn_4->setIcon(icon1);
        addThreadBtn_4->setIconSize(QSize(350, 350));

        gridLayout->addWidget(addThreadBtn_4, 1, 1, 1, 1);

        addThreadBtn_1 = new QPushButton(addThreadGrp);
        addThreadBtn_1->setObjectName(QStringLiteral("addThreadBtn_1"));
        addThreadBtn_1->setIcon(icon1);
        addThreadBtn_1->setIconSize(QSize(350, 350));
        addThreadBtn_1->setAutoDefault(false);
        addThreadBtn_1->setFlat(false);

        gridLayout->addWidget(addThreadBtn_1, 0, 0, 1, 1);


        verticalLayout_4->addWidget(addThreadGrp);

        addThreadGrp->raise();
        actionGrp->raise();

        horizontalLayout_8->addWidget(centralSec);

        horizontalLayout_8->setStretch(0, 3);
        horizontalLayout_8->setStretch(1, 7);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1237, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        residentLbl->setBuddy(residentTxt);
        acMemTimeLbl->setBuddy(acMemTimeTxt);
        acTLBTimeLbl->setBuddy(acTLBTimeTxt);
        intrptTimeLbl->setBuddy(intrptTimeTxt);
        addrCntLbl->setBuddy(addrCntTxt);
        addrLimLbl->setBuddy(addrLowLimTxt);
#endif // QT_NO_SHORTCUT

        menuBar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        addThreadBtn_1->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        leftBar->setTitle(QString());
        settingGrp->setTitle(QApplication::translate("MainWindow", "\350\256\276\345\256\232", Q_NULLPTR));
        residentGrp->setTitle(QString());
        residentLbl->setText(QApplication::translate("MainWindow", "\351\251\273\347\225\231\351\233\206\345\244\247\345\260\217", Q_NULLPTR));
        timeSet->setTitle(QApplication::translate("MainWindow", "\346\227\266\351\227\264", Q_NULLPTR));
        acMemTimeGrp->setTitle(QString());
        acMemTimeLbl->setText(QApplication::translate("MainWindow", "\350\256\277\351\227\256\345\206\205\345\255\230\346\227\266\351\227\264", Q_NULLPTR));
        acMemTimeTxt->setText(QApplication::translate("MainWindow", "50", Q_NULLPTR));
        nsLbl_1->setText(QApplication::translate("MainWindow", "ns", Q_NULLPTR));
        acTLBTimeGrp->setTitle(QString());
        acTLBTimeLbl->setText(QApplication::translate("MainWindow", "\350\256\277\351\227\256\345\277\253\350\241\250\346\227\266\351\227\264", Q_NULLPTR));
        acTLBTimeTxt->setText(QApplication::translate("MainWindow", "5", Q_NULLPTR));
        nsLbl_2->setText(QApplication::translate("MainWindow", "ns", Q_NULLPTR));
        intrptTimeGrp->setTitle(QString());
        intrptTimeLbl->setText(QApplication::translate("MainWindow", "\344\270\255\346\226\255\345\244\204\347\220\206\346\227\266\351\227\264", Q_NULLPTR));
        intrptTimeTxt->setText(QApplication::translate("MainWindow", "1e4", Q_NULLPTR));
        nsLbl_3->setText(QApplication::translate("MainWindow", "ns", Q_NULLPTR));
        addrGrp->setTitle(QApplication::translate("MainWindow", "\345\234\260\345\235\200", Q_NULLPTR));
        addrManuGrp->setTitle(QString());
        addrManuHeaderGrp->setTitle(QString());
        addrManuLbl->setText(QApplication::translate("MainWindow", "\345\234\260\345\235\200\345\272\217\345\210\227", Q_NULLPTR));
        loadFileBtn->setText(QString());
        addrAutoGrp->setTitle(QString());
        addrCntGrp->setTitle(QString());
        addrCntLbl->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\346\225\260\351\207\217", Q_NULLPTR));
        addrLimGrp->setTitle(QString());
        addrLimLbl->setText(QApplication::translate("MainWindow", "\350\214\203\345\233\264", Q_NULLPTR));
        addrLowLimTxt->setText(QApplication::translate("MainWindow", "00000000H", Q_NULLPTR));
        connectSymbLbl->setText(QApplication::translate("MainWindow", "~", Q_NULLPTR));
        addrGreatLimTxt->setText(QApplication::translate("MainWindow", "0000f000H", Q_NULLPTR));
        addrGenerBtn->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220", Q_NULLPTR));
        restartBtn->setText(QApplication::translate("MainWindow", "\351\207\215\345\220\257", Q_NULLPTR));
        centralSec->setTitle(QApplication::translate("MainWindow", "\350\277\233\347\250\213", Q_NULLPTR));
        actionGrp->setTitle(QString());
        startBtn->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", Q_NULLPTR));
        addThreadGrp->setTitle(QString());
        addThreadBtn_2->setText(QString());
        addThreadBtn_3->setText(QString());
        addThreadBtn_4->setText(QString());
        addThreadBtn_1->setText(QString());
        menu->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
