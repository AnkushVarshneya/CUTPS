#include "QueryControl.h"

QueryControl::QueryControl(){
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../cuTPS.db");
    if(!db.open())
        qDebug() << "FAILED TO CONNECT TO DATA BASE";
    else {
        qDebug() << "CONNECT TO DATA BASE";
    }
}

QueryControl::~QueryControl(){
    qDebug()<< "IN QUERY CONTROL DESTRUCTOR";
    db.commit();
    db.removeDatabase("QSQLITE");
    db.close();
    qDebug() << db.databaseName();
}

PaymentInformation* QueryControl::getExistingBillingInfo(QString studentNumber) const{
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
        return NULL;
    }

    return info;
}


//Query for studentViewTextbooks use case where argument passed in is a student number
//and a termID. Returns a list of courses that the student is registered in
QList<Course*>& QueryControl::studentViewTextbooks(QString studentNumber, qint32 termID) const{
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

bool QueryControl::saveBillingInformation(const QString studentNumber, PaymentInformation *info){

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

bool QueryControl::createCourse(Course *course, qint32 termID){
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

bool QueryControl::createTextbook(Textbook *textbook){
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

QList<Textbook*>& QueryControl::viewAllTextbooks(qint32 termID){
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

QList<Course*>& QueryControl::viewCourses(qint32 termID) {
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
