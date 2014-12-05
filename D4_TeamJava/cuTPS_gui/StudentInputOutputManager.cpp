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
    chaptersAndSectionsModel->clear();
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

    qDebug() << "wut: " << courseAndTextbookModel->itemFromIndex( studentInterface->getCourseTreeView()->currentIndex() )->data();
    qDebug() << "thing selected: " << studentInterface->getCourseTreeView()->currentIndex().data();

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
   fakeCourses = shopFacade->viewContent(fakeStudent,
                            terms.at( studentInterface->getTermSelectOption()->currentIndex() ));

    buildCourseAndTextbookModel();
    this->setStudentInterfaceViewModel(studentInterface->getCourseTreeView(), courseAndTextbookModel);
    this->setStudentInterfaceViewModel(studentInterface->getChaptersAndSectionsTreeView(), chaptersAndSectionsModel);

    //hide chapters and sections in the course tree view
    for (int i = 0; i < courseAndTextbookModel->rowCount(); i ++) {
//        qDebug() << courseAndTextbookModel->item(i)->data();
//        qDebug() << "item has children?" << courseAndTextbookModel->item(i)->hasChildren();

        //rowCount() returns number of children when parent is valid, parent has default value of own model index.
            for(int j = 0; j < courseAndTextbookModel->item(i)->rowCount(); j++)
            {
                for (int k = 0; k < courseAndTextbookModel->item(i)->child(j)->rowCount(); k++) {
                    studentInterface->getCourseTreeView()->setRowHidden(k, courseAndTextbookModel->item(i)->child(j)->index(), true );
                }
            }
    }

}
