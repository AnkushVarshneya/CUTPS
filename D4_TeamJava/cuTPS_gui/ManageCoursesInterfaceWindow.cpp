#include "ManageCoursesInterfaceWindow.h"
#include "ui_ManageCoursesInterfaceWindow.h"

ManageCoursesInterfaceWindow::ManageCoursesInterfaceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageCoursesInterfaceWindow)
{
    ui->setupUi(this);
}

ManageCoursesInterfaceWindow* ManageCoursesInterfaceWindow::instance = 0;

ManageCoursesInterfaceWindow* ManageCoursesInterfaceWindow::getInstance(){
    if(instance == 0){
        instance = new ManageCoursesInterfaceWindow();
    }
    return instance;
}

ManageCoursesInterfaceWindow::~ManageCoursesInterfaceWindow()
{
    delete ui;
}


//List getters
QAbstractItemView*  ManageCoursesInterfaceWindow::getCourseListView(){ return ui->courseListView; }
QAbstractItemView*  ManageCoursesInterfaceWindow::getRegisteredStudentsListView(){ return ui->registeredStudentListView;}
QAbstractItemView*  ManageCoursesInterfaceWindow::getAssignedTextbooksListView(){ return ui->assignedTextbookListView;}

//Button getters
QPushButton*    ManageCoursesInterfaceWindow::getBackButton() { return ui->backButton;}
QPushButton*    ManageCoursesInterfaceWindow::getCreateCourseButton(){ return ui->createCourseOption;}
QPushButton*    ManageCoursesInterfaceWindow::getEditCourseButton(){ return ui->editCourseOption; }
QPushButton*    ManageCoursesInterfaceWindow::getDeleteCourseButton(){ return ui->deleteCourseOption; }
QComboBox*    ManageCoursesInterfaceWindow::getTermSelectOption(){ return ui->termSelectOption; }
QPushButton*    ManageCoursesInterfaceWindow::getEnrollStudentOption(){return ui->enrollStudentOption;}
QPushButton*    ManageCoursesInterfaceWindow::getAssignTextbookOption(){return ui->linkTextbookOption;}

