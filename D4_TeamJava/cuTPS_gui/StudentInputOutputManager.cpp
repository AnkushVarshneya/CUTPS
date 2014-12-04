#include "StudentInputOutputManager.h"

StudentInputOutputManager::StudentInputOutputManager()
{
    courseAndTextbookModel = new QStandardItemModel(this);
    studentInterface = new StudentInterfaceWindow();
    studentInterface->show();

    //connect signals from boundary options to slot functions on the student i/o manager
    connect(studentInterface->getAddTextbookOption(), SIGNAL( clicked() ), this, SLOT(on_studentInterface_addTextbookOptionSelected()));
    connect(studentInterface->getViewCartOption(), SIGNAL(clicked()), this, SLOT(on_studentInterface_viewCartOptionSelected()));
    connect(studentInterface->getViewDetailsOption(), SIGNAL(clicked()), this, SLOT(on_studentInterface_viewDetailsOptionSelected()));
    connect(studentInterface->getTermSelectOption(), SIGNAL(activated(QString)), this, SLOT(on_studentInterface_termSelected()));


    //construct the shopping management facade
    this->shopFacade = new ShoppingManagementFacade();
    this->getTerms();
    fakeStudent = new Student();

}

void    StudentInputOutputManager::getTerms() {
    terms = shopFacade->getTermList();

    //populate the ui widget
    QList<Term*>::iterator i;
    for (i = terms.begin(); i != terms.end(); i++) {
        qDebug() << "iterating over term list";
        studentInterface->getTermSelectOption()->addItem((*i)->getTermName(), (*i)->getTermName() );
    }
    //todo: what if it fails etc
}


void StudentInputOutputManager::buildCourseAndTextbookModel() {
    courseAndTextbookModel->clear();
    OurStandardItem *temp;
    QList<Course*>::iterator i;
    for (i = fakeCourses.begin(); i != fakeCourses.end(); i++) {
        qDebug() << (*i)->getCourseCode();
        temp = new OurStandardItem( *i );
        qDebug() << (*i);
        courseAndTextbookModel->appendRow(temp);
    }
}

void StudentInputOutputManager::setStudentInterfaceViewModel(QAbstractItemView *view, QStandardItemModel *model) {
view->setModel(model);
}

void StudentInputOutputManager::on_studentInterface_addTextbookOptionSelected() {

}

void StudentInputOutputManager::on_studentInterface_viewCartOptionSelected() {

}

void StudentInputOutputManager::on_studentInterface_viewDetailsOptionSelected() {

    qDebug() << courseAndTextbookModel->itemFromIndex( studentInterface->getCourseTreeView()->currentIndex() )->data();

    qDebug() << studentInterface->getCourseTreeView()->currentIndex().data();

}

void StudentInputOutputManager::on_studentInterface_termSelected() {
    qDebug() << "a term has been selected";
    qDebug() << terms.value( studentInterface->getTermSelectOption()->currentIndex() )->getTermName();
   fakeCourses = shopFacade->viewContent(fakeStudent,
                            terms.at( studentInterface->getTermSelectOption()->currentIndex() ));

    buildCourseAndTextbookModel();
    this->setStudentInterfaceViewModel(studentInterface->getCourseTreeView(), courseAndTextbookModel);

}
