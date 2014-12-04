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

class ContentManagementFacade
{
public:
    ContentManagementFacade();
private:
    ContentManagementInputControl inputControl;
    ContentManagementUpdateControl updateControl;
};

#endif // CONTENTMANAGEMENTFACADE_H
