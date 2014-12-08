#include "ContentInputOutputManager.h"
#include <QDebug>


ContentInputOutputManager::ContentInputOutputManager()
{
    manageTextbooksInterface = new ManageTextbooksInterfaceWindow();
    manageTextbooksInterface->show();

    connect_manageTextbooksInterface();

    textbookModel = new QStandardItemModel(this);
    chapterModel = new QStandardItemModel(this);
    sectionModel = new QStandardItemModel(this);

    contentManagementFacade = new ContentManagementFacade();
    fakeTextbooks = contentManagementFacade->viewAllContent();
    buildTextbookModel();

    setContentManagementInterfaceViewModel(manageTextbooksInterface->getTextbooksListView(), textbookModel);
}

void ContentInputOutputManager::connect_manageTextbooksInterface() {
    //Connect manageTextbooksInterface UI buttons
    connect(manageTextbooksInterface->getBackButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_back_button()));
    connect(manageTextbooksInterface->getEditTextbookButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_createTextbook_button()));
    connect(manageTextbooksInterface->getModifyTextbookButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_editTextbook_button()));
    connect(manageTextbooksInterface->getDeleteTextbookButton(),SIGNAL(clicked()),this,SLOT(on_manageTextbooksInterface_deleteTextbook_button()));
    connect(manageTextbooksInterface->getTextbooksListView(),SIGNAL(clicked(QModelIndex)),this,SLOT(on_manageTextbooksInterface_selectTextbook()));
    connect(manageTextbooksInterface->getChaptersListView(),SIGNAL(clicked(QModelIndex)),this,SLOT(on_manageTextbooksInterface_selectChapter()));
}

void ContentInputOutputManager::connect_editTextbookForm() {
    //Connect editTextbookForm UI buttons
    connect(editTextbookForm->getBackButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_back_button()));
    connect(editTextbookForm->getCreateButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_create_button()));
    connect(editTextbookForm->getViewEditChaptersButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_editChapter_button()));
    connect(editTextbookForm->getAddChapterButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_createChapter_button()));
}

void ContentInputOutputManager::connect_editChapterForm() {
    //Connect editChapterForm UI buttons
    connect(editChapterForm->getBackButton(), SIGNAL(clicked()),this,SLOT(on_editChapterForm_back_button()));
    connect(editChapterForm->getCreateButton(), SIGNAL(clicked()),this,SLOT(on_editChapterForm_create_button()));
    connect(editChapterForm->getCreateSectionButton(), SIGNAL(clicked()),this,SLOT(on_editChapterForm_createSection_button()));
    connect(editChapterForm->getEditSectionButton(), SIGNAL(clicked()),this,SLOT(on_editChapterForm_editSection_button()));
}

void ContentInputOutputManager::connect_editSectionForm() {
    //Connect editSectionForm UI buttons
    connect(editSectionForm->getBackButton(), SIGNAL(clicked()),this,SLOT(on_editSectionForm_back_button()));
    connect(editSectionForm->getCreateButton(), SIGNAL(clicked()),this,SLOT(on_editSectionForm_create_button()));
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



/*
 *manageTextbooksInterface UI handling
 */



void ContentInputOutputManager::on_manageTextbooksInterface_selectTextbook() {
    qDebug() << "selected textbook";

    fakeChapters = manageTextbooks_getSelectedTextbook()->getChapterList();
    qDebug() << "created fakechapters";
    buildChapterModel();
    qDebug()<< "built chaptermodel";

    setContentManagementInterfaceViewModel(manageTextbooksInterface->getChaptersListView(), chapterModel);
    qDebug() << "set chapterslistview";

}
void ContentInputOutputManager::on_manageTextbooksInterface_selectChapter() {
    qDebug() << "selected chapter";

    fakeSections = manageTextbooks_getSelectedChapter()->getChapterSections();
    buildSectionModel();
    setContentManagementInterfaceViewModel(manageTextbooksInterface->getSectionsListView(), sectionModel);
}
void ContentInputOutputManager::on_manageTextbooksInterface_back_button() {
    delete manageTextbooksInterface;
    delete this;
}
void ContentInputOutputManager::on_manageTextbooksInterface_createTextbook_button() {
    manageTextbooksInterface->hide();
    editTextbookForm = new EditTextbookFormWindow();
    editTextbookForm->show();

    connect_editTextbookForm();

    currentTextbook = new Textbook();
    createOrEditTFlag = 0;
}
void ContentInputOutputManager::on_manageTextbooksInterface_editTextbook_button() {

    currentTextbook = manageTextbooks_getSelectedTextbook();
    qDebug() << "";
    if(currentTextbook == NULL) {
        qDebug() << "no textbooks to edit";
    }

    manageTextbooksInterface->hide();
    editTextbookForm = new EditTextbookFormWindow();
    editTextbookForm->show();

    editTextbookForm->getTitleTextbox()->setText(currentTextbook->getItemTitle());
    editTextbookForm->getAuthorTextbox()->setText(currentTextbook->getAuthor());
    editTextbookForm->getEditionTextbox()->setText(currentTextbook->getEdition());
    editTextbookForm->getPublisherTextbox()->setText(currentTextbook->getPublisher());
    editTextbookForm->getISBNTextbox()->setText(currentTextbook->getISBN());
    editTextbookForm->getCoverImageTextbox()->setText(currentTextbook->getCoverImageLoc());
    editTextbookForm->getPriceSpinBox()->setValue(currentTextbook->getPrice());
    editTextbookForm->getAvailabilityCheckBox()->setChecked(currentTextbook->isAvailable());
    editTextbookForm->getDescriptionTextbox()->setHtml(currentTextbook->getDesc());

    fakeChapters = currentTextbook->getChapterList();
    buildChapterModel();
    setContentManagementInterfaceViewModel(editTextbookForm->getChaptersListView(), chapterModel);

    connect_editTextbookForm();


    createOrEditTFlag = 1;
}
void ContentInputOutputManager::on_manageTextbooksInterface_deleteTextbook_button() {
    /*
    qDebug() << "Are you sure?";
    textbookToRemove = getSelectedTextbook();
    queryServer("deletetextbook",getSelectedTextbook());



    fakeTextbooks.removeAll(getSelectedTextbook());
    buildTextbookModel();
    setContentManagementInterfaceViewModel(manageTextbooksInterface->getTextbooksListView(), textbookModel);
    */
}





/*
 *editTextbookForm UI handling
 */



void ContentInputOutputManager::on_editTextbookForm_back_button() {
    delete editTextbookForm;
    manageTextbooksInterface->show();

    if(createOrEditTFlag == 0)
        delete currentTextbook;
    fakeChapters.clear();
    currentTextbook = 0;
}
void ContentInputOutputManager::on_editTextbookForm_create_button() {
    qDebug() << "create a new textbook with the fields from the form and go back to the managetextbooksinterface";


    currentTextbook->setItemTitle(editTextbookForm->getTitleTextbox()->text());
    currentTextbook->setAuthor(editTextbookForm->getAuthorTextbox()->text());
    currentTextbook->setEdition(editTextbookForm->getEditionTextbox()->text());
    currentTextbook->setPublisher(editTextbookForm->getPublisherTextbox()->text());
    currentTextbook->setISBN(editTextbookForm->getISBNTextbox()->text());
    currentTextbook->setCoverImageLoc(editTextbookForm->getCoverImageTextbox()->text());
    currentTextbook->setPrice(editTextbookForm->getPriceSpinBox()->value());
    currentTextbook->setAvailability(editTextbookForm->getAvailabilityCheckBox()->isChecked());
    currentTextbook->setDescription(editTextbookForm->getDescriptionTextbox()->toPlainText());

    if(createOrEditTFlag==0){
        fakeTextbooks.push_back(currentTextbook);
        //contentManagementFacade->fakeTextbooks.push_back(currentTextbook);
    }

    QJsonObject json;
    currentTextbook->write(json);
    qDebug()<< json;
    qDebug() << contentManagementFacade->updateContent(currentTextbook);

    buildTextbookModel();
    setContentManagementInterfaceViewModel(manageTextbooksInterface->getTextbooksListView(), textbookModel);

    delete editTextbookForm;
    manageTextbooksInterface->show();
    qDebug()<<"exiting edittext_create";
}
void ContentInputOutputManager::on_editTextbookForm_editChapter_button() {
    qDebug() << "about to check";
    if(editTextbookForm->getChaptersListView()->model() == NULL){
        qDebug() << "EMPTY3";
    }
    if(editTextbookForm->getChaptersListView() == NULL){
        qDebug() << "EMPTY2";
    }
//    if(editTextbookForm->getChaptersListView()->model()->rowCount()){
//        qDebug() << "EMPTY";
//        return;
//    }
    qDebug() << "FAILED";
    currentChapter = editTextbookForm_getSelectedChapter();
    if(currentChapter == NULL) {
        qDebug() << "no chapters to edit";
    }


    editTextbookForm->hide();
    editChapterForm = new EditChapterFormWindow();
    editChapterForm->show();
    connect_editChapterForm();



    editChapterForm->getTitleTextbox()->setText(currentChapter->getItemTitle());
    editChapterForm->getChapterNumberSpinBox()->setValue(currentChapter->getChapterNumber());
    editChapterForm->getPriceSpinBox()->setValue(currentChapter->getPrice());
    editChapterForm->getAvailabilityCheckBox()->setChecked(currentChapter->isAvailable());

    fakeSections = currentChapter->getChapterSections();
    buildSectionModel();
    setContentManagementInterfaceViewModel(editChapterForm->getSectionsListView(), sectionModel);

    createOrEditCFlag = 1;
}
void ContentInputOutputManager::on_editTextbookForm_createChapter_button() {
    qDebug() << "create a new chapter and edit it";
    editTextbookForm->hide();
    editChapterForm = new EditChapterFormWindow();
    editChapterForm->show();
    //connect create chapter vs connect edit chapter?
    connect_editChapterForm();

    currentChapter = new Chapter("",-1,-1,-1,0);
    createOrEditCFlag = 0;
}



/*
 *editChapterForm UI handling
 */



void ContentInputOutputManager::on_editChapterForm_back_button() {
    //qDebug() << "go back to the edittextbookform";
    //editChapterForm->hide();
    delete editChapterForm;
    editTextbookForm->show();
    if(createOrEditCFlag == 0)
        delete currentChapter;
    fakeSections.clear();
    currentChapter = 0;
}
void ContentInputOutputManager::on_editChapterForm_create_button() {
    qDebug() << "create a new chapter with the fields from the form and go back to the edittextbookform";


    currentChapter->setItemTitle(editChapterForm->getTitleTextbox()->text());
    currentChapter->setChapterNumber(editChapterForm->getChapterNumberSpinBox()->value());
    currentChapter->setPrice(editChapterForm->getPriceSpinBox()->value());
    currentChapter->setAvailability(editChapterForm->getAvailabilityCheckBox()->isChecked());

    if(createOrEditCFlag==0){
        currentTextbook->addChapter(currentChapter);
        fakeChapters.push_back(currentChapter);
    }

    buildChapterModel();
    setContentManagementInterfaceViewModel(editTextbookForm->getChaptersListView(), chapterModel);

    editChapterForm->hide();
    delete editChapterForm;
    editTextbookForm->show();
}
void ContentInputOutputManager::on_editChapterForm_createSection_button() {
    qDebug() << "create a new section and edit it";
    editChapterForm->hide();
    editSectionForm = new EditSectionFormWindow();
    editSectionForm->show();

    createOrEditSFlag = 0;
    currentSection = new Section("",-1,-1,-1,0);

    connect_editSectionForm();
}
void ContentInputOutputManager::on_editChapterForm_editSection_button() {
    currentSection = editChapterForm_getSelectedSection();
    if(currentSection == NULL){
        qDebug() << "no sections to edit";
    }

    qDebug() << "edit an existing section";
    editChapterForm->hide();
    editSectionForm = new EditSectionFormWindow();
    editSectionForm->show();

    createOrEditSFlag = 1;

    connect_editSectionForm();

    editSectionForm->getTitleTextbox()->setText(currentSection->getItemTitle());
    editSectionForm->getSectionNumberSpinBox()->setValue(currentSection->getSectionNumber());
    editSectionForm->getPriceSpinBox()->setValue(currentSection->getPrice());
    editSectionForm->getAvailabilityCheckBox()->setChecked(currentSection->isAvailable());
}





/*
*editSectionForm UI handling
*/



void ContentInputOutputManager::on_editSectionForm_back_button() {
    qDebug() << "go back to the editchapterform";
    delete editSectionForm;
    editChapterForm->show();
    if(createOrEditSFlag == 0)
        delete currentSection;
    currentSection = 0;
}
void ContentInputOutputManager::on_editSectionForm_create_button() {
    qDebug() << "create a new section with the fields from the form and go back to the editchapterform";    

    currentSection->setItemTitle(editSectionForm->getTitleTextbox()->text());
    currentSection->setSectionNumber(editSectionForm->getSectionNumberSpinBox()->value());
    currentSection->setPrice(editSectionForm->getPriceSpinBox()->value());
    currentSection->setAvailability(editSectionForm->getAvailabilityCheckBox()->isChecked());

    if(createOrEditSFlag==0){
        currentChapter->addSection(currentSection);
        fakeSections.push_back(currentSection);
    }

    buildSectionModel();
    setContentManagementInterfaceViewModel(editChapterForm->getSectionsListView(), sectionModel);

    //fakeSections.push_back(currentSection);

    delete editSectionForm;
    editChapterForm->show();
}



void ContentInputOutputManager::update_editChapterForm_SectionList() {
    fakeSections = currentChapter->getChapterSections();
    buildSectionModel();
    setContentManagementInterfaceViewModel(editChapterForm->getSectionsListView(), sectionModel);
}
void ContentInputOutputManager::update_editTextbookForm_ChapterList() {

}



//Item getters for ListViews

Chapter* ContentInputOutputManager::manageTextbooks_getSelectedChapter() {
    //if(manageTextbooksInterface->getChaptersListView()->model()->rowc;
    qDebug() << "in getselectedchapter";
    int selectedIndex = manageTextbooksInterface->getChaptersListView()->currentIndex().row();
    return manageTextbooks_getSelectedTextbook()->getChapterList().at(selectedIndex);
}
Textbook* ContentInputOutputManager::manageTextbooks_getSelectedTextbook() {
    qDebug() << "in getselectedtextbook";
    int selectedIndex = manageTextbooksInterface->getTextbooksListView()->currentIndex().row();
    qDebug() << "got index";
    return fakeTextbooks.at(selectedIndex);
}
Section* ContentInputOutputManager::manageTextbooks_getSelectedSection() {
    qDebug() << "in getselectedsection";
    int selectedIndex = manageTextbooksInterface->getSectionsListView()->currentIndex().row();
    return manageTextbooks_getSelectedChapter()->getChapterSections().at(selectedIndex);
}
Chapter* ContentInputOutputManager::editTextbookForm_getSelectedChapter() {
    qDebug() << "getselectedchap";
    int selectedIndex = editTextbookForm->getChaptersListView()->currentIndex().row();
    Textbook* t = manageTextbooks_getSelectedTextbook();
    return t->getChapterList().at(selectedIndex);
}
Section* ContentInputOutputManager::editChapterForm_getSelectedSection() {
    qDebug() << "getselectedsect";
    int selectedIndex = editChapterForm->getSectionsListView()->currentIndex().row();
    //return editTextbookForm_getSelectedChapter()->getChapterSections().at(selectedIndex);
    return currentChapter->getChapterSections().at(selectedIndex);
}
