#include "ContentInputOutputManager.h"
#include <QDebug>


ContentInputOutputManager::ContentInputOutputManager()
{



    manageTextbooksInterface = new ManageTextbooksInterfaceWindow();
    manageTextbooksInterface->show();


    connect(manageTextbooksInterface->getBackButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_back_button()));
    connect(manageTextbooksInterface->getEditTextbookButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_createTextbook_button()));
    connect(manageTextbooksInterface->getModifyTextbookButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_editTextbook_button()));
    connect(manageTextbooksInterface->getDeleteTextbookButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_deleteTextbook_button()));


}


void ContentInputOutputManager::on_manageTextbooksInterface_back_button()
{
    manageTextbooksInterface->hide();
    delete this;
}

void ContentInputOutputManager::on_manageTextbooksInterface_createTextbook_button()
{
    qDebug() << "ayy lmao3";


    manageTextbooksInterface->hide();
    editTextbookForm = new EditTextbookFormWindow();
    editTextbookForm->show();


    //Connect EditTextbookForm UI buttons
    connect(editTextbookForm->getBackButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_back_button()));
    connect(editTextbookForm->getCreateButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_create_button()));
    connect(editTextbookForm->getViewEditChaptersButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_editChapter_button()));
    connect(editTextbookForm->getAddChapterButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_createChapter_button()));

}

void ContentInputOutputManager::on_manageTextbooksInterface_editTextbook_button()
{
    manageTextbooksInterface->hide();
    editTextbookForm = new EditTextbookFormWindow();
    editTextbookForm->show();

    //Connect EditTextbookForm UI buttons
    connect(editTextbookForm->getBackButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_back_button()));
    connect(editTextbookForm->getCreateButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_create_button()));
    connect(editTextbookForm->getViewEditChaptersButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_editChapter_button()));
    connect(editTextbookForm->getAddChapterButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_createChapter_button()));
}

void ContentInputOutputManager::on_manageTextbooksInterface_deleteTextbook_button()
{
    qDebug() << "Are you sure?";
}

void ContentInputOutputManager::on_editTextbookForm_back_button()
{
    qDebug() << "ayy lmao";
    delete editTextbookForm;
    manageTextbooksInterface->show();
}

void ContentInputOutputManager::on_editTextbookForm_create_button()
{
    qDebug() << "create a new textbook with the fields from the form and go back to the managetextbooksinterface";

}

void ContentInputOutputManager::on_editTextbookForm_editChapter_button()
{
    qDebug() << "ayy lmao2";

    editTextbookForm->hide();
    editChapterForm = new EditChapterFormWindow();
    editChapterForm->show();

    //connect(editChapterForm->get)

}

void ContentInputOutputManager::on_editTextbookForm_createChapter_button()
{
    qDebug() << "create a new chapter and edit it";
    editTextbookForm->hide();
    editChapterForm = new EditChapterFormWindow();
    editChapterForm->show();
}

void ContentInputOutputManager::on_editChapterForm_back_button()
{
    qDebug() << "go back to the edittextbookform";

    editChapterForm->hide();
    delete editChapterForm;
    editTextbookForm->show();
}

void ContentInputOutputManager::on_editChapterForm_createSection_button()
{
    qDebug() << "create a new section and edit it";
    editChapterForm->hide();
    editSectionForm = new EditSectionFormWindow();
    editSectionForm->show();
}

void ContentInputOutputManager::on_editChapterForm_create_button()
{
    qDebug() << "create a new chapter with the fields from the form and go back to the edittextbookform";
    editChapterForm->hide();
    delete editChapterForm;
    editTextbookForm->show();
}

void ContentInputOutputManager::on_editChapterForm_editSection_button()
{
    qDebug() << "edit an existing section";
    editChapterForm->hide();
    editSectionForm->show();
}

void ContentInputOutputManager::on_editSectionForm_back_button()
{
    qDebug() << "go back to the editchapterform";
    delete editSectionForm;
    editChapterForm->show();
}

void ContentInputOutputManager::on_editSectionForm_create_button()
{
    qDebug() << "create a new section with the fields from the form and go back to the editchapterform";
    editSectionForm->hide();
    delete editSectionForm;
    editChapterForm->show();
}
