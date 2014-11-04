#include "login.h"
#include "ui_login.h"
#include "Term.h"
#include "Textbook.h"
#include "Chapter.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    // setup db connection
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../cuTPS.db");

    if(!db.open())
        qDebug() << "FAILED TO CONNECT TO DATA BASE";
    else {
        qDebug() << "CONNECT TO DATA BASE";

        // test for view studentView
        foreach(Course *crs, studentViewTextbooks("100853074", 1)){
            QJsonObject *json = new QJsonObject();
            crs->write(*json);
            qDebug() << *json;
        }

        //if there was a connection end it
        QSqlDatabase::database().commit();
    }
}

Login::~Login()
{
    delete ui;
}

QList<Course*>& Login::studentViewTextbooks(QString studentNumber, qint32 termID) const{
    QList<Course*> *courses = new QList<Course*>();

    // get all courses in the term for a perticular student
    QSqlQuery courseQuery;
    courseQuery.prepare("SELECT Course.courseCode, "
                                "Course.section, "
                                "Course.instructor, "
                                "Term.startDate, "
                                "Term.endDate, "
                                "Term.termID "
                            "FROM Course "
                            "JOIN Student_RegisteredIn_Course ON "
                                "Course.courseCode = Student_RegisteredIn_Course.courseCode AND "
                                "Course.section = Student_RegisteredIn_Course.section AND "
                                "Course.termID = Student_RegisteredIn_Course.termID "
                            "JOIN Student ON "
                                "student_RegisteredIn_Course.studentNumber = Student.studentNumber "
                            "JOIN term ON "
                                "Course.termID = Term.TermID "
                            "WHERE Course.termID=:termID AND student.studentNumber=:studentNumber "
                                "ORDER BY Course.courseCode ASC, Course.section ASC;");
    courseQuery.bindValue(":termID", termID);
    courseQuery.bindValue(":studentNumber", studentNumber);
    courseQuery.exec();

    while (courseQuery.next()){
        Course *course = new Course(courseQuery.value(courseQuery.record().indexOf("courseCode")).toString(),
                                   courseQuery.value(courseQuery.record().indexOf("section")).toString(),
                                   courseQuery.value(courseQuery.record().indexOf("instructor")).toString());
        course->setTerm(*(new Term(QDate::fromString(courseQuery.value(courseQuery.record().indexOf("startDate")).toString(), "yyyyMMdd"),
                                   QDate::fromString(courseQuery.value(courseQuery.record().indexOf("endDate")).toString(), "yyyyMMdd"),
                                   courseQuery.value(courseQuery.record().indexOf("termID")).toInt())));

        // get all textbooks for this course
        QSqlQuery textBookQuery;
        textBookQuery.prepare("SELECT Textbook.textBookTitle, "
                                    "Textbook.author, "
                                    "Textbook.edition, "
                                    "Textbook.publisher, "
                                    "Textbook.ISBN, "
                                    "Textbook.desc, "
                                    "Textbook.itemID, "
                                    "PurchasableItem.price, "
                                    "PurchasableItem.availability, "
                                    "Textbook.coverImageLocation "
                                "FROM Textbook "
                                "JOIN Course_Assigned_Textbook ON "
                                    "Textbook.ISBN = Course_Assigned_Textbook.ISBN "
                                "JOIN Course ON "
                                    "Course_Assigned_Textbook.courseCode = Course.courseCode AND "
                                    "Course_Assigned_Textbook.section = Course.section AND "
                                    "Course_Assigned_Textbook.termID = Course.termID "
                                "JOIN PurchasableItem ON "
                                    "Textbook.itemID = PurchasableItem.ItemID "
                                "WHERE Course.courseCode=:courseCode AND Course.section=:section AND Course.termID=:termID "
                                    "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC;");
        textBookQuery.bindValue(":courseCode", course->getCourseCode());
        textBookQuery.bindValue(":section", course->getCourseSection());
        textBookQuery.bindValue(":termID", course->getTerm()->getTermID());
        textBookQuery.exec();

         while (textBookQuery.next()){
             Textbook *textbook = new Textbook(textBookQuery.value(textBookQuery.record().indexOf("textBookTitle")).toString(),
                                               textBookQuery.value(textBookQuery.record().indexOf("author")).toString(),
                                               textBookQuery.value(textBookQuery.record().indexOf("edition")).toString(),
                                               textBookQuery.value(textBookQuery.record().indexOf("publisher")).toString(),
                                               textBookQuery.value(textBookQuery.record().indexOf("ISBN")).toString(),
                                               textBookQuery.value(textBookQuery.record().indexOf("desc")).toString(),
                                               textBookQuery.value(textBookQuery.record().indexOf("itemID")).toInt(),
                                               textBookQuery.value(textBookQuery.record().indexOf("price")).toDouble(),
                                               textBookQuery.value(textBookQuery.record().indexOf("availability")).toBool());
             textbook->setCoverImageLoc(textBookQuery.value(textBookQuery.record().indexOf("coverImageLocation")).toString());

             // get all chapters for this textbook
             QSqlQuery chapterQuery;
             chapterQuery.prepare("SELECT Chapter.chapterTitle, "
                                        "Chapter.chapterNumber, "
                                        "Chapter.itemID, "
                                        "PurchasableItem.price, "
                                        "PurchasableItem.availability "
                                    "FROM Chapter "
                                    "JOIN Textbook ON "
                                        "Chapter.ISBN = Textbook.ISBN "
                                    "JOIN PurchasableItem ON "
                                        "Chapter.itemID = PurchasableItem.ItemID "
                                    "WHERE Textbook.ISBN=:ISBN "
                                        "ORDER BY Chapter.chapterNumber ASC;");
             chapterQuery.bindValue(":ISBN", textbook->getISBN());
             chapterQuery.exec();

             while (chapterQuery.next()){
                Chapter *chapter = new Chapter(chapterQuery.value(chapterQuery.record().indexOf("chapterTitle")).toString(),
                                               chapterQuery.value(chapterQuery.record().indexOf("chapterNumber")).toInt(),
                                               chapterQuery.value(chapterQuery.record().indexOf("itemID")).toInt(),
                                               chapterQuery.value(chapterQuery.record().indexOf("price")).toDouble(),
                                               chapterQuery.value(chapterQuery.record().indexOf("availability")).toBool());

                    // get all section for this chapter
                    QSqlQuery sectionQuery;
                    sectionQuery.prepare("SELECT section.sectionTitle, "
                                                "section.sectionNumber, "
                                                "section.itemID, "
                                                "PurchasableItem.price, "
                                                "PurchasableItem.availability "
                                            "FROM Section "
                                            "JOIN Chapter ON "
                                                "section.ISBN = Chapter.ISBN AND "
                                                "section.chapterNumber = Chapter.chapterNumber "
                                            "JOIN PurchasableItem ON "
                                                "section.itemID = PurchasableItem.ItemID "
                                            "WHERE Chapter.ISBN=:ISBN AND Chapter.chapterNumber=:chapterNumber "
                                                "ORDER BY Section.sectionNumber ASC;");
                    sectionQuery.bindValue(":ISBN", textbook->getISBN());
                    sectionQuery.bindValue(":chapterNumber", chapter->getChapterNumber());
                    sectionQuery.exec();

                    while (sectionQuery.next()){
                       Section *section = new Section(sectionQuery.value(sectionQuery.record().indexOf("sectionTitle")).toString(),
                                                      sectionQuery.value(sectionQuery.record().indexOf("sectionNumber")).toInt(),
                                                      sectionQuery.value(sectionQuery.record().indexOf("itemID")).toInt(),
                                                      sectionQuery.value(sectionQuery.record().indexOf("price")).toDouble(),
                                                      sectionQuery.value(sectionQuery.record().indexOf("availability")).toBool());
                       chapter->addSection(section);
                    }
                textbook->addChapter(chapter);
             }
             course->addTextbook(textbook);
         }
         courses->push_back(course);
    }
    return *courses;
}
