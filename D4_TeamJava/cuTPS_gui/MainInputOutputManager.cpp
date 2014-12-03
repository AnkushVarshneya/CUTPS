#include "MainInputOutputManager.h"
#include <QDebug>

MainInputOutputManager::MainInputOutputManager()
{
    //connect(contentIOManager,SIGNAL(destroyed()),this,SLOT(on_contentIOManager_deleted()));

    //connect(mainWindow.getContentManagerButton(),SIGNAL(clicked()),this,SLOT(on_contentManager_clicked()));
    //connect(mainWindow.getStudentButton(),SIGNAL(clicked()),this,SLOT(on_student_clicked()));



    mainWindow.show();
}

void MainInputOutputManager::on_contentIOManager_deleted()
{
    qDebug() << "wheee";
}

void MainInputOutputManager::on_contentManager_clicked()
{
    contentManagerInterface = new ContentManagerInterfaceWindow();
    //contentManagerInterface->show();
    mainWindow.hide();

    //connect(contentManagerInterface->getManageTextbooksButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooks_clicked()));
    //connect(contentManagerInterface->getManageCoursesButton(),SIGNAL(clicked()),this,SLOT(on_manageCourses_clicked()));
}

void MainInputOutputManager::on_student_clicked()
{

}

void MainInputOutputManager::on_manageTextbooks_clicked()
{
    contentIOManager = new ContentInputOutputManager();
}

void MainInputOutputManager::on_manageCourses_clicked()
{

}
