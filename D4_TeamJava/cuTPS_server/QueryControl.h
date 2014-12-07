#ifndef QUERYCONTROL_H
#define QUERYCONTROL_H

#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "Course.h"
#include "PaymentInformation.h"
#include "Term.h"
#include "Textbook.h"
#include "Chapter.h"

class QueryControl
{

public:
    QueryControl();
    ~QueryControl();

    void test();

    bool resetDatabase();
    bool resetSchema();

    // term options
    QList<Term*>* retrieveTermList();

    // Course operations
    bool updateCourse(Course*, qint32);
    bool deleteCourse(Course*, qint32);
    QList<Course*>* retrieveStudentCourseList(QString, qint32);
    QList<Course*>* retrieveCourseList(qint32);

    // Textbook operations
    bool updateTextbook(Textbook*);
    bool deleteTextbook(Textbook*);
    Textbook* retrieveTextbook(QString, bool);
    QList<Textbook*>* retrieveTextbookList(Course*, qint32, bool);
    QList<Textbook*>* retrieveAllTextbookList();

    // Chapter operations
    bool updateChapter(Chapter*, QString);
    bool deleteChapter(Chapter*, QString);
    Chapter* retrieveChapter(qint32, QString, bool);
    QList<Chapter*>* retrieveChapterList(QString, bool);

    // Section operations
    bool updateSection(Section*, qint32, QString);
    bool deleteSection(Section*, qint32, QString);
    Section* retrieveSection(qint32, qint32, QString, bool);
    QList<Section*>* retrieveSectionList(qint32, QString, bool);

    // linking operations on course
    bool updateCourseTextbookLink(Course*, qint32, Textbook*);
    bool updateCourseStudentLink(Course*, qint32, Student*);

    // Student operation
    bool updatePaymentInformation(Student*, PaymentInformation*);
    PaymentInformation* retrievePaymentInformation(Student*);
    Student* retrieveStudent(QString);
    QList<Student*>* retrieveStudentList(Course*, qint32);

    // purchasable item & shopping cart operation
    bool updatePurchasableItem(PurchasableItem*);
    bool deletePurchasableItem(PurchasableItem*);
    QList< QPair<PurchasableItem*,qint32> >* getShoppingCartItemList(Student*, bool);
    QList<PurchasableItem*>* getPurchasableItemList(bool);
    bool emptyShoppingCart(Student*);
    bool addPurchasableItemToCart(PurchasableItem*, Student*);
    bool updateOrderContents(PurchasableItem*, Student*);

private:
    QSqlDatabase db;
};

#endif
