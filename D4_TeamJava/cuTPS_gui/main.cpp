#include "mainwindow.h"
#include <QApplication>

/*
#include "ContentInputOutputManager.h"
#include "EditTextbookFormWindow.h"
*/

#include "MainInputOutputManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    MainWindow w;
    w.show();
*/

    //ContentInputOutputManager b;

    MainInputOutputManager mainIOManager;

    return a.exec();
}
