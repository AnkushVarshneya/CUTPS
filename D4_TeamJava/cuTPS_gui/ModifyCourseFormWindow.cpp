#include "ModifyCourseFormWindow.h"
#include "ui_ModifyCourseFormWindow.h"

ModifyCourseFormWindow::ModifyCourseFormWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyCourseFormWindow)
{
    ui->setupUi(this);
}

ModifyCourseFormWindow::~ModifyCourseFormWindow()
{
    delete ui;
}

QPushButton*    ModifyCourseFormWindow::getBackButton()             { return ui->backButton; }
QPushButton*    ModifyCourseFormWindow::getCreateButton()           { return ui->createButton; }
QPushButton*    ModifyCourseFormWindow::getEnrollButton()           { return ui->enrollStudentButton; }
QPushButton*    ModifyCourseFormWindow::getLinkTextbookButton()     { return ui->linkTextbookButton; }

QComboBox*      ModifyCourseFormWindow::getTermComboBox()           { return ui->termSelectOption; }

QLineEdit*      ModifyCourseFormWindow::getCourseCodeTextBox()      { return ui->courseCodeTextBox; }
QLineEdit*      ModifyCourseFormWindow::getCourseSectionTextBox()   { return ui->courseSectionTextBox; }
QLineEdit*      ModifyCourseFormWindow::getInstructorTextBox()      { return ui->instructorTextBox; }
