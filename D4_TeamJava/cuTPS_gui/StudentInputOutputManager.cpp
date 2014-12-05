#include "StudentInputOutputManager.h"

StudentInputOutputManager::StudentInputOutputManager()
{
    courseAndTextbookModel = new QStandardItemModel(this);
    chaptersAndSectionsModel = new QStandardItemModel(this);
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
    fakeStudent->setStudentNum("100853074");


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
    //ryan's TODO: just list books with course prefixed in text only, no need for tree for list of books.
    //do use a tree for chapters and sections. should be able to use two views without having to explicitly
    //hide anything.


    courseAndTextbookModel->clear();
    chaptersAndSectionsModel->clear();
    OurStandardItem *temp;
    QList<Course*>::iterator i;
    for (i = coursesAndContent.begin(); i != coursesAndContent.end(); i++) {
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

    qDebug() << "wut: " << courseAndTextbookModel->itemFromIndex( studentInterface->getCourseTreeView()->currentIndex() )->data();
    qDebug() << "thing selected: " << studentInterface->getCourseTreeView()->currentIndex().data();

    QList<Course*>::iterator it;
    QList<Textbook*>::iterator at;

    for(it = coursesAndContent.begin(); it != coursesAndContent.end(); it ++) {
        //qDebug() << (*it)->getRequiredTextbooks();
        for (at = (*it)->getRequiredTextbooks().begin(); at != (*it)->getRequiredTextbooks().end(); at++) {
            qDebug() << "not crashed? isbn is: " << (*at)->getISBN();
        }

    }

    chaptersAndSectionsModel->clear();

    chaptersAndSectionsModel->appendRow( courseAndTextbookModel->itemFromIndex( studentInterface->getCourseTreeView()->currentIndex() )->child(0));
    qDebug() << "testing second model";
    qDebug() <<  courseAndTextbookModel->itemFromIndex(studentInterface->getCourseTreeView()->currentIndex())->text();
    qDebug() << "second model row count: " << chaptersAndSectionsModel->rowCount();

//    textbookDetailsWindow = new TextbookDetailsWindow();
//    textbookDetailsWindow->show();

}

void StudentInputOutputManager::on_studentInterface_termSelected() {
    qDebug() << "a term has been selected";
    qDebug() << terms.value( studentInterface->getTermSelectOption()->currentIndex() )->getTermName();

   coursesAndContent = shopFacade->viewContent(fakeStudent,
                            terms.at( studentInterface->getTermSelectOption()->currentIndex() ));

    buildCourseAndTextbookModel();
    this->setStudentInterfaceViewModel(studentInterface->getCourseTreeView(), courseAndTextbookModel);
    this->setStudentInterfaceViewModel(studentInterface->getChaptersAndSectionsTreeView(), chaptersAndSectionsModel);

    //hide chapters and sections in the course tree view
    for (int i = 0; i < courseAndTextbookModel->rowCount(); i ++) {
            for(int j = 0; j < courseAndTextbookModel->item(i)->rowCount(); j++)
            {
                for (int k = 0; k < courseAndTextbookModel->item(i)->child(j)->rowCount(); k++) {
                    studentInterface->getCourseTreeView()->setRowHidden(k, courseAndTextbookModel->item(i)->child(j)->index(), true );
                }
            }
    }

}
