#include "OurStandardItem.h"

//OurStandardItem::OurStandardItem(QObject *parent) :
//    QStandardItem(parent)
//{
//}
 OurStandardItem::OurStandardItem(PurchasableItem *item) {
    this->setData(item->getItemID());
    this->setText(item->getItemTitle());
}

 OurStandardItem::OurStandardItem(PurchasableItem *item, qint32 quantity)
 {
     this->setData(item->getItemID());
     this->setText(item->getItemTitle() + " x " + QString::number(quantity)
                                        + " $" + QString::number(item->getPrice()));
 }

  OurStandardItem::OurStandardItem(Course *course) {
     this->setData(course->getCourseCode());
     this->setText(course->getCourseCode());

     for (int i = 0; i < course->getRequiredTextbooks().count(); i++) {
         OurStandardItem *temp = new OurStandardItem(course->getBook(), true);
         this->setChild(i, temp);
     }
 }

  OurStandardItem::OurStandardItem(Textbook *textbook, bool makeItemsForChildren) {
     this->setData(textbook->getItemID());
     this->setText(textbook->getItemTitle());

      if (makeItemsForChildren) {
         for(int i = 0; i < textbook->getChapterList().count(); i++){
                qDebug() << textbook->getChapterList()[i]->getItemTitle(); //i because there is no 0 chapter
                OurStandardItem *temp = new OurStandardItem(textbook->getChapterList()[i], this);
                this->setChild(i, temp);
         }
      }
 }

  OurStandardItem::OurStandardItem(Textbook *textbook, Course *course, bool makeItemsForChildren) {
      this->setData(textbook->getItemID());
      //this->setText(textbook->getItemTitle());
    QString  tempStr = course->getCourseCode();
    tempStr.append(": ");
    tempStr.append(textbook->getItemTitle());
    this->setText(tempStr);

       if (makeItemsForChildren) {
          for(int i = 0; i < textbook->getChapterList().count(); i++){
                 qDebug() << textbook->getChapterList()[i]->getItemTitle(); //i because there is no 0 chapter
                 OurStandardItem *temp = new OurStandardItem(textbook->getChapter(i + 1), this);
                 this->setChild(i, temp);
          }
       }
  }



  OurStandardItem::OurStandardItem(Chapter *chapter, OurStandardItem *parent) {
      qDebug() << "making item from chapter";

      if(chapter == 0)
          qDebug() << "NULL";
     this->setData(chapter->getItemID());
      qDebug() << "making1";
     this->setText(chapter->getItemTitle());
      qDebug() << "Passed setting data and set text";
     for(int i = 0; i < chapter->getChapterSections().count(); i ++) {
         qDebug() << chapter->getChapterSections()[i]->getItemTitle();

         OurStandardItem *temp = new OurStandardItem(chapter->getChapterSections()[i], this);
         this->setChild(i, temp);
     }
     qDebug() << "Passed setting chapter sections";

 }

  OurStandardItem::OurStandardItem(Section *section, OurStandardItem *parent) {
      this->setData(section->getItemID());
      this->setText(section->getItemTitle());
      qDebug() << "data" << this->data();
      qDebug() << "text" << this->text();

  }
