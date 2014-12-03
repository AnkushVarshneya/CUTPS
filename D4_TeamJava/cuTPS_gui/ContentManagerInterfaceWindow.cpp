#include "ContentManagerInterfaceWindow.h"
#include "ui_ContentManagerInterfaceWindow.h"
#include <QPixmap>

ContentManagerInterfaceWindow::ContentManagerInterfaceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentManagerInterfaceWindow)
{
    ui->setupUi(this);

    QPixmap book_img("../Images/textbook_clipart.gif");
    QPixmap course_img("../Images/course_clipart.png");
    ui->textbook_pic_label->setPixmap(book_img);
    ui->course_pic_label->setPixmap(course_img);

}

ContentManagerInterfaceWindow::~ContentManagerInterfaceWindow()
{
    delete ui;
}



/*
//On clicking the ManageTextbooksOption, A list of textbooks are shown
//Options to Create Textbook, Modify Textbook, and Delete Textbooks are shown
void ContentManagerInterfaceWindow::on_manageTextbooksOption_clicked()
{
    contentIOManager.editTextbookForm->show();
    this->hide();
}


//On clicking the ManageCoursesOption, A new Interface window is shown specifically for course management
void ContentManagerInterfaceWindow::on_manageCoursesOption_clicked()
{

}
*/
QPushButton* ContentManagerInterfaceWindow::getManageTextbooksButton()
{
    return ui->manageTextbooksOption;
}

QPushButton* ContentManagerInterfaceWindow::getManageCoursesButton()
{
    return ui->manageCoursesOption;
}
