#include "QueryControl.h"

/**
 * @brief QueryControl::QueryControl
 *  connects to DB
 *  if DB is currupt it will reset to default schema and values
 */
QueryControl::QueryControl() {
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../cuTPS.db");
    if(!db.open())
        qDebug() << "FAILED TO CONNECT TO DATA BASE";
    else {
        qDebug() << "CONNECT TO DATA BASE";

        //enable it for on cascade
        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");

        // if role table not found assume curruft or missing DB and reset it!
        if(!db.tables().contains("Role")) {
            qDebug() << "DATABASE NOT INITIALIZED... LOADING DEFAULT VALUES";
            qDebug() <<  this->resetDatabase();
        }
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

    qDebug() << "\ntest for resetDatabase\n";
    qDebug() << this->resetDatabase();

    qDebug() << "\ntest for retrieveTextbookList\n";
    foreach(Textbook *tbks, *(this->retrieveAllTextbookList())){
        json = QJsonObject();
        tbks->write(json);
        qDebug() <<json;
    }

    foreach(Textbook *tbks,  *(this->retrieveTextbookList(new Course("COMP3004", "A", "a"), 1, true))){
        qDebug() << "\ntest for retrieveTextbookList on predifined course\n";
        json = QJsonObject();
        tbks->write(json);
        qDebug() <<json;

        foreach(Chapter *chpts, *(this->retrieveChapterList(tbks->getISBN(), true))){
            qDebug() << "\ntest for retrieveChapterList on predifined course\n";
            json = QJsonObject();
            chpts->write(json);
            qDebug() <<json;

            foreach(Section *sec, *(this->retrieveSectionList(chpts->getChapterNumber(), tbks->getISBN(), true))){
                qDebug() << "\ntest for retrieveSectionList on predifined course\n";
                json = QJsonObject();
                sec->write(json);
                qDebug() <<json;
            }
        }
    }

    qDebug() << "\ntest for retrieveTermList\n";
    QList<Term*> *termlist= this->retrieveTermList();
    foreach(Term *trm, *termlist){
        json = QJsonObject();
        trm->write(json);
        qDebug() <<json;
    }

    Term *term = termlist->at(0);

    Course *course = new Course("COMP3004","N","Dr. Laurendeau");
    course->setTerm(term);

    qDebug() << "\ntest for createCourse\n";
    qDebug() << this->updateCourse(course, term->getTermID());

    qDebug() << "\ntest for retrieveCourseList after createCourse\n";
    foreach(Course *crs,  *(this->retrieveCourseList(term->getTermID()))){
        json = QJsonObject();
        crs->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for updateCourse\n";
    course->setInstructor("L Nel");
    qDebug() << this->updateCourse(course, term->getTermID());

    qDebug() << "\ntest for retrieveCourseList after updateCourse\n";
    foreach(Course *crs,  *(this->retrieveCourseList(term->getTermID()))){
        json = QJsonObject();
        crs->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for retrieveStudent\n";
    Student *student = this->retrieveStudent("100853074");
    json = QJsonObject();
    student->write(json);
    qDebug() <<json;

    qDebug() << "\ntest for retrievePaymentInformation\n";
    PaymentInformation *paymentInformation = this->retrievePaymentInformation(student);
    student->setPayInfo(*paymentInformation);
    json = QJsonObject();
    student->write(json);
    qDebug() <<json;

    delete(paymentInformation);

    qDebug() << "\ntest for updatePaymentInformation\n";
    paymentInformation = new PaymentInformation(); // will use default const
    qDebug() << this->updatePaymentInformation(student, paymentInformation);

    delete(paymentInformation);

    qDebug() << "\ntest for retrieveCourseList after savePaymentInformation\n";
    paymentInformation = this->retrievePaymentInformation(student);
    student->setPayInfo(*paymentInformation);
    json = QJsonObject();
    student->write(json);
    qDebug() <<json;

    qDebug() << "\ntest for retrieveStudentCourseList\n";
    foreach(Course *crs,  *(this->retrieveStudentCourseList(student->getStudentNum(), term->getTermID()))){
        json = QJsonObject();
        crs->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for updateCourseStudentLink\n";
    qDebug() << this->updateCourseStudentLink(course, term->getTermID(), student);

    qDebug() << "\ntest for retrieveStudentCourseList after updateCourseStudentLink after createCourse\n";
    foreach(Course *crs, *(this->retrieveStudentCourseList(student->getStudentNum(), term->getTermID()))){
        json = QJsonObject();
        crs->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for retrieveStudentList after updateCourseStudentLink after createCourse\n";
    foreach(Student *stu, *(this->retrieveStudentList(course, term->getTermID()))){
        json = QJsonObject();
        stu->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for createTextbook\n";
    Textbook *textbook = new Textbook();
    qDebug() << this->updateTextbook(textbook);

    QString isbn = textbook->getISBN();
    delete(textbook);

    qDebug() << "\ntest for retrieveTextbook after createTextbook\n";
    textbook = this->retrieveTextbook(isbn,false);
    json = QJsonObject();
    textbook->write(json);
    qDebug() <<json;

    qDebug() << "\ntest for updateCourseTextbookLink\n";
    qDebug() << this->updateCourseTextbookLink(course, term->getTermID(), textbook);

    qDebug() << "\ntest for retrieveTextbookList after updateCourseTextbookLink\n";
    foreach(Textbook *tbks,  *(this->retrieveTextbookList(course, term->getTermID(), false))){
        json = QJsonObject();
        tbks->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for updateTextbook\n";
    textbook->setEdition("900");
    textbook->setItemTitle("a random textbook");
    textbook->setPrice(1000);
    textbook->setAvailability(true);

    qDebug() << this->updateTextbook(textbook);

    delete(textbook);

    qDebug() << "\ntest for retrieveTextbook after updateTextbook\n";
    textbook = this->retrieveTextbook(isbn, false);
    json = QJsonObject();
    textbook->write(json);
    qDebug() <<json;

    qDebug() << "\ntest for retrieveTextbookList after updateTextbook\n";
    qDebug() << this->updateTextbook(textbook);
    foreach(Textbook *tbks,  *(this->retrieveTextbookList(course, term->getTermID(), false))){
        json = QJsonObject();
        tbks->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for createChapter\n";
    Chapter *chapter = new Chapter();
    qDebug() << this->updateChapter(chapter, isbn);

    qint32 chapterNumber = chapter->getChapterNumber();
    delete(chapter);

    qDebug() << "\ntest for retrieveChapter after createChapter\n";
    chapter = this->retrieveChapter(chapterNumber, isbn, false);
    json = QJsonObject();
    chapter->write(json);
    qDebug() <<json;

    qDebug() << "\ntest for retrieveChapterList after createChapter\n";
    foreach(Chapter *chpts, *(this->retrieveChapterList(isbn, false))){
        json = QJsonObject();
        chpts->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for updateChapter\n";
    chapter->setItemTitle("a random chapter");
    chapter->setPrice(1000);
    chapter->setAvailability(true);

    qDebug() << this->updateChapter(chapter, isbn);

    delete(chapter);

    qDebug() << "\ntest for retrieveChapter after updateChapter\n";
    chapter = this->retrieveChapter(chapterNumber, isbn, false);
    json = QJsonObject();
    chapter->write(json);
    qDebug() <<json;

    qDebug() << "\ntest for retrieveChapterList after updateChapter\n";
    foreach(Chapter *chpts, *(this->retrieveChapterList(isbn, false))){
        json = QJsonObject();
        chpts->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for createSection\n";
    Section *section = new Section();
    qDebug() << this->updateSection(section, chapterNumber, isbn);

    qint32 sectionNumber = section->getSectionNumber();
    delete(section);

    qDebug() << "\ntest for retrieveSection after createSection\n";
    section = this->retrieveSection(sectionNumber, chapterNumber, isbn, false);
    json = QJsonObject();
    section->write(json);
    qDebug() <<json;

    qDebug() << "\ntest for retrieveSectionList after createSection\n";
    foreach(Section *sec, *(this->retrieveSectionList(chapterNumber, isbn, false))){
        json = QJsonObject();
        sec->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for updateSection\n";
    section->setItemTitle("a random section");
    section->setPrice(1000);
    section->setAvailability(true);

    qDebug() << this->updateSection(section, chapterNumber, isbn);

    delete(section);

    qDebug() << "\ntest for retrieveSection after updateSection\n";
    section = this->retrieveSection(sectionNumber, chapterNumber, isbn, false);
    json = QJsonObject();
    section->write(json);
    qDebug() <<json;

    qDebug() << "\ntest for retrieveSectionList after updateSection\n";
    foreach(Section *sec, *(this->retrieveSectionList(chapterNumber, isbn, false))){
        json = QJsonObject();
        sec->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntext for getShoppingCartItemList\n";
    QList< QPair<PurchasableItem*,qint32> > *list = this->retrieveShoppingCartItemList(student, false);
    for(int i = 0; i<list->length(); i++) {
        json = QJsonObject();
        list->at(i).first->write(json);
        qDebug() <<json;
    }
    delete(list);

    qDebug() << "\ntext for addPurchasableItemToCart\n";
    qDebug() << addPurchasableItemToCart((PurchasableItem*) textbook, student);
    qDebug() << addPurchasableItemToCart((PurchasableItem*) chapter, student);
    qDebug() << addPurchasableItemToCart((PurchasableItem*) section, student);

    qDebug() << "\ntext for getShoppingCartItemList after addPurchasableItemToCart\n";
    list = this->retrieveShoppingCartItemList(student, false);
    for(int i = 0; i<list->length(); i++) {
        json = QJsonObject();
        list->at(i).first->write(json);
        qDebug() <<json;
    }
    delete(list);

    qDebug() << "\ntext for emptyShoppingCart\n";
    qDebug() << emptyShoppingCart(student);

    qDebug() << "\ntext for getShoppingCartItemList after emptyShoppingCart\n";
    list = this->retrieveShoppingCartItemList(student, false);
    for(int i = 0; i<list->length(); i++) {
        json = QJsonObject();
        list->at(i).first->write(json);
        qDebug() <<json;
    }
    delete(list);

    qDebug() << "\ntext for addPurchasableItemToCart after after emptyShoppingCart\n";
    qDebug() << addPurchasableItemToCart((PurchasableItem*) textbook, student);
    qDebug() << addPurchasableItemToCart((PurchasableItem*) chapter, student);
    qDebug() << addPurchasableItemToCart((PurchasableItem*) section, student);

    qDebug() << "\ntext for getShoppingCartItemList after addPurchasableItemToCart after emptyShoppingCart\n";
    list = this->retrieveShoppingCartItemList(student, false);
    for(int i = 0; i<list->length(); i++) {
        json = QJsonObject();
        list->at(i).first->write(json);
        qDebug() <<json;
    }
    delete(list);

    qDebug() << "\ntext for updateOrderContents\n";
    qDebug() << updateOrderContents((PurchasableItem*) textbook, student);
    qDebug() << updateOrderContents((PurchasableItem*) chapter, student);
    qDebug() << updateOrderContents((PurchasableItem*) section, student);

    qDebug() << "\ntest for deleteSection\n";
    qDebug() << this->deleteSection(section, chapterNumber, isbn);

    delete(section);

    qDebug() << "\ntest for retrieveSection after deleteSection\n";
    section = this->retrieveSection(sectionNumber, chapterNumber, isbn, false);
    if (section != NULL){
        json = QJsonObject();
        section->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for retrieveSectionList after deleteSection\n";
    foreach(Section *sec, *(this->retrieveSectionList(chapterNumber, isbn, false))){
        json = QJsonObject();
        sec->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for deleteChapter\n";
    qDebug() << this->deleteChapter(chapter, isbn);

    delete(chapter);

    qDebug() << "\ntest for retrieveChapter after deleteChapter\n";
    chapter = this->retrieveChapter(chapterNumber, isbn, false);
    if (chapter != NULL){
        json = QJsonObject();
        chapter->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for retrieveChapterList after deleteChapter\n";
    foreach(Chapter *chpts, *(this->retrieveChapterList(isbn, false))){
        json = QJsonObject();
        chpts->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for deleteTextbook\n";
    qDebug() << this->deleteTextbook(textbook);

    delete(textbook);

    qDebug() << "\ntest for retrieveTextbook after deleteTextbook\n";
    textbook = this->retrieveTextbook(isbn, false);
    if(textbook!=NULL) {
        json = QJsonObject();
        textbook->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for retrieveTextbookList after deleteTextbook\n";
    foreach(Textbook *tbks,  *(this->retrieveTextbookList(course, term->getTermID(), false))){
        json = QJsonObject();
        tbks->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for deleteCourse\n";
    qDebug() << this->deleteCourse(course, term->getTermID());

    qDebug() << "\ntest for retrieveStudentCourseList after deleteCourse\n";
    foreach(Course *crs,  *(this->retrieveStudentCourseList(student->getStudentNum(), term->getTermID()))){
        json = QJsonObject();
        crs->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for retrieveStudentList after updateCourseStudentLink after deleteCourse\n";
    foreach(Student *stu, *(this->retrieveStudentList(course, term->getTermID()))){
        json = QJsonObject();
        stu->write(json);
        qDebug() <<json;
    }

    qDebug() << "\ntest for getPurchasableItemList\n";
    foreach (PurchasableItem *pi, *(this->retrieveAllPurchasableItemList(false))){
        json = QJsonObject();
        pi->write(json);
        qDebug() <<json;
    }
/**/
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
    noError = noError && query.exec("begin transaction;");                                                                                                                                                          //qDebug() << query.lastQuery() << query.lastError();

    // load default values

    // insert default User(s)
    noError = noError && query.exec("INSERT INTO User (userName,fullName,password,roleID) "
                                        "VALUES ('Nooyen', 'Robert Nguyen', 'hunter', 3);");                                                                                                                        //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO User (userName,fullName,password,roleID) "
                                        "VALUES ('BurryInAHurry', 'Graham Burry', 'huntermanager', 2);");                                                                                                           //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO User (userName,fullName,password,roleID) "
                                        "VALUES ('Kushlord', 'Ankush Varshneya', 'hunter1', 1);");                                                                                                                  //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO User (userName,fullName,password,roleID) "
                                        "VALUES ('Mooreloaded', 'Ryan Moore', 'hunter2', 1);");                                                                                                                     //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO User (userName,fullName,password,roleID) "
                                        "VALUES ('LorettaBetta','Loretta Lee','hunter3',1);");                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();

    // insert default Students(s)
    noError = noError && query.exec("INSERT INTO Student (studentNumber,cmail,userName) "
                                        "VALUES ('100853074','ankushlord@cmail.carleton.ca','Kushlord');");                                                                                                         //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Student (studentNumber,cmail,userName) "
                                        "VALUES ('100853075','ryanmoore@cmail.carleton.ca','Mooreloaded');");                                                                                                       //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Student (studentNumber,cmail,userName) "
                                        "VALUES ('100853076','somestudent@cmail.carleton.ca','LorettaBetta');");                                                                                                    //qDebug() << query.lastQuery() << query.lastError();

    // insert default PaymentInformation(s)
    noError = noError && query.exec("INSERT INTO PaymentInformation (creditCardNumber, cardType, cvv, expirationDate, nameOnCard,postalCode,province,city,streetName,houseNumber,studentNumber) "
                                        "Values ('2345-5675-1234', 'Master Card', '756','19760420','Ankush Dabess Varshneya','H8R8H8','Ontario','Ottawa','Swag St.',420,'100853074');");                            //qDebug() << query.lastQuery() << query.lastError();

    // insert default Terms(s)
    noError = noError && query.exec("INSERT INTO Term (termID,termName,startDate,endDate) "
                                        "VALUES (1,'fall2014','20140905','20141209');");                                                                                                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Term (termID,termName,startDate,endDate) "
                                        "VALUES (2,'winter2015','20150105','20151209');");                                                                                                                          //qDebug() << query.lastQuery() << query.lastError();

    // insert default Course(s)
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('COMP3004','A', 'Christine Laurendeau',1);");                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('COMP3804', 'B', 'Amin Gheibi',1);");                                                                                                                               //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('COMP3000','C', 'Anil Somayaji',1);");                                                                                                                             //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('COMP3203', 'D', 'Michel Barbeau',1);");                                                                                                                            //qDebug() << query.lastQuery() << query.lastError();

    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('COMP3005','A', 'Louis Nel',2);");                                                                                                                                 //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('COMP3007', 'B', 'Gail Carmichael',2);");                                                                                                                           //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('COMP3008','C', 'Sonia Chiasson',2);");                                                                                                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('COMP2406','D', 'Anil Somayaji',2);");                                                                                                                                 //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course (courseCode,section,instructor,termID) "
                                        "VALUES ('COMP2402', 'E', 'Patrick Morin',2);");                                                                                                                           //qDebug() << query.lastQuery() << query.lastError();

    // insert default PurchasableItem(s)
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (1,1.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (2,2.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (3,3.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (4,4.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (5,5.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (6,6.99,0);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (7,1.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (8,2.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (9,3.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (10,4.99,1);");                                                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (11,5.99,1);");                                                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (12,6.99,0);");                                                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (13,1.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (14,2.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (15,3.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (16,4.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (17,5.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (18,6.99,0);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (19,1.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (20,2.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (21,3.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (22,4.99,1);");                                                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (23,5.99,1);");                                                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (24,6.99,0);");                                                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (25,1.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (26,2.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (27,3.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (28,4.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (29,5.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (30,6.99,0);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (31,1.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (32,2.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (33,3.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (34,4.99,1);");                                                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (35,5.99,1);");                                                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (36,6.99,0);");                                                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (37,1.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (38,2.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (39,3.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (40,4.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (41,5.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (42,6.99,0);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (43,1.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (44,2.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (45,3.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (46,4.99,1);");                                                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (47,5.99,1);");                                                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (48,6.99,0);");                                                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (49,1.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (50,2.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (51,3.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (52,4.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (53,5.99,1);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO PurchasableItem (itemID,price,availability) "
                                        "VALUES (54,6.99,0);");                                                                                                                                                      //qDebug() << query.lastQuery() << query.lastError();

    // insert default Textbook(s), Chapter(s), Section(s)

    // Textbook#1
    noError = noError && query.exec("INSERT INTO Textbook (itemID,ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition) "
                                        "VALUES (1,'111-1-11-111111-0','./COMP3004.png','COMP3004 course pack is required!','Author of COMP3004','COMP3004 A Course Pack','Carleton Course Pack Inc.','1st');");    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (2,'111-1-11-111111-0',1,'Intro To COMP3004');");                                                                                                                   //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (3,'111-1-11-111111-0',1,1,'Pre-reqs for COMP3004');");                                                                                                             //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (4,'111-1-11-111111-0',1,2,'Review needed information for COMP3004');");                                                                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (5,'111-1-11-111111-0',2,'COMP3004 Midterm');");                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (6,'111-1-11-111111-0',2,1,'COMP3004 Midterm mark break-up');");                                                                                                    //qDebug() << query.lastQuery() << query.lastError();

    // Textbook#2
    noError = noError && query.exec("INSERT INTO Textbook (itemID,ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition) "
                                        "VALUES (7,'222-2-22-222222-0','./COMP3804.png','COMP3804 course pack is required!','Author of COMP3804','COMP3804 A Course Pack','Carleton Course Pack Inc.','1st');");    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (8,'222-2-22-222222-0',1,'Intro To COMP3804');");                                                                                                                   //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (9,'222-2-22-222222-0',1,1,'Pre-reqs for COMP3804');");                                                                                                             //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (10,'222-2-22-222222-0',1,2,'Review needed information for COMP3804');");                                                                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (11,'222-2-22-222222-0',2,'COMP3804 Midterm');");                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (12,'222-2-22-222222-0',2,1,'COMP3804 Midterm mark break-up');");                                                                                                    //qDebug() << query.lastQuery() << query.lastError();

    // Textbook#3
    noError = noError && query.exec("INSERT INTO Textbook (itemID,ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition) "
                                        "VALUES (13,'333-3-33-333333-0','./COMP3000.png','COMP3000 course pack is required!','Author of COMP3000','COMP3000 A Course Pack','Carleton Course Pack Inc.','1st');");    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (14,'333-3-33-333333-0',1,'Intro To COMP3000');");                                                                                                                   //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (15,'333-3-33-333333-0',1,1,'Pre-reqs for COMP3000');");                                                                                                             //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (16,'333-3-33-333333-0',1,2,'Review needed information for COMP3000');");                                                                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (17,'333-3-33-333333-0',2,'COMP3000 Midterm');");                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (18,'333-3-33-333333-0',2,1,'COMP3000 Midterm mark break-up');");

    // Textbook#4
    noError = noError && query.exec("INSERT INTO Textbook (itemID,ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition) "
                                        "VALUES (19,'444-4-44-444444-0','./COMP3203.png','COMP3203 course pack is required!','Author of COMP3203','COMP3203 A Course Pack','Carleton Course Pack Inc.','1st');");    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (20,'444-4-44-444444-0',1,'Intro To COMP3203');");                                                                                                                   //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (21,'444-4-44-444444-0',1,1,'Pre-reqs for COMP3203');");                                                                                                             //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (22,'444-4-44-444444-0',1,2,'Review needed information for COMP3203');");                                                                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (23,'444-4-44-444444-0',2,'COMP3203 Midterm');");                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (24,'444-4-44-444444-0',2,1,'COMP3203 Midterm mark break-up');");

    // Textbook#5
    noError = noError && query.exec("INSERT INTO Textbook (itemID,ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition) "
                                        "VALUES (25,'555-5-55-555555-0','./COMP3005.png','COMP3005 course pack is required!','Author of COMP3005','COMP3005 A Course Pack','Carleton Course Pack Inc.','1st');");    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (26,'555-5-55-555555-0',1,'Intro To COMP3005');");                                                                                                                   //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (27,'555-5-55-555555-0',1,1,'Pre-reqs for COMP3005');");                                                                                                             //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (28,'555-5-55-555555-0',1,2,'Review needed information for COMP3005');");                                                                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (29,'555-5-55-555555-0',2,'COMP3005 Midterm');");                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (30,'555-5-55-555555-0',2,1,'COMP3005 Midterm mark break-up');");

    // Textbook#6
    noError = noError && query.exec("INSERT INTO Textbook (itemID,ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition) "
                                        "VALUES (31,'666-6-66-666666-0','./COMP3007.png','COMP3007 course pack is required!','Author of COMP3007','COMP3007 A Course Pack','Carleton Course Pack Inc.','1st');");    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (32,'666-6-66-666666-0',1,'Intro To COMP3007');");                                                                                                                   //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (33,'666-6-66-666666-0',1,1,'Pre-reqs for COMP3007');");                                                                                                             //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (34,'666-6-66-666666-0',1,2,'Review needed information for COMP3007');");                                                                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (35,'666-6-66-666666-0',2,'COMP3007 Midterm');");                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (36,'666-6-66-666666-0',2,1,'COMP3007 Midterm mark break-up');");

    // Textbook#7
    noError = noError && query.exec("INSERT INTO Textbook (itemID,ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition) "
                                        "VALUES (37,'777-7-77-777777-0','./COMP3008.png','COMP3008 course pack is required!','Author of COMP3008','COMP3008 A Course Pack','Carleton Course Pack Inc.','1st');");    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (38,'777-7-77-777777-0',1,'Intro To COMP3008');");                                                                                                                   //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (39,'777-7-77-777777-0',1,1,'Pre-reqs for COMP3008');");                                                                                                             //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (40,'777-7-77-777777-0',1,2,'Review needed information for COMP3008');");                                                                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (41,'777-7-77-777777-0',2,'COMP3008 Midterm');");                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (42,'777-7-77-777777-0',2,1,'COMP3008 Midterm mark break-up');");

    // Textbook#8
    noError = noError && query.exec("INSERT INTO Textbook (itemID,ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition) "
                                        "VALUES (43,'888-8-88-888888-0','./COMP2406.png','COMP2406 course pack is required!','Author of COMP2406','COMP2406 A Course Pack','Carleton Course Pack Inc.','1st');");    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (44,'888-8-88-888888-0',1,'Intro To COMP2406');");                                                                                                                   //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (45,'888-8-88-888888-0',1,1,'Pre-reqs for COMP2406');");                                                                                                             //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (46,'888-8-88-888888-0',1,2,'Review needed information for COMP2406');");                                                                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (47,'888-8-88-888888-0',2,'COMP2406 Midterm');");                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (48,'888-8-88-888888-0',2,1,'COMP2406 Midterm mark break-up');");

    // Textbook#9
    noError = noError && query.exec("INSERT INTO Textbook (itemID,ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition) "
                                        "VALUES (49,'999-9-99-999999-0','./COMP2402.png','COMP2402 course pack is required!','Author of COMP2402','COMP2402 A Course Pack','Carleton Course Pack Inc.','1st');");    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (50,'999-9-99-999999-0',1,'Intro To COMP2402');");                                                                                                                   //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (51,'999-9-99-999999-0',1,1,'Pre-reqs for COMP2402');");                                                                                                             //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (52,'999-9-99-999999-0',1,2,'Review needed information for COMP2402');");                                                                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Chapter (itemID,ISBN,chapterNumber,chapterTitle) "
                                        "VALUES (53,'999-9-99-999999-0',2,'COMP2402 Midterm');");                                                                                                                    //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Section (itemID,ISBN,chapterNumber,sectionNumber,sectionTitle) "
                                        "VALUES (54,'999-9-99-999999-0',2,1,'COMP2402 Midterm mark break-up');");

    // insert default Course_Assigned_Textbook(s)
    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('111-1-11-111111-0','COMP3004','A',1);");                                                                                                                          //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('222-2-22-222222-0','COMP3804','B',1);");                                                                                                                          //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('333-3-33-333333-0','COMP3000','C',1);");                                                                                                                          //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('444-4-44-444444-0','COMP3203','D',1);");                                                                                                                          //qDebug() << query.lastQuery() << query.lastError();


    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('555-5-55-555555-0','COMP3005','A',2);");                                                                                                                          //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('666-6-66-666666-0','COMP3007','B',2);");                                                                                                                          //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('777-7-77-777777-0','COMP3008','C',2);");                                                                                                                          //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('888-8-88-888888-0','COMP2406','D',2);");                                                                                                                          //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
                                        "VALUES ('999-9-99-999999-0','COMP2402','E',2);");                                                                                                                          //qDebug() << query.lastQuery() << query.lastError();

    // insert default Student_RegisteredIn_Course(s)
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP3004', 'A', 1);");                                                                                                                                //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP3804', 'B', 1);");                                                                                                                                //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP3000', 'C', 1);");                                                                                                                                //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP3203', 'D', 1);");                                                                                                                                //qDebug() << query.lastQuery() << query.lastError();

    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP3005', 'A', 2);");                                                                                                                                //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP3007', 'B', 2);");                                                                                                                                //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP3008', 'C', 2);");                                                                                                                                //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP2406', 'D', 2);");                                                                                                                                //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                                        "VALUES ('100853074','COMP2402', 'E', 2);");                                                                                                                                //qDebug() << query.lastQuery() << query.lastError();

    //commit transaction
    noError = noError && query.exec("commit;");                                                                                                                                                                     //qDebug() << query.lastQuery() << query.lastError();

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
    noError = noError && query.exec("drop table if exists ShoppingCart;");                                      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists Orders;");                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists Student_RegisteredIn_Course;");                       //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists Course_Assigned_Textbook;");                          //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists Course;");                                            //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists Term;");                                              //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists Textbook;");                                          //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists Chapter;");                                           //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists Section;");                                           //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists PurchasableItem;");                                   //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists PaymentInformation;");                                //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists Student;");                                           //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists User;");                                              //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("drop table if exists Role;");                                              //qDebug() << query.lastQuery() << query.lastError();

    // creating the Table called Role
    noError = noError && query.exec("create table Role("
                                        "roleID integer NOT NULL,"
                                        "roleType varchar(20),"
                                        "PRIMARY KEY (roleID)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();
    // insert default Role(s)
    noError = noError && query.exec("insert into Role (roleID, roleType) values (1, 'Student');");              //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("insert into Role (roleID, roleType) values (2, 'Content Manager');");      //qDebug() << query.lastQuery() << query.lastError();
    noError = noError && query.exec("insert into Role (roleID, roleType) values (3, 'Administrator');");        //qDebug() << query.lastQuery() << query.lastError();

    // creating the Table called User
    noError = noError && query.exec("create table User("
                                        "userName varchar(50) NOT NULL,"
                                        "fullName varchar(50),"
                                        "password varchar(20),"
                                        "roleID integer NOT NULL,"
                                        "FOREIGN KEY (roleID) references Role(roleID) on delete cascade,"
                                        "PRIMARY KEY (userName)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

    // creating the Table called Student
    noError = noError && query.exec("create table Student("
                                        "studentNumber varchar(10) NOT NULL,"
                                        "cmail varchar(100) NOT NULL UNIQUE,"
                                        "userName varchar(50) NOT NULL,"
                                        "FOREIGN KEY (userName) references User(userName) on delete cascade,"
                                        "PRIMARY KEY (studentNumber)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

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
                                        "studentNumber varchar(10) NOT NULL,"
                                        "FOREIGN KEY (studentNumber) references Student(studentNumber) on delete cascade,"
                                        "PRIMARY KEY (studentNumber, creditCardNumber)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

    //creating the Table called Student_RegisteredIn_Course
    noError = noError && query.exec("create table Student_RegisteredIn_Course("
                                        "studentNumber varchar(10) NOT NULL,"
                                        "courseCode varchar(8) NOT NULL,"
                                        "section varchar(1) NOT NULL,"
                                        "termID integer NOT NULL,"
                                        "FOREIGN KEY (studentNumber) references Student(studentNumber) on delete cascade,"
                                        "FOREIGN KEY (courseCode, section, termID) references Course(courseCode, section, termID) on delete cascade,"
                                        "PRIMARY KEY (studentNumber, courseCode, section, termID)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

    //creating the Table called Course
    noError = noError && query.exec("create table Course("
                                        "courseCode varchar(8) NOT NULL,"
                                        "section varchar(1) NOT NULL,"
                                        "instructor varchar(20),"
                                        "termID integer NOT NULL,"
                                        "FOREIGN KEY (termID) references Term(termID) on delete cascade,"
                                        "PRIMARY KEY (courseCode, section, termID)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

    // creating the Table called Term
    noError = noError && query.exec("create table Term("
                                        "termID integer NOT NULL,"
                                        "termName varchar(25),"
                                        "startDate varchar(10),"
                                        "endDate varchar(10),"
                                        "PRIMARY KEY (termID)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

    //creating the Table called Textbook
    noError = noError && query.exec("create table Textbook("
                                        "ISBN varchar(20) NOT NULL,"
                                        "coverImageLocation varchar(100),"
                                        "desc varchar(200),"
                                        "author varchar(50),"
                                        "textBookTitle varchar(50),"
                                        "publisher varchar(50),"
                                        "edition varchar(50),"
                                        "itemID integer NOT NULL,"
                                        "FOREIGN KEY (itemID) references PurchasableItem(itemID) on delete cascade,"
                                        "PRIMARY KEY (ISBN)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

   // creating the Table called Chapter
    noError = noError && query.exec("create table Chapter("
                                        "ISBN varchar(20) NOT NULL,"
                                        "chapterNumber integer NOT NULL,"
                                        "chapterTitle varchar(50),"
                                        "itemID integer NOT NULL,"
                                        "FOREIGN KEY (itemID) references PurchasableItem(itemID) on delete cascade,"
                                        "FOREIGN KEY (ISBN) references Textbook(ISBN) on delete cascade, "
                                        "PRIMARY KEY (ISBN, chapterNumber)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

    // creating the Table called Section
    noError = noError && query.exec("create table Section("
                                        "ISBN varchar(20),"
                                        "chapterNumber integer,"
                                        "sectionNumber integer NOT NULL,"
                                        "sectionTitle varchar(50),"
                                        "itemID integer NOT NULL,"
                                        "FOREIGN KEY (itemID) references PurchasableItem(itemID) on delete cascade,"
                                        "FOREIGN KEY (ISBN, chapterNumber) references Chapter(ISBN, chapterNumber) on delete cascade,"
                                        "PRIMARY KEY (ISBN, chapterNumber, sectionNumber)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

    // creating the Table called PurchasableItem
    noError = noError && query.exec("create table PurchasableItem("
                                        "itemID integer NOT NULL,"
                                        "price decimal(18,2),"
                                        "availability boolean,"
                                        "PRIMARY KEY (itemID)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

    // creating the Table called Course_Assigned_Textbook
    noError = noError && query.exec("create table Course_Assigned_Textbook("
                                        "ISBN varchar(20) NOT NULL,"
                                        "courseCode varchar(8) NOT NULL,"
                                        "section varchar(1) NOT NULL,"
                                        "termID integer NOT NULL,"
                                        "FOREIGN KEY (ISBN) references Textbook(ISBN) on delete cascade,"
                                        "FOREIGN KEY (courseCode, section, termID) references Course(courseCode, section, termID) on delete cascade,"
                                        "PRIMARY KEY (ISBN, courseCode, section, termID)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

    // creating the Table called ShoppingCart
    noError = noError && query.exec("create table ShoppingCart("
                                        "studentNumber varchar(10) NOT NULL,"
                                        "itemID integer NOT NULL,"
                                        "quantity integer,"
                                        "FOREIGN KEY (studentNumber) references Student(studentNumber) on delete cascade,"
                                        "FOREIGN KEY (itemID) references PurchasableItem(itemID) on delete cascade,"
                                        "PRIMARY KEY (studentNumber, itemID)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

    // creating the Table called Orders
    noError = noError && query.exec("create table Orders("
                                        "orderID integer NOT NULL,"
                                        "studentNumber varchar(10) NOT NULL,"
                                        "itemID integer NOT NULL,"
                                        "FOREIGN KEY (studentNumber) references Student(studentNumber) on delete cascade,"
                                        "FOREIGN KEY (itemID) references PurchasableItem(itemID) on delete cascade,"
                                        "PRIMARY KEY (orderID)"
                                    ");");                                                                      //qDebug() << query.lastQuery() << query.lastError();

    //commit transaction
    noError = noError && query.exec("commit;");                                                                 //qDebug() << query.lastQuery() << query.lastError();

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
 * @brief QueryControl::updateCourse
 *  creates a new Course or replace/update a existing Course in DB
 *  Note:
 *  1) If you want to update existing course primary ID
 *     i.e Course::courseCode, Course::courseSection, termID
 *     must remain not change otherwize operation will create a new Course
 *  2) to add a student use QueryControl::updateCourseStudentLink()
 *  3) to add a textbook use QueryControl::updateCourseTextbookLink()
 * @param course
 *  Course object to create or replace/update to DB
 * @param termID
 *  termID to create or replace/update the Course under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updateCourse(Course *course, qint32 termID) {
    // create or update/replace a Course
    QSqlQuery courseQuery;

    courseQuery.prepare("REPLACE INTO Course (courseCode,section,instructor,termID) "
                            "VALUES (:courseCode,:section,:instructor,:termID);");
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
 *  1) If you want to delete existing Course primary ID
 *     i.e Course::courseCode, Course::courseSection, termID
 *     must remain not change otherwize operation will not delete the Course
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
    // delete a Course
    QSqlQuery courseQuery;

    courseQuery.prepare("DELETE FROM Course WHERE "
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
 * @brief QueryControl::updateTextbook
 *  creates a new Textbook or replace/update a existing Textbook in DB
 *  Note:
 *  1) If you want to update existing Textbook primary ID
 *     i.e Textbook::isbn, Textbook::itemID
 *     must remain not change otherwize operation create a new Textbook
 *  2) to create or replace/update a Chapter use QueryControl::updateChapter()
 *  3) uses QueryControl::updatePurchasableItem()
 * @param textbook
 *  Textbook object to create or replace/update to DB
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updateTextbook(Textbook *textbook){
    bool noError = true;

    // create or replace/update the PurchasableItem component first
    noError = noError && updatePurchasableItem((PurchasableItem*)textbook);

    // create or replace/update a Textbook
    QSqlQuery textBookQuery;

    textBookQuery.prepare("REPLACE INTO Textbook (ISBN,coverImageLocation,Desc,Author,TextbookTitle,Publisher,Edition,itemID) "
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

    return noError;
}

/**
 * @brief QueryControl::deleteTextbook
 *  delete a existing Textbook in DB
 *  Note:
 *  1) If you want to delete existing Textbook primary ID
 *     i.e Textbook::isbn, Textbook::itemID
 *     must remain not change otherwize operation will not delete the Textbook
 *  2) to delete a chapter use QueryControl::deleteChapter()
 *  3) uses QueryControl::deletePurchasableItem()
 * @param textbook
 *  Textbook object to delete in DB
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::deleteTextbook(Textbook *textbook){
    bool noError = true;

    // delete a Textbook
    QSqlQuery textBookQuery;

    textBookQuery.prepare("DELETE FROM Textbook WHERE "
                            "ISBN = :ISBN;");
    textBookQuery.bindValue(":ISBN", textbook->getISBN());

    noError = noError && textBookQuery.exec();

    //delete the PurchasableItem component last
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
 * @param getavailabilityOnly
 *  if true then get only avaliable item
 *  else get all items
 * @return
 *  returns a Textbook
 */
Textbook* QueryControl::retrieveTextbook(QString isbn, bool getavailabilityOnly){
    Textbook *textbook = NULL;

    QSqlQuery textBookQuery;
    if(!getavailabilityOnly) {
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
    }
    else {
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
                                    "AND PurchasableItem.availability=1 "
                                    "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC;");
    }
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
 * @param getavailabilityOnly
 *  if true then get only avaliable item
 *  else get all items
 * @return
 *  returns a list of Textbooks
 */
QList<Textbook*>* QueryControl::retrieveTextbookList(Course *course,  qint32 termID, bool getavailabilityOnly){
    QList<Textbook*> *textbooks = new QList<Textbook*>();

    QSqlQuery textBookQuery;
    if(!getavailabilityOnly) {
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
                                "WHERE Course.courseCode=:courseCode AND "
                                    "Course.section=:section AND "
                                    "Course.termID=:termID "
                                    "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC;");
    }
    else{
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
                               "WHERE Course.courseCode=:courseCode AND "
                                   "Course.section=:section AND "
                                   "Course.termID=:termID "
                                   "AND PurchasableItem.availability=1 "
                                   "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC;");
    }
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
 * @brief QueryControl::retrieveAllTextbookList
 *  retrives a existing list of all Textbooks
 * @return
 *  returns a list of Textbooks
 */
QList<Textbook*>* QueryControl::retrieveAllTextbookList(){
    QList<Textbook*> *textbooks = new QList<Textbook*>();

    QSqlQuery textBookQuery;

    textBookQuery.exec("SELECT Textbook.textBookTitle, "
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
                             "Textbook.itemID = PurchasableItem.ItemID;");

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
 * @brief QueryControl::updateChapter
 *  creates a new Chapter or replace/update a existing Chapter in DB
 *  Note:
 *  1) If you want to update existing Chapter primary ID
 *     i.e Textbook::isbn, Chapter::itemID, Chapter::chapterNumber
 *     must remain not change otherwize operation create a new Chapter
 *  2) to create or replace/update a Section use QueryControl::updateSection()
 *  3) uses QueryControl::updatePurchasableItem()
 * @param chapter
 *  Chapter object to create or replace/update to DB
 * @param isbn
 *  isbn (primary key of Textbook) to create or replace/update the Chapter under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updateChapter(Chapter *chapter, QString isbn){
    bool noError = true;

    // create or replace/update the PurchasableItem component first
    noError = noError && updatePurchasableItem((PurchasableItem*)chapter);

    // create or replace/update a Chapter
    QSqlQuery chapterQuery;

    chapterQuery.prepare("REPLACE INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID) "
                            "VALUES (:ISBN,:chapterNumber,:chapterTitle,:itemID);");
    chapterQuery.bindValue(":ISBN", isbn);
    chapterQuery.bindValue(":chapterNumber", chapter->getChapterNumber());
    chapterQuery.bindValue(":chapterTitle", chapter->getItemTitle());
    chapterQuery.bindValue(":itemID", chapter->getItemID());

    noError = noError && chapterQuery.exec();

    return noError;
}

/**
 * @brief QueryControl::deleteChapter
 *  Delete a existing Chapter in DB
 *  Note:
 *  1) If you want to delete existing Chapter primary ID
 *     i.e Textbook::isbn, Chapter::itemID, Chapter::chapterNumber
 *     must remain not change otherwize operation will not delete the Chapter
 *  2) to delete a chapter use QueryControl::deleteSection()
 *  3) uses QueryControl::deletePurchasableItem()
 * @param chapter
 *  Chapter object to delete in DB
 * @param isbn
 *  isbn (primary key of Textbook) to delete the Chapter under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::deleteChapter(Chapter *chapter, QString isbn){
    bool noError = true;

    // delete a Chapter
    QSqlQuery chapterQuery;

    chapterQuery.prepare("DELETE FROM Chapter WHERE "
                             "ISBN = :ISBN AND "
                             "chapterNumber = :chapterNumber;");
    chapterQuery.bindValue(":ISBN", isbn);
    chapterQuery.bindValue(":chapterNumber", chapter->getChapterNumber());

    noError = noError && chapterQuery.exec();

    //delete the PurchasableItem component last
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
 * @param getavailabilityOnly
 *  if true then get only avaliable item
 *  else get all items
 * @return
 *  returns a Chapter
 */
Chapter* QueryControl::retrieveChapter(qint32 chapterNumber, QString isbn, bool getavailabilityOnly){
    Chapter *chapter = NULL;

    QSqlQuery chapterQuery;
    if(!getavailabilityOnly) {
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
    }
    else {
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
                                   "AND PurchasableItem.availability=1 "
                                   "ORDER BY Chapter.chapterNumber ASC;");
    }
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
 * @param getavailabilityOnly
 *  if true then get only avaliable item
 *  else get all items
 * @return
 *  returns a list of Chapters
 */
QList<Chapter*>* QueryControl::retrieveChapterList(QString isbn, bool getavailabilityOnly){
    QList<Chapter*> *chapters = new QList<Chapter*>();

    QSqlQuery chapterQuery;
    if(!getavailabilityOnly) {
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
    }
    else {
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
                                   "AND PurchasableItem.availability=1 "
                                   "ORDER BY Chapter.chapterNumber ASC;");
    }
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
 * @brief QueryControl::updateSection
 *  creates a new Section or replace/update a existing Section in DB
 *  Note:
 *  1) If you want to update existing Section primary ID
 *     i.e Textbook::isbn, Section::itemID, Chapter::chapterNumber, Section::sectionNumber
 *     must remain not change otherwize operation create a new Section
 *  2) uses QueryControl::updatePurchasableItem()
 * @param section
 *  Section object to create or replace/update to DB
 * @param chapterNumber
 *  chapterNumber (primary key of chapter) to create or replace/update the section under
 * @param isbn
 *  isbn (primary key of Textbook) to create or replace/update the section under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updateSection(Section *section, qint32 chapterNumber, QString isbn){
    bool noError = true;

    // create or replace/update the PurchasableItem component first
    noError = noError && updatePurchasableItem((PurchasableItem*)section);

    // create or replace/update a Section
    QSqlQuery sectionQuery;

    sectionQuery.prepare("REPLACE INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID) "
                            "VALUES (:ISBN,:chapterNumber,:sectionNumber,:sectionTitle,:itemID);");
    sectionQuery.bindValue(":ISBN", isbn);
    sectionQuery.bindValue(":chapterNumber", chapterNumber);
    sectionQuery.bindValue(":sectionNumber", section->getSectionNumber());
    sectionQuery.bindValue(":sectionTitle", section->getItemTitle());
    sectionQuery.bindValue(":itemID", section->getItemID());

    noError = noError && sectionQuery.exec();

    return noError;

}

/**
 * @brief QueryControl::deleteSection
 *  Delete a existing Section in DB
 *  Note:
 *  1) If you want to delete existing Section primary ID
 *     i.e Textbook::isbn, Section::itemID, Chapter::chapterNumber, Section::sectionNumber
 *     must remain not change otherwize operation will not delete the Section
 *  2) uses QueryControl::deletePurchasableItem()
 * @param section
 *  Section object to delete in DB
 * @param chapterNumber
 *  chapterNumber (primary key of chapter) to delete the section under
 * @param isbn
 *  isbn (primary key of Textbook) to delete the section under
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::deleteSection(Section *section, qint32 chapterNumber, QString isbn){
    bool noError = true;

    // delete a Section
    QSqlQuery sectionQuery;

    sectionQuery.prepare("DELETE FROM Section WHERE "
                             "ISBN = :ISBN AND "
                             "chapterNumber = :chapterNumber AND "
                             "sectionNumber = :sectionNumber;");
    sectionQuery.bindValue(":ISBN", isbn);
    sectionQuery.bindValue(":chapterNumber", chapterNumber);
    sectionQuery.bindValue(":sectionNumber", section->getSectionNumber());

    noError = noError && sectionQuery.exec();

    //delete the PurchasableItem component last
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
 * @param getavailabilityOnly
 *  if true then get only avaliable item
 *  else get all items
 * @return
 *  returns a Section
 */
Section* QueryControl::retrieveSection(qint32 sectionNumber, qint32 chapterNumber, QString isbn, bool getavailabilityOnly){
    Section *section = NULL;

    QSqlQuery sectionQuery;
    if(!getavailabilityOnly) {
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
    }
    else {
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
                                    "AND PurchasableItem.availability=1 "
                                    "ORDER BY Section.sectionNumber ASC;");
    }
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
 * @param getavailabilityOnly
 *  if true then get only avaliable item
 *  else get all items
 * @return
 *  returns a list of Section
 */
QList<Section*>* QueryControl::retrieveSectionList(qint32 chapterNumber, QString isbn, bool getavailabilityOnly){
    QList<Section*> *sections = new QList<Section*>();

    QSqlQuery sectionQuery;
    if(!getavailabilityOnly) {
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
                                    "Chapter.chapterNumber=:chapterNumber "
                                    "ORDER BY Section.sectionNumber ASC;");
    }
    else {
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
                                    "Chapter.chapterNumber=:chapterNumber "
                                    "AND PurchasableItem.availability=1 "
                                    "ORDER BY Section.sectionNumber ASC;");
    }
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

    linkQuery.prepare("REPLACE INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID) "
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

    linkQuery.prepare("REPLACE INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID) "
                            "VALUES (:studentNumber,:courseCode,:section,:termID);");
    linkQuery.bindValue(":studentNumber", student->getStudentNum());
    linkQuery.bindValue(":courseCode", course->getCourseCode());
    linkQuery.bindValue(":section", course->getCourseSection());
    linkQuery.bindValue(":termID", termID);

    return linkQuery.exec();
}

/**
 * @brief QueryControl::updatePaymentInformation
 *  creates a new PaymentInformation or replace/update
 *  a existing PaymentInformation in DB for a student
 *  Note:
 *  1) Student primary ID Student::studentNum
 *     must remain not change otherwize operation will not
 *     create a new PaymentInformation or replace/update
 *     a existing PaymentInformation in DB for a student
 * @param student
 *  Student to create or replace/update PaymentInformation under
 * @param info
 *  PaymentInformation object to create or replace/update to DB
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updatePaymentInformation(Student *student, PaymentInformation *info) {

    // edit payment information
    QSqlQuery PaymentInformationQuery;

    PaymentInformationQuery.prepare("REPLACE INTO PaymentInformation (creditCardNumber, cardType, cvv, expirationDate, nameOnCard, postalCode, province, city, streetName, houseNumber, studentNumber) "
                                        "VALUES(:creditCardNumber, :cardType, :cvv, :expirationDate, :nameOnCard, :postalCode, :province, :city, :streetName, :houseNumber, :studentNumber);");
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

    // update name of user as the name on its payment information changed
    QSqlQuery nameQuery;
    nameQuery.prepare("UPDATE User SET "
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

/**
 * @brief QueryControl::retrievePaymentInformation
 *  retrieve payment information for a student
 * @param student
 *  Student to save retrieve payment information under
 * @return
 *  Returns PaymentInformation
 */
PaymentInformation* QueryControl::retrievePaymentInformation(Student *student) {
    PaymentInformation *info = NULL;

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
    Student *student = NULL;

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
                                "Student.studentNumber = Student_RegisteredIn_Course.studentNumber "
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
 * @brief QueryControl::updatePurchasableItem
 *  creates a new PurchasableItem or replace/update a existing PurchasableItem in DB
 *  Note:
 *  1) If you want to update existing PurchasableItem primary ID
 *     i.e PurchasableItem::itemID
 *     must remain not change otherwize operation create a new PurchasableItem
 * @param purchasableItem
 *  PurchasableItem object to create or replace/update to DB
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::updatePurchasableItem(PurchasableItem* purchasableItem) {
    bool noError = true;

    // itemID <= -1 mean item is new to generate id
    if(purchasableItem->getItemID() <= -1) {
        //get the current max item id
        int nextItemID = -1;
        QSqlQuery maxItemID("SELECT MAX(itemID)+1 AS nextItemID FROM PurchasableItem;");
        noError = noError && maxItemID.exec();
        if(maxItemID.first()){
            nextItemID = maxItemID.value(maxItemID.record().indexOf("nextItemID")).toInt();
        }
        purchasableItem->setItemID(nextItemID);
    }

    // create or replace/update PurchasableItem
    QSqlQuery purchasableItemQuery;

    purchasableItemQuery.prepare("REPLACE INTO PurchasableItem (itemID,price,availability) "
                      "VALUES (:itemID,:price,:availability);");
    purchasableItemQuery.bindValue(":itemID", purchasableItem->getItemID());
    purchasableItemQuery.bindValue(":price", purchasableItem->getPrice());
    purchasableItemQuery.bindValue(":availability", purchasableItem->isAvailable());

    noError = noError && purchasableItemQuery.exec();

    return noError;
}

/**
 * @brief QueryControl::deletePurchasableItem
 *  Delete a existing PurchasableItem in DB
 *  Note:
 *  1) If you want to delete existing PurchasableItem primary ID
 *     i.e PurchasableItem::itemID
 *     must remain not change otherwize operation will not delete the PurchasableItem
 * @param purchasableItem
 *  PurchasableItem object to delete in DB
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::deletePurchasableItem(PurchasableItem* purchasableItem) {
    bool noError = true;

    // delete PurchasableItem
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
 * @param student
 *  Student to get the shopping cart for
 * @param getavailabilityOnly
 *  if true then get only avaliable item
 *  else get all items
 * @return
 *  returns a list of pairs(PurchasableItem, quantity of that PurchasableItem)
 */
QList< QPair<PurchasableItem*,qint32> >* QueryControl::retrieveShoppingCartItemList(Student *student, bool getavailabilityOnly) {
    QList< QPair<PurchasableItem*,qint32> > *purchasableItems = new QList< QPair<PurchasableItem*,qint32> >();

    QSqlQuery textBookQuery;
    QSqlQuery chapterQuery;
    QSqlQuery sectionQuery;

    if(!getavailabilityOnly) {
        // get all textbooks in shopping cart
        textBookQuery.prepare("SELECT Textbook.textBookTitle, "
                                    "Textbook.author, "
                                    "Textbook.edition, "
                                    "Textbook.publisher, "
                                    "Textbook.ISBN, "
                                    "Textbook.desc, "
                                    "Textbook.coverImageLocation, "
                                    "Textbook.itemID, "
                                    "PurchasableItem.price, "
                                    "PurchasableItem.availability, "
                                    "ShoppingCart.quantity "
                                "FROM Textbook "
                                "JOIN PurchasableItem ON "
                                   "Textbook.itemID = PurchasableItem.ItemID "
                                "JOIN ShoppingCart ON "
                                    "PurchasableItem.ItemID = ShoppingCart.ItemID "
                                "JOIN Student ON "
                                    "ShoppingCart.studentNumber = Student.studentNumber "
                                "WHERE Student.studentNumber=:studentNumber "
                                    "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC;");

        // get all chapters in shopping cart
        chapterQuery.prepare("SELECT Chapter.chapterTitle, "
                                   "Chapter.chapterNumber, "
                                   "Chapter.itemID, "
                                   "PurchasableItem.price, "
                                   "PurchasableItem.availability, "
                                   "ShoppingCart.quantity "
                               "FROM Chapter "
                               "JOIN PurchasableItem ON "
                                   "Chapter.itemID = PurchasableItem.ItemID "
                               "JOIN ShoppingCart ON "
                                   "PurchasableItem.ItemID = ShoppingCart.ItemID "
                               "JOIN Student ON "
                                   "ShoppingCart.studentNumber = Student.studentNumber "
                               "WHERE Student.studentNumber=:studentNumber "
                                   "ORDER BY Chapter.chapterNumber ASC;");

        // get all sections in shopping cart
        sectionQuery.prepare("SELECT section.sectionTitle, "
                                    "section.sectionNumber, "
                                    "section.itemID, "
                                    "PurchasableItem.price, "
                                    "PurchasableItem.availability, "
                                    "ShoppingCart.quantity "
                                "FROM Section "
                                "JOIN PurchasableItem ON "
                                    "Section.itemID = PurchasableItem.ItemID "
                                "JOIN ShoppingCart ON "
                                    "PurchasableItem.ItemID = ShoppingCart.ItemID "
                                "JOIN Student ON "
                                    "ShoppingCart.studentNumber = Student.studentNumber "
                                "WHERE Student.studentNumber=:studentNumber "
                                    "ORDER BY Section.sectionNumber ASC;");
    }
    else {
        // get all textbooks in shopping cart
        textBookQuery.prepare("SELECT Textbook.textBookTitle, "
                                    "Textbook.author, "
                                    "Textbook.edition, "
                                    "Textbook.publisher, "
                                    "Textbook.ISBN, "
                                    "Textbook.desc, "
                                    "Textbook.coverImageLocation, "
                                    "Textbook.itemID, "
                                    "PurchasableItem.price, "
                                    "PurchasableItem.availability, "
                                    "ShoppingCart.quantity "
                                "FROM Textbook "
                                "JOIN PurchasableItem ON "
                                   "Textbook.itemID = PurchasableItem.ItemID "
                                "JOIN ShoppingCart ON "
                                    "PurchasableItem.ItemID = ShoppingCart.ItemID "
                                "JOIN Student ON "
                                    "ShoppingCart.studentNumber = Student.studentNumber "
                                "WHERE Student.studentNumber=:studentNumber "
                                    "AND PurchasableItem.availability=1 "
                                    "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC;");
        textBookQuery.bindValue(":studentNumber", student->getStudentNum());

        // get all chapters in shopping cart
        chapterQuery.prepare("SELECT Chapter.chapterTitle, "
                                   "Chapter.chapterNumber, "
                                   "Chapter.itemID, "
                                   "PurchasableItem.price, "
                                   "PurchasableItem.availability, "
                                   "ShoppingCart.quantity "
                               "FROM Chapter "
                               "JOIN PurchasableItem ON "
                                   "Chapter.itemID = PurchasableItem.ItemID "
                               "JOIN ShoppingCart ON "
                                   "PurchasableItem.ItemID = ShoppingCart.ItemID "
                               "JOIN Student ON "
                                   "ShoppingCart.studentNumber = Student.studentNumber "
                               "WHERE Student.studentNumber=:studentNumber "
                                   "AND PurchasableItem.availability=1 "
                                   "ORDER BY Chapter.chapterNumber ASC;");
        chapterQuery.bindValue(":studentNumber", student->getStudentNum());

        // get all sections in shopping cart
        sectionQuery.prepare("SELECT section.sectionTitle, "
                                    "section.sectionNumber, "
                                    "section.itemID, "
                                    "PurchasableItem.price, "
                                    "PurchasableItem.availability, "
                                    "ShoppingCart.quantity "
                                "FROM Section "
                                "JOIN PurchasableItem ON "
                                    "Section.itemID = PurchasableItem.ItemID "
                                "JOIN ShoppingCart ON "
                                    "PurchasableItem.ItemID = ShoppingCart.ItemID "
                                "JOIN Student ON "
                                    "ShoppingCart.studentNumber = Student.studentNumber "
                                "WHERE Student.studentNumber=:studentNumber "
                                    "AND PurchasableItem.availability=1 "
                                    "ORDER BY Section.sectionNumber ASC;");
        sectionQuery.bindValue(":studentNumber", student->getStudentNum());
    }

    textBookQuery.bindValue(":studentNumber", student->getStudentNum());
    chapterQuery.bindValue(":studentNumber", student->getStudentNum());
    sectionQuery.bindValue(":studentNumber", student->getStudentNum());

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

         purchasableItems->push_back(QPair<PurchasableItem*,qint32>(textbook, textBookQuery.value(textBookQuery.record().indexOf("quantity")).toInt()));
    }

    chapterQuery.exec();
    while (chapterQuery.next()){
       purchasableItems->push_back(QPair<PurchasableItem*,qint32>(new Chapter(chapterQuery.value(chapterQuery.record().indexOf("chapterTitle")).toString(),
                                                                              chapterQuery.value(chapterQuery.record().indexOf("chapterNumber")).toInt(),
                                                                              chapterQuery.value(chapterQuery.record().indexOf("itemID")).toInt(),
                                                                              chapterQuery.value(chapterQuery.record().indexOf("price")).toDouble(),
                                                                              chapterQuery.value(chapterQuery.record().indexOf("availability")).toBool()),
       chapterQuery.value(chapterQuery.record().indexOf("quantity")).toInt()));
    }

    sectionQuery.exec();
    while (sectionQuery.next()){
       purchasableItems->push_back(QPair<PurchasableItem*,qint32>(new Section(sectionQuery.value(sectionQuery.record().indexOf("sectionTitle")).toString(),
                                                                              sectionQuery.value(sectionQuery.record().indexOf("sectionNumber")).toInt(),
                                                                              sectionQuery.value(sectionQuery.record().indexOf("itemID")).toInt(),
                                                                              sectionQuery.value(sectionQuery.record().indexOf("price")).toDouble(),
                                                                              sectionQuery.value(sectionQuery.record().indexOf("availability")).toBool()),
       sectionQuery.value(sectionQuery.record().indexOf("quantity")).toInt()));
    }

    return purchasableItems;
}

/**
 * @brief QueryControl::getPurchasableItemList
 *  get all PurchasableItem in the DB
 * @param getavailabilityOnly
 *  if true then get only avaliable item
 *  else get all items
 * @return
 *  returns a list of PurchasableItem
 */
QList<PurchasableItem*>* QueryControl::retrieveAllPurchasableItemList(bool getavailabilityOnly){
     QList<PurchasableItem*> *purchasableItems = new QList<PurchasableItem*>();

    QSqlQuery textBookQuery;
    QSqlQuery chapterQuery;
    QSqlQuery sectionQuery;

    if(!getavailabilityOnly) {
        // get all textbooks
        textBookQuery.exec("SELECT Textbook.textBookTitle, "
                                    "Textbook.author, "
                                    "Textbook.edition, "
                                    "Textbook.publisher, "
                                    "Textbook.ISBN, "
                                    "Textbook.desc, "
                                    "Textbook.coverImageLocation, "
                                    "Textbook.itemID, "
                                    "PurchasableItem.price, "
                                    "PurchasableItem.availability "
                                "FROM Textbook "
                                "JOIN PurchasableItem ON "
                                   "Textbook.itemID = PurchasableItem.ItemID "
                                   "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC;");

        // get all chapters
        chapterQuery.exec("SELECT Chapter.chapterTitle, "
                                   "Chapter.chapterNumber, "
                                   "Chapter.itemID, "
                                   "PurchasableItem.price, "
                                   "PurchasableItem.availability "
                               "FROM Chapter "
                               "JOIN PurchasableItem ON "
                                   "Chapter.itemID = PurchasableItem.ItemID "
                                   "ORDER BY Chapter.chapterNumber ASC;");

        // get all sections
        sectionQuery.exec("SELECT section.sectionTitle, "
                                    "section.sectionNumber, "
                                    "section.itemID, "
                                    "PurchasableItem.price, "
                                    "PurchasableItem.availability "
                                "FROM Section "
                                "JOIN PurchasableItem ON "
                                    "Section.itemID = PurchasableItem.ItemID "
                                    "ORDER BY Section.sectionNumber ASC;");
    }
    else {
        // get all textbooks
        textBookQuery.exec("SELECT Textbook.textBookTitle, "
                                    "Textbook.author, "
                                    "Textbook.edition, "
                                    "Textbook.publisher, "
                                    "Textbook.ISBN, "
                                    "Textbook.desc, "
                                    "Textbook.coverImageLocation, "
                                    "Textbook.itemID, "
                                    "PurchasableItem.price, "
                                    "PurchasableItem.availability "
                                "FROM Textbook "
                                "JOIN PurchasableItem ON "
                                   "Textbook.itemID = PurchasableItem.ItemID "
                                "WHERE PurchasableItem.availability=1 "
                                   "ORDER BY Textbook.textBookTitle ASC, Textbook.ISBN ASC;");

        // get all chapters
        chapterQuery.exec("SELECT Chapter.chapterTitle, "
                                   "Chapter.chapterNumber, "
                                   "Chapter.itemID, "
                                   "PurchasableItem.price, "
                                   "PurchasableItem.availability "
                               "FROM Chapter "
                               "JOIN PurchasableItem ON "
                                   "Chapter.itemID = PurchasableItem.ItemID "
                               "WHERE PurchasableItem.availability=1 "
                                   "ORDER BY Chapter.chapterNumber ASC;");

        // get all sections
        sectionQuery.exec("SELECT section.sectionTitle, "
                                    "section.sectionNumber, "
                                    "section.itemID, "
                                    "PurchasableItem.price, "
                                    "PurchasableItem.availability "
                                "FROM Section "
                                "JOIN PurchasableItem ON "
                                    "Section.itemID = PurchasableItem.ItemID "
                                "WHERE PurchasableItem.availability=1 "
                                    "ORDER BY Section.sectionNumber ASC;");
    }

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


    while (chapterQuery.next()){
         purchasableItems->push_back(new Chapter(chapterQuery.value(chapterQuery.record().indexOf("chapterTitle")).toString(),
                                                                    chapterQuery.value(chapterQuery.record().indexOf("chapterNumber")).toInt(),
                                                                    chapterQuery.value(chapterQuery.record().indexOf("itemID")).toInt(),
                                                                    chapterQuery.value(chapterQuery.record().indexOf("price")).toDouble(),
                                                                    chapterQuery.value(chapterQuery.record().indexOf("availability")).toBool()));
    }

    while (sectionQuery.next()){
         purchasableItems->push_back(new Section(sectionQuery.value(sectionQuery.record().indexOf("sectionTitle")).toString(),
                                                                    sectionQuery.value(sectionQuery.record().indexOf("sectionNumber")).toInt(),
                                                                    sectionQuery.value(sectionQuery.record().indexOf("itemID")).toInt(),
                                                                    sectionQuery.value(sectionQuery.record().indexOf("price")).toDouble(),
                                                                    sectionQuery.value(sectionQuery.record().indexOf("availability")).toBool()));
    }

    qDebug() << textBookQuery.lastQuery() << textBookQuery.lastError();
    qDebug() << chapterQuery.lastQuery() << chapterQuery.lastError();
    qDebug() << sectionQuery.lastQuery() << sectionQuery.lastError();
    return purchasableItems;
}

/**
 * @brief QueryControl::emptyShoppingCart
 *  delete all items form shopping cart for a given student
 * @param student
 *  student who the shopping cart belongs to
 * @return
 *  Returns if operation was a success
 */
bool QueryControl::emptyShoppingCart(Student *student){

    bool noError = true;

    // delete shopping cart
    QSqlQuery shoppingCartQuery;

    shoppingCartQuery.prepare("DELETE FROM ShoppingCart WHERE "
                            "studentNumber = :studentNumber;");
    shoppingCartQuery.bindValue(":studentNumber", student->getStudentNum());

    noError = noError && shoppingCartQuery.exec();

    return noError;
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

    noError = noError && purchasableItemQuery.exec();

    return noError;
}
