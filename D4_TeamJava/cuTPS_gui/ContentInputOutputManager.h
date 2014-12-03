#ifndef CONTENTINPUTOUTPUTMANAGER_H
#define CONTENTINPUTOUTPUTMANAGER_H

//#include "ContentManagerInterfaceWindow.h"
#include "EditChapterFormWindow.h"
#include "EditSectionFormWindow.h"
#include "EditTextbookFormWindow.h"
#include "ManageTextbooksInterfaceWindow.h"



class ContentInputOutputManager : public QObject
{
    Q_OBJECT
public:
    ContentInputOutputManager();

private slots:
    void on_editTextbookForm_back_button();
    void on_editTextbookForm_viewEditChapters_button();
    void on_editTextbookForm_create_button();
    void on_editTextbookForm_addChapter_button();

    void on_manageTextbooksInterface_back_button();
    void on_manageTextbooksInterface_editTextbook_button();
    void on_manageTextbooksInterface_modifyTextbook_button();
    void on_manageTextbooksInterface_deleteTextbook_button();




private:
    ManageTextbooksInterfaceWindow*     manageTextbooksInterface;
    EditTextbookFormWindow*           editTextbookForm;
    EditChapterFormWindow*            editChapterForm;
    EditSectionFormWindow*            editSectionForm;


};

#endif // CONTENTINPUTOUTPUTMANAGER_H
