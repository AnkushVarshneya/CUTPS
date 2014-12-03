#include "ContentInputOutputManager.h"
#include <QDebug>

ContentInputOutputManager::ContentInputOutputManager()
{



    manageTextbooksInterface = new ManageTextbooksInterfaceWindow();
    manageTextbooksInterface->show();

    connect(manageTextbooksInterface->getBackButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_back_button()));
    connect(manageTextbooksInterface->getEditTextbookButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_editTextbook_button()));
    connect(manageTextbooksInterface->getModifyTextbookButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_modifyTextbook_button()));
    connect(manageTextbooksInterface->getDeleteTextbookButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_deleteTextbook_button()));


}

void ContentInputOutputManager::on_manageTextbooksInterface_back_button()
{
    manageTextbooksInterface->hide();
}

void ContentInputOutputManager::on_manageTextbooksInterface_editTextbook_button()
{
    qDebug() << "ayy lmao3";

    manageTextbooksInterface->hide();
    editTextbookForm = new EditTextbookFormWindow();
    editTextbookForm->show();


    //Connect EditTextbookForm UI buttons
    connect(editTextbookForm->getBackButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_back_button()));
    connect(editTextbookForm->getCreateButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_create_button()));
    connect(editTextbookForm->getViewEditChaptersButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_viewEditChapters_button()));
    connect(editTextbookForm->getAddChapterButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_addChapter_button()));

}

void ContentInputOutputManager::on_manageTextbooksInterface_modifyTextbook_button()
{
    manageTextbooksInterface->hide();
}

void ContentInputOutputManager::on_manageTextbooksInterface_deleteTextbook_button()
{

}

void ContentInputOutputManager::on_editTextbookForm_back_button()
{
    qDebug() << "ayy lmao";
}

void ContentInputOutputManager::on_editTextbookForm_create_button()
{
    qDebug() << "ayy lmao";
}

void ContentInputOutputManager::on_editTextbookForm_viewEditChapters_button()
{
    qDebug() << "ayy lmao2";
    editChapterForm = new EditChapterFormWindow();
    editChapterForm->show();
}

void ContentInputOutputManager::on_editTextbookForm_addChapter_button()
{
    qDebug() << "ayy lmao4";
}


