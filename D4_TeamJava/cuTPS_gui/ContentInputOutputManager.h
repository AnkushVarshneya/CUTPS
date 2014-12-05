#ifndef CONTENTINPUTOUTPUTMANAGER_H
#define CONTENTINPUTOUTPUTMANAGER_H

#include "EditChapterFormWindow.h"
#include "EditSectionFormWindow.h"
#include "EditTextbookFormWindow.h"
#include "ManageTextbooksInterfaceWindow.h"

#include "OurStandardItem.h"
#include <QAbstractItemView>

#include "ContentManagementFacade.h"


class ContentInputOutputManager : public QObject
{
    Q_OBJECT
public:
    ContentInputOutputManager();

private slots:




    void on_manageTextbooksInterface_back_button();
    void on_manageTextbooksInterface_createTextbook_button();
    void on_manageTextbooksInterface_editTextbook_button();
    void on_manageTextbooksInterface_deleteTextbook_button();

    void on_editTextbookForm_back_button();
    void on_editTextbookForm_create_button();
    void on_editTextbookForm_editChapter_button();
    void on_editTextbookForm_createChapter_button();

    void on_editChapterForm_back_button();
    void on_editChapterForm_editSection_button();
    void on_editChapterForm_create_button();
    void on_editChapterForm_createSection_button();

    void on_editSectionForm_back_button();
    void on_editSectionForm_create_button();

    void on_manageTextbooksInterface_selectTextbook();
    void on_manageTextbooksInterface_selectChapter();




private:
    ManageTextbooksInterfaceWindow*     manageTextbooksInterface;
    EditTextbookFormWindow*             editTextbookForm;
    EditChapterFormWindow*              editChapterForm;
    EditSectionFormWindow*              editSectionForm;

    ContentManagementFacade*            contentManagementFacade;

    QStandardItemModel*                 textbookModel;
    QStandardItemModel*                 chapterModel;
    QStandardItemModel*                 sectionModel;

    QList<Textbook*>                    fakeTextbooks;
    QList<Chapter*>                     fakeChapters;
    QList<Section*>                     fakeSections;

    void setContentManagementInterfaceViewModel(QAbstractItemView*, QStandardItemModel*);

    void buildTextbookModel();
    void buildChapterModel();
    void buildSectionModel();

    Textbook*   getSelectedTextbook();
    Chapter*    getSelectedChapter();
    Section*    getSelectedSection();

};

#endif // CONTENTINPUTOUTPUTMANAGER_H
