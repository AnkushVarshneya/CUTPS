#include "ContentInputOutputManager.h"
#include <QDebug>


ContentInputOutputManager::ContentInputOutputManager()
{
    try{
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

        manageTextbooksInterface->getTextbooksListView()->setCurrentIndex(QModelIndex());
    }
    catch (QString error){
        messageDialog.getMessageTextBox()->setText(error);
        messageDialog.show();
    }
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
    connect(editTextbookForm->getDeleteChapterButton(), SIGNAL(clicked()),this,SLOT(on_editTextbookForm_deleteChapter_button()));
}
void ContentInputOutputManager::connect_editChapterForm() {
    //Connect editChapterForm UI buttons
    connect(editChapterForm->getBackButton(), SIGNAL(clicked()),this,SLOT(on_editChapterForm_back_button()));
    connect(editChapterForm->getCreateButton(), SIGNAL(clicked()),this,SLOT(on_editChapterForm_create_button()));
    connect(editChapterForm->getCreateSectionButton(), SIGNAL(clicked()),this,SLOT(on_editChapterForm_createSection_button()));
    connect(editChapterForm->getEditSectionButton(), SIGNAL(clicked()),this,SLOT(on_editChapterForm_editSection_button()));
    connect(editChapterForm->getDeleteSectionButton(), SIGNAL(clicked()),this,SLOT(on_editChapterForm_deleteSection_button()));
}
void ContentInputOutputManager::connect_editSectionForm() {
    //Connect editSectionForm UI buttons
    connect(editSectionForm->getBackButton(), SIGNAL(clicked()),this,SLOT(on_editSectionForm_back_button()));
    connect(editSectionForm->getCreateButton(), SIGNAL(clicked()),this,SLOT(on_editSectionForm_create_button()));
}
void ContentInputOutputManager::connect_deleteTextbookConfirmationForm() {
    connect(confirmationForm->getYesButton(),SIGNAL(clicked()),this,SLOT(on_deleteTextbookConfirmationForm_yesButton()));
    connect(confirmationForm->getNoButton(),SIGNAL(clicked()),this,SLOT(on_deleteTextbookConfirmationForm_noButton()));
}
void ContentInputOutputManager::connect_deleteChapterConfirmationForm() {
    connect(confirmationForm->getYesButton(),SIGNAL(clicked()),this,SLOT(on_deleteChapterConfirmationForm_yesButton()));
    connect(confirmationForm->getNoButton(),SIGNAL(clicked()),this,SLOT(on_deleteChapterConfirmationForm_noButton()));
}
void ContentInputOutputManager::connect_deleteSectionConfirmationForm() {
    connect(confirmationForm->getYesButton(),SIGNAL(clicked()),this,SLOT(on_deleteSectionConfirmationForm_yesButton()));
    connect(confirmationForm->getNoButton(),SIGNAL(clicked()),this,SLOT(on_deleteSectiononfirmationForm_noButton()));
}

void ContentInputOutputManager::on_deleteChapterConfirmationForm_yesButton() {
    currentChapter = editTextbookForm_getSelectedChapter();
    fakeChapters.removeAll(currentChapter);
    foreach (Section* sec, currentChapter->getChapterSections()){
        try{
            contentManagementFacade->deleteContent(sec);
            currentChapter->getChapterSections().removeAll(sec);
            delete sec;
        }
        catch (QString error){
            messageDialog.getMessageTextBox()->setText(error);
            messageDialog.show();
        }

    }
    try{
        contentManagementFacade->deleteContent(currentChapter);
        currentTextbook->getChapterList().removeAll(currentChapter);
        fakeChapters.removeAll(currentChapter);


        buildChapterModel();
        setContentManagementInterfaceViewModel(editTextbookForm->getChaptersListView(), chapterModel);


        delete confirmationForm;
    }
    catch (QString error){
        messageDialog.getMessageTextBox()->setText(error);
        messageDialog.show();
    }

}
void ContentInputOutputManager::on_deleteChapterConfirmationForm_noButton() {
    //confirmationForm->setModal(false);
    delete confirmationForm;
}
void ContentInputOutputManager::on_deleteSectionConfirmationForm_yesButton() {
    if(editChapterForm->getSectionsListView()->currentIndex().row() == -1){
        qDebug() << "no item selected";
        return;
    }
    currentSection = editChapterForm_getSelectedSection();
    try{
        contentManagementFacade->deleteContent(currentSection);
        fakeSections.removeAll(currentSection);
        currentChapter->getChapterSections().removeAll(currentSection);

        delete currentSection;
        currentSection = 0;

        buildSectionModel();
        setContentManagementInterfaceViewModel(editChapterForm->getSectionsListView(), sectionModel);

        //confirmationForm->setModal(false);
        delete confirmationForm;
    }
    catch (QString error){
        messageDialog.getMessageTextBox()->setText(error);
        messageDialog.show();
    }

}
void ContentInputOutputManager::on_deleteSectionConfirmationForm_noButton() {
    //confirmationForm->setModal(false);
    delete confirmationForm;
}
void ContentInputOutputManager::on_deleteTextbookConfirmationForm_yesButton() {
    currentTextbook = manageTextbooks_getSelectedTextbook();
    foreach (Chapter* chap, currentTextbook->getChapterList()){
        foreach (Section* sec, chap->getChapterSections()){
            try{
                contentManagementFacade->deleteContent(sec);
                chap->getChapterSections().removeAll(sec);

                delete sec;
            }
            catch (QString error){
                messageDialog.getMessageTextBox()->setText(error);
                messageDialog.show();
            }
        }
        try{
            contentManagementFacade->deleteContent(chap);
        }
        catch (QString error){
            messageDialog.getMessageTextBox()->setText(error);
            messageDialog.show();
        }

        qDebug() << "deleted chapter";
    }

    try{
        contentManagementFacade->deleteContent(currentTextbook);
        fakeTextbooks.removeAll(currentTextbook);
        delete currentTextbook;


        fakeChapters.clear();
        fakeSections.clear();


        buildTextbookModel();
        setContentManagementInterfaceViewModel(manageTextbooksInterface->getTextbooksListView(), textbookModel);


        //confirmationForm->setModal(false);
        delete confirmationForm;
    }
    catch(QString error){
        messageDialog.getMessageTextBox()->setText(error);
        messageDialog.show();
    }


}
void ContentInputOutputManager::on_deleteTextbookConfirmationForm_noButton() {
    //confirmationForm->setModal(false);
    delete confirmationForm;
}

void ContentInputOutputManager::buildTextbookModel() {
    textbookModel->clear();
    chapterModel->clear();
    sectionModel->clear();
    OurStandardItem *temp;
    QList<Textbook*>::iterator i;
    qDebug() << fakeTextbooks.length();
    for (i = fakeTextbooks.begin(); i != fakeTextbooks.end(); i++) {
        qDebug() << 1;
        qDebug() << (*i)->getItemTitle();
        qDebug() << 2;
        temp = new OurStandardItem( *i );
        qDebug() << 3;
        qDebug() << (*i);
        qDebug() << 4;
        textbookModel->appendRow(temp);
        qDebug() << 5;
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
    fakeChapters.clear();
    qDebug() << "set chapterslistview";

}
void ContentInputOutputManager::on_manageTextbooksInterface_selectChapter() {
    qDebug() << "selected chapter";

    fakeSections = manageTextbooks_getSelectedChapter()->getChapterSections();
    buildSectionModel();
    setContentManagementInterfaceViewModel(manageTextbooksInterface->getSectionsListView(), sectionModel);
    fakeSections.clear();
}
void ContentInputOutputManager::on_manageTextbooksInterface_back_button() {
    delete manageTextbooksInterface;
    delete this;
}
void ContentInputOutputManager::on_manageTextbooksInterface_createTextbook_button() {
    fakeChapters.clear();

    manageTextbooksInterface->hide();
    editTextbookForm = new EditTextbookFormWindow();
    editTextbookForm->show();

    connect_editTextbookForm();



    currentTextbook = new Textbook();
    createOrEditTFlag = 0;
}
void ContentInputOutputManager::on_manageTextbooksInterface_editTextbook_button() {

    if(manageTextbooksInterface->getTextbooksListView()->currentIndex().row() == -1){
        qDebug() << "no item selected";
        messageDialog.getMessageTextBox()->setText("No Item Selected");
        messageDialog.show();
        return;
    }

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
    editTextbookForm->getISBNTextbox()->setEnabled(false);
}
void ContentInputOutputManager::on_manageTextbooksInterface_deleteTextbook_button() {

    if(manageTextbooksInterface->getTextbooksListView()->currentIndex().row() == -1){
        messageDialog.getMessageTextBox()->setText("No Item Selected");
        messageDialog.show();
        qDebug() << "no item selected";
        return;
    }

    confirmationForm = new ConfirmationDialogWindow();
    //confirmationForm->setModal(true);
    connect_deleteTextbookConfirmationForm();
    confirmationForm->getMessageTextBox()->setText("Are you sure you want to delete this textbook?");
    confirmationForm->show();
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
    try{
        fakeTextbooks = contentManagementFacade->viewAllContent();

        buildTextbookModel();
        setContentManagementInterfaceViewModel(manageTextbooksInterface->getTextbooksListView(), textbookModel);
    }
    catch(QString error){
        messageDialog.getMessageTextBox()->setText(error);
        messageDialog.show();
    }
}

void ContentInputOutputManager::on_editTextbookForm_create_button() {
    foreach(Textbook *t,fakeTextbooks) {
        if((t->getISBN() == editTextbookForm->getISBNTextbox()->text())
                &&
               (t != currentTextbook)) {
            messageDialog.getMessageTextBox()->setText("Error: Textbooks with duplicate ISBN's cannot be added. Change this textbook's ISBN so that it doesn't share its ISBN with any other textbooks.");
            messageDialog.show();
            return;
        }
    }

    qDebug() << "setting currenttextbook vals";

    currentTextbook->setItemTitle(editTextbookForm->getTitleTextbox()->text());
    currentTextbook->setAuthor(editTextbookForm->getAuthorTextbox()->text());
    currentTextbook->setEdition(editTextbookForm->getEditionTextbox()->text());
    currentTextbook->setPublisher(editTextbookForm->getPublisherTextbox()->text());
    currentTextbook->setISBN(editTextbookForm->getISBNTextbox()->text());
    currentTextbook->setCoverImageLoc(editTextbookForm->getCoverImageTextbox()->text());
    currentTextbook->setPrice(editTextbookForm->getPriceSpinBox()->value());
    currentTextbook->setAvailability(editTextbookForm->getAvailabilityCheckBox()->isChecked());
    currentTextbook->setDescription(editTextbookForm->getDescriptionTextbox()->toPlainText());


//    if(createOrEditTFlag==0){
//        fakeTextbooks.push_back(currentTextbook);
//        //contentManagementFacade->fakeTextbooks.push_back(currentTextbook);
//    }
    QJsonObject json;
    //currentTextbook->write(json);
    //qDebug()<< json;



    try{
        contentManagementFacade->updateContent(currentTextbook);
        fakeChapters.clear();
        currentTextbook = 0;

        fakeTextbooks = contentManagementFacade->viewAllContent();
        buildTextbookModel();
        setContentManagementInterfaceViewModel(manageTextbooksInterface->getTextbooksListView(), textbookModel);
        delete editTextbookForm;
        manageTextbooksInterface->show();

    }
    catch(QString error){
        messageDialog.getMessageTextBox()->setText(error);
        messageDialog.show();
    }


    qDebug()<<"exiting edittext_create";
}

void ContentInputOutputManager::on_editTextbookForm_editChapter_button() {
    if(editTextbookForm->getChaptersListView()->currentIndex().row() == -1){
        messageDialog.getMessageTextBox()->setText("No Item Selected");
        messageDialog.show();
        qDebug() << "no item selected";
        return;
    }

    currentChapter = editTextbookForm_getSelectedChapter();
    if(currentChapter == NULL) {
        messageDialog.getMessageTextBox()->setText("No Chapters To Edit");
        messageDialog.show();
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
    editChapterForm->getChapterNumberSpinBox()->setEnabled(false);
}

void ContentInputOutputManager::on_editTextbookForm_createChapter_button() {
    fakeSections.clear();

    qDebug() << "create a new chapter and edit it";
    editTextbookForm->hide();
    editChapterForm = new EditChapterFormWindow();
    editChapterForm->show();
    //connect create chapter vs connect edit chapter?
    connect_editChapterForm();



    currentChapter = new Chapter("",-1,-1,-1,0);
    createOrEditCFlag = 0;
}

void ContentInputOutputManager::on_editTextbookForm_deleteChapter_button() {
    /*
    qDebug() << "Are you sure?";
    */

    if(editTextbookForm->getChaptersListView()->currentIndex().row() == -1){
        messageDialog.getMessageTextBox()->setText("No Item Selected");
        messageDialog.show();
        qDebug() << "no item selected";
        return;
    }

    confirmationForm = new ConfirmationDialogWindow();
    //confirmationForm->setModal(true);
    connect_deleteChapterConfirmationForm();
    confirmationForm = new ConfirmationDialogWindow();
    //confirmationForm->setModal(true);
    connect_deleteChapterConfirmationForm();
    confirmationForm->getMessageTextBox()->setText("Are you sure you want to delete this chapter?");
    confirmationForm->show();
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
    foreach(Chapter *c,currentTextbook->getChapterList()) {
        if((c->getChapterNumber() == editChapterForm->getChapterNumberSpinBox()->value())
                &&
               (c != currentChapter)) {
            messageDialog.getMessageTextBox()->setText("Error: Chapters in the same textbook that have duplicate chapter numbers cannot be added. Change this chapter's chapter number so that it doesn't share its chapter number with any other chapters in this textbook.");
            messageDialog.show();
            return;
        }
    }

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

    //editChapterForm->hide();
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

    if(editChapterForm->getSectionsListView()->currentIndex().row() == -1){
        messageDialog.getMessageTextBox()->setText("No Item Selected");
        messageDialog.show();
        qDebug() << "no item selected";
        return;
    }

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

    editSectionForm->getSectionNumberSpinBox()->setEnabled(false);
}

void ContentInputOutputManager::on_editChapterForm_deleteSection_button() {
    /*
    qDebug() << "Are you sure?";
    */

    confirmationForm = new ConfirmationDialogWindow();
    //confirmationForm->setModal(true);
    connect_deleteSectionConfirmationForm();
    confirmationForm->getMessageTextBox()->setText("Are you sure you want to delete this section?");
    confirmationForm->show();
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

    foreach(Section *s,currentChapter->getChapterSections()) {
        if((s->getSectionNumber() == editSectionForm->getSectionNumberSpinBox()->value())
                &&
               (s != currentSection)) {
            qDebug() << "ayyyyyyy duplicate section #";
            messageDialog.getMessageTextBox()->setText("Error: Sections with duplicate section numbers cannot be added. Change this section's section number so that it doesn't share its section number with any other sections in this textbook.");
            messageDialog.show();
            return;
        }
    }

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





//Item getters for ListViews




Chapter*    ContentInputOutputManager::manageTextbooks_getSelectedChapter() {
    //if(manageTextbooksInterface->getChaptersListView()->model()->rowc;
    qDebug() << "in getselectedchapter";
    int selectedIndex = manageTextbooksInterface->getChaptersListView()->currentIndex().row();
    return manageTextbooks_getSelectedTextbook()->getChapterList().at(selectedIndex);
}
Textbook*   ContentInputOutputManager::manageTextbooks_getSelectedTextbook() {
    qDebug() << "in getselectedtextbook";
    int selectedIndex = manageTextbooksInterface->getTextbooksListView()->currentIndex().row();
    qDebug() << "got index: " << selectedIndex;
    return fakeTextbooks.at(selectedIndex);
}
Section*    ContentInputOutputManager::manageTextbooks_getSelectedSection() {
    qDebug() << "in getselectedsection";
    int selectedIndex = manageTextbooksInterface->getSectionsListView()->currentIndex().row();
    //return manageTextbooks_getSelectedChapter()->getChapterSections().at(selectedIndex);
    return currentChapter->getChapterSections().at(selectedIndex);
}
Chapter*    ContentInputOutputManager::editTextbookForm_getSelectedChapter() {
    qDebug() << "getselectedchap";
    int selectedIndex = editTextbookForm->getChaptersListView()->currentIndex().row();
    //Textbook* t = manageTextbooks_getSelectedTextbook();
    return currentTextbook->getChapterList().at(selectedIndex);
}
Section*    ContentInputOutputManager::editChapterForm_getSelectedSection() {
    qDebug() << "getselectedsect";
    int selectedIndex = editChapterForm->getSectionsListView()->currentIndex().row();
    //return editTextbookForm_getSelectedChapter()->getChapterSections().at(selectedIndex);
    return currentChapter->getChapterSections().at(selectedIndex);
}
