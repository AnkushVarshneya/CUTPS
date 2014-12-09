#include "CourseInputOutputManager.h"
#include <QDebug>
CourseInputOutputManager::CourseInputOutputManager()
{
    manageCoursesInterface = new ManageCoursesInterfaceWindow();
    manageCoursesInterface->show();

    connect_manageCoursesInterface();

    courseModel = new QStandardItemModel(this);
    //studentModel = new QStandardItemModel(this);
    textbookModel = new QStandardItemModel(this);

    courseManagementFacade = new CourseManagementFacade();
    //fakeTextbooks = courseManagementFacade->retrieveAllTextbooks();
    //fakeTextbooks = courseManagementFacade->
    //buildTextbookModel();

//    setCourseManagementInterfaceViewModel(manageCoursesInterface->get);


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
void CourseInputOutputManager::connect_editCourseForm() {
    connect(editCourseForm->getBackButton(),SIGNAL(clicked()),this,SLOT(on_editCourseForm_backButton()));
    connect(editCourseForm->getCreateButton(),SIGNAL(clicked()),this,SLOT(on_editCourseForm_createButton()));
    connect(editCourseForm->getEnrollButton(),SIGNAL(clicked()),this,SLOT(on_editCourseForm_enrollButton()));
    connect(editCourseForm->getLinkTextbookButton(),SIGNAL(clicked()),this,SLOT(on_editCourseForm_linkTextbookButton()));
}
void CourseInputOutputManager::connect_linkTextbookForm() {
    connect(linkTextbookForm->getBackButton(),SIGNAL(clicked()),this,SLOT(on_linkTextbookForm_backButton()));
    connect(linkTextbookForm->getLinkTextbookButton(),SIGNAL(clicked()),this,SLOT(on_linkTextbookForm_linkTextbookButton()));
    connect(linkTextbookForm->getAllTextbooksListView(),SIGNAL(clicked(QModelIndex)),this,SLOT(on_linkTextbookForm_selectTextbook()));
    connect(linkTextbookForm->getRegisteredTextbooksListView(),SIGNAL(clicked(QModelIndex)),this,SLOT(on_linkTextbookForm_selectRegisteredTextbook()));
}

void CourseInputOutputManager::on_editCourseForm_backButton() {
    manageCoursesInterface->show();
    //editCourseForm->hide();
    delete editCourseForm;
}
void CourseInputOutputManager::on_editCourseForm_createButton() {}
void CourseInputOutputManager::on_editCourseForm_enrollButton() {}
void CourseInputOutputManager::on_editCourseForm_linkTextbookButton() {}

void CourseInputOutputManager::on_linkTextbookForm_backButton() {
    manageCoursesInterface->show();
    //linkTextbookForm->hide();
    delete linkTextbookForm;
}
void CourseInputOutputManager::on_linkTextbookForm_linkTextbookButton() {}
void CourseInputOutputManager::on_linkTextbookForm_selectTextbook() {}
void CourseInputOutputManager::on_linkTextbookForm_selectRegisteredTextbook() {}

void CourseInputOutputManager::on_manageCoursesInterface_back_button(){
    delete manageCoursesInterface;
    delete this;
}

void CourseInputOutputManager::on_manageCoursesInterface_createCourse_button(){
    qDebug() << "Create Course button clicked";
    editCourseForm = new ModifyCourseFormWindow();
    connect_editCourseForm();
    editCourseForm->show();
    manageCoursesInterface->hide();
}

void CourseInputOutputManager::on_manageCoursesInterface_editCourse_button(){
    qDebug() << "Edit Course Button clicked";
    editCourseForm = new ModifyCourseFormWindow();
    connect_editCourseForm();
    editCourseForm->show();
    manageCoursesInterface->hide();
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
    linkTextbookForm = new LinkTextbookFormWindow();
    connect_linkTextbookForm();
    linkTextbookForm->show();
    manageCoursesInterface->hide();
}

void CourseInputOutputManager::on_manageCoursesInterface_selectCourse(){
    qDebug() << "Selected Course";
}



