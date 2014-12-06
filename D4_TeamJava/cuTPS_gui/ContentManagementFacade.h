/*Class responsible for providing an interface for the Content Manager Interface to manage content
 *such as textbooks, chapters, and chapter sections. Interface includes functions like creating, modifying, and deleting
 *this content
 *
 *
 *Traceability: SS-02-02 (Part of Content Management Subsystem)
 *
 */
#ifndef CONTENTMANAGEMENTFACADE_H
#define CONTENTMANAGEMENTFACADE_H
#include "ContentManagementInputControl.h"
#include "ContentManagementUpdateControl.h"

#include "PurchasableItem.h"

#include "Textbook.h"
#include "Chapter.h"
#include "Section.h"

#include <QDebug>
#include <QList>

class ContentManagementFacade
{
public:
    ContentManagementFacade();
    QList<Textbook*>    viewAllContent();
    /*
    bool                createTextbook(Textbook*);
    bool                modifyTextbook(Textbook*);
    bool                modifyContentAvailability(PurchasableItem*, bool);
    bool                modifyContentPrices(PurchasableItem*,int);
    bool                modifyContentBasicInfo(PurchasableItem*);
    bool                deleteContent(PurchasableItem*);
    */

private:
    QList<Textbook*>                fakeTextbooks;
    ContentManagementInputControl   inputControl;
    ContentManagementUpdateControl  updateControl;
};

#endif // CONTENTMANAGEMENTFACADE_H
