#include "MainInputOutputManager.h"
#include <QDebug>

MainInputOutputManager::MainInputOutputManager()
{

    connect(mainWindow.getContentManagerButton(),SIGNAL(clicked()),this,SLOT(on_contentManager_clicked()));
    connect(mainWindow.getStudentButton(),SIGNAL(clicked()),this,SLOT(on_student_clicked()));

    mainWindow.show();
    qDebug() << "tst";
}

void MainInputOutputManager::on_contentIOManager_deleted()
{
    qDebug() << "wheee";
//    contentManagerInterface = new ContentManagerInterfaceWindow();
    contentManagerInterface->show();

//    connect(contentManagerInterface->getManageTextbooksButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooks_clicked()));
//    connect(contentManagerInterface->getManageCoursesButton(),SIGNAL(clicked()),this,SLOT(on_manageCourses_clicked()));
}

void MainInputOutputManager::on_contentManager_clicked()
{
    contentManagerInterface = new ContentManagerInterfaceWindow();
    contentManagerInterface->show();
    mainWindow.hide();

    connect(contentManagerInterface->getManageTextbooksButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooks_clicked()));
    connect(contentManagerInterface->getManageCoursesButton(),SIGNAL(clicked()),this,SLOT(on_manageCourses_clicked()));
}

void MainInputOutputManager::on_student_clicked()
{
    mainWindow.hide();
    studentIOManager = new StudentInputOutputManager();
}

void MainInputOutputManager::on_manageTextbooks_clicked()
{
    contentManagerInterface->hide();
    //delete contentManagerInterface;
    contentIOManager = new ContentInputOutputManager();

    connect(contentIOManager,SIGNAL(destroyed()),this,SLOT(on_contentIOManager_deleted()));

    qDebug() << "manage textbooks";
}

void MainInputOutputManager::on_manageCourses_clicked()
{
    contentManagerInterface->hide();
    delete contentManagerInterface;
}
