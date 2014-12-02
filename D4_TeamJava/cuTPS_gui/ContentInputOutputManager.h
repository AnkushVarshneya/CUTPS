#ifndef CONTENTINPUTOUTPUTMANAGER_H
#define CONTENTINPUTOUTPUTMANAGER_H

#include "ContentManagerInterfaceWindow.h"
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


private:
    ContentManagerInterfaceWindow* cm_interface_window;
    CreateChapterFormWindow* create_chapter_form_window;


};

#endif // CONTENTINPUTOUTPUTMANAGER_H
