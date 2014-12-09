#include "CourseInputOutputManager.h"
#include <QDebug>
CourseInputOutputManager::CourseInputOutputManager()
{
    manageCoursesInterface = new ManageCoursesInterfaceWindow();
    manageCoursesInterface->show();

    connect_manageCoursesInterface();

    courseManagementFacade = new CourseManagementFacade();

}

void CourseInputOutputManager::connect_manageCoursesInterface(){
    //Connect manageCoursesInterface UI Buttons and Views
    connect(manageCoursesInterface->getBackButton(),SIGNAL(clicked()), this, SLOT(on_manageCoursesInterface_back_button()));
    connect(manageCoursesInterface->getCreateCourseButton(),SIGNAL(clicked()), this, SLOT(on_manageCoursesInterface_createCourse_button()));
    connect(manageCoursesInterface->getEditCourseButton(),SIGNAL(clicked()),this, SLOT(on_manageCoursesInterface_editCourse_button()));
    connect(manageCoursesInterface->getDeleteCourseButton(), SIGNAL(clicked()), this, SLOT(on_manageCoursesInterface_deleteCourse_button()));
    connect(manageCoursesInterface->getTermSelectOption(), SIGNAL(activated(QString)), this, SLOT(on_manageCoursesInterface_termSelected()));
    connect(manageCoursesInterface->getEnrollStudentOption(), SIGNAL(clicked()), this, SLOT(on_manageCoursesInterface_enrollStudent_button()));
    connect(manageCoursesInterface->getAssignTextbookOption(), SIGNAL(clicked()), this, SLOT(on_manageCoursesInterface_assignTextbook_button()));

    connect(manageCoursesInterface->getCourseListView(),SIGNAL(clicked(QModelIndex)),this,SLOT(on_manageCoursesInterface_selectCourse()));



}

void CourseInputOutputManager::on_manageCoursesInterface_back_button(){
    delete manageCoursesInterface;
    delete this;
}

void CourseInputOutputManager::on_manageCoursesInterface_createCourse_button(){
    qDebug() << "Create Course button clicked";
}

void CourseInputOutputManager::on_manageCoursesInterface_editCourse_button(){
    qDebug() << "Edit Course Button clicked";
}

void CourseInputOutputManager::on_manageCoursesInterface_deleteCourse_button(){
    qDebug() << "Delete Course button clicked";
}

void CourseInputOutputManager::on_manageCoursesInterface_termSelected(){
    qDebug() << "Term Selected button clicked";
}


void CourseInputOutputManager::on_manageCoursesInterface_enrollStudent_button(){
    qDebug() << "Enroll Student button clicked";
}

void CourseInputOutputManager::on_manageCoursesInterface_assignTextbook_button(){
    qDebug() << "Assign textbook button clicked";
}

void CourseInputOutputManager::on_manageCoursesInterface_selectCourse(){
    qDebug() << "Selected Course";
}



