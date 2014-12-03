#include "StudentInputOutputManager.h"

StudentInputOutputManager::StudentInputOutputManager()
{
    studentInterface = new StudentInterfaceWindow();
    studentInterface->show();

    //connect signals from boundary options to slot functions on the student i/o manager
    connect(studentInterface->getAddTextbookOption(), SIGNAL( clicked() ), this, SLOT(on_studentInterface_addTextbookOptionSelected()));
    connect(studentInterface->getViewCartOption(), SIGNAL(clicked()), this, SLOT(on_studentInterface_viewCartOptionSelected()));
    connect(studentInterface->getViewDetailsOption(), SIGNAL(clicked()), this, SLOT(on_studentInterface_viewDetailsOptionSelected()));
    connect(studentInterface->getTermSelectOption(), SIGNAL(activated(QString)), this, SLOT(on_studentInterface_termSelected()));

    //construct the shopping management facade
    this->shopFacade = new ShoppingManagementFacade();


    //make some fake courses
    crs1 = new Course();
    crs2 = new Course("COMP666", "A", "prof");

        Textbook    *text = new Textbook();
        Textbook    *treeText = new Textbook("all about trees", "david suzuki","3rd ed");
        Chapter *chp1 = new Chapter();
        Chapter *chp2 = new Chapter("chp2", 2, 64, 22, true);
        Chapter *chp3 = new Chapter("chapter 3", 3, 11, 77, true);
        treeText->addChapter(chp1);
        treeText->addChapter(chp2);
        treeText->addChapter(chp3);

        Section *sec1 = new Section("1st sec");
        sec1->setSectionNumber(1);

        Section *sec2 = new Section("1nd sec diff chapter");
        sec2->setSectionNumber(1);
        sec2->setItemID(10);

        Section *sec3 = new Section("2rd sec");
        sec3->setSectionNumber(2);
        sec3->setItemID(11);

        chp1->addSection(sec1);
        chp2->addSection(sec2);
        chp2->addSection(sec3);
    crs1->addTextbook(text);
    crs2->addTextbook(treeText);

    fakeCourses.append(crs1);
    fakeCourses.append(crs2);

    OurStandardItem *osicrs1 = new OurStandardItem(crs1);
    OurStandardItem *osicrs2 = new OurStandardItem(crs2);
    qDebug() << "made a course item, did it work?";
    qDebug() << osicrs1->data();

}


void StudentInputOutputManager::on_studentInterface_addTextbookOptionSelected() {

}

void StudentInputOutputManager::on_studentInterface_viewCartOptionSelected() {

}

void StudentInputOutputManager::on_studentInterface_viewDetailsOptionSelected() {

}

void StudentInputOutputManager::on_studentInterface_termSelected() {
    //should populate list of books
    //todo: make standard items out of courses

}
