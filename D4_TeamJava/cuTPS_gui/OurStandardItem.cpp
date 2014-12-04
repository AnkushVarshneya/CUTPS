#include "OurStandardItem.h"

//OurStandardItem::OurStandardItem(QObject *parent) :
//    QStandardItem(parent)
//{
//}
 OurStandardItem::OurStandardItem(PurchasableItem *item) {
    this->setData(item->getItemID());
    this->setText(item->getItemTitle());
}

 OurStandardItem::OurStandardItem(Course *course) {
     this->setData(course->getCourseCode());
     this->setText(course->getCourseCode());

     for (int i = 0; i < course->getRequiredTextbooks().count(); i++) {
         OurStandardItem *temp = new OurStandardItem(course->getBook(), false);
         this->setChild(i, temp);
     }
 }

  OurStandardItem::OurStandardItem(Textbook *textbook, bool makeItemsForChildren) {
     this->setData(textbook->getItemID());
     this->setText(textbook->getItemTitle());

      if (makeItemsForChildren) {
         for(int i = 0; i < textbook->getChapterList().count(); i++){
                qDebug() << textbook->getChapter(i + 1)->getItemTitle(); //i because there is no 0 chapter
                OurStandardItem *temp = new OurStandardItem(textbook->getChapter(i + 1), this);
                this->setChild(i, temp);
         }
      }
 }



  OurStandardItem::OurStandardItem(Chapter *chapter, OurStandardItem *parent) {
      qDebug() << "making item from chapter";
     this->setData(chapter->getItemID());
     this->setText(chapter->getItemTitle());
     for(int i = 0; i < chapter->getChapterSections().count(); i ++) {
         qDebug() << chapter->getSection(i + 1)->getItemTitle();
         OurStandardItem *temp = new OurStandardItem(chapter->getSection(i + 1), this);
         this->setChild(i, temp);
     }

 }

  OurStandardItem::OurStandardItem(Section *section, OurStandardItem *parent) {
      this->setData(section->getItemID());
      this->setText(section->getItemTitle());
      qDebug() << "data" << this->data();
      qDebug() << "text" << this->text();

  }
