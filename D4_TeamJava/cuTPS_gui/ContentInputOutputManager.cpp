#include "ContentInputOutputManager.h"
#include <QDebug>

ContentInputOutputManager::ContentInputOutputManager()
{



    createTextbookForm = new CreateTextbookFormWindow();
    //createTextbookForm->show();


    //Connect CreateTextbookForm UI buttons
    connect(createTextbookForm->getBackButton(), SIGNAL(clicked()),this,SLOT(on_textbook_back_button()));
    connect(createTextbookForm->getViewEditChaptersButton(), SIGNAL(clicked()),this,SLOT(on_textbook_viewEditChapters_button()));
    connect(createTextbookForm->getCreateButton(), SIGNAL(clicked()),this,SLOT(on_textbook_create_button()));
    connect(createTextbookForm->getAddChapterButton(), SIGNAL(clicked()),this,SLOT(on_textbook_addChapter_button()));
}

void ContentInputOutputManager::on_textbook_back_button()
{
    qDebug() << "ayy lmao";
}

void ContentInputOutputManager::on_textbook_viewEditChapters_button()
{
    qDebug() << "ayy lmao2";
    createChapterForm = new CreateChapterFormWindow();
    createChapterForm->show();
}

void ContentInputOutputManager::on_textbook_create_button()
{
    qDebug() << "ayy lmao3";

}

void ContentInputOutputManager::on_textbook_addChapter_button()
{
    qDebug() << "ayy lmao4";
}
