#include "ManageCoursesInterfaceWindow.h"
#include "ui_ManageCoursesInterfaceWindow.h"

ManageCoursesInterfaceWindow::ManageCoursesInterfaceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageCoursesInterfaceWindow)
{
    ui->setupUi(this);
}

ManageCoursesInterfaceWindow::~ManageCoursesInterfaceWindow()
{
    delete ui;
}


//List getters
QAbstractItemView*  ManageCoursesInterfaceWindow::getCourseListView(){ return ui->courseListView; }
QAbstractItemView*  ManageCoursesInterfaceWindow::getAssignedTextbooksListView(){ return ui->assignedTextbookListView;}

//Button getters
QPushButton*    ManageCoursesInterfaceWindow::getBackButton() { return ui->backButton;}
QPushButton*    ManageCoursesInterfaceWindow::getCreateCourseButton(){ return ui->createCourseOption;}
QPushButton*    ManageCoursesInterfaceWindow::getEditCourseButton(){ return ui->editCourseOption; }
QPushButton*    ManageCoursesInterfaceWindow::getDeleteCourseButton(){ return ui->deleteCourseOption; }
QComboBox*      ManageCoursesInterfaceWindow::getTermSelectOption(){ return ui->termSelectOption; }


