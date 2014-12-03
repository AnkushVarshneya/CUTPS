#ifndef CONTENTINPUTOUTPUTMANAGER_H
#define CONTENTINPUTOUTPUTMANAGER_H

//#include "ContentManagerInterfaceWindow.h"
#include "EditChapterFormWindow.h"
#include "EditSectionFormWindow.h"
#include "EditTextbookFormWindow.h"
#include "ManageTextbooksInterfaceWindow.h"

class MainInputOutputManager;



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




private:
    ManageTextbooksInterfaceWindow*     manageTextbooksInterface;
    EditTextbookFormWindow*           editTextbookForm;
    EditChapterFormWindow*            editChapterForm;
    EditSectionFormWindow*            editSectionForm;


};

#endif // CONTENTINPUTOUTPUTMANAGER_H
