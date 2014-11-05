#include "login.h"
#include "ui_login.h"

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
            QJsonObject json = QJsonObject();
            crs->write(json);
            //qDebug() <<json;
        }

        // test for getExistingBillingInfo
        QJsonObject json = QJsonObject();
        PaymentInformation info = getExistingBillingInfo("100853074");
        info.write(json);
        qDebug() <<json;

        // test for saveBillingInformation use default values by calling default const.
        info.setBillInfo(*(new BillingAddress()));
        info.setCreditCardInfo(*(new CreditCardInformation()));

        if(saveBillingInformation("100853074", &info)) {
            qDebug()<<"changed it!";
            json = QJsonObject();
            PaymentInformation info2  = getExistingBillingInfo("100853074");
            info2.write(json);
            qDebug() <<json;
        }
/*
        //test for creating a textbook
        Textbook *textbook = new Textbook();
        Chapter *chapter = new Chapter();
        Section *section = new Section();
        Course *course = new Course();
        chapter->addSection(section);
        textbook->addChapter(chapter);

        qDebug() << createTextbook(textbook);
        qDebug() << createCourse(course, 1);
        qDebug() << linkTextbook(textbook, course, 1);

        // test for viewCourses
        foreach(Course *crs, viewCourses(1)){
            QJsonObject json = QJsonObject();
            crs->write(json);
            qDebug() <<json<< endl;
        }

        // test for viewCourses
        foreach(Textbook *tb, viewAllTextbooks(1)){
            QJsonObject json = QJsonObject();
            tb->write(json);
            qDebug() <<json<< endl;
        }
*/
        qDebug() << resetDatabase();
        //if there was a connection end it
        QSqlDatabase::database().commit();
    }
}

Login::~Login()
{
    delete ui;
}

bool Login::resetDatabase(){
    bool noError = true;
    QSqlQuery query;

    noError = noError && query.exec("begin transaction;");
    noError = noError && query.exec("drop table if exists Role;");
    noError = noError && query.exec("drop table if exists User;");
    noError = noError && query.exec("drop table if exists Student;");
    noError = noError && query.exec("drop table if exists PaymentInformation;");
    noError = noError && query.exec("drop table if exists Student_RegisteredIn_Course;");
    noError = noError && query.exec("drop table if exists Course;");
    noError = noError && query.exec("drop table if exists Term;");
    noError = noError && query.exec("drop table if exists Textbook;");
    noError = noError && query.exec("drop table if exists Chapter;");
    noError = noError && query.exec("drop table if exists Section;");
    noError = noError && query.exec("drop table if exists ShoppingCart;");
    noError = noError && query.exec("drop table if exists ShoppinCart_Contains_PurchasableItem;");
    noError = noError && query.exec("drop table if exists PurchasableItem;");
    noError = noError && query.exec("drop table if exists Course_Assigned_Textbook;");

    // creating the Table called Role
    noError = noError && query.exec("create table Role( "
                                        "roleID integer NOT NULL primary key, "
                                        "roleType varchar(20) "
                                    ");");
    // insert default Role(s)
    noError = noError && query.exec("insert into Role (roleID, roleType) values (1, 'Student');");
    noError = noError && query.exec("insert into Role (roleID, roleType) values (2, 'Content Manager');");
    noError = noError && query.exec("insert into Role (roleID, roleType) values (3, 'Administrator');");

    // creating the Table called User
    noError = noError && query.exec("create table User( "
                                        "userName varchar(50) NOT NULL primary key, "
                                        "fullName varchar(50), "
                                        "password varchar(20), "
                                        "roleID integer NOT NULL, "
                                        "foreign key (roleID) references Role(roleID) on delete cascade "
                                    ");");
    // insert default User(s)
    noError = noError && query.exec("INSERT INTO User (userName,fullName,password,roleID) "
                                        "VALUES ('Nooyen', 'Robert Nguyen', 'hunter', 3);");
    noError = noError && query.exec("INSERT INTO User (userName,fullName,password,roleID) "
                                        "VALUES ('BurryInAHurry', 'Graham Burry', 'huntermanager', 2);");
    noError = noError && query.exec("INSERT INTO User (userName,fullName,password,roleID) "
                                        "VALUES ('Kushlord', 'Ankush Varshneya', 'hunter1', 1);");
    noError = noError && query.exec("INSERT INTO User (userName,fullName,password,roleID) "
                                        "VALUES ('Mooreloaded', 'Ryan Moore', 'hunter2', 1);");
    noError = noError && query.exec("INSERT INTO User (userName,fullName,password,roleID) "
                                        "VALUES ('LorettaBetta','Loretta Lee','hunter3',1);");

    // creating the Table called Student
    noError = noError && query.exec("create table Student( "
                                        "studentNumber varchar(10) NOT NULL primary key, "
                                        "cmail varchar(100) NOT NULL UNIQUE, "
                                        "userName varchar(50) NOT NULL, "
                                        "foreign key (userName) references User(userName) on delete cascade "
                                    ");");

    // insert default Students(s)
    noError = noError && query.exec("INSERT INTO Student (studentNumber,cmail,userName) "
                                        "VALUES ('100853074','ankushlord@cmail.carleton.ca','Kushlord');");
    noError = noError && query.exec("INSERT INTO Student (studentNumber,cmail,userName) "
                                        "VALUES ('195372839','ryanmoore@cmail.carleton.ca','Mooreloaded');");
    noError = noError && query.exec("INSERT INTO Student (studentNumber,cmail,userName) "
                                        "VALUES ('123456789','somestudent@cmail.carleton.ca','LorettaBetta');");

    // creating the Table called PaymentInformation
    noError = noError && query.exec("create table PaymentInformation( "
                                        "creditCardNumber varchar(50) NOT NULL, "
                                        "cardType varchar(50), "
                                        "cvv varchar(50), "
                                        "expirationDate varchar(10), "
                                        "nameOnCard varchar(50), "
                                        "postalCode varchar(7), "
                                        "province varchar(50), "
                                        "city varchar(50), "
                                        "streetName varchar(50), "
                                        "houseNumber integer, "
                                        "studentNumber varchar(10) NOT NULL, "
                                        "foreign key (studentNumber) references Student(studentNumber) on delete cascade, "
                                        "primary key(studentNumber, creditCardNumber) "
                                    ");");

    // insert default PaymentInformation(s)
    noError = noError && query.exec("INSERT INTO PaymentInformation (creditCardNumber, cardType, cvv, expirationDate, nameOnCard,postalCode,province,city,streetName,houseNumber,studentNumber) "
                                        "Values ('2345-5675-1234', 'Master Card', '756','19760420','Ankush Dabess Varshneya','H8R8H8','Ontario','Ottawa','Swag St.',420,'100853074');");

    //creating the Table called Student_RegisteredIn_Course
    noError = noError && query.exec("create table Student_RegisteredIn_Course( "
                                        "studentNumber varchar(10) NOT NULL references Student(studentNumber), "
                                        "courseCode varchar(8) NOT NULL references Course(courseCode), "
                                        "section varchar(1) NOT NULL references Course(section), "
                                        "termID integer NOT NULL references Course(termID), "
                                        "primary key(studentNumber, courseCode, section, termID) "
                                    ");");

    // insert default Student_RegisteredIn_Course(s)
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP3004', 'A', 1);");
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP3804', 'A', 1);");
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('195372839','PHIL1002','C',1);");

    //creating the Table called Course
    noError = noError && query.exec("create table Course( "
                                        "courseCode varchar(8) NOT NULL, "
                                        "section varchar(1) NOT NULL, "
                                        "instructor varchar(20), "
                                        "termID integer NOT NULL, "
                                        "foreign key (termID) references Term(termID) on delete cascade, "
                                        "primary key(courseCode, section, termID) "
                                    ");");

    // insert default Course(s)
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('COMP3004','A', 'Christine Laurendeau',1);");
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES('COMP3804', 'A', 'Amin Gheibi',1);");
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('PHIL1002','C','Peter Dinklage',1);");

    // creating the Table called Term
    noError = noError && query.exec("create table Term( "
                                        "termID integer NOT NULL primary key, "
                                        "startDate varchar(10), "
                                        "endDate varchar(10) "
                                    ");");
    // insert default Terms(s)
    noError = noError && query.exec("INSERT INTO Term (termID,startDate,endDate) "
                                        "VALUES (1,'20140905','20141209');");
    noError = noError && query.exec("INSERT INTO Term (termID,startDate,endDate) "
                                        "VALUES (2,'20150105','20151209');");

    //creating the Table called Textbook
    noError = noError && query.exec("create table Textbook( "
                                        "ISBN varchar(20) NOT NULL primary key, "
                                        "coverImageLocation varchar(100), "
                                        "desc varchar(200), "
                                        "author varchar(50), "
                                        "textBookTitle varchar(50), "
                                        "publisher varchar(50), "
                                        "edition varchar(50), "
                                        "itemID integer NOT NULL, "
                                        "foreign key (itemID) references PurchasableItem(itemID) on delete cascade "
                                    ");");

    // insert default Textbook(s)
    noError = noError && query.exec("INSERT INTO Textbook (ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition,itemID) "
                                        "VALUES ('111-1-11-111111-0','./COMP3004.png','COMP3004 course pack is required!','Author of COMP3004','COMP3004 A Course Pack','Carleton Course Pack Inc.','1st',1);");
    noError = noError && query.exec("INSERT INTO Textbook (ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition,itemID) "
                                        "VALUES ('222-2-22-222222-0','./COMP3804.png','COMP3804 course pack is required!','Author of COMP3804','COMP3804 A Course Pack','Carleton Course Pack Inc.','1st',7);");

   // creating the Table called Chapter
    noError = noError && query.exec("create table Chapter( "
                                        "ISBN varchar(20) NOT NULL, "
                                        "chapterNumber integer NOT NULL, "
                                        "chapterTitle varchar(50), "
                                        "itemID integer NOT NULL, "
                                        "foreign key (ISBN) references Textbook(ISBN) on delete cascade, "
                                        "foreign key (itemID) references PurchasableItem(itemID) on delete cascade, "
                                        "primary key(ISBN, chapterNumber) "
                                    ");");

    // insert default Chapter(s)
    noError = noError && query.exec("INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID) "
                                        "VALUES ('111-1-11-111111-0',1,'Intro To COMP3004',2);");
    noError = noError && query.exec("INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID) "
                                        "VALUES ('111-1-11-111111-0',2,'COMP3004 Midterm',5);");
    noError = noError && query.exec("INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID) "
                                        "VALUES ('222-2-22-222222-0',1,'Intro To COMP3804',8);");
    noError = noError && query.exec("INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID) "
                                        "VALUES ('222-2-22-222222-0',2,'COMP3804 Midterm',11);");

    // creating the Table called Section
    noError = noError && query.exec("create table Section( "
                                        "ISBN varchar(20) NOT NULL, "
                                        "chapterNumber integer NOT NULL, "
                                        "sectionNumber integer NOT NULL, "
                                        "sectionTitle varchar(50), "
                                        "itemID integer NOT NULL, "
                                        "foreign key (ISBN) references Chapter(ISBN) on delete cascade, "
                                        "foreign key (chapterNumber) references Chapter(chapterNumber) on delete cascade, "
                                        "foreign key (itemID) references PurchasableItem(itemID) on delete cascade, "
                                        "primary key(ISBN, chapterNumber, sectionNumber) "
                                    ");");

    // insert default Section(s)
    noError = noError && query.exec("INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID) "
                                        "VALUES ('111-1-11-111111-0',1,1,'Pre-reqs for COMP3004',3);");
    noError = noError && query.exec("INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID) "
                                        "VALUES ('111-1-11-111111-0',1,2,'Review needed information for COMP3004',4);");
    noError = noError && query.exec("INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID) "
                                        "VALUES ('111-1-11-111111-0',2,1,'COMP3004 Midterm mark break-up',6);");
    noError = noError && query.exec("INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID) "
                                        "VALUES ('222-2-22-222222-0',1,1,'Pre-reqs for COMP3804',9);");
    noError = noError && query.exec("INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID) "
                                        "VALUES ('222-2-22-222222-0',1,2,'Review needed information for COMP3804',10);");
    noError = noError && query.exec("INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID) "
                                        "VALUES ('222-2-22-222222-0',2,1,'COMP3804 Midterm mark break-up',12);");

    // creating the Table called PurchasableItem
    noError = noError && query.exec("create table PurchasableItem( "
                                        "itemID integer NOT NULL primary key, "
                                        "price decimal(18,2), "
                                        "availability boolean "
                                    ");");

    // insert default PurchasableItem(s)
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (1,1.99,0);");
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (2,2.99,0);");
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (3,3.99,0);");
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (4,4.99,0);");
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (5,5.99,0);");
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (6,6.99,0);");
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (7,7.99,0);");
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (8,8.99,0);");
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (9,9.99,0);");
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (10,10.99,0);");
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (11,11.99,0);");
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (12,12.99,0);");

    // creating the Table called Course_Assigned_Textbook
    noError = noError && query.exec("create table Course_Assigned_Textbook( "
                                        "ISBN varchar(20) NOT NULL references Textbook(ISBN), "
                                        "courseCode varchar(8) NOT NULL references Course(courseCode), "
                                        "section varchar(1) NOT NULL references Course(section), "
                                        "termID integer NOT NULL references Course(termID), "
                                        "primary key(ISBN, courseCode, section, termID) "
                                    ");");

    // insert default Course_Assigned_Textbook(s)
    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('111-1-11-111111-0','COMP3004','A',1);");
    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('222-2-22-222222-0','COMP3804','A',1);");

    //commit transaction
    noError = noError && query.exec("commit;");

    return noError;
}

QList<Textbook*>& Login::viewAllTextbooks(qint32 termID){
    QList<Textbook*> *textbooks = new QList<Textbook*>();

    // get all textbooks for the term
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
                            "WHERE Course.termID=:termID "
                                "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC;");
    textBookQuery.bindValue(":termID", termID);
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
        textbooks->push_back(textbook);
    }
    return *textbooks;
}

QList<Course*>& Login::viewCourses(qint32 termID) {
    QList<Course*> *courses = new QList<Course*>();

    // get all courses in the term
    QSqlQuery courseQuery;
    courseQuery.prepare("SELECT Course.courseCode, "
                                "Course.section, "
                                "Course.instructor, "
                                "Term.startDate, "
                                "Term.endDate, "
                                "Term.termID "
                            "FROM Course "
                            "JOIN term ON "
                                "Course.termID = Term.TermID "
                            "WHERE Course.termID=:termID "
                                "ORDER BY Course.courseCode ASC, Course.section ASC;");
    courseQuery.bindValue(":termID", termID);
    courseQuery.exec();
    qDebug() << courseQuery.lastError();
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

bool Login::linkTextbook(Textbook *textbook, Course *course, qint32 termID){
    // link a text book to a course
    QSqlQuery linkQuery;

    linkQuery.prepare("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                            "VALUES (:ISBN,:courseCode,:section,:termID);");
    linkQuery.bindValue(":ISBN", textbook->getISBN());
    linkQuery.bindValue(":courseCode", course->getCourseCode());
    linkQuery.bindValue(":section", course->getCourseSection());
    linkQuery.bindValue(":termID", termID);

    return linkQuery.exec();
}

bool Login::createCourse(Course *course, qint32 termID){
    // create a course
    QSqlQuery courseQuery;

    courseQuery.prepare("INSERT INTO Course (courseCode,section,instructor,termID) "
                            "VALUES (:courseCode,:section,:instructor,:termID);");
    courseQuery.bindValue(":courseCode", course->getCourseCode());
    courseQuery.bindValue(":section", course->getCourseSection());
    courseQuery.bindValue(":instructor", course->getInstructor());
    courseQuery.bindValue(":termID", termID);

    return courseQuery.exec();
}

bool Login::createTextbook(Textbook *textbook){
    bool noError = true;

    //get the current max item id
    int nextItemID = -1;
    QSqlQuery maxItemID("SELECT MAX(itemID)+1 AS nextItemID FROM PurchasableItem;");
    noError = noError && maxItemID.exec();
    if(maxItemID.first()){
        nextItemID = maxItemID.value(maxItemID.record().indexOf("nextItemID")).toInt();
    }
    else{
        nextItemID++;
    }
    textbook->setItemID(nextItemID);

    // create a textbook
    QSqlQuery textBookQuery;

    textBookQuery.prepare("INSERT INTO Textbook (ISBN,coverImageLocation,Desc,Author,TextbookTitle,Publisher,Edition,itemID) "
                            "VALUES (:ISBN,:coverImageLocation,:Desc,:Author,:TextbookTitle,:Publisher,:Edition,:itemID);");
    textBookQuery.bindValue(":ISBN", textbook->getISBN());
    textBookQuery.bindValue(":coverImageLocation", textbook->getCoverImageLoc());
    textBookQuery.bindValue(":Desc", textbook->getDesc());
    textBookQuery.bindValue(":Author", textbook->getAuthor());
    textBookQuery.bindValue(":TextbookTitle", textbook->getItemTitle());
    textBookQuery.bindValue(":Publisher", textbook->getPublisher());
    textBookQuery.bindValue(":Edition", textbook->getEdition());
    textBookQuery.bindValue(":itemID", textbook->getItemID());

    //create its PurchasableItem
    QSqlQuery textBookItemQuery;

    textBookItemQuery.prepare("INSERT INTO PurchasableItem (itemID,price,availability) "
                      "VALUES (:itemID,:price,:availability);");
    textBookItemQuery.bindValue(":itemID", textbook->getItemID());
    textBookItemQuery.bindValue(":price", textbook->getPrice());
    textBookItemQuery.bindValue(":availability", textbook->isAvailable());

    noError = noError && textBookQuery.exec();
    noError = noError && textBookItemQuery.exec();

    foreach(Chapter *chapter, textbook->getChapterList()){
        noError = noError && maxItemID.exec();
        if(maxItemID.first()){
            nextItemID = maxItemID.value(maxItemID.record().indexOf("nextItemID")).toInt();
        }
        else{
            nextItemID++;
        }
        chapter->setItemID(nextItemID);

        //create a chapter
        QSqlQuery chapterQuery;

        chapterQuery.prepare("INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID) "
                                "VALUES (:ISBN,:chapterNumber,:chapterTitle,:itemID);");
        chapterQuery.bindValue(":ISBN", textbook->getISBN());
        chapterQuery.bindValue(":chapterNumber", chapter->getChapterNumber());
        chapterQuery.bindValue(":chapterTitle", chapter->getItemTitle());
        chapterQuery.bindValue(":itemID", chapter->getItemID());

        //create its PurchasableItem
        QSqlQuery chapterItemQuery;

        chapterItemQuery.prepare("INSERT INTO PurchasableItem (itemID,price,availability) "
                          "VALUES (:itemID,:price,:availability);");
        chapterItemQuery.bindValue(":itemID", chapter->getItemID());
        chapterItemQuery.bindValue(":price", chapter->getPrice());
        chapterItemQuery.bindValue(":availability", chapter->isAvailable());

        noError = noError && chapterQuery.exec();
        noError = noError && chapterItemQuery.exec();

        foreach(Section *section, chapter->getChapterSections()){
            noError = noError && maxItemID.exec();
            if(maxItemID.first()){
                nextItemID = maxItemID.value(maxItemID.record().indexOf("nextItemID")).toInt();
            }
            else{
                nextItemID++;
            }
            section->setItemID(nextItemID);

            //create a section
            QSqlQuery sectionQuery;

            sectionQuery.prepare("INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID) "
                                    "VALUES (:ISBN,:chapterNumber,:sectionNumber,:sectionTitle,:itemID);");
            sectionQuery.bindValue(":ISBN", textbook->getISBN());
            sectionQuery.bindValue(":chapterNumber", chapter->getChapterNumber());
            sectionQuery.bindValue(":sectionNumber", section->getSectionNumber());
            sectionQuery.bindValue(":sectionTitle", section->getItemTitle());
            sectionQuery.bindValue(":itemID", section->getItemID());

            //create its PurchasableItem
            QSqlQuery sectionItemQuery;

            sectionItemQuery.prepare("INSERT INTO PurchasableItem (itemID,price,availability) "
                              "VALUES (:itemID,:price,:availability);");
            sectionItemQuery.bindValue(":itemID", section->getItemID());
            sectionItemQuery.bindValue(":price", section->getPrice());
            sectionItemQuery.bindValue(":availability", section->isAvailable());

            noError = noError && sectionQuery.exec();
            noError = noError && sectionItemQuery.exec();
        }
    }

    return noError;
}

bool Login::saveBillingInformation(const QString studentNumber, PaymentInformation *info){

    //check if there is a student with that id
    QSqlQuery studentQuery;
    studentQuery.prepare("SELECT COUNT(*) FROM student "
                            "WHERE studentNumber =:studentNumber;");
    studentQuery.bindValue(":studentNumber", studentNumber);
    studentQuery.exec();

    if(studentQuery.first() && (studentQuery.value(studentQuery.record().indexOf("COUNT(*)")).toInt()>0)){
        // edit payment information
        QSqlQuery PaymentInformationQuery;

        PaymentInformationQuery.prepare("UPDATE PaymentInformation SET "
                                            "creditCardNumber=:creditCardNumber, "
                                            "cardType=:cardType, "
                                            "cvv=:cvv, "
                                            "expirationDate=:expirationDate, "
                                            "nameOnCard=:nameOnCard, "
                                            "postalCode=:postalCode, "
                                            "province=:province, "
                                            "city=:city, "
                                            "streetName=:streetName, "
                                            "houseNumber=:houseNumber "
                                        "WHERE studentNumber=:studentNumber; ");

        PaymentInformationQuery.bindValue(":creditCardNumber", info->getCreditCardInfo().getCreditCardNo());
        PaymentInformationQuery.bindValue(":cardType", info->getCreditCardInfo().getCardType());
        PaymentInformationQuery.bindValue(":cvv", info->getCreditCardInfo().getCVV());
        PaymentInformationQuery.bindValue(":expirationDate", info->getCreditCardInfo().getExpDate());
        PaymentInformationQuery.bindValue(":nameOnCard", info->getCreditCardInfo().getNameOnCard());
        PaymentInformationQuery.bindValue(":postalCode", info->getBillInfo().getPostalCode());
        PaymentInformationQuery.bindValue(":province", info->getBillInfo().getProvince());
        PaymentInformationQuery.bindValue(":city", info->getBillInfo().getCity());
        PaymentInformationQuery.bindValue(":streetName", info->getBillInfo().getStreetName());
        PaymentInformationQuery.bindValue(":houseNumber", info->getBillInfo().getHouseNumber());
        PaymentInformationQuery.bindValue(":studentNumber", studentNumber);

        // edit name
        QSqlQuery nameQuery;

        nameQuery.prepare(  "UPDATE User SET "
                                "fullName=:fullName "
                            "WHERE userName= "
                                "( "
                                    "SELECT userName FROM Student "
                                    "WHERE Student.studentNumber=:studentNumber "
                                "); ");

        nameQuery.bindValue(":fullName", info->getBillInfo().getName());
        nameQuery.bindValue(":studentNumber", studentNumber);

        return PaymentInformationQuery.exec() && nameQuery.exec();
    }

    return false;
}


PaymentInformation& Login::getExistingBillingInfo(QString studentNumber) const{
    PaymentInformation *info;

    // get the student payment information
    QSqlQuery PaymentInformationQuery;

    PaymentInformationQuery.prepare("SELECT paymentInformation.creditCardNumber, "
                                            "paymentInformation.cardType, "
                                            "paymentInformation.cvv, "
                                            "paymentInformation.expirationDate, "
                                            "paymentInformation.nameOnCard, "
                                            "paymentInformation.postalCode, "
                                            "paymentInformation.province, "
                                            "paymentInformation.city, "
                                            "paymentInformation.streetName, "
                                            "paymentInformation.houseNumber, "
                                            "User.fullName "
                                        "FROM PaymentInformation "
                                        "JOIN Student ON "
                                            "paymentInformation.studentNumber = Student.StudentNumber "
                                        "JOIN User ON "
                                            "Student.username = User.username AND "
                                            "User.roleID = (Select roleID from Role where roleType = 'Student') "
                                        "WHERE Student.studentNumber=:studentNumber;");
    PaymentInformationQuery.bindValue(":studentNumber", studentNumber);
    PaymentInformationQuery.exec();

    //if student has payment info set it else its NULL
    if(PaymentInformationQuery.first()){
        info = new PaymentInformation();
        info->setBillInfo(*(new BillingAddress(PaymentInformationQuery.value(PaymentInformationQuery.record().indexOf("fullName")).toString(),
                                        PaymentInformationQuery.value(PaymentInformationQuery.record().indexOf("houseNumber")).toInt(),
                                        PaymentInformationQuery.value(PaymentInformationQuery.record().indexOf("streetName")).toString(),
                                        PaymentInformationQuery.value(PaymentInformationQuery.record().indexOf("city")).toString(),
                                        PaymentInformationQuery.value(PaymentInformationQuery.record().indexOf("province")).toString(),
                                        PaymentInformationQuery.value(PaymentInformationQuery.record().indexOf("postalCode")).toString())));

        info->setCreditCardInfo(*(new CreditCardInformation(PaymentInformationQuery.value(PaymentInformationQuery.record().indexOf("creditCardNumber")).toString(),
                                                     PaymentInformationQuery.value(PaymentInformationQuery.record().indexOf("cvv")).toString(),
                                                     QDate::fromString(PaymentInformationQuery.value(PaymentInformationQuery.record().indexOf("expirationDate")).toString(), "yyyyMMdd"),
                                                     PaymentInformationQuery.value(PaymentInformationQuery.record().indexOf("cardType")).toString(),
                                                     PaymentInformationQuery.value(PaymentInformationQuery.record().indexOf("nameOnCard")).toString())));
    }
    else{
        info=NULL;
    }

    return *info;
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
