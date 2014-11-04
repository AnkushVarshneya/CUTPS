#include "login.h"
#include "ui_login.h"
#include "Term.h"
#include "Course.h"
#include "Textbook.h"
#include "Chapter.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    //ui->setupUi(this);

    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../cuTPS.db");

    qDebug() << "started";

    if(!db.open())
        qDebug() << "FAILED TO CONNECT TO DATA BASE";
    else {
         qDebug() << "connected....";
         qint32 tid = 1;
         QString sNum = "100853074";

        // get term
        QSqlQuery termQuery;
        termQuery.prepare(" SELECT * FROM term WHERE termID=:termID;");
        termQuery.bindValue(":termID", tid);
        termQuery.exec();

        while (termQuery.next()) {
            qDebug() << "term...";

            Term *term = new Term(QDate::fromString(
                                      termQuery.value(termQuery.record().indexOf("startDate")).toString(),
                                      "yyyyMMdd"),
                                  QDate::fromString(
                                      termQuery.value(termQuery.record().indexOf("endDate")).toString(),
                                      "yyyyMMdd"),
                                  termQuery.value(termQuery.record().indexOf("termID")).toInt());

            // get all courses in the term for a perticular student
            QSqlQuery courseQuery;
            courseQuery.prepare("SELECT * FROM Student "
                                    "JOIN Student_RegisteredIn_Course ON "
                                        "student.studentNumber = Student_RegisteredIn_Course.studentNumber "
                                    "JOIN Course ON "
                                        "Student_RegisteredIn_Course.courseCode = Course.courseCode AND "
                                        "Student_RegisteredIn_Course.section = Course.section AND "
                                        "Student_RegisteredIn_Course.termID = Course.termID "
                                    "WHERE Course.termID=:termID AND student.studentNumber=:studentNumber "
                                        "ORDER BY Course.courseCode ASC, Course.section ASC; ");
            courseQuery.bindValue(":termID", term->getTermID());
            courseQuery.bindValue(":studentNumber", sNum);
            courseQuery.exec();

            while (courseQuery.next()){
                qDebug() << "course...";

                Course *course = new Course(courseQuery.value(courseQuery.record().indexOf("courseCode")).toString(),
                                           courseQuery.value(courseQuery.record().indexOf("section")).toString(),
                                           courseQuery.value(courseQuery.record().indexOf("instructor")).toString());
                course->setTerm(*term);

                // get all textbooks for this course
                QSqlQuery textBookQuery;
                textBookQuery.prepare("SELECT * FROM Textbook "
                                        "JOIN Course_Assigned_Textbook ON "
                                            "Textbook.ISBN = Course_Assigned_Textbook.ISBN "
                                        "JOIN Course ON "
                                            "Course_Assigned_Textbook.courseCode = Course.courseCode AND "
                                            "Course_Assigned_Textbook.section = Course.section AND "
                                            "Course_Assigned_Textbook.termID = Course.termID "
                                        "JOIN PurchasableItem ON "
                                            "Textbook.itemID = PurchasableItem.ItemID "
                                        "WHERE Course.courseCode=:courseCode AND Course.section=:section AND Course.termID=:termID "
                                            "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC; ");
                textBookQuery.bindValue(":courseCode", course->getCourseCode());
                textBookQuery.bindValue(":section", course->getCourseSection());
                textBookQuery.bindValue(":termID", course->getTerm()->getTermID());
                textBookQuery.exec();

                 while (textBookQuery.next()){
                     qDebug() << "textbook...";

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
                     chapterQuery.prepare("SELECT * from Textbook "
                                            "JOIN Chapter ON "
                                                "Textbook.ISBN = Chapter.ISBN "
                                            "JOIN PurchasableItem ON "
                                                "Chapter.itemID = PurchasableItem.ItemID "
                                            "WHERE Textbook.ISBN=:ISBN "
                                                "ORDER BY Chapter.chapterNumber ASC;");
                     chapterQuery.bindValue(":ISBN", textbook->getISBN());
                     chapterQuery.exec();

                     while (chapterQuery.next()){
                        qDebug() << "chapter...";

                        Chapter *chapter = new Chapter(chapterQuery.value(chapterQuery.record().indexOf("chapterTitle")).toString(),
                                                       chapterQuery.value(chapterQuery.record().indexOf("chapterNumber")).toInt(),
                                                       chapterQuery.value(chapterQuery.record().indexOf("itemID")).toInt(),
                                                       chapterQuery.value(chapterQuery.record().indexOf("price")).toDouble(),
                                                       chapterQuery.value(chapterQuery.record().indexOf("availability")).toBool());

                            // get all section for this chapter
                            QSqlQuery sectionQuery;
                            sectionQuery.prepare("SELECT * FROM Chapter "
                                                   "JOIN Section ON "
                                                       "Chapter.ISBN = section.ISBN AND "
                                                       "Chapter.chapterNumber = section.chapterNumber "
                                                   "JOIN PurchasableItem ON "
                                                       "section.itemID = PurchasableItem.ItemID "
                                                   "WHERE Chapter.ISBN=:ISBN AND Chapter.chapterNumber=:chapterNumber "
                                                       "ORDER BY Section.sectionNumber ASC;");
                            sectionQuery.bindValue(":ISBN", textbook->getISBN());
                            sectionQuery.bindValue(":chapterNumber", chapter->getChapterNumber());
                            sectionQuery.exec();

                            while (sectionQuery.next()){
                               qDebug() << "section...";

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
                 term->addCourse(course);
            }
            QJsonObject *json = new QJsonObject();
            term->write(*json);
            qDebug() << *json;
        }
    }
}

Login::~Login()
{
    delete ui;
}
