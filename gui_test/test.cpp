

#include "Term.h"
#include "Chapter.h"
#include "PurchasableItem.h"
#include "Textbook.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
    QDate date = QDate(1,4,20);

  //  cout << date.toString();
    cout << date.toString().toStdString() << endl;


    Textbook textbook;
    Chapter* chapter = new Chapter();
    Section* section = new Section();

    textbook.addChapter(chapter);
    textbook.getChapter(chapter->getChapterNumber());

    return 0;
}
