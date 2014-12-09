#include "ContentManagementUpdateControl.h"

//Constructor
ContentManagementUpdateControl::ContentManagementUpdateControl()
{
    clientComm = ClientCommunicatorManagementControl::getInstance();
}

//Retrieves all content saved in storage
QList<Textbook*>* ContentManagementUpdateControl::retrieveAllContent(){
  return clientComm->retrieveAllContent();
}

//Updates the information for the content
bool ContentManagementUpdateControl::updateContent(Textbook* text){
    qDebug() << "here";
    return clientComm->updateContent(text);
}

//Deletes the content from storage
bool ContentManagementUpdateControl::deleteContent(PurchasableItem* item){
    return clientComm->deleteContent(item);
}
