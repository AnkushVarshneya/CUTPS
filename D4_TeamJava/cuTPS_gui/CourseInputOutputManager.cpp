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
    linkedTextbookModel = new QStandardItemModel(this);

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
    linkedTextbookModel->clear();
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
void CourseInputOutputManager::connect_deleteCourseConfirmationForm() {
    connect(confirmationForm->getYesButton(),SIGNAL(clicked()),this,SLOT(on_deleteCourseConfirmationForm_yesButton()));
    connect(confirmationForm->getNoButton(),SIGNAL(clicked()),this,SLOT(on_deleteCourseConfirmationForm_noButton()));
}

void CourseInputOutputManager::on_deleteCourseConfirmationForm_yesButton() {
    int selectedCourseIndex = manageCoursesInterface->getCourseListView()->currentIndex().row();
    selectedCourse = fakeCourses->at(selectedCourseIndex);
    fakeCourses->removeAll(selectedCourse);

    fakeTextbooks = courseManagementFacade->retrieveAllTextbooks();



    courseManagementFacade->deleteCourse(selectedCourse,selectedCourse->getTerm());

    fakeTextbooks = courseManagementFacade->retrieveAllTextbooks();
    populateTermComboBox(manageCoursesInterface->getTermSelectOption());
    buildCourseModel();
    setCourseManagementInterfaceViewModel(manageCoursesInterface->getCourseListView(),courseModel);

    delete confirmationForm;
}
void CourseInputOutputManager::on_deleteCourseConfirmationForm_noButton() {
    //confirmationForm->setModal(false);
    delete confirmationForm;
}

void CourseInputOutputManager::on_editCourseForm_backButton() {

    if(createOrEditCFlag == 0)
        delete selectedCourse;


    manageCoursesInterface->show();
    //editCourseForm->hide();
    delete editCourseForm;
}
void CourseInputOutputManager::on_editCourseForm_createButton() {
    try{
        int newTermIndex = editCourseForm->getTermComboBox()->currentIndex();
        Term* newTerm = fakeTerms->at(newTermIndex);

        //selectedCourse->setTerm(newTerm);
        selectedCourse->setCourseCode(editCourseForm->getCourseCodeTextBox()->text());
        selectedCourse->setCourseSection(editCourseForm->getCourseSectionTextBox()->text());
        selectedCourse->setInstructor(editCourseForm->getInstructorTextBox()->text());

        if(createOrEditCFlag == 0) {
            fakeCourses->push_back(selectedCourse);
            selectedCourse->setTerm(newTerm);

        }

        courseManagementFacade->updateCourse(selectedCourse,newTerm);

        if(createOrEditCFlag == 0) {
            foreach(Textbook* linkedTextbook,selectedCourse->getRequiredTextbooks()){
                courseManagementFacade->assignTextbookToCourse(selectedCourse,linkedTextbook,selectedCourse->getTerm());
            }
        }
        courseModel->clear();
        textbookModel->clear();
        linkedTextbookModel->clear();

        fakeTextbooks = courseManagementFacade->retrieveAllTextbooks();
        fakeTerms = courseManagementFacade->retrieveAllTermList();
        populateTermComboBox(manageCoursesInterface->getTermSelectOption());

        int selectedTermIndex = manageCoursesInterface->getTermSelectOption()->currentIndex();
        selectedTerm = fakeTerms->at(selectedTermIndex);

        fakeCourses = courseManagementFacade->retrieveCourseList(selectedTerm);

        buildCourseModel();
        setCourseManagementInterfaceViewModel(manageCoursesInterface->getCourseListView(),courseModel);

        editCourseForm->hide();
        delete editCourseForm;
        manageCoursesInterface->show();
    }
    catch(QString error){
        messageDialog.getMessageTextBox()->setText(error);
    }

}
void CourseInputOutputManager::on_editCourseForm_linkTextbookButton() {
    linkTextbookForm = new LinkTextbookFormWindow();
    linkTextbookForm->show();

    connect_linkTextbookForm();

    editCourseForm->hide();

    buildTextbookModel();
    setCourseManagementInterfaceViewModel(linkTextbookForm->getAllTextbooksListView(),textbookModel);

    buildLinkedTextbookModel();
    setCourseManagementInterfaceViewModel(linkTextbookForm->getRegisteredTextbooksListView(),linkedTextbookModel);
}

void CourseInputOutputManager::on_linkTextbookForm_backButton() {
    editCourseForm->show();
    //linkTextbookForm->hide();
    delete linkTextbookForm;
}
void CourseInputOutputManager::on_linkTextbookForm_linkTextbookButton() {

    int selectedTextbookIndex = linkTextbookForm->getAllTextbooksListView()->currentIndex().row();
    if(selectedTextbookIndex == -1) {
        qDebug() << "no textbook selected";
        return;
    }

    Textbook* selectedTextbook = fakeTextbooks->at(selectedTextbookIndex);
    if(selectedCourse->getRequiredTextbooks().contains(selectedTextbook)){
        qDebug() << "already contains the textbook";
        return;
    }

    if(createOrEditCFlag == 1){
        courseManagementFacade->assignTextbookToCourse(selectedCourse,selectedTextbook,selectedCourse->getTerm());
    }

    selectedCourse->addTextbook(selectedTextbook);

    fakeLinkedTextbooks->push_back(selectedTextbook);

    buildLinkedTextbookModel();
    setCourseManagementInterfaceViewModel(linkTextbookForm->getRegisteredTextbooksListView(),linkedTextbookModel);
}
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

    selectedCourse = new Course("","","");

    populateTermComboBox(editCourseForm->getTermComboBox());
    createOrEditCFlag = 0;

}

void CourseInputOutputManager::on_manageCoursesInterface_editCourse_button(){
    qDebug() << "Edit Course Button clicked";

    int selectedCourseIndex = manageCoursesInterface->getCourseListView()->currentIndex().row();
    if(selectedCourseIndex == -1) {
        qDebug() << "no course selected";
        return;
    }

    editCourseForm = new ModifyCourseFormWindow();
    connect_editCourseForm();
    editCourseForm->show();
    manageCoursesInterface->hide();

    selectedCourse = fakeCourses->at(selectedCourseIndex);

    editCourseForm->getCourseCodeTextBox()->setText(selectedCourse->getCourseCode());
    editCourseForm->getCourseSectionTextBox()->setText(selectedCourse->getCourseSection());
    populateTermComboBox(editCourseForm->getTermComboBox());
    editCourseForm->getTermComboBox()->setCurrentIndex(manageCoursesInterface->getTermSelectOption()->currentIndex());
    editCourseForm->getInstructorTextBox()->setText(selectedCourse->getInstructor());

    editCourseForm->getTermComboBox()->setEnabled(false);
    editCourseForm->getCourseCodeTextBox()->setEnabled(false);
    editCourseForm->getCourseSectionTextBox()->setEnabled(false);

    createOrEditCFlag = 1;
}

void CourseInputOutputManager::on_manageCoursesInterface_deleteCourse_button(){
    qDebug() << "Delete Course button clicked";

    int selectedCourseIndex = manageCoursesInterface->getCourseListView()->currentIndex().row();
    if(selectedCourseIndex == -1) {
        qDebug() << "no course selected";
        return;
    }

    confirmationForm = new ConfirmationDialogWindow();
    confirmationForm->getMessageTextBox()->setText("Are you sure you want to delete this course?");
    connect_deleteCourseConfirmationForm();
    confirmationForm->show();
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

    fakeLinkedTextbooks->clear();
    int selectedCourseIndex = manageCoursesInterface->getCourseListView()->currentIndex().row();
    qDebug() << 1;
    selectedCourse = fakeCourses->at(selectedCourseIndex);
    qDebug() << 2;
    qDebug() << selectedCourse->getRequiredTextbooks().length();
    foreach(Textbook* t, selectedCourse->getRequiredTextbooks()) {
        qDebug() << 3;
        fakeLinkedTextbooks->push_back(t);
    }
    qDebug() << 4;

    //fakeLinkedTextbooks = selectedCourse->getRequiredTextbooks();



    buildLinkedTextbookModel();
    qDebug() << 5;
    setCourseManagementInterfaceViewModel(manageCoursesInterface->getAssignedTextbooksListView(),linkedTextbookModel);
    qDebug() << 6;

}



