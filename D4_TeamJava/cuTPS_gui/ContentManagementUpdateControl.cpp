#include "ContentManagementUpdateControl.h"
#include "MessageDialog.h"
//Constructor
ContentManagementUpdateControl::ContentManagementUpdateControl()
{
    clientComm = ClientCommunicatorManagementControl::getInstance();
}

//Retrieves all content saved in storage
QList<Textbook*>* ContentManagementUpdateControl::retrieveAllContent() throw (QString){
    return clientComm->retrieveAllContent();
}

//Updates the information for the content
bool ContentManagementUpdateControl::updateContent(Textbook* text) throw (QString){
    return clientComm->updateContent(text);
}

//Deletes the content from storage
bool ContentManagementUpdateControl::deleteContent(PurchasableItem* item) throw (QString){
    return clientComm->deleteContent(item);
}
