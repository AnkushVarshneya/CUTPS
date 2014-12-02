#ifndef MAININPUTOUTPUTMANAGER_H
#define MAININPUTOUTPUTMANAGER_H

#include "mainwindow.h"
#include "ContentManagerInterfaceWindow.h"
#include "ContentInputOutputManager.h"

class MainInputOutputManager : public QObject
{
    Q_OBJECT
public:
    MainInputOutputManager();

private slots:
    void on_contentIOManager_deleted();

    void on_contentManager_clicked();
    void on_student_clicked();

    void on_manageTextbooks_clicked();
    void on_manageCourses_clicked();

private:
    MainWindow mainWindow;
    ContentManagerInterfaceWindow *contentManagerInterface;
    ContentInputOutputManager *contentIOManager;
};

#endif // MAININPUTOUTPUTMANAGER_H
