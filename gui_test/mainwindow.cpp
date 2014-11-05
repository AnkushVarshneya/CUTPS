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
    QList<Course*> courses;

    Term* testterm = new Term(QDate(2014,9,5),QDate(2014,12,9),1);
    testterm->getTermCourses().push_back(new Course());

    Term* testTermEmpty;

    PaymentInformation* payInfo = new PaymentInformation();

    switch (behaviour){
        case StudentViewShoppingCart_hasitems:
            //view a shopping cart with items
            if(!control->viewShoppingCart("100859320").isEmpty())
                ui->textBrowser->setText("Pass: Expected nonempty cart, got nonempty cart.");
            else
                ui->textBrowser->setText("Fail: Expected nonempty cart, got empty cart.");
            break;

        case StudentViewShoppingCart_noitems:
            //view an empty shopping cart
            if(!control->viewShoppingCart("100848920").isEmpty())
                ui->textBrowser->setText("Failure: Expected empty Shopping Cart, got nonempty Shopping Cart.");
            else
                ui->textBrowser->setText("Pass: Expected empty Shopping Cart, got empty Shopping Cart.");
            break;





        case ContentManagerCreateCourse_NullCourse:
            //call control object with test for create course-null course
            if(control->createCourse(NULL, 1))
                ui->textBrowser->setText("Failure: Added a NULL Course.");
            else
                ui->textBrowser->setText("Success: could not create a NULL Course."); break;

        case ContentManagerCreateCourse_ValidCourse:
            //creating valid course

            c = Course("COMP3005","B","Louis Nel");
            if(control->createCourse(&c, 1))
                ui->textBrowser->setText("Pass: Course successfully added.");
            else
                ui->textBrowser->setText("Failure: Valid Course could not be added."); break;

        case ContentManagerCreateCourse_AlreadyExists:
            //creating duplicate courses
            control->createCourse(&c, 1);

            if(control->createCourse(&c, 1))
                ui->textBrowser->setText("Failure: Created a duplicate course.");
            else
                ui->textBrowser->setText("Pass: Could not add a duplicate Course"); break;

        case ContentManagerCreateCourse_ExistsDiffTerm:
            //creating a Course with same course code and different Term
            control->createCourse(&c, 1);
            if(control->createCourse(&c, 2))
                ui->textBrowser->setText("Pass: Added Course with identical course code and section with different Term.");
            else
                ui->textBrowser->setText("Failure: Could not add Course with identical course code and section with different Term."); break;

        case ContentManagerCreateCourse_ExistsDiffSect:
            //creating a Course with same course code and different Term
            control->createCourse(&c, 1);
            c.setCourseSection("B");

            if(control->createCourse(&c, 1))
                ui->textBrowser->setText("Pass: Added Course with identical course code and Term with different section.");
            else
                ui->textBrowser->setText("Failure: Could not add Course with identical course code and Term with different section."); break;




        case StudentViewTextbooks_unenrolled:
            //viewing the Textbooks of a Student who has no Courses but exists in the database
            courses = control->studentViewTextbooks("unenrolledStu", &t);
            if(courses.empty())
                ui->textBrowser->setText("Pass: Could not view Textbooks of an unenrolled Student.");
            else
                ui->textBrowser->setText("Failure: An unenrolled Student should have no Textbooks."); break;

        case StudentViewTextbooks_notextbooks:
            //viewing the Textbooks of a Student who is enrolled but has no Textbooks
            courses = control->studentViewTextbooks("noTextbooksStu", &t);
            if(courses.empty())
                ui->textBrowser->setText("Pass: A Student who is enrolled with no Textbooks should have no Textbooks.");
            else
                ui->textBrowser->setText("Failure: A Student who is enrolled with no Textbooks should have no Textbooks."); break;

        case StudentViewTextbooks_hastextbooks:
            //viewing the Textbooks of a Student who has Textbooks
            courses = control->studentViewTextbooks("100853074", testterm);
            if(!courses.empty()){
                if(courses.front() != 0){
                  if(!courses.front()->getRequiredTextbooks().isEmpty()){
                      if(courses.front()->getRequiredTextbooks().front() != 0){
                          if(courses.front()->getRequiredTextbooks().front()){
                              ui->textBrowser->setText("Pass: Viewed the Textbooks of a Student who has Textbooks.");
                          }
                          else
                              ui->textBrowser->setText("Failure: 1"); break;
                      }
                      else
                          ui->textBrowser->setText("Failure: 2"); break;
                  }
                  else
                      ui->textBrowser->setText("Failure: 3"); break;
                }
                else
                    ui->textBrowser->setText("Failure: 4"); break;
            }
            else
                ui->textBrowser->setText("Failure: Could not view the Textbooks of a Student who has Textbooks."); break;

        case StudentViewTextbooks_studentnotfound:
            //viewing the Textbooks of a Student who is not found in the database
            courses = control->studentViewTextbooks("nonexistentStu", &t);
            if(courses.empty())
                ui->textBrowser->setText("Pass: Expected no Textbooks, got no Textbooks");
            else
                ui->textBrowser->setText("Failure: Expected no Textbooks, got Textbooks"); break;

        case StudentViewTextbooks_termnotfound:
            //viewing the Textbooks of a Student when the Term is not found in the database
            t.setTermID(4000);
            courses = control->studentViewTextbooks("hasTextbooksStu", &t);
            if(courses.empty())
                ui->textBrowser->setText("Pass: Expected no Textbooks, got Textbooks.");
            else
                ui->textBrowser->setText("Failure: Expected no Textbooks, got Textbooks."); break;




        case ContentManagerCreateTextbook_textbookexists:
            control->createTextbook(&textbook);
            if(control->createTextbook(&textbook))
                ui->textBrowser->setText("Failure: Expected failure, got success.");
            else
                ui->textBrowser->setText("Pass: Expected failure, got failure.");
            break;

        case ContentManagerCreateTextbook_nulltextbook:
            if(control->createTextbook(NULL))
                ui->textBrowser->setText("Failure: Expected failure, got success.");
            else
                ui->textBrowser->setText("Success: Expected failure, got failure.");
            break;

        case ContentManagerCreateTextbook_withchaptersandsections:
            if(control->createTextbook(&textbook))
                ui->textBrowser->setText("Pass: Expected success, got success.");
            else
                ui->textBrowser->setText("Pass: Expected success, got failure.");
            break;




        case ContentManagerLinkTextbook_alreadylinked:
            control->linkTextbook(&textbook,&c,1 );
            if(control->linkTextbook(&textbook,&c, 1))
                ui->textBrowser->setText("Failure: Expected link failure, got link success.");
            else
                ui->textBrowser->setText("Pass: Expected link failure, got link failure,");
            break;

        case ContentManagerLinkTextbook_nulltextbook:
            if(control->linkTextbook(NULL,&c, 1))
                ui->textBrowser->setText("Failure: Expected link failure, got link success.");
            else
                ui->textBrowser->setText("Pass: Expected link failure, got link failure.");
            break;

        case ContentManagerLinkTextbook_nullcourse:
            if(control->linkTextbook(&textbook,NULL, 1))
                ui->textBrowser->setText("Failure: Expected link failure, got link success.");
            else
                ui->textBrowser->setText("Pass: Expected link failure, got link failure.");
            break;
        case ContentManagerLinkTextbook_validlink:
            if(control->linkTextbook(&textbook,&c, 1))
                ui->textBrowser->setText("Pass: Expected link success, got link success.");
            else
                ui->textBrowser->setText("Failure: Expected link success, got link failure.");
            break;





        case ContentManagerViewTextbooks_notextbooks:
            if(control->cManagerViewTextbooks(testTermEmpty).empty())
                ui->textBrowser->setText("Pass: Expected no textbooks, got no textbooks.");
            else
                ui->textBrowser->setText("Failure: Expected no textbooks, got textbooks.");
            break;

        case ContentManagerViewTextbooks_hastextbooks:
            if(control->cManagerViewTextbooks(testterm).empty())
                ui->textBrowser->setText("Failure: Expected textbooks, got no textbooks.");
            else
                ui->textBrowser->setText("Pass: Expected no textbooks, got textbooks.");
            break;




        case ContentManagerViewCourses_nocourses:
            if(control->cManagerViewCourses(testTermEmpty).isEmpty())
                ui->textBrowser->setText("Pass: Expected no Courses, got no Courses.");
            else
                ui->textBrowser->setText("Failure: Expected no Courses, got Courses.");
            break;

        case ContentManagerViewCourses_hascourses:
            if(control->cManagerViewCourses(testterm).isEmpty())
                ui->textBrowser->setText("Failure: Expected Courses, got no Courses.");
            else
                ui->textBrowser->setText("Pass: Expected Courses, got Courses.");
            break;




        case StudentGetExistingPaymentInformation_hasinfo:
            if(control->getExistingPaymentInfo("100853074"))
                ui->textBrowser->setText("Pass: Expected Payment Information, got Payment Information.");
            else
                ui->textBrowser->setText("Failure: Expected Payment Information, got no Payment Information.");
            break;

        case StudentGetExistingPaymentInformation_noinfo:
            if(control->getExistingPaymentInfo("123456789"))
                ui->textBrowser->setText("Failure: Expected no Payment Information, got Payment Information.");
            else
                ui->textBrowser->setText("Pass: Expected no Payment Information, got no Payment Information.");
                break;




        case StudentEmptyShoppingCart_hasitems:
            if(control->emptyShoppingCart("100853074"))
                ui->textBrowser->setText("Pass: Emptied Shopping Cart.");
            else
                ui->textBrowser->setText("Failure: Could not empty Shopping Cart.");
            break;

        case StudentEmptyShoppingCart_noitems:
            if(control->emptyShoppingCart("195372839"))
                ui->textBrowser->setText("Pass: Shopping Cart is already empty.");
            else
                ui->textBrowser->setText("Failure: Could not empty Shopping Cart.");
            break;

        case StudentEmptyShoppingCart_studentnotfound:
            if(control->emptyShoppingCart("dneStu"))
                ui->textBrowser->setText("Failure: Emptied Shopping Cart of a Student not found in the database.");
            else
                ui->textBrowser->setText("Pass: Could not empty the Shopping Cart of a Student not found in the database.");
            break;





        case StudentAddContent_textbook:
            if(control->addContent("100853074",1,1))
                ui->textBrowser->setText("Pass: Added a Textbook to the Shopping Cart.");
            else
                ui->textBrowser->setText("Failure: Could not add a Textbook to the Shopping Cart.");
            break;

        case StudentAddContent_chapter:
            if(control->addContent("100853074",2,1))
                ui->textBrowser->setText("Pass: Added a Chapter to the Shopping Cart.");
            else
                ui->textBrowser->setText("Failure: Could not add a Chapter to the Shopping Cart.");
            break;
        case StudentAddContent_section:
            if(control->addContent("100853074",3,1))
                ui->textBrowser->setText("Pass: Added a Section to the Shopping Cart.");
            else
                ui->textBrowser->setText("Failure: Could not add a Section to the Shopping Cart.");
            break;
        case StudentAddContent_multipleitems:
            if(control->addContent("100853074",1,4))
                ui->textBrowser->setText("Pass: Added multiple items to the Shopping Cart.");
            else
                ui->textBrowser->setText("Failure: Could not add multiple items to the Shopping Cart.");
            break;
        case StudentAddContent_invalidnumofitems:
            if(control->addContent("100853074",1,-2))
                ui->textBrowser->setText("Failure: Added invalid number of items to the Shopping Cart.");
            else
                ui->textBrowser->setText("Pass: Could not add invalid number of items to the Shopping Cart.");
            break;
        case StudentAddContent_studentnotfound:
            if(control->addContent("dneStu",1,1))
                ui->textBrowser->setText("Failure: Added content to the Shopping Cart of a Student that is not found in the database.");
            else
                ui->textBrowser->setText("Pass: Could not add content to the Shopping Cart of a Student that is not found in the database.");
            break;
        case StudentAddContent_itemnotfound:
            if(control->addContent("100853074",50,1))
                ui->textBrowser->setText("Failure: Added an item not found in the database.");
            else
                ui->textBrowser->setText("Pass: Could not add an item not found in the database.");
            break;

        case StudentSavePaymentInformation_validformat:
            if(control->savePaymentInfo("123456789",payInfo))
                ui->textBrowser->setText("Pass: Saved valid Payment Information");
            else
                ui->textBrowser->setText("Failure: Could not save valid Payment Information.");
            break;

        case StudentSavePaymentInformation_hasinfo:
            if(control->savePaymentInfo("100853074",payInfo))
                ui->textBrowser->setText("Pass: Saved valid Payment Information");
            else
                ui->textBrowser->setText("Failure: Could not save valid Payment Information.");
            break;

        case StudentSavePaymentInformation_studentnotfound:
            if(control->savePaymentInfo("dneStu",payInfo))
                ui->textBrowser->setText("Failure: Saved Payment Information for a Student not found in the database.");
            else
                ui->textBrowser->setText("Pass: Could not save Payment Information for a Student not found in the database.");
            break;

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




/*****************************
Content Manager View Textbooks
*****************************/

//No Textbooks in database
void MainWindow::on_actionContentManager_ViewTextbooksByTerm_notextbooks_triggered()
{
    ui->textBrowser->setText("View Textbooks in a Term that has no Textbooks.");
    behaviour = ContentManagerViewTextbooks_notextbooks;
}
//Textbooks in database
void MainWindow::on_actionContentManager_ViewTextbooksByTerm_hastextbooks_triggered()
{
    ui->textBrowser->setText("View Textbooks in a Term that has Textbooks.");
    behaviour = ContentManagerViewTextbooks_hastextbooks;
}




/*****************************
Content Manager View Courses
*****************************/

//No Courses in database
void MainWindow::on_actionContentManager_ViewCourses_nocourses_triggered()
{
    ui->textBrowser->setText("View Courses in a Term that has no Courses.");
    behaviour = ContentManagerViewCourses_nocourses;
}
//Courses in database
void MainWindow::on_actionContentManager_ViewCourses_hascourses_triggered()
{
    ui->textBrowser->setText("View Courses in a Term that has Courses.");
    behaviour = ContentManagerViewCourses_hascourses;
}




/*****************************
Student Empty Shopping Cart
*****************************/

//Shopping Cart has items
void MainWindow::on_actionStudent_EmptyShoppingCart_hasitems_triggered()
{
    ui->textBrowser->setText("Empty a Shopping Cart that contains items.");
    behaviour = StudentEmptyShoppingCart_hasitems;
}
//Shopping Cart is empty
void MainWindow::on_actionStudent_EmptyShoppingCart_noitems_triggered()
{
    ui->textBrowser->setText("Empty a Shopping Cart that is already empty.");
    behaviour = StudentEmptyShoppingCart_noitems;
}
//Student is not found in the database
void MainWindow::on_actionStudent_EmptyShoppingCart_studentnotfound_triggered()
{
    ui->textBrowser->setText("Empty a Shopping Cart when the Student is not found in the database.");
    behaviour = StudentEmptyShoppingCart_studentnotfound;
}




/*************************************
Student Add Content (to shopping cart)
**************************************/

//Add a NULL item to the Student's Shopping Cart
void MainWindow::on_actionStudent_AddContent_nullitem_triggered()
{
    ui->textBrowser->setText("Add a NULL item to a Student's Shopping Cart.");
    behaviour = StudentAddContent_nullitem;
}
//Add a Textbook to the Student's Shopping Cart
void MainWindow::on_actionStudent_AddContent_Textbook_triggered()
{
    ui->textBrowser->setText("Add a Textbook to a Student's Shopping Cart.");
    behaviour = StudentAddContent_textbook;
}
//Add a Chapter to the Student's Shopping Cart
void MainWindow::on_actionStudent_AddContent_Chapter_triggered()
{
    ui->textBrowser->setText("Add a Chapter to a Student's Shopping Cart.");
    behaviour = StudentAddContent_chapter;
}
//Add a Section to the Student's Shopping Cart
void MainWindow::on_actionStudent_AddContent_Section_triggered()
{
    ui->textBrowser->setText("Add a Section to a Student's Shopping Cart.");
    behaviour = StudentAddContent_section;
}
//Add multiple items to the Student's Shopping Cart
void MainWindow::on_actionStudent_AddContent_multipleitems_triggered()
{
    ui->textBrowser->setText("Add multiple items to a Student's Shopping Cart.");
    behaviour = StudentAddContent_multipleitems;
}
//Add an invalid number of items to the Student's Shopping Cart
void MainWindow::on_actionStudent_AddContent_invalidnumofitems_triggered()
{
    ui->textBrowser->setText("Add an invalid number of items to a Student's Shopping Cart.");
    behaviour = StudentAddContent_invalidnumofitems;
}
//Add content to a Student's Shopping Cart when the Student is not found in the database
void MainWindow::on_actionStudent_AddContent_studentnotfound_triggered()
{
    ui->textBrowser->setText("Add an item to a Student's Shopping Cart when the Student is not found in the database.");
    behaviour = StudentAddContent_studentnotfound;
}
//Add an item to a Student's Shopping Cart when the item is not found in the database
void MainWindow::on_actionStudent_AddContent_itemnotfound_triggered()
{
    ui->textBrowser->setText("Add an item to a Student's Shopping Cart when the item is not found in the database.");
    behaviour = StudentAddContent_itemnotfound;
}





/****************************************
Student Get Existing Payment Information
****************************************/

//There is existing Payment Information
void MainWindow::on_actionStudent_GetExistingPaymentInformation_hasinfo_triggered()
{
    ui->textBrowser->setText("Get existing Payment Information when there is existing information.");
    behaviour = StudentGetExistingPaymentInformation_hasinfo;
}
//No existing Payment Information
void MainWindow::on_actionStudent_GetExistingPaymentInformation_noinfo_triggered()
{
    ui->textBrowser->setText("Get existing Payment Information when there isn't any existing information.");
    behaviour = StudentGetExistingPaymentInformation_noinfo;
}





/*******************************
Student Save Billing Information
*******************************/

//Invalid format
void MainWindow::on_actionStudent_SavePaymentInformation_invalidformat_triggered()
{
    ui->textBrowser->setText("Save Payment Information with an invalid format.");
    behaviour = StudentSavePaymentInformation_invalidformat;
}
//Valid format, no existing information
void MainWindow::on_actionStudent_SavePaymentInformation_validformat_triggered()
{
    ui->textBrowser->setText("Save Payment Information with a valid format and no existing Payment Information.");
    behaviour = StudentSavePaymentInformation_validformat;
}
//Valid format, existing information
void MainWindow::on_actionStudent_SavePaymentInformation_hasinfo_triggered()
{
    ui->textBrowser->setText("Save Payment Information with a valid format and existing Payment Information.");
        behaviour = StudentSavePaymentInformation_hasinfo;
}
//Student not found
void MainWindow::on_actionStudent_SavePaymentInformation_studentnotfound_triggered()
{
    ui->textBrowser->setText("Save Payment Information of a Student not found in the database.");
        behaviour = StudentSavePaymentInformation_studentnotfound;
}
