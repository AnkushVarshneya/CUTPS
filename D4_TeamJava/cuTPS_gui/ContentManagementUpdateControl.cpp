#include "ContentManagementUpdateControl.h"

ContentManagementUpdateControl::ContentManagementUpdateControl()
{
    clientComm = ClientCommunicatorManagementControl::getInstance();
}

QList<Textbook*>* ContentManagementUpdateControl::retrieveAllContent(){
  return clientComm->retrieveAllContent();
}

bool ContentManagementUpdateControl::updateContent(Textbook* text){
    qDebug() << "here";
    return clientComm->updateContent(text);
}

bool ContentManagementUpdateControl::deleteContent(PurchasableItem* item){
    return clientComm->deleteContent(item);
}
