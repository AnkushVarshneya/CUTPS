#include "CourseInputOutputManager.h"
#include <QDebug>
#include "Term.h"
CourseInputOutputManager::CourseInputOutputManager()
{
    manageCoursesInterface = new ManageCoursesInterfaceWindow();
    manageCoursesInterface->show();

    connect_manageCoursesInterface();

    fakeTextbooks = new QList<Textbook*>();
    fakeLinkedTextbooks = new QList<Textbook*>();
    fakeCourses = new QList<Course*>();
    fakeTerms = new QList<Term*>();


    courseModel = new QStandardItemModel(this);
    textbookModel = new QStandardItemModel(this);

    courseManagementFacade = new CourseManagementFacade();
    fakeTextbooks = courseManagementFacade->retrieveAllTextbooks();




    fakeTerms = courseManagementFacade->retrieveAllTermList();
    populateTermComboBox(manageCoursesInterface->getTermSelectOption());





    int selectedTermIndex = manageCoursesInterface->getTermSelectOption()->currentIndex();
    selectedTerm = fakeTerms->at(selectedTermIndex);

    fakeCourses = courseManagementFacade->retrieveCourseList(selectedTerm);
    buildCourseModel();
    setCourseManagementInterfaceViewModel(manageCoursesInterface->getCourseListView(),courseModel);




}

void CourseInputOutputManager::setCourseManagementInterfaceViewModel(QAbstractItemView *view, QStandardItemModel *model) {
    view->setModel(model);

}

void CourseInputOutputManager::populateTermComboBox(QComboBox* termComboBox) {
    QList<Term*>::iterator i;
    qDebug() << fakeTerms->length();
    for (i = fakeTerms->begin(); i != fakeTerms->end(); i++) {
        termComboBox->addItem((*i)->getTermName(),(*i)->getTermName());
    }
}

void CourseInputOutputManager::buildTextbookModel() {
    textbookModel->clear();
    OurStandardItem *temp;
    QList<Textbook*>::iterator i;
    qDebug() << fakeTextbooks->length();
    for (i = fakeTextbooks->begin(); i != fakeTextbooks->end(); i++) {
        qDebug() << (*i)->getItemTitle();
        temp = new OurStandardItem( *i );
        qDebug() << (*i);
        textbookModel->appendRow(temp);
    }
}

void CourseInputOutputManager::buildLinkedTextbookModel() {
    fakeLinkedTextbooks->clear();
    OurStandardItem *temp;
    QList<Textbook*>::iterator i;
    qDebug() << fakeLinkedTextbooks->length();
    for (i = fakeLinkedTextbooks->begin(); i != fakeLinkedTextbooks->end(); i++) {
        qDebug() << (*i)->getItemTitle();
        temp = new OurStandardItem( *i );
        qDebug() << (*i);
        linkedTextbookModel->appendRow(temp);
    }
}

void CourseInputOutputManager::buildCourseModel() {
    courseModel->clear();
    OurStandardItem *temp;
    QList<Course*>::iterator i;
    qDebug() << fakeCourses->length();
    for (i = fakeCourses->begin(); i != fakeCourses->end(); i++) {
        qDebug() << (*i)->getCourseCode();
        temp = new OurStandardItem( *i );
        qDebug() << (*i);
        courseModel->appendRow(temp);
    }
}


void CourseInputOutputManager::connect_manageCoursesInterface(){
    //Connect manageCoursesInterface UI Buttons and Views
    connect(manageCoursesInterface->getBackButton(),SIGNAL(clicked()), this, SLOT(on_manageCoursesInterface_back_button()));
    connect(manageCoursesInterface->getCreateCourseButton(),SIGNAL(clicked()), this, SLOT(on_manageCoursesInterface_createCourse_button()));
    connect(manageCoursesInterface->getEditCourseButton(),SIGNAL(clicked()),this, SLOT(on_manageCoursesInterface_editCourse_button()));
    connect(manageCoursesInterface->getDeleteCourseButton(), SIGNAL(clicked()), this, SLOT(on_manageCoursesInterface_deleteCourse_button()));
    connect(manageCoursesInterface->getTermSelectOption(), SIGNAL(activated(QString)), this, SLOT(on_manageCoursesInterface_termSelected()));
    connect(manageCoursesInterface->getCourseListView(),SIGNAL(clicked(QModelIndex)),this,SLOT(on_manageCoursesInterface_selectCourse()));
}
void CourseInputOutputManager::connect_editCourseForm() {
    connect(editCourseForm->getBackButton(),SIGNAL(clicked()),this,SLOT(on_editCourseForm_backButton()));
    connect(editCourseForm->getCreateButton(),SIGNAL(clicked()),this,SLOT(on_editCourseForm_createButton()));
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
void CourseInputOutputManager::on_editCourseForm_createButton() {

    //selectedCourse
    selectedCourse->setCourseCode(editCourseForm->getCourseCodeTextBox()->text());
    selectedCourse->setCourseSection(editCourseForm->getCourseSectionTextBox()->text());
    selectedCourse->setInstructor(editCourseForm->getInstructorTextBox()->text());
}
void CourseInputOutputManager::on_editCourseForm_linkTextbookButton() {
    linkTextbookForm = new LinkTextbookFormWindow();
    //linkTextbookForm =
}

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

    populateTermComboBox(editCourseForm->getTermComboBox());
    createCFlag = 0;
}

void CourseInputOutputManager::on_manageCoursesInterface_editCourse_button(){
    qDebug() << "Edit Course Button clicked";
    editCourseForm = new ModifyCourseFormWindow();
    connect_editCourseForm();
    editCourseForm->show();
    manageCoursesInterface->hide();

    int selectedCourseIndex = manageCoursesInterface->getCourseListView()->currentIndex().row();
    if(selectedCourseIndex == -1) {
        qDebug() << "no course selected";
    }
    selectedCourse = fakeCourses->at(selectedCourseIndex);

    editCourseForm->getCourseCodeTextBox()->setText(selectedCourse->getCourseCode());
    editCourseForm->getCourseSectionTextBox()->setText(selectedCourse->getCourseSection());
    populateTermComboBox(editCourseForm->getTermComboBox());
    editCourseForm->getTermComboBox()->setCurrentIndex(manageCoursesInterface->getTermSelectOption()->currentIndex());
    editCourseForm->getInstructorTextBox()->setText(selectedCourse->getInstructor());

    createCFlag = 1;
}

void CourseInputOutputManager::on_manageCoursesInterface_deleteCourse_button(){
    qDebug() << "Delete Course button clicked";

}

void CourseInputOutputManager::on_manageCoursesInterface_termSelected(){
    qDebug() << "Term Selected button clicked";
    int selectedTermIndex = manageCoursesInterface->getTermSelectOption()->currentIndex();
    Term* selectedTerm = fakeTerms->at(selectedTermIndex);
    fakeCourses = courseManagementFacade->retrieveCourseList(selectedTerm);
    buildCourseModel();
    setCourseManagementInterfaceViewModel(manageCoursesInterface->getCourseListView(),courseModel);
}

void CourseInputOutputManager::on_manageCoursesInterface_selectCourse(){
    qDebug() << "Selected Course";

    int selectedCourseIndex = manageCoursesInterface->getCourseListView()->currentIndex().row();
    qDebug() << 1;
    selectedCourse = fakeCourses->at(selectedCourseIndex);
    qDebug() << 1;
    qDebug() << selectedCourse->getRequiredTextbooks().length();
    foreach(Textbook* t, selectedCourse->getRequiredTextbooks()) {
        qDebug() << 1;
        fakeLinkedTextbooks->push_back(t);
    }
    qDebug() << 1;

    //fakeLinkedTextbooks = selectedCourse->getRequiredTextbooks();



    buildLinkedTextbookModel();
    qDebug() << 1;
    setCourseManagementInterfaceViewModel(manageCoursesInterface->getAssignedTextbooksListView(),linkedTextbookModel);

}



