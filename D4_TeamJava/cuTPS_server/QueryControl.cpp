#include "QueryControl.h"

/**
 * @brief QueryControl::QueryControl
 *  connects to DB
 */
QueryControl::QueryControl() {
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../cuTPS.db");
    if(!db.open())
        qDebug() << "FAILED TO CONNECT TO DATA BASE";
    else {
        qDebug() << "CONNECT TO DATA BASE";
        test();
    }
}

/**
 * @brief QueryControl::~QueryControl
 *  dissconnects from DB
 */
QueryControl::~QueryControl() {
    qDebug()<< "IN QUERY CONTROL DESTRUCTOR";
    db.commit();
    db.removeDatabase("QSQLITE");
    db.close();
    qDebug() << db.databaseName();
}

/**
 * @brief QueryControl::test
 *  test cases
 */
void QueryControl::test(){
     QJsonObject json;

    qDebug() << resetDatabase();

    QList<Term*> *termlist= this->retrieveTermList();

    // test for terms
    foreach(Term *trm, *termlist){
        json = QJsonObject();
        trm->write(json);
        qDebug() <<json;
    }

    Term *term = termlist->at(0);

    Course *course = new Course("COMP3004","N","Dr. Laurendeau");
    course->setTerm(term);

    // create the course
    this->createCourse(course, term->getTermID());

    // get the courses to check if it was created
    foreach(Course *crs,  *(this->retrieveCourseList(term->getTermID()))){
        json = QJsonObject();
        crs->write(json);
        //qDebug() <<json;
    }

    // modify the course
    course->setInstructor("L Nel");
    this->updateCourse(course, term->getTermID());

    // get the courses to check if it was modified
    foreach(Course *crs,  *(this->retrieveCourseList(term->getTermID()))){
        json = QJsonObject();
        crs->write(json);
        //qDebug() <<json;
    }

    // get a student
    Student *student = this->retrieveStudent("100853074");
    // get the students payment information
    PaymentInformation *paymentInformation = this->retrievePaymentInformation(student);
    student->setPayInfo(*paymentInformation);
    json = QJsonObject();
    student->write(json);
    qDebug() <<json;

    //link student to a new new course
    this->updateCourseStudentLink(course, term->getTermID(), student);

    // get course for a student
    foreach(Course *crs,  *(this->retrieveStudentCourseList(student->getStudentNum(), term->getTermID()))){
        json = QJsonObject();
        crs->write(json);
        qDebug() <<json;
    }

/*
    // test for view studentView
    foreach(Course *crs, studentViewTextbooks("100853074", 1)){
        QJsonObject json = QJsonObject();
        crs->write(json);
        qDebug() <<json;
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


    // test for viewAllTerm
    foreach(Term *tr, viewAllTerm()){
        QJsonObject json = QJsonObject();
        tr->write(json);
        qDebug() <<json<< endl;
    }

    qDebug() << resetDatabase();
*/
}

/**
 * @brief QueryControl::resetDatabase
 *  Reset The Schema using QueryControl::resetSchema()
 *  And then loads default values
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::resetDatabase() {
    bool noError = true;
    QSqlQuery query;

    //reset schema
    noError = noError && resetSchema();

    // begain transaction
    noError = noError && query.exec("begin transaction;");

    // load default values

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

    // insert default Students(s)
    noError = noError && query.exec("INSERT INTO Student (studentNumber,cmail,userName) "
                                        "VALUES ('100853074','ankushlord@cmail.carleton.ca','Kushlord');");
    noError = noError && query.exec("INSERT INTO Student (studentNumber,cmail,userName) "
                                        "VALUES ('195372839','ryanmoore@cmail.carleton.ca','Mooreloaded');");
    noError = noError && query.exec("INSERT INTO Student (studentNumber,cmail,userName) "
                                        "VALUES ('123456789','somestudent@cmail.carleton.ca','LorettaBetta');");

    // insert default PaymentInformation(s)
    noError = noError && query.exec("INSERT INTO PaymentInformation (creditCardNumber, cardType, cvv, expirationDate, nameOnCard,postalCode,province,city,streetName,houseNumber,studentNumber) "
                                        "Values ('2345-5675-1234', 'Master Card', '756','19760420','Ankush Dabess Varshneya','H8R8H8','Ontario','Ottawa','Swag St.',420,'100853074');");

    // insert default Student_RegisteredIn_Course(s)
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP3004', 'A', 1);");
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP3804', 'A', 1);");
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('195372839','PHIL1002','C',1);");

    // insert default Course(s)
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('COMP3004','A', 'Christine Laurendeau',1);");
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES('COMP3804', 'A', 'Amin Gheibi',1);");
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('PHIL1002','C','Peter Dinklage',1);");

    // insert default Terms(s)
    noError = noError && query.exec("INSERT INTO Term (termID,termName,startDate,endDate) "
                                        "VALUES (1,'fall2014','20140905','20141209');");
    noError = noError && query.exec("INSERT INTO Term (termID,termName,startDate,endDate) "
                                        "VALUES (2,'winter2015','20150105','20151209');");

    // insert default Textbook(s)
    noError = noError && query.exec("INSERT INTO Textbook (ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition,itemID) "
                                        "VALUES ('111-1-11-111111-0','./COMP3004.png','COMP3004 course pack is required!','Author of COMP3004','COMP3004 A Course Pack','Carleton Course Pack Inc.','1st',1);");
    noError = noError && query.exec("INSERT INTO Textbook (ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition,itemID) "
                                        "VALUES ('222-2-22-222222-0','./COMP3804.png','COMP3804 course pack is required!','Author of COMP3804','COMP3804 A Course Pack','Carleton Course Pack Inc.','1st',7);");

    // insert default Chapter(s)
    noError = noError && query.exec("INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID) "
                                        "VALUES ('111-1-11-111111-0',1,'Intro To COMP3004',2);");
    noError = noError && query.exec("INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID) "
                                        "VALUES ('111-1-11-111111-0',2,'COMP3004 Midterm',5);");
    noError = noError && query.exec("INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID) "
                                        "VALUES ('222-2-22-222222-0',1,'Intro To COMP3804',8);");
    noError = noError && query.exec("INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID) "
                                        "VALUES ('222-2-22-222222-0',2,'COMP3804 Midterm',11);");

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

    // insert default Course_Assigned_Textbook(s)
    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('111-1-11-111111-0','COMP3004','A',1);");
    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('222-2-22-222222-0','COMP3804','A',1);");

    //commit transaction
    noError = noError && query.exec("commit;");

    return noError;
}

/**
 * @brief QueryControl::resetDatabase
 *  Reset The Schema
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::resetSchema() {
    bool noError = true;
    QSqlQuery query;

    // begain transaction
    noError = noError && query.exec("begin transaction;");

    // drop old schema as needed
    noError = noError && query.exec("drop table if exists Role;");
    noError = noError && query.exec("drop table if exists User;");
    noError = noError && query.exec("drop table if exists Student;");
    noError = noError && query.exec("drop table if exists PaymentInformation;");
    noError = noError && query.exec("drop table if exists Student_RegisteredIn_Course;");
    noError = noError && query.exec("drop table if exists Course;");
    noError = noError && query.exec("drop table if exists Term;");
    noError = noError && query.exec("drop table if exists Course_Assigned_Textbook;");
    noError = noError && query.exec("drop table if exists Textbook;");
    noError = noError && query.exec("drop table if exists Chapter;");
    noError = noError && query.exec("drop table if exists Section;");
    noError = noError && query.exec("drop table if exists PurchasableItem;");
    noError = noError && query.exec("drop table if exists ShoppingCart;");
    noError = noError && query.exec("drop table if exists Orders;");

    // creating the Table called Role
    noError = noError && query.exec("create table Role("
                                        "roleID integer NOT NULL primary key,"
                                        "roleType varchar(20)"
                                    ");");
    // insert default Role(s)
    noError = noError && query.exec("insert into Role (roleID, roleType) values (1, 'Student');");
    noError = noError && query.exec("insert into Role (roleID, roleType) values (2, 'Content Manager');");
    noError = noError && query.exec("insert into Role (roleID, roleType) values (3, 'Administrator');");

    // creating the Table called User
    noError = noError && query.exec("create table User("
                                        "userName varchar(50) NOT NULL primary key,"
                                        "fullName varchar(50),"
                                        "password varchar(20),"
                                        "roleID integer NOT NULL references Role(roleID) on delete cascade"
                                    ");");

    // creating the Table called Student
    noError = noError && query.exec("create table Student("
                                        "studentNumber varchar(10) NOT NULL primary key,"
                                        "cmail varchar(100) NOT NULL UNIQUE,"
                                        "userName varchar(50) NOT NULL references User(userName) on delete cascade"
                                    ");");

    // creating the Table called PaymentInformation
    noError = noError && query.exec("create table PaymentInformation("
                                        "creditCardNumber varchar(50) NOT NULL,"
                                        "cardType varchar(50),"
                                        "cvv varchar(50),"
                                        "expirationDate varchar(10),"
                                        "nameOnCard varchar(50),"
                                        "postalCode varchar(7),"
                                        "province varchar(50),"
                                        "city varchar(50),"
                                        "streetName varchar(50),"
                                        "houseNumber integer,"
                                        "studentNumber varchar(10) NOT NULL references Student(studentNumber) on delete cascade,"
                                        "primary key(studentNumber, creditCardNumber)"
                                    ");");

    //creating the Table called Student_RegisteredIn_Course
    noError = noError && query.exec("create table Student_RegisteredIn_Course("
                                        "studentNumber varchar(10) NOT NULL references Student(studentNumber) on delete cascade,"
                                        "courseCode varchar(8) NOT NULL references Course(courseCode) on delete cascade,"
                                        "section varchar(1) NOT NULL references Course(section) on delete cascade,"
                                        "termID integer NOT NULL references Course(termID) on delete cascade,"
                                        "primary key(studentNumber, courseCode, section, termID)"
                                    ");");

    //creating the Table called Course
    noError = noError && query.exec("create table Course("
                                        "courseCode varchar(8) NOT NULL,"
                                        "section varchar(1) NOT NULL,"
                                        "instructor varchar(20),"
                                        "termID integer NOT NULL references Term(termID) on delete cascade,"
                                        "primary key(courseCode, section, termID)"
                                    ");");

    // creating the Table called Term
    noError = noError && query.exec("create table Term("
                                        "termID integer NOT NULL primary key,"
                                        "termName varchar(25),"
                                        "startDate varchar(10),"
                                        "endDate varchar(10)"
                                    ");");

    //creating the Table called Textbook
    noError = noError && query.exec("create table Textbook("
                                        "ISBN varchar(20) NOT NULL primary key,"
                                        "coverImageLocation varchar(100),"
                                        "desc varchar(200),"
                                        "author varchar(50),"
                                        "textBookTitle varchar(50),"
                                        "publisher varchar(50),"
                                        "edition varchar(50),"
                                        "itemID integer NOT NULL references PurchasableItem(itemID) on delete cascade"
                                    ");");

   // creating the Table called Chapter
    noError = noError && query.exec("create table Chapter("
                                        "ISBN varchar(20) NOT NULL references Textbook(ISBN) on delete cascade,"
                                        "chapterNumber integer NOT NULL,"
                                        "chapterTitle varchar(50),"
                                        "itemID integer NOT NULL references PurchasableItem(itemID) on delete cascade,"
                                        "primary key(ISBN, chapterNumber)"
                                    ");");

    // creating the Table called Section
    noError = noError && query.exec("create table Section("
                                    "ISBN varchar(20) NOT NULL references Chapter(ISBN) on delete cascade,"
                                        "chapterNumber integer NOT NULL references Chapter(chapterNumber) on delete cascade,"
                                        "sectionNumber integer NOT NULL,"
                                        "sectionTitle varchar(50),"
                                        "itemID integer NOT NULL references PurchasableItem(itemID) on delete cascade,"
                                        "primary key(ISBN, chapterNumber, sectionNumber)"
                                    ");");

    // creating the Table called PurchasableItem
    noError = noError && query.exec("create table PurchasableItem("
                                        "itemID integer NOT NULL primary key,"
                                        "price decimal(18,2),"
                                        "availability boolean"
                                    ");");

    // creating the Table called Course_Assigned_Textbook
    noError = noError && query.exec("create table Course_Assigned_Textbook("
                                        "ISBN varchar(20) NOT NULL references Textbook(ISBN) on delete cascade,"
                                        "courseCode varchar(8) NOT NULL references Course(courseCode) on delete cascade,"
                                        "section varchar(1) NOT NULL references Course(section) on delete cascade,"
                                        "termID integer NOT NULL references Course(termID) on delete cascade,"
                                        "primary key(ISBN, courseCode, section, termID)"
                                    ");");

    // creating the Table called ShoppingCart
    noError = noError && query.exec("create table ShoppingCart("
                                        "studentNumber varchar(10) NOT NULL references Student(studentNumber) on delete cascade,"
                                        "itemID integer NOT NULL references PurchasableItem(itemID) on delete cascade,"
                                        "quantity integer,"
                                        "primary key(studentNumber, itemID)"
                                    ");");

    // creating the Table called Orders
    noError = noError && query.exec("create table Orders("
                                        "orderID integer NOT NULL primary key,"
                                        "studentNumber varchar(10) NOT NULL references Student(studentNumber) on delete cascade,"
                                        "itemID integer NOT NULL references PurchasableItem(itemID) on delete cascade"
                                    ");");

    //commit transaction
    noError = noError && query.exec("commit;");

    return noError;
}

/**
 * @brief QueryControl::retrieveTermList
 *  retrives a existing list of terms
 * @return
 *  returns a list of terms
 */
QList<Term*>* QueryControl::retrieveTermList(){
    QList<Term*> *terms = new QList<Term*>();

    // get all terms
    QSqlQuery termQuery;
    termQuery.exec("SELECT Term.termID, "
                                "Term.termName, "
                                "Term.startDate, "
                                "Term.endDate "
                            "FROM Term;");

    while (termQuery.next()) {
        terms->push_back(new Term(QDate::fromString(termQuery.value(termQuery.record().indexOf("startDate")).toString(), "yyyyMMdd"),
                                  QDate::fromString(termQuery.value(termQuery.record().indexOf("endDate")).toString(), "yyyyMMdd"),
                                  termQuery.value(termQuery.record().indexOf("termID")).toInt(),
                                  termQuery.value(termQuery.record().indexOf("termName")).toString()));
    }
    return terms;
}

/**
 * @brief QueryControl::createCourse
 *  creates a new Course
 *  Note:
 *  1) to add a student use QueryControl::updateCourseStudentLink()
 *  2) to add a textbook use QueryControl::createTextbook() and then QueryControl::updateCourseTextbookLink()
 * @param course
 *  Course object to save to DB
 * @param termID
 *  termID to create the course under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::createCourse(Course *course, qint32 termID) {
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

/**
 * @brief QueryControl::updateCourse
 *  update a existing Course in DB
 *  Note:
 *  1) primary ID  i.e Course::courseCode, Course::courseSection, termID
 *     must remain not change otherwize operation will not change any thing
 *     as the above values are needed to change a exisiting Course
 *  2) to update a existing student use
 *  3) to update a existing textbook use QueryControl::updateTextbook()
 * @param course
 *  Course object to save to DB
 * @param termID
 *  termID to update the course under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updateCourse(Course *course, qint32 termID) {
    // create a course
    QSqlQuery courseQuery;

    courseQuery.prepare("UPDATE Course SET "
                            "courseCode = :courseCode,"
                            "section = :section,"
                            "instructor = :instructor,"
                            "termID = :termID"
                        " WHERE "
                            "courseCode = :courseCode AND "
                            "section = :section AND "
                            "termID = :termID;");
    courseQuery.bindValue(":courseCode", course->getCourseCode());
    courseQuery.bindValue(":section", course->getCourseSection());
    courseQuery.bindValue(":instructor", course->getInstructor());
    courseQuery.bindValue(":termID", termID);

    return courseQuery.exec();
}

/**
 * @brief QueryControl::deleteCourse
 *  delete a existing course
 *  Note:
 *  1) primary ID  i.e Course::courseCode, Course::courseSection, termID
 *     must remain not change otherwize operation will not change any thing
 *     as the above values are needed to change a exisiting Course
 *  2) to delete a existing student use
 *  3) to delete a existing textbook use QueryControl::deleteTextbook()
 * @param course
 *  Course object to delete in DB
 * @param termID
 *  termID to delete the course under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::deleteCourse(Course *course, qint32 termID) {
    // create a course
    QSqlQuery courseQuery;

    courseQuery.prepare("DELETE FROM Course SET  WHERE "
                            "courseCode = :courseCode AND "
                            "section = :section AND "
                            "termID = :termID;");
    courseQuery.bindValue(":courseCode", course->getCourseCode());
    courseQuery.bindValue(":section", course->getCourseSection());
    courseQuery.bindValue(":termID", termID);

    return courseQuery.exec();
}

/**
 * @brief QueryControl::retrieveStudentCourseList
 *  retrives a existing list of Courses for some studentNumber and termID
 *  note:
 *  1) To load student list use QueryControl::retrieveStudentList()
 *  2) to load testbooklist use QueryControl::retrieveTextbookList()
 * @param studentNumber
 *  studentNumber to get courses for
 * @param termID
 *  termID to get courses for
 * @return
 *  returns a list of Courses
 */
QList<Course*>* QueryControl::retrieveStudentCourseList(QString studentNumber, qint32 termID) {
    QList<Course*> *courses = new QList<Course*>();

    // get all courses in the term for a perticular student
    QSqlQuery courseQuery;
    courseQuery.prepare("SELECT Course.courseCode, "
                                "Course.section, "
                                "Course.instructor, "
                                "Term.startDate, "
                                "Term.endDate, "
                                "Term.termID, "
                                "Term.termName "
                            "FROM Course "
                            "JOIN term ON "
                                "Course.termID = Term.TermID "
                            "JOIN Student_RegisteredIn_Course ON "
                                "Course.courseCode = Student_RegisteredIn_Course.courseCode AND "
                                "Course.section = Student_RegisteredIn_Course.section AND "
                                "Course.termID = Student_RegisteredIn_Course.termID "
                            "JOIN Student ON "
                                "student_RegisteredIn_Course.studentNumber = Student.studentNumber "
                            "WHERE Course.termID=:termID AND student.studentNumber=:studentNumber "
                                "ORDER BY Course.courseCode ASC, Course.section ASC;");
    courseQuery.bindValue(":termID", termID);
    courseQuery.bindValue(":studentNumber", studentNumber);
    courseQuery.exec();

    while (courseQuery.next()) {
        Course *course = new Course(courseQuery.value(courseQuery.record().indexOf("courseCode")).toString(),
                                   courseQuery.value(courseQuery.record().indexOf("section")).toString(),
                                   courseQuery.value(courseQuery.record().indexOf("instructor")).toString());

        course->setTerm(new Term(QDate::fromString(courseQuery.value(courseQuery.record().indexOf("startDate")).toString(), "yyyyMMdd"),
                                QDate::fromString(courseQuery.value(courseQuery.record().indexOf("endDate")).toString(), "yyyyMMdd"),
                                courseQuery.value(courseQuery.record().indexOf("termID")).toInt(),
                                courseQuery.value(courseQuery.record().indexOf("termName")).toString()));

        courses->push_back(course);
    }

    return courses;
}

/**
 * @brief QueryControl::retrieveCourseList
 *  retrives a existing list of Courses for some termID
 *  note:
 *  1) To load student list use QueryControl::retrieveStudentList()
 *  2) to load testbooklist use QueryControl::retrieveTextbookList()
 * @param termID
 *  termID to get courses for
 * @return
 *  returns a list of Courses
 */
QList<Course*>* QueryControl::retrieveCourseList(qint32 termID) {
    QList<Course*> *courses = new QList<Course*>();

    // get all courses in the term for a perticular student
    QSqlQuery courseQuery;
    courseQuery.prepare("SELECT Course.courseCode, "
                                "Course.section, "
                                "Course.instructor, "
                                "Term.startDate, "
                                "Term.endDate, "
                                "Term.termID, "
                                "Term.termName "
                            "FROM Course "
                            "JOIN term ON "
                                "Course.termID = Term.TermID "
                            "WHERE Course.termID=:termID "
                                "ORDER BY Course.courseCode ASC, Course.section ASC;");
    courseQuery.bindValue(":termID", termID);
    courseQuery.exec();

    while (courseQuery.next()) {
        Course *course = new Course(courseQuery.value(courseQuery.record().indexOf("courseCode")).toString(),
                                   courseQuery.value(courseQuery.record().indexOf("section")).toString(),
                                   courseQuery.value(courseQuery.record().indexOf("instructor")).toString());

        course->setTerm(new Term(QDate::fromString(courseQuery.value(courseQuery.record().indexOf("startDate")).toString(), "yyyyMMdd"),
                                QDate::fromString(courseQuery.value(courseQuery.record().indexOf("endDate")).toString(), "yyyyMMdd"),
                                courseQuery.value(courseQuery.record().indexOf("termID")).toInt(),
                                courseQuery.value(courseQuery.record().indexOf("termName")).toString()));

        courses->push_back(course);
    }

    return courses;
}

/**
 * @brief QueryControl::createTextbook
 *  creates a new Textbook in DB
 *  Note:
 *  1) to add a chapter use QueryControl::createChapter()
 *  2) uses QueryControl::createPurchasableItem()
 * @param textbook
 *  Textbook object to save to DB
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::createTextbook(Textbook *textbook){
    bool noError = true;

    //get the current max item id
    int nextItemID = -1;
    QSqlQuery maxItemID("SELECT MAX(itemID)+1 AS nextItemID FROM PurchasableItem;");
    noError = noError && maxItemID.exec();
    if(maxItemID.first()){
        nextItemID = maxItemID.value(maxItemID.record().indexOf("nextItemID")).toInt();
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

    noError = noError && textBookQuery.exec();

    //create its PurchasableItem
    noError = noError && createPurchasableItem((PurchasableItem*)textbook);

    return noError;
}

/**
 * @brief QueryControl::updateTextbook
 *  update a existing Textbook in DB
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Textbook::itemID
 *     must remain not change otherwize operation will not change any thing
 *     as the above values are needed to change a exisiting Textbook
 *  2) to update a chapter use QueryControl::updateChapter()
 * @param textbook
 *  Textbook object to save to DB
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updateTextbook(Textbook *textbook){
    bool noError = true;

    // update a textbook
    QSqlQuery textBookQuery;

    textBookQuery.prepare("UPDATE Textbook SET "
                            "ISBN = :ISBN,"
                            "coverImageLocation = :coverImageLocation,"
                            "Desc = :Desc,"
                            "Author = :Author,"
                            "TextbookTitle = :TextbookTitle,"
                            "Publisher = :Publisher,"
                            "Edition = :Edition,"
                            "itemID = :itemID"
                          " WHERE "
                            "ISBN = :ISBN;");
    textBookQuery.bindValue(":ISBN", textbook->getISBN());
    textBookQuery.bindValue(":coverImageLocation", textbook->getCoverImageLoc());
    textBookQuery.bindValue(":Desc", textbook->getDesc());
    textBookQuery.bindValue(":Author", textbook->getAuthor());
    textBookQuery.bindValue(":TextbookTitle", textbook->getItemTitle());
    textBookQuery.bindValue(":Publisher", textbook->getPublisher());
    textBookQuery.bindValue(":Edition", textbook->getEdition());
    textBookQuery.bindValue(":itemID", textbook->getItemID());

    noError = noError && textBookQuery.exec();

    //update its PurchasableItem
    noError = noError && updatePurchasableItem((PurchasableItem*)textbook);

    return noError;
}

/**
 * @brief QueryControl::deleteTextbook
 *  delete a existing Textbook in DB
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Textbook::itemID
 *     must remain not change otherwize operation will not change any thing
 *     as the above values are needed to change a exisiting Textbook
 *  2) to delete a chapter use QueryControl::deleteChapter()
 * @param textbook
 *  Textbook object to delete in DB
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::deleteTextbook(Textbook *textbook){
    bool noError = true;

    // delete a textbook
    QSqlQuery textBookQuery;

    textBookQuery.prepare("DELETE FROM Textbook SET WHERE "
                            "ISBN = :ISBN;");
    textBookQuery.bindValue(":ISBN", textbook->getISBN());

    noError = noError && textBookQuery.exec();

    //delete its PurchasableItem
    noError = noError && deletePurchasableItem((PurchasableItem*)textbook);

    return noError;
}

/**
 * @brief QueryControl::retrieveTextbook
 *  retrieve a existing Textbook from DB
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Textbook::itemID
 *     must remain not change otherwize operation will not get the right thing
 *     as the above values are needed to retrive a exisiting Textbook
 *  2) to retrive a chapter use QueryControl::retrieveChapter()
 * @param isbn
 *  primary key of Textbook
 * @return
 *  returns a Textbook
 */
Textbook* QueryControl::retrieveTextbook(QString isbn){
    Textbook *textbook;

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
                            "JOIN PurchasableItem ON "
                               "Textbook.itemID = PurchasableItem.ItemID "
                            "WHERE Textbook.ISBN =:ISBN "
                                "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC;");
    textBookQuery.bindValue(":ISBN", isbn);
    textBookQuery.exec();

    if (textBookQuery.first()){
         textbook = new Textbook(textBookQuery.value(textBookQuery.record().indexOf("textBookTitle")).toString(),
                                   textBookQuery.value(textBookQuery.record().indexOf("author")).toString(),
                                   textBookQuery.value(textBookQuery.record().indexOf("edition")).toString(),
                                   textBookQuery.value(textBookQuery.record().indexOf("publisher")).toString(),
                                   textBookQuery.value(textBookQuery.record().indexOf("ISBN")).toString(),
                                   textBookQuery.value(textBookQuery.record().indexOf("desc")).toString(),
                                   textBookQuery.value(textBookQuery.record().indexOf("itemID")).toInt(),
                                   textBookQuery.value(textBookQuery.record().indexOf("price")).toDouble(),
                                   textBookQuery.value(textBookQuery.record().indexOf("availability")).toBool());
         textbook->setCoverImageLoc(textBookQuery.value(textBookQuery.record().indexOf("coverImageLocation")).toString());
    }

    return textbook;
}

/**
 * @brief QueryControl::retrieveTextbookList
 *  retrives a existing list of Textbooks for some Course
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Textbook::itemID
 *     must remain not change otherwize operation will not get the right thing
 *     as the above values are needed to retrive a exisiting Textbook
 *  2) to retrive chapter list use QueryControl::retrieveChapterList()
 * @param courseCode
 *  courseCode to get the textbook for
 * @param courseSection
 *  courseSection to get the textbook for
 * @param termID
 *  termID of the course for which the textbook is under
 * @return
 *  returns a list of Textbooks
 */
QList<Textbook*>* QueryControl::retrieveTextbookList(Course *course,  qint32 termID){
    QList<Textbook*> *textbooks = new QList<Textbook*>();

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
                            "JOIN PurchasableItem ON "
                               "Textbook.itemID = PurchasableItem.ItemID "
                            "JOIN Course_Assigned_Textbook ON "
                                "Textbook.ISBN = Course_Assigned_Textbook.ISBN "
                            "JOIN Course ON "
                                "Course_Assigned_Textbook.courseCode = Course.courseCode AND "
                                "Course_Assigned_Textbook.section = Course.section AND "
                                "Course_Assigned_Textbook.termID = Course.termID "
                            "WHERE Course.courseCode=:courseCode AND Course.section=:section AND Course.termID=:termID "
                                "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC;");
    textBookQuery.bindValue(":courseCode", course->getCourseCode());
    textBookQuery.bindValue(":section", course->getCourseSection());
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

         textbooks->push_back(textbook);
    }

    return textbooks;
}

/**
 * @brief QueryControl::createChapter
 *  creates a new Chapter in DB
 *  Note:
 *  1) to add a chapter use QueryControl::createSection()
 *  2) uses QueryControl::createPurchasableItem()
 * @param chapter
 *  Chapter object to save to DB
 * @param isbn
 *  isbn (primary key of Textbook) to save the chapter under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::createChapter(Chapter *chapter, QString isbn){
    bool noError = true;

    //get the current max item id
    int nextItemID = -1;
    QSqlQuery maxItemID("SELECT MAX(itemID)+1 AS nextItemID FROM PurchasableItem;");
    noError = noError && maxItemID.exec();
    if(maxItemID.first()){
        nextItemID = maxItemID.value(maxItemID.record().indexOf("nextItemID")).toInt();
    }
    chapter->setItemID(nextItemID);

    //create a chapter
    QSqlQuery chapterQuery;

    chapterQuery.prepare("INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID) "
                            "VALUES (:ISBN,:chapterNumber,:chapterTitle,:itemID);");
    chapterQuery.bindValue(":ISBN", isbn);
    chapterQuery.bindValue(":chapterNumber", chapter->getChapterNumber());
    chapterQuery.bindValue(":chapterTitle", chapter->getItemTitle());
    chapterQuery.bindValue(":itemID", chapter->getItemID());

    noError = noError && chapterQuery.exec();

    //create its PurchasableItem
    noError = noError && createPurchasableItem((PurchasableItem*)chapter);

    return noError;
}

/**
 * @brief QueryControl::updateChapter
 *  update a existing Chapter in DB
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Chapter::itemID, Chapter::chapterNumber
 *     must remain not change otherwize operation will not change any thing
 *     as the above values are needed to change a exisiting Chapter
 *  2) to update a chapter use QueryControl::updateSection()
 * @param chapter
 *  Chapter object to save to DB
 * @param isbn
 *  isbn (primary key of Textbook) to save the chapter under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updateChapter(Chapter *chapter, QString isbn){
    bool noError = true;

    //update a chapter
    QSqlQuery chapterQuery;

    chapterQuery.prepare("UPDATE Chapter SET "
                             "ISBN = :ISBN,"
                             "chapterNumber = :chapterNumber,"
                             "chapterTitle = :chapterTitle,"
                             "itemID = :itemID"
                         " WHERE "
                             "ISBN = :ISBN AND "
                             "chapterNumber = :chapterNumber;");
    chapterQuery.bindValue(":ISBN", isbn);
    chapterQuery.bindValue(":chapterNumber", chapter->getChapterNumber());
    chapterQuery.bindValue(":chapterTitle", chapter->getItemTitle());
    chapterQuery.bindValue(":itemID", chapter->getItemID());

    noError = noError && chapterQuery.exec();

    //update its PurchasableItem
    noError = noError && updatePurchasableItem((PurchasableItem*)chapter);

    return noError;
}

/**
 * @brief QueryControl::deleteChapter
 *  Delete a existing Chapter in DB
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Chapter::itemID, Chapter::chapterNumber
 *     must remain not change otherwize operation will not change any thing
 *     as the above values are needed to change a exisiting Chapter
 *  2) to delete a chapter use QueryControl::deleteSection()
 * @param chapter
 *  Chapter object to delete in DB
 * @param isbn
 *  isbn (primary key of Textbook) to delete the chapter under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::deleteChapter(Chapter *chapter, QString isbn){
    bool noError = true;

    //delete a chapter
    QSqlQuery chapterQuery;

    chapterQuery.prepare("DELETE FROM Chapter  WHERE "
                             "ISBN = :ISBN AND "
                             "chapterNumber = :chapterNumber;");
    chapterQuery.bindValue(":ISBN", isbn);
    chapterQuery.bindValue(":chapterNumber", chapter->getChapterNumber());

    noError = noError && chapterQuery.exec();

    //delete its PurchasableItem
    noError = noError && deletePurchasableItem((PurchasableItem*)chapter);

    return noError;

}

/**
 * @brief QueryControl::retrieveChapter
 *  retrieve a existing Chapter from DB
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Chapter::itemID, Chapter::chapterNumber
 *     must remain not change otherwize operation will not get the right thing
 *     as the above values are needed to retrive a exisiting chapter
 *  2) to retrive a section use QueryControl::retrieveSection()
 * @param chapterNumber
 *  primary key of the chapter
 * @param isbn
 *  isbn (primary key of Textbook) to retrive the chapter under
 * @return
 *  returns a Chapter
 */
Chapter* QueryControl::retrieveChapter(qint32 chapterNumber, QString isbn){
    Chapter *chapter;

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
                           "WHERE Textbook.ISBN=:ISBN AND "
                               "Chapter.chapterNumber=:chapterNumber "
                               "ORDER BY Chapter.chapterNumber ASC;");
    chapterQuery.bindValue(":ISBN", isbn);
    chapterQuery.bindValue(":chapterNumber", chapterNumber);

    chapterQuery.exec();

    if (chapterQuery.first()){
       chapter = new Chapter(chapterQuery.value(chapterQuery.record().indexOf("chapterTitle")).toString(),
                              chapterQuery.value(chapterQuery.record().indexOf("chapterNumber")).toInt(),
                              chapterQuery.value(chapterQuery.record().indexOf("itemID")).toInt(),
                              chapterQuery.value(chapterQuery.record().indexOf("price")).toDouble(),
                              chapterQuery.value(chapterQuery.record().indexOf("availability")).toBool());
    }

    return chapter;
}

/**
 * @brief QueryControl::retrieveChapterList
 *  retrives a existing list of Chapters for some Textbook
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Chapter::itemID, Chapter::chapterNumber
 *     must remain not change otherwize operation will not get the right thing
 *     as the above values are needed to retrive a exisiting chapter
 *  2) to retrive a sectionlist use QueryControl::retrieveSectionList()
 * @param isbn
 *  isbn (primary key of Textbook) to retrive the chapter under
 * @return
 *  returns a list of Chapters
 */
QList<Chapter*>* QueryControl::retrieveChapterList(QString isbn){
    QList<Chapter*> *chapters = new QList<Chapter*>();

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
    chapterQuery.bindValue(":ISBN", isbn);
    chapterQuery.exec();

    while (chapterQuery.next()){
       chapters->push_back(new Chapter(chapterQuery.value(chapterQuery.record().indexOf("chapterTitle")).toString(),
                                      chapterQuery.value(chapterQuery.record().indexOf("chapterNumber")).toInt(),
                                      chapterQuery.value(chapterQuery.record().indexOf("itemID")).toInt(),
                                      chapterQuery.value(chapterQuery.record().indexOf("price")).toDouble(),
                                      chapterQuery.value(chapterQuery.record().indexOf("availability")).toBool()));
    }

    return chapters;
}

/**
 * @brief QueryControl::createSection
 *  creates a new Section in DB
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Section::itemID, Chapter::chapterNumber, Section::sectionNumber
 *     must remain not change otherwize operation will not change the right thing
 *     as the above values are needed to change a exisiting section
 *  2) uses QueryControl::createPurchasableItem()
 * @param section
 *  Section object to save to DB
 * @param chapterNumber
 *  chapterNumber (primary key of chapter) to save the section under
 * @param isbn
 *  isbn (primary key of Textbook) to save the section under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::createSection(Section *section, qint32 chapterNumber, QString isbn){
    bool noError = true;

    //get the current max item id
    int nextItemID = -1;
    QSqlQuery maxItemID("SELECT MAX(itemID)+1 AS nextItemID FROM PurchasableItem;");
    noError = noError && maxItemID.exec();
    if(maxItemID.first()){
        nextItemID = maxItemID.value(maxItemID.record().indexOf("nextItemID")).toInt();
    }
    section->setItemID(nextItemID);

    //create a section
    QSqlQuery sectionQuery;

    sectionQuery.prepare("INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID) "
                            "VALUES (:ISBN,:chapterNumber,:sectionNumber,:sectionTitle,:itemID);");
    sectionQuery.bindValue(":ISBN", isbn);
    sectionQuery.bindValue(":chapterNumber", chapterNumber);
    sectionQuery.bindValue(":sectionNumber", section->getSectionNumber());
    sectionQuery.bindValue(":sectionTitle", section->getItemTitle());
    sectionQuery.bindValue(":itemID", section->getItemID());

    noError = noError && sectionQuery.exec();

    //create its PurchasableItem
    noError = noError && createPurchasableItem((PurchasableItem*)section);

    return noError;

}

/**
 * @brief QueryControl::updateSection
 *  update a existing Section in DB
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Section::itemID, Chapter::chapterNumber, Section::sectionNumber
 *     must remain not change otherwize operation will not change the right thing
 *     as the above values are needed to change a exisiting section
 *  2) uses QueryControl::updatePurchasableItem()
 * @param section
 *  Section object to save to DB
 * @param chapterNumber
 *  chapterNumber (primary key of chapter) to save the section under
 * @param isbn
 *  isbn (primary key of Textbook) to save the section under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updateSection(Section *section, qint32 chapterNumber, QString isbn){
    bool noError = true;

    //update a section
    QSqlQuery sectionQuery;

    sectionQuery.prepare("UPDATE Section SET "
                            "ISBN = :ISBN,"
                            "chapterNumber = :chapterNumber,"
                            "sectionNumber = :sectionNumber,"
                            "sectionTitle = :sectionTitle,"
                            "itemID = :itemID"
                         " WHERE "
                             "ISBN = :ISBN AND"
                             "chapterNumber = :chapterNumber AND"
                             "sectionNumber = :sectionNumber;");
    sectionQuery.bindValue(":ISBN", isbn);
    sectionQuery.bindValue(":chapterNumber", chapterNumber);
    sectionQuery.bindValue(":sectionNumber", section->getSectionNumber());
    sectionQuery.bindValue(":sectionTitle", section->getItemTitle());
    sectionQuery.bindValue(":itemID", section->getItemID());

    noError = noError && sectionQuery.exec();

    //update its PurchasableItem
    noError = noError && updatePurchasableItem((PurchasableItem*)section);

    return noError;
}

/**
 * @brief QueryControl::deleteSection
 *  Delete a existing Section in DB
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Section::itemID, Chapter::chapterNumber, Section::sectionNumber
 *     must remain not change otherwize operation will not change the right thing
 *     as the above values are needed to change a exisiting section
 *  2) uses QueryControl::deletePurchasableItem()
 * @param section
 *  Section object to save to DB
 * @param chapterNumber
 *  chapterNumber (primary key of chapter) to delete the section under
 * @param isbn
 *  isbn (primary key of Textbook) to delete the section under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::deleteSection(Section *section, qint32 chapterNumber, QString isbn){
    bool noError = true;

    //delete a section
    QSqlQuery sectionQuery;

    sectionQuery.prepare("DELETE FROM Section WHERE "
                             "ISBN = :ISBN AND"
                             "chapterNumber = :chapterNumber AND"
                             "sectionNumber = :sectionNumber;");
    sectionQuery.bindValue(":ISBN", isbn);
    sectionQuery.bindValue(":chapterNumber", chapterNumber);
    sectionQuery.bindValue(":sectionNumber", section->getSectionNumber());

    noError = noError && sectionQuery.exec();

    //delete its PurchasableItem
    noError = noError && deletePurchasableItem((PurchasableItem*)section);

    return noError;
}

/**
 * @brief QueryControl::retrieveSection
 *  retrieve a existing Chapter from DB
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Section::itemID, Chapter::chapterNumber, Section::sectionNumber
 *     must remain not change otherwize operation will not get the right thing
 *     as the above values are needed to retrive a exisiting section
 * @param sectionNumber
 *  primary key of the section
 * @param chapterNumber
 *  chapterNumber (primary key of chapter) to retrive the section under
 * @param isbn
 *  isbn (primary key of Textbook) to retrive the chapter under
 * @return
 *  returns a Section
 */
Section* QueryControl::retrieveSection(qint32 sectionNumber, qint32 chapterNumber, QString isbn){
    Section *section;

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
                            "WHERE Chapter.ISBN=:ISBN AND "
                                "Chapter.chapterNumber=:chapterNumber AND "
                                "Section.sectionNumber=:sectionNumber "
                                "ORDER BY Section.sectionNumber ASC;");
    sectionQuery.bindValue(":ISBN", isbn);
    sectionQuery.bindValue(":chapterNumber", chapterNumber);
    sectionQuery.bindValue(":sectionNumber", sectionNumber);

    sectionQuery.exec();

    if (sectionQuery.first()){
       section = new Section(sectionQuery.value(sectionQuery.record().indexOf("sectionTitle")).toString(),
                                      sectionQuery.value(sectionQuery.record().indexOf("sectionNumber")).toInt(),
                                      sectionQuery.value(sectionQuery.record().indexOf("itemID")).toInt(),
                                      sectionQuery.value(sectionQuery.record().indexOf("price")).toDouble(),
                                      sectionQuery.value(sectionQuery.record().indexOf("availability")).toBool());
    }

    return section;
}

/**
 * @brief QueryControl::retrieveSectionList
 *  retrives a existing list of Sections for some Chapter in some Textbook
 *  Note:
 *  1) primary ID  i.e Textbook::isbn, Chapter::itemID, Chapter::chapterNumber
 *     must remain not change otherwize operation will not get the right thing
 *     as the above values are needed to retrive a exisiting chapter
 *  2) to retrive a sectionlist use QueryControl::retrieveSectionList()
 * @param chapterNumber
 *  chapterNumber (primary key of chapter) to retrive the section under
 * @param isbn
 *  isbn (primary key of Textbook) to retrive the chapter under
 * @return
 *  returns a list of Section
 */
QList<Section*>* QueryControl::retrieveSectionList(qint32 chapterNumber, QString isbn){
    QList<Section*> *sections = new QList<Section*>();

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
    sectionQuery.bindValue(":ISBN", isbn);
    sectionQuery.bindValue(":chapterNumber", chapterNumber);
    sectionQuery.exec();

    while (sectionQuery.next()){
       sections->push_back(new Section(sectionQuery.value(sectionQuery.record().indexOf("sectionTitle")).toString(),
                                      sectionQuery.value(sectionQuery.record().indexOf("sectionNumber")).toInt(),
                                      sectionQuery.value(sectionQuery.record().indexOf("itemID")).toInt(),
                                      sectionQuery.value(sectionQuery.record().indexOf("price")).toDouble(),
                                      sectionQuery.value(sectionQuery.record().indexOf("availability")).toBool()));
    }

    return sections;
}

/**
 * @brief QueryControl::updateCourseTextbookLink
 *  Link a Textbook to a Course in some term
 * @param course
 *  Course to link to
 * @param termID
 *  termID the course is under
 * @param textbook
 *  Textbook to link
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updateCourseTextbookLink(Course *course, qint32 termID, Textbook *textbook){
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

/**
 * @brief QueryControl::updateCourseStudentLink
 *  Link a Student to a Course in some term
 * @param course
 *  Course to link to
 * @param termID
 *  termID the course is under
 * @param student
 *  Student to link
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updateCourseStudentLink(Course *course, qint32 termID, Student *student){
    // link a student book to a course
    QSqlQuery linkQuery;

    linkQuery.prepare("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                            "VALUES (:studentNumber,:courseCode,:section,:termID);");
    linkQuery.bindValue(":studentNumber", student->getStudentNum());
    linkQuery.bindValue(":courseCode", course->getCourseCode());
    linkQuery.bindValue(":section", course->getCourseSection());
    linkQuery.bindValue(":termID", termID);

    return linkQuery.exec();
}

/**
 * @brief QueryControl::savePaymentInformation
 *  Save payment information for a student
 * @param student
 *  Student to save the payment information under
 * @param info
 *  payment information to save
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::savePaymentInformation(Student *student, PaymentInformation *info) {

    //check if there is a student with that id
    QSqlQuery studentQuery;
    studentQuery.prepare("SELECT COUNT(*) FROM student "
                            "WHERE studentNumber =:studentNumber;");
    studentQuery.bindValue(":studentNumber", student->getStudentNum());
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
        PaymentInformationQuery.bindValue(":studentNumber", student->getStudentNum());

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
        nameQuery.bindValue(":studentNumber", student->getStudentNum());

        return PaymentInformationQuery.exec() && nameQuery.exec();
    }

    return false;
}

/**
 * @brief QueryControl::retrievePaymentInformation
 *  retrieve payment information for a student
 * @param student
 *  Student to save retrieve payment information under
 * @return
 *  Returns PaymentInformation
 */
PaymentInformation* QueryControl::retrievePaymentInformation(Student *student) {
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
    PaymentInformationQuery.bindValue(":studentNumber", student->getStudentNum());
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

    return info;
}

/**
 * @brief QueryControl::retriveStudent
 *  retrieve a student
 * Note:
 *  1) to retrieve payment information use QueryControl::retrieveStudent()
 *  2) to get students shopping cart use QueryControl::getShoppingCartItemList()
 * @param studentNumber
 *  primary key of student
 * @return
 *  returns a Student
 */
Student* QueryControl::retrieveStudent(QString studentNumber){
    Student *student;

    QSqlQuery studentQuery;
    studentQuery.prepare("SELECT Student.studentNumber, "
                                "Student.cmail, "
                                "User.userName, "
                                "User.password, "
                                "User.fullName "
                            "FROM Student "
                            "JOIN User ON "
                               "Student.userName = User.userName "
                            "WHERE Student.studentNumber =:studentNumber "
                                "ORDER BY User.fullName ASC;");
    studentQuery.bindValue(":studentNumber", studentNumber);
    studentQuery.exec();

    if (studentQuery.first()){
         student = new Student(studentQuery.value(studentQuery.record().indexOf("studentNumber")).toString(),
                                   studentQuery.value(studentQuery.record().indexOf("cmail")).toString(),
                                   studentQuery.value(studentQuery.record().indexOf("userName")).toString(),
                                   studentQuery.value(studentQuery.record().indexOf("password")).toString(),
                                   studentQuery.value(studentQuery.record().indexOf("fullName")).toString());
    }

    return student;
}

/**
 * @brief QueryControl::retrieveStudentList
 *  retrieve a list of students for a course
 * @param course
 *  Course to get students for
 * @param termID
 *  termID the course is under
 * @return
 *  returns a list of students
 */
QList<Student*>* QueryControl::retrieveStudentList(Course *course, qint32 termID) {
    QList<Student*> *Students = new QList<Student*>();

    QSqlQuery studentQuery;
    studentQuery.prepare("SELECT Student.studentNumber, "
                                "Student.cmail, "
                                "User.userName, "
                                "User.password, "
                                "User.fullName "
                            "FROM Student "
                            "JOIN User ON "
                               "Student.userName = User.userName "
                            "JOIN Student_RegisteredIn_Course ON "
                                "Student.studentNumber = Student_RegisteredIn_Course.studentNumber"
                            "JOIN Course ON "
                                "Student_RegisteredIn_Course.courseCode = Course.courseCode AND "
                                "Student_RegisteredIn_Course.section = Course.section AND "
                                "Student_RegisteredIn_Course.termID = Course.termID "
                            "WHERE Course.courseCode=:courseCode AND Course.section=:section AND Course.termID=:termID "
                                "ORDER BY User.fullName ASC;");
    studentQuery.bindValue(":courseCode", course->getCourseCode());
    studentQuery.bindValue(":section", course->getCourseSection());
    studentQuery.bindValue(":termID", termID);
    studentQuery.exec();

    while (studentQuery.next()){
        Students->push_back(new Student(studentQuery.value(studentQuery.record().indexOf("studentNumber")).toString(),
                                   studentQuery.value(studentQuery.record().indexOf("cmail")).toString(),
                                   studentQuery.value(studentQuery.record().indexOf("userName")).toString(),
                                   studentQuery.value(studentQuery.record().indexOf("password")).toString(),
                                   studentQuery.value(studentQuery.record().indexOf("fullName")).toString()));
    }

    return Students;
}

/**
 * @brief QueryControl::createPurchasableItem
 *  creates a new PurchasableItem in DB
 * @param purchasableItem
 *  PurchasableItem object to save to DB
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::createPurchasableItem(PurchasableItem* purchasableItem) {
    bool noError = true;

    //create PurchasableItem
    QSqlQuery purchasableItemQuery;

    purchasableItemQuery.prepare("INSERT INTO PurchasableItem (itemID,price,availability) "
                      "VALUES (:itemID,:price,:availability);");
    purchasableItemQuery.bindValue(":itemID", purchasableItem->getItemID());
    purchasableItemQuery.bindValue(":price", purchasableItem->getPrice());
    purchasableItemQuery.bindValue(":availability", purchasableItem->isAvailable());

    noError = noError && purchasableItemQuery.exec();

    return noError;
}

/**
 * @brief QueryControl::updatePurchasableItem
 *  update a existing PurchasableItem in DB
 * @param purchasableItem
 *  PurchasableItem object to save to DB
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updatePurchasableItem(PurchasableItem* purchasableItem) {
    bool noError = true;

    //update PurchasableItem
    QSqlQuery purchasableItemQuery;

    purchasableItemQuery.prepare("UPDATE PurchasableItem SET "
                                    "itemID = :itemID,"
                                    "price = :price"
                                    "availability = availability"
                                 " WHERE "
                                    "itemID = :itemID;");
    purchasableItemQuery.bindValue(":itemID", purchasableItem->getItemID());
    purchasableItemQuery.bindValue(":price", purchasableItem->getPrice());
    purchasableItemQuery.bindValue(":availability", purchasableItem->isAvailable());

    noError = noError && purchasableItemQuery.exec();

    return noError;
}

/**
 * @brief QueryControl::deletePurchasableItem
 *  delete a existing PurchasableItem in DB
 * @param purchasableItem
 *  PurchasableItem object to delete in DB
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::deletePurchasableItem(PurchasableItem* purchasableItem) {
    bool noError = true;

    //delete PurchasableItem
    QSqlQuery purchasableItemQuery;

    purchasableItemQuery.prepare("DELETE FROM PurchasableItem WHERE "
                                    "itemID = :itemID;");
    purchasableItemQuery.bindValue(":itemID", purchasableItem->getItemID());

    noError = noError && purchasableItemQuery.exec();

    return noError;
}

/**
 * @brief QueryControl::getShoppingCartItemList
 *  get a student shopping cart as list of PurchasableItem
 * @return
 *  returns a list of PurchasableItem
 */
QList<PurchasableItem*>* QueryControl::getShoppingCartItemList(Student *student) {
    QList<PurchasableItem*> *purchasableItems = new QList<PurchasableItem*>();

    // get all textbooks in shopping cart
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
                            "JOIN PurchasableItem ON "
                               "Textbook.itemID = PurchasableItem.ItemID "
                            "JOIN ShoppingCart ON "
                                "PurchasableItem.ItemID = ShoppingCart.ItemID "
                            "JOIN Student ON "
                                "ShoppingCart.studentNumber = Student.studentNumber "
                            "WHERE Student.studentNumber=:studentNumber "
                                "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC;");
    textBookQuery.bindValue(":studentNumber", student->getStudentNum());
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

         purchasableItems->push_back(textbook);
    }

    // get all chapters in shopping cart
    QSqlQuery chapterQuery;
    chapterQuery.prepare("SELECT Chapter.chapterTitle, "
                               "Chapter.chapterNumber, "
                               "Chapter.itemID, "
                               "PurchasableItem.price, "
                               "PurchasableItem.availability "
                           "FROM Chapter "
                           "JOIN PurchasableItem ON "
                               "Chapter.itemID = PurchasableItem.ItemID "
                           "JOIN ShoppingCart ON "
                               "PurchasableItem.ItemID = ShoppingCart.ItemID "
                           "JOIN Student ON "
                               "ShoppingCart.studentNumber = Student.studentNumber "
                           "WHERE Student.studentNumber=:studentNumber "
                               "ORDER BY Chapter.chapterNumber ASC;");
    chapterQuery.bindValue(":studentNumber", student->getStudentNum());
    chapterQuery.exec();

    while (chapterQuery.next()){
       purchasableItems->push_back(new Chapter(chapterQuery.value(chapterQuery.record().indexOf("chapterTitle")).toString(),
                                      chapterQuery.value(chapterQuery.record().indexOf("chapterNumber")).toInt(),
                                      chapterQuery.value(chapterQuery.record().indexOf("itemID")).toInt(),
                                      chapterQuery.value(chapterQuery.record().indexOf("price")).toDouble(),
                                      chapterQuery.value(chapterQuery.record().indexOf("availability")).toBool()));
    }

    // get all sections in shopping cart
    QSqlQuery sectionQuery;
    sectionQuery.prepare("SELECT section.sectionTitle, "
                                "section.sectionNumber, "
                                "section.itemID, "
                                "PurchasableItem.price, "
                                "PurchasableItem.availability "
                            "FROM Section "
                            "JOIN PurchasableItem ON "
                                "Section.itemID = PurchasableItem.ItemID "
                            "JOIN ShoppingCart ON "
                                "PurchasableItem.ItemID = ShoppingCart.ItemID "
                            "JOIN Student ON "
                                "ShoppingCart.studentNumber = Student.studentNumber "
                            "WHERE Student.studentNumber=:studentNumber "
                                "ORDER BY Section.sectionNumber ASC;");
    sectionQuery.bindValue(":studentNumber", student->getStudentNum());
    sectionQuery.exec();

    while (sectionQuery.next()){
       purchasableItems->push_back(new Section(sectionQuery.value(sectionQuery.record().indexOf("sectionTitle")).toString(),
                                      sectionQuery.value(sectionQuery.record().indexOf("sectionNumber")).toInt(),
                                      sectionQuery.value(sectionQuery.record().indexOf("itemID")).toInt(),
                                      sectionQuery.value(sectionQuery.record().indexOf("price")).toDouble(),
                                      sectionQuery.value(sectionQuery.record().indexOf("availability")).toBool()));
    }

    return purchasableItems;
}

/**
 * @brief QueryControl::addPurchasableItemToCart
 *  Add a PurchasableItem to a students ShoppingCart in DB
 * @param purchasableItem
 *  purchasableItem to add
 * @param student
 *  the student who owns the shopping cart
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::addPurchasableItemToCart(PurchasableItem *purchasableItem, Student *student) {
    bool noError = true;

    // check if the item in in cart
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT quantity FROM ShoppingCart WHERE studentNumber=:studentNumber AND itemID=:itemID");
    checkQuery.bindValue(":studentNumber",student->getStudentNum());
    checkQuery.bindValue(":itemID",purchasableItem->getItemID());
    checkQuery.exec();

    int quantity = 0;
    if(checkQuery.next()) {
        quantity = checkQuery.value(checkQuery.record().indexOf("quantity")).toInt();
    }
    // increase quantity from before
    quantity++;
    //add PurchasableItem To Cart
    QSqlQuery purchasableItemQuery;

    purchasableItemQuery.prepare("REPLACE INTO ShoppingCart(studentNumber,itemID,quantity) "
                      "VALUES (:studentNumber,:itemID,:quantity);");
    purchasableItemQuery.bindValue(":studentNumber", student->getStudentNum());
    purchasableItemQuery.bindValue(":itemID", purchasableItem->getItemID());
    purchasableItemQuery.bindValue(":quantity", quantity);

    noError = noError && purchasableItemQuery.exec();

    return noError;
}

/**
 * @brief QueryControl::updateOrderContents
 *  Add a PurchasableItem to a students order DB
 *  Needed for record keeping
 * @param purchasableItem
 *  purchasableItem to add to order
 * @param student
 *  the student who the order is processed for
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updateOrderContents(PurchasableItem *purchasableItem, Student *student) {
    bool noError = true;

    //get the current max order id asume one for no entry condition
    int nextOrderID = 1;
    QSqlQuery maxOrderID("SELECT MAX(orderID)+1 AS nextOrderID FROM Orders;");
    noError = noError && maxOrderID.exec();
    if(maxOrderID.first()){
        nextOrderID = maxOrderID.value(maxOrderID.record().indexOf("nextOrderID")).toInt();
    }

    //add PurchasableItem To Orders
    QSqlQuery purchasableItemQuery;

    purchasableItemQuery.prepare("INSERT INTO Orders(studentNumber,itemID,orderID) "
                      "VALUES (:studentNumber,:itemID,:orderID);");
    purchasableItemQuery.bindValue(":studentNumber", student->getStudentNum());
    purchasableItemQuery.bindValue(":itemID", purchasableItem->getItemID());
    purchasableItemQuery.bindValue(":orderID", nextOrderID);

    return noError;
}

