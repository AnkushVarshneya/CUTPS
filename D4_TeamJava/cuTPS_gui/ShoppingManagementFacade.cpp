#include "ShoppingManagementFacade.h"

ShoppingManagementFacade::ShoppingManagementFacade()
{
    shopUpdateControl = new ShopUpdateControl();


    //fake terms for testing
    int year, month, day;
    year = 2014;
    month = 9;
    day = 4;
    QDate startDate = QDate(year, month, day);
    month = 12;
    day = 21;
    QDate endDate = QDate(year, month, day);
    Term *tf14 = new Term(startDate,endDate);
    tf14->setTermName("Fall 2014");

    year = 2015;
    month = 1;
    day = 6;
    startDate = QDate(year, month, day);
    month = 4;
    day = 28;
    endDate = QDate(year, month, day);
    Term *tw15 = new Term(startDate, endDate);
    tw15->setTermName("Winter 2015");

    fakeTerms.append(tf14);
    fakeTerms.append(tw15);

    //make some fake courses
    Course *crs1 = new Course();
    crs1->setTerm(tf14);
    Course *crs2 = new Course("COMP666", "A", "prof");
    crs2->setTerm(tw15);

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

}

QList<Term*>    ShoppingManagementFacade::getTermList() {
    return *shopUpdateControl->retrieveAllTerms();

}

QList<Course*>  ShoppingManagementFacade::viewContent(Student *student, Term *term) {
    qDebug() << "view content called with student: " << student->getStudentNum();
    qDebug() << "and term: " << term->getTermName();

    return *shopUpdateControl->retrieveContent(student, term);
}
