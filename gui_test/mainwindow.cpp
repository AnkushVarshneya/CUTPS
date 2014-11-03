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
    switch (behaviour){
        case CreateCourse_NullCourse:
            //call control object with test for create course-null course
            if(control->createCourse(NULL))
                update_fail("Failure: Added a NULL Course.");
            else
                update_pass("Success: could not create a NULL Course."); break;

        case CreateCourse_ValidCourse:
            //creating valid course
            t = Term(QDate(2015,01,05),QDate(2015,05,01),2);
            c.setTerm(t);
            if(control->createCourse(&c))
                update_pass("Pass: Course successfully added.");
            else
                update_fail("Failure: Valid Course could not be added."); break;

        case CreateCourse_AlreadyExists:
            //creating duplicate courses
            control->createCourse(&c);

            if(control->createCourse(&c))
                update_fail("Failure: Created a duplicate course.");
            else
                update_pass("Pass: Could not add a duplicate Course"); break;

        case CreateCourse_ExistsDiffTerm:
            //creating a Course with same course code and different Term
            control->createCourse(&c);
            t = Term(QDate(2015,01,05),QDate(2015,05,01),2);
            c.setTerm(t);

            if(control->createCourse(&c))
                update_pass("Pass: Added Course with identical course code and section with different Term.");
            else
                update_fail("Failure: Could not add Course with identical course code and section with different Term."); break;

        case CreateCourse_ExistsDiffSect:
            //creating a Course with same course code and different Term
            control->createCourse(&c);
            c.setCourseSection("B");

            if(control->createCourse(&c))
                update_pass("Pass: Added Course with identical course code and Term with different section.");
            else
                update_fail("Failure: Could not add Course with identical course code and Term with different section."); break;
    }
}



/*************************
Student View Shopping Cart
*************************/

//Shopping Cart contains items
void MainWindow::on_actionStudent_ViewShoppingCart_hasitems_triggered()
{

}
//Shopping Cart is empty
void MainWindow::on_actionStudent_ViewShoppingCart_noitems_triggered()
{

}



/*********************
Student View Textbooks
*********************/

//Student is not enrolled in any Courses
void MainWindow::on_actionStudent_ViewTextbooks_unenrolled_triggered()
{

}
//Student has no textbooks
void MainWindow::on_actionStudent_ViewTextbooks_notextbooks_triggered()
{

}
//Student has textbooks
void MainWindow::on_actionStudent_ViewTextbooks_hastextbooks_triggered()
{

}
//Student is not found in the database
void MainWindow::on_actionStudent_ViewTextbooks_studentnotfound_triggered()
{

}
//Term is not found in the database
void MainWindow::on_actionStudent_ViewTextbooks_termnotfound_triggered()
{

}



/****************************
Content Manager Create Course
****************************/

//Course is NULL
void MainWindow::on_actionContentManager_CreateCourse_nullcourse_triggered()
{
    ui->textBrowser->setText("Create a NULL Course");
    behaviour = CreateCourse_NullCourse;



}
//Course is valid
void MainWindow::on_actionContentManager_CreateCourse_validcourse_triggered()
{
    ui->textBrowser->setText("Create a valid Course");
    behaviour = CreateCourse_ValidCourse;
}
//Identical course exists in database
void MainWindow::on_actionContentManager_CreateCourse_coursealreadyexists_triggered()
{
    ui->textBrowser->setText("Create a duplicate Course");
    behaviour = CreateCourse_AlreadyExists;
}
//Course exists in database with a different term
void MainWindow::on_actionContentManager_CreateCourse_existsdiffterm_triggered()
{
    ui->textBrowser->setText("Create two Courses that are identical except they have different Terms.");
    behaviour = CreateCourse_ExistsDiffTerm;
}
//Course exists in database with a different section
void MainWindow::on_actionContentManager_CreateCourse_existsdiffsection_triggered()
{
    ui->textBrowser->setText("Create two Courses that are identical except they have different sections.");
    behaviour = CreateCourse_ExistsDiffSect;
}




/****************************
Content Manager Create Textbook
****************************/

void MainWindow::on_actionContentManager_CreateTextbook_textbookexists_triggered()
{

}

void MainWindow::on_actionContentManager_CreateTextbook_nulltextbook_triggered()
{

}


