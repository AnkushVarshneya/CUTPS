/*
 *Traceability: SS-02-02 (Part of Content Management Subsystem)
 */
#ifndef CONTENTMANAGEMENTUPDATECONTROL_H
#define CONTENTMANAGEMENTUPDATECONTROL_H

#include "ClientCommunicatorManagementControl.h"
class ContentManagementUpdateControl
{
public:
    ContentManagementUpdateControl();
    QList<Textbook*>* retrieveAllContent();
    bool        updateContent(Textbook*);
    bool        deleteContent(PurchasableItem*);
private:
    ClientCommunicatorManagementControl clientComm;
};

#endif // CONTENTMANAGEMENTUPDATECONTROL_H
