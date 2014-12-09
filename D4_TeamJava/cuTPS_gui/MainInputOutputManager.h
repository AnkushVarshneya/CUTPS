/*An initial input output manager mediator for the user to choose the selected user role
 *Not a part of our system design, for demo purposes only. Provides option in the form of dialog box
 *to enter in a student number, and the IP address to connect to server
 *
 */
#ifndef MAININPUTOUTPUTMANAGER_H
#define MAININPUTOUTPUTMANAGER_H

#include "mainwindow.h"
#include "ContentManagerInterfaceWindow.h"
#include "ContentInputOutputManager.h"
#include "ManageCoursesInterfaceWindow.h"
#include "StudentInputOutputManager.h"
#include "StudentInterfaceWindow.h"
#include "CourseInputOutputManager.h"

class MainInputOutputManager : public QObject
{
    Q_OBJECT
public:
    MainInputOutputManager();

private slots:
    void on_contentIOManager_deleted();
    void on_courseIOManager_deleted();
    void on_contentManager_clicked();
    void on_student_clicked();

    void on_manageTextbooks_clicked();
    void on_manageCourses_clicked();

private:
    MainWindow mainWindow;
    ContentManagerInterfaceWindow *contentManagerInterface;
    ContentInputOutputManager *contentIOManager;

    StudentInterfaceWindow *studentInterface;
    StudentInputOutputManager *studentIOManager;

    ManageCoursesInterfaceWindow *courseInterface;
    CourseInputOutputManager *courseIOManager;

};

#endif // MAININPUTOUTPUTMANAGER_H
