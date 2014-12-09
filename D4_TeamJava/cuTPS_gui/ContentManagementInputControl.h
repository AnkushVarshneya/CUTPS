/*Class responsible for Rule checking user inputs to check for errors.
 *
 *Used by the ContentManagementFacade for this purpose
 *
 *Traceability: SS-02-02 (Part of ContentManagement Subsystem)
 *
 */

#ifndef CONTENTMANAGEMENTINPUTCONTROL_H
#define CONTENTMANAGEMENTINPUTCONTROL_H

#include "PurchasableItem.h"

#include "Textbook.h"
#include "Chapter.h"
#include "Section.h"

#include <QDebug>

class ContentManagementInputControl
{
public:
    ContentManagementInputControl();
    void validateUpdateContent(Textbook* text) throw(QString);
    void validateDeleteContent(PurchasableItem* item) throw(QString);

};

#endif // CONTENTMANAGEMENTINPUTCONTROL_H
