#include <QCoreApplication>
#include "CUtpsServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CutpsServer testServ;
    testServ.startServer();
    return a.exec();
}
