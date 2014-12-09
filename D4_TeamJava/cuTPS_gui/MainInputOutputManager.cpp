#include "MainInputOutputManager.h"
#include <QDebug>

MainInputOutputManager::MainInputOutputManager()
{

    ipAddressForm = new IPAddressForm();
    connect(ipAddressForm->getOkButton(),SIGNAL(clicked()),this,SLOT(on_ipAddressForm_okButton()));
    ipAddressForm->show();


}

void MainInputOutputManager::on_ipAddressForm_okButton()
{
    QString ipAddress = ipAddressForm->getIPAddressTextBox()->text().simplified();
    if(ipAddress != ""){
        ClientCommunicatorManagementControl::getInstance()->setConnectToHost(QHostAddress(ipAddress),60000);
        connect(mainWindow.getContentManagerButton(),SIGNAL(clicked()),this,SLOT(on_contentManager_clicked()));
        connect(mainWindow.getStudentButton(),SIGNAL(clicked()),this,SLOT(on_student_clicked()));

        mainWindow.show();
        qDebug() << "tst";
        delete ipAddressForm;
    }

}

void MainInputOutputManager::on_contentIOManager_deleted()
{
    contentManagerInterface->show();
}

void MainInputOutputManager::on_courseIOManager_deleted()
{

    contentManagerInterface->show();
}

void MainInputOutputManager::on_contentManager_clicked()
{
    contentManagerInterface = new ContentManagerInterfaceWindow();
    contentManagerInterface->show();
    mainWindow.hide();

    connect(contentManagerInterface->getManageTextbooksButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooks_clicked()));
    connect(contentManagerInterface->getManageCoursesButton(),SIGNAL(clicked()),this,SLOT(on_manageCourses_clicked()));
}

void MainInputOutputManager::on_student_clicked()
{
    mainWindow.hide();

    stuNumForm = new StudentNumberForm();
    connect(stuNumForm->getOkButton(),SIGNAL(clicked()),this,SLOT(on_stuNumForm_okButton()));
    connect(stuNumForm->getCancelButton(),SIGNAL(clicked()),this,SLOT(on_stuNumForm_cancelButton()));
    stuNumForm->show();


}

void MainInputOutputManager::on_stuNumForm_okButton() {
    if(stuNumForm->getStudentNumberTextBox()->text().simplified() != "") {
        QString studentNumber = stuNumForm->getStudentNumberTextBox()->text().simplified();
        studentIOManager = new StudentInputOutputManager(studentNumber);
        delete stuNumForm;
    }
}

void MainInputOutputManager::on_stuNumForm_cancelButton() {
    mainWindow.show();
    delete stuNumForm;
}

void MainInputOutputManager::on_manageTextbooks_clicked()
{
    contentManagerInterface->hide();
    contentIOManager = new ContentInputOutputManager();

    connect(contentIOManager,SIGNAL(destroyed()),this,SLOT(on_contentIOManager_deleted()));

    qDebug() << "manage textbooks";
}

void MainInputOutputManager::on_manageCourses_clicked()
{

    contentManagerInterface->hide();

    courseIOManager = new CourseInputOutputManager();
    connect(courseIOManager,SIGNAL(destroyed()),this, SLOT(on_courseIOManager_deleted()));


}
