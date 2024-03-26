#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QIcon(":/icon/addThrdBtnIcon.svg");
    QIcon(":/icon/file.svg");
    QFile styleFile(":/style/group.qss");
    if(styleFile.open(QIODevice::ReadOnly))
    {
        qDebug("open success");
        QString setStyleSheet(styleFile.readAll());
        a.setStyleSheet(setStyleSheet);
        styleFile.close();
    }

    int e=a.exec();
    if(e==114){
        QProcess::startDetached(qApp->applicationFilePath(),QStringList());
    }
    return e;
}
