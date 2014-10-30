

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


    Textbook*   textbook    = new Textbook();
    Chapter*    chapter1    = new Chapter("Ryan Lays down the Law", 1);
    Chapter*    chapter2    = new Chapter("Robert Nguyen's Greatest Hits", 2);
    Chapter*    chapter3    = new Chapter("Ankush's Drug Dealing Ways", 3);
    //Section*    section    = new Section();
    textbook->addChapter(chapter1);
    textbook->addChapter(chapter2);
    textbook->addChapter(chapter3);

    Section*    c1sect1    = new Section("Legalese 101", 1);
    Section*    c1sect2    = new Section("Ryan's Roadsters", 2);
    Section*    c2sect1    = new Section("Chair Wars Episode XVI", 1);
    chapter1->addSection(c1sect1);
    chapter1->addSection(c1sect2);

    chapter3->addSection(c2sect1);
    //cout << *textbook->getChapter(3);
    //cout << *chapter3;

    cout << *textbook;
    return 0;
}

