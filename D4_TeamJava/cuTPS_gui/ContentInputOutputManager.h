#ifndef CONTENTINPUTOUTPUTMANAGER_H
#define CONTENTINPUTOUTPUTMANAGER_H

//#include "ContentManagerInterfaceWindow.h"
#include "CreateChapterFormWindow.h"
#include "CreateSectionFormWindow.h"
#include "CreateTextbookFormWindow.h"
#include "ManageTextbooksInterfaceWindow.h"



class ContentInputOutputManager : public QObject
{
    Q_OBJECT
public:
    ContentInputOutputManager();

private slots:
    void on_textbook_back_button();
    void on_textbook_viewEditChapters_button();
    void on_textbook_create_button();
    void on_textbook_addChapter_button();

private:
    CreateTextbookFormWindow* createTextbookForm;
    CreateChapterFormWindow* createChapterForm;
    CreateSectionFormWindow* createSectionForm;


};

#endif // CONTENTINPUTOUTPUTMANAGER_H
