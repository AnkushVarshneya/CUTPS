#include <QCoreApplication>
#include "cutpsServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cutpsServer testServ;
    testServ.startServer();
    return a.exec();
}
