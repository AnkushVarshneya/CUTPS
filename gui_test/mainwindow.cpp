#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    networkSession(0),
    tcpConnection(new QTcpSocket(this)) //does this work
{
    control = new cuTPSTestAPIControl();
    ui->setupUi(this);
   // this->connectTcp();
}

cuTPSTestAPIControl* MainWindow::getControl(){
    return control;
}

//void MainWindow::connectTcp() {
//   // this->tcpConnection = new QTcpSocket(this);
//    const QString & testaddress = "0.0.0.0";
//    QHostAddress address = QHostAddress(testaddress);
//    this->tcpConnection->connectToHost(address, 1234);
//    this->tcpConnection->write(" testing data write to server. \n");
//    this->tcpConnection->write(" testing further data write to server. \n");

//    connect(this->tcpConnection, SIGNAL(readyRead()), this, SLOT(readyRead()));
//}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_pass(QString text){
    ui->textBrowser->setText(ui->textBrowser->toHtml() + text);
}

void MainWindow::update_fail(QString text){
    ui->textBrowser->setText(ui->textBrowser->toHtml() + text);
}


/*************
Execute Button
*************/
void MainWindow::on_pushButton_clicked()
{
    Course c;
    Term t;
    Textbook textbook;

    switch (behaviour){
        case ContentManagerCreateCourse_NullCourse:
            //call control object with test for create course-null course
            if(control->createCourse(NULL))
                update_fail("Failure: Added a NULL Course.");
            else
                update_pass("Success: could not create a NULL Course."); break;

        case ContentManagerCreateCourse_ValidCourse:
            //creating valid course
            t = Term(QDate(2015,01,05),QDate(2015,05,01),2);
            c.setTerm(t);
            if(control->createCourse(&c))
                update_pass("Pass: Course successfully added.");
            else
                update_fail("Failure: Valid Course could not be added."); break;

        case ContentManagerCreateCourse_AlreadyExists:
            //creating duplicate courses
            control->createCourse(&c);

            if(control->createCourse(&c))
                update_fail("Failure: Created a duplicate course.");
            else
                update_pass("Pass: Could not add a duplicate Course"); break;

        case ContentManagerCreateCourse_ExistsDiffTerm:
            //creating a Course with same course code and different Term
            control->createCourse(&c);
            t = Term(QDate(2015,01,05),QDate(2015,05,01),2);
            c.setTerm(t);

            if(control->createCourse(&c))
                update_pass("Pass: Added Course with identical course code and section with different Term.");
            else
                update_fail("Failure: Could not add Course with identical course code and section with different Term."); break;

        case ContentManagerCreateCourse_ExistsDiffSect:
            //creating a Course with same course code and different Term
            control->createCourse(&c);
            c.setCourseSection("B");

            if(control->createCourse(&c))
                update_pass("Pass: Added Course with identical course code and Term with different section.");
            else
                update_fail("Failure: Could not add Course with identical course code and Term with different section."); break;




        case StudentViewTextbooks_unenrolled:
            //viewing the Textbooks of a Student who has no Courses but exists in the database
            if(control->studentViewTextbooks("unenrolledStu", &t).empty())
                update_pass("Pass: Could not view Textbooks of an unenrolled Student.");
            else
                update_fail("Failure: An unenrolled Student should have no Textbooks."); break;

        case StudentViewTextbooks_notextbooks:
            //viewing the Textbooks of a Student who is enrolled but has no Textbooks
            if(control->studentViewTextbooks("noTextbooksStu", &t).empty())
                update_pass("Pass: A Student who is enrolled with no Textbooks should have no Textbooks.");
            else
                update_fail("Failure: A Student who is enrolled with no Textbooks should have no Textbooks."); break;

        case StudentViewTextbooks_hastextbooks:
            //viewing the Textbooks of a Student who has Textbooks
            if(*control->studentViewTextbooks("hasTextbooksStu", &t).front()->getRequiredTextbooks().front() == textbook)
                update_pass("Pass: Viewed the Textbooks of a Student who has Textbooks.");
            else
                update_fail("Failure: Could not view the Textbooks of a Student who has Textbooks."); break;

        case StudentViewTextbooks_studentnotfound:
            //viewing the Textbooks of a Student who is not found in the database
            if(control->studentViewTextbooks("nonexistentStu", &t).empty())
                update_pass("Pass: Expected no Textbooks, got no Textbooks");
            else
                update_fail("Failure: Expected no Textbooks, got Textbooks"); break;

        case StudentViewTextbooks_termnotfound:
            //viewing the Textbooks of a Student when the Term is not found in the database
            t.setTermID(4000);
            if(control->studentViewTextbooks("hasTextbooksStu", &t).empty())
                update_pass("Pass: Expected no Textbooks, got Textbooks.");
            else
                update_fail("Failure: Expected no Textbooks, got Textbooks."); break;



/*
        case ContentManagerLinkTextbook_alreadylinked:
            control->linkTextbook(&textbook,&c);
            if(control->linkTextbook(&textbook,&c))
                update_fail("Failure: Expected link failure, got link success.");
            else
                update_pass("Pass: Expected link failure, got link failure,");
            break;

        case ContentManagerLinkTextbook_nulltextbook:
            if(control->linkTextbook(NULL,&c))
                update_fail("Failure: Expected link failure, got link success.");
            else
                update_pass("Pass: Expected link failure, got link failure.");
            break;

        case ContentManagerLinkTextbook_nullcourse:
            if(control->linkTextbook(&textbook,NULL))
                update_fail("Failure: Expected link failure, got link success.");
            else
                update_pass("Pass: Expected link failure, got link failure.");
            break;
        case ContentManagerLinkTextbook_validlink:
            if(control->linkTextbook(&textbook,&c))
                update_pass("Pass: Expected link success, got link success.");
            else
                update_fail("Failure: Expected link success, got link failure.");
            break;
            */
    }
}



/*************************
Student View Shopping Cart
*************************/

//Shopping Cart contains items
void MainWindow::on_actionStudent_ViewShoppingCart_hasitems_triggered()
{
    ui->textBrowser->setText("View a Shopping Cart that contains items.");
    behaviour = StudentViewShoppingCart_hasitems;
}
//Shopping Cart is empty
void MainWindow::on_actionStudent_ViewShoppingCart_noitems_triggered()
{
    ui->textBrowser->setText("View an empty Shopping Cart.");
    behaviour = StudentViewShoppingCart_noitems;
}



/*********************
Student View Textbooks
*********************/

//Student is not enrolled in any Courses
void MainWindow::on_actionStudent_ViewTextbooks_unenrolled_triggered()
{
    ui->textBrowser->setText("View an unenrolled Student's Textbooks.");
    behaviour = StudentViewTextbooks_unenrolled;
}
//Student has no textbooks
void MainWindow::on_actionStudent_ViewTextbooks_notextbooks_triggered()
{
    ui->textBrowser->setText("View the Textbooks of a Student who has no Textbooks");
    behaviour = StudentViewTextbooks_notextbooks;
}
//Student has textbooks
void MainWindow::on_actionStudent_ViewTextbooks_hastextbooks_triggered()
{
    ui->textBrowser->setText("View a Student's Textbooks when the Student has Textbooks.");
    behaviour = StudentViewTextbooks_hastextbooks;
}
//Student is not found in the database
void MainWindow::on_actionStudent_ViewTextbooks_studentnotfound_triggered()
{
    ui->textBrowser->setText("View a Student's Textbooks when the Student is not found in the database.");
    behaviour = StudentViewTextbooks_studentnotfound;
}
//Term is not found in the database
void MainWindow::on_actionStudent_ViewTextbooks_termnotfound_triggered()
{
    ui->textBrowser->setText("View the Textbooks of a Student in a Term not found in the database.");
    behaviour = StudentViewTextbooks_termnotfound;
}



/****************************
Content Manager Create Course
****************************/

//Course is NULL
void MainWindow::on_actionContentManager_CreateCourse_nullcourse_triggered()
{
    ui->textBrowser->setText("Create a NULL Course");
    behaviour = ContentManagerCreateCourse_NullCourse;
}
//Course is valid
void MainWindow::on_actionContentManager_CreateCourse_validcourse_triggered()
{
    ui->textBrowser->setText("Create a valid Course");
    behaviour = ContentManagerCreateCourse_ValidCourse;
}
//Identical course exists in database
void MainWindow::on_actionContentManager_CreateCourse_coursealreadyexists_triggered()
{
    ui->textBrowser->setText("Create a duplicate Course");
    behaviour = ContentManagerCreateCourse_AlreadyExists;
}
//Course exists in database with a different term
void MainWindow::on_actionContentManager_CreateCourse_existsdiffterm_triggered()
{
    ui->textBrowser->setText("Create two Courses that are identical except they have different Terms.");
    behaviour = ContentManagerCreateCourse_ExistsDiffTerm;
}
//Course exists in database with a different section
void MainWindow::on_actionContentManager_CreateCourse_existsdiffsection_triggered()
{
    ui->textBrowser->setText("Create two Courses that are identical except they have different sections.");
    behaviour = ContentManagerCreateCourse_ExistsDiffSect;
}




/****************************
Content Manager Create Textbook
****************************/

//Textbook is already in the database
void MainWindow::on_actionContentManager_CreateTextbook_textbookexists_triggered()
{
    ui->textBrowser->setText("Create a Textbook that already exists in the database.");
    behaviour = ContentManagerCreateTextbook_textbookexists;
}
//Create a NULL Textbook
void MainWindow::on_actionContentManager_CreateTextbook_nulltextbook_triggered()
{
    ui->textBrowser->setText("Create a NULL Textbook.");
    behaviour = ContentManagerCreateTextbook_nulltextbook;
}
//Create Textbook with Chapters and Sections
void MainWindow::on_actionContentManager_CreateTextbook_withchaptersandsections_triggered()
{
    ui->textBrowser->setText("Create a Textbook with Chapters and Sections.");
    behaviour = ContentManagerCreateTextbook_withchaptersandsections;
}

/****************************
Content Manager Link Textbook
****************************/

//Textbook and Course are already linked together
void MainWindow::on_actionContentManager_LinkTextbook_alreadylinked_triggered()
{
    ui->textBrowser->setText("Link a Textbook and Course that are already linked together.");
    behaviour = ContentManagerLinkTextbook_alreadylinked;
}
//Textbook is NULL
void MainWindow::on_actionContentManager_LinkTextbook_nulltextbook_triggered()
{
    ui->textBrowser->setText("Link a Textbook and Course when the Textbook is NULL.");
    behaviour = ContentManagerLinkTextbook_nulltextbook;
}
//Course is NULL
void MainWindow::on_actionContentManager_LinkTextbook_nullcourse_triggered()
{
    ui->textBrowser->setText("Link a Textbook and Course when the Course is NULL.");
    behaviour = ContentManagerLinkTextbook_nullcourse;
}
//Link is valid
void MainWindow::on_actionContentManager_LinkTextbook_validlink_triggered()
{
    ui->textBrowser->setText("Link a Textbook and Course.");
    behaviour = ContentManagerLinkTextbook_validlink;
}
