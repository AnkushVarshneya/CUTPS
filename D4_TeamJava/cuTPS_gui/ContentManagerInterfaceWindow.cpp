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

QPushButton* ContentManagerInterfaceWindow::getManageTextbooksButton()  { return ui->manageTextbooksOption; }
QPushButton* ContentManagerInterfaceWindow::getManageCoursesButton()    { return ui->manageCoursesOption; }
