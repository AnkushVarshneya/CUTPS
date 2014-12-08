#include "ContentManagementFacade.h"

ContentManagementFacade::ContentManagementFacade()
{


//    Textbook    *text = new Textbook();
//    Textbook    *treeText = new Textbook("all about trees", "david suzuki","3rd ed");
//    Chapter *chp1 = new Chapter();
//    Chapter *chp2 = new Chapter("chp2", 2, 64, 22, true);
//    Chapter *chp3 = new Chapter("chapter 3", 3, 11, 77, true);
//    treeText->addChapter(chp1);
//    treeText->addChapter(chp2);
//    treeText->addChapter(chp3);


//    Section *sec1 = new Section("1st sec");
//    sec1->setSectionNumber(1);

//    Section *sec2 = new Section("1nd sec diff chapter");
//    sec2->setSectionNumber(1);
//    sec2->setItemID(10);

//    Section *sec3 = new Section("2rd sec");
//    sec3->setSectionNumber(2);
//    sec3->setItemID(11);

//    chp1->addSection(sec1);
//    chp2->addSection(sec2);
//    chp2->addSection(sec3);

//    treeText->setPrice(12.50);
//    chp1->setPrice(5.00);
//    chp2->setPrice(10.00);
//    chp3->setPrice(15.00);

//    sec1->setPrice(1);
//    sec2->setPrice(2);
//    sec3->setPrice(3);

    //fakeTextbooks = *(updateControl.retrieveAllContent());
    //fakeTextbooks.append(text);
    //fakeTextbooks.append(treeText);
}

QList<Textbook*>  ContentManagementFacade::viewAllContent() {
    qDebug() << "view all content";

    return *(updateControl.retrieveAllContent());
}

bool ContentManagementFacade::updateContent(Textbook* text){
    return updateControl.updateContent(text);
}

bool ContentManagementFacade::deleteContent(PurchasableItem* item){
    return updateControl.deleteContent(item);
}
