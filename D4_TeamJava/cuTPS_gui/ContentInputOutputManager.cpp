#include "ContentInputOutputManager.h"
#include <QDebug>


ContentInputOutputManager::ContentInputOutputManager()
{

    textbookModel = new QStandardItemModel(this);
    chapterModel = new QStandardItemModel(this);
    sectionModel = new QStandardItemModel(this);


    manageTextbooksInterface = new ManageTextbooksInterfaceWindow();
    manageTextbooksInterface->show();



    connect(manageTextbooksInterface->getBackButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_back_button()));
    connect(manageTextbooksInterface->getEditTextbookButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_createTextbook_button()));
    connect(manageTextbooksInterface->getModifyTextbookButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_editTextbook_button()));
    connect(manageTextbooksInterface->getDeleteTextbookButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_deleteTextbook_button()));

    connect(manageTextbooksInterface->getTextbooksListView(),SIGNAL(clicked(QModelIndex)),this,SLOT(on_manageTextbooksInterface_selectTextbook()));
    connect(manageTextbooksInterface->getChaptersListView(),SIGNAL(clicked(QModelIndex)),this,SLOT(on_manageTextbooksInterface_selectChapter()));

    contentManagementFacade = new ContentManagementFacade();
    fakeTextbooks = contentManagementFacade->viewAllContent();
    buildTextbookModel();

    setContentManagementInterfaceViewModel(manageTextbooksInterface->getTextbooksListView(), textbookModel);
}

void ContentInputOutputManager::buildTextbookModel() {
    textbookModel->clear();
    chapterModel->clear();
    sectionModel->clear();
    OurStandardItem *temp;
    QList<Textbook*>::iterator i;
    qDebug() << fakeTextbooks.length();
    for (i = fakeTextbooks.begin(); i != fakeTextbooks.end(); i++) {
        qDebug() << (*i)->getItemTitle();
        temp = new OurStandardItem( *i );
        qDebug() << (*i);
        textbookModel->appendRow(temp);
    }
}

void ContentInputOutputManager::buildChapterModel() {
    chapterModel->clear();
    sectionModel->clear();
    OurStandardItem *temp;
    QList<Chapter*>::iterator i;
    qDebug() << fakeChapters.length();
    for (i = fakeChapters.begin(); i != fakeChapters.end(); i++) {
        qDebug() << (*i)->getItemTitle();
        temp = new OurStandardItem( *i );
        qDebug() << (*i);
        chapterModel->appendRow(temp);
    }
}

void ContentInputOutputManager::buildSectionModel() {
    sectionModel->clear();
    OurStandardItem *temp;
    QList<Section*>::iterator i;
    qDebug() << fakeSections.length();
    for (i = fakeSections.begin(); i != fakeSections.end(); i++) {
        qDebug() << (*i)->getItemTitle();
        temp = new OurStandardItem( *i );
        qDebug() << (*i);
        sectionModel->appendRow(temp);
    }
}

void ContentInputOutputManager::setContentManagementInterfaceViewModel(QAbstractItemView *view, QStandardItemModel *model) {
    view->setModel(model);
}

void ContentInputOutputManager::on_manageTextbooksInterface_selectTextbook()
{
    qDebug() << "selected textbook";

//    int selectedIndex = manageTextbooksInterface->getTextbooksListView()->currentIndex().row();
//    qDebug() << contentManagementFacade->viewAllContent().at(selectedIndex)->getItemTitle();
//    fakeChapters = contentManagementFacade->viewAllContent().at(selectedIndex)->getChapterList();
    fakeChapters = getSelectedTextbook()->getChapterList();
    buildChapterModel();
    setContentManagementInterfaceViewModel(manageTextbooksInterface->getChaptersListView(), chapterModel);
}

void ContentInputOutputManager::on_manageTextbooksInterface_selectChapter()
{
    qDebug() << "selected chapter";
//    int selectedTextbookIndex = manageTextbooksInterface->getTextbooksListView()->currentIndex().row();
//    int selectedChapterIndex = manageTextbooksInterface->getChaptersListView()->currentIndex().row();
//    qDebug() << contentManagementFacade->viewAllContent().at(selectedTextbookIndex)->getChapterList().at(selectedChapterIndex);



//    fakeSections = contentManagementFacade->viewAllContent().at(selectedTextbookIndex)->getChapterList().at(selectedChapterIndex)->getChapterSections();
    fakeSections = getSelectedChapter()->getChapterSections();
    buildSectionModel();
    setContentManagementInterfaceViewModel(manageTextbooksInterface->getSectionsListView(), sectionModel);
}


Chapter* ContentInputOutputManager::getSelectedChapter()
{
    int selectedIndex = manageTextbooksInterface->getChaptersListView()->currentIndex().row();
    return getSelectedTextbook()->getChapterList().at(selectedIndex);
}

Textbook* ContentInputOutputManager::getSelectedTextbook()
{
    int selectedIndex = manageTextbooksInterface->getTextbooksListView()->currentIndex().row();
    return contentManagementFacade->viewAllContent().at(selectedIndex);
}

Section* ContentInputOutputManager::getSelectedSection()
{
    int selectedIndex = manageTextbooksInterface->getSectionsListView()->currentIndex().row();
    return getSelectedChapter()->getChapterSections().at(selectedIndex);
}

void ContentInputOutputManager::on_manageTextbooksInterface_back_button()
{
    manageTextbooksInterface->hide();
    delete manageTextbooksInterface;
    delete this;
}

void ContentInputOutputManager::on_manageTextbooksInterface_createTextbook_button()
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
    delete editTextbookForm;
    manageTextbooksInterface->show();
}

void ContentInputOutputManager::on_editTextbookForm_create_button()
{
    qDebug() << "create a new textbook with the fields from the form and go back to the managetextbooksinterface";

}

void ContentInputOutputManager::on_editTextbookForm_editChapter_button()
{
    editTextbookForm->hide();
    editChapterForm = new EditChapterFormWindow();
    editChapterForm->show();
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
