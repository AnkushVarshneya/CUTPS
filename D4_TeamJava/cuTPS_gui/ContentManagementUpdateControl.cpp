#include "ContentManagementUpdateControl.h"

ContentManagementUpdateControl::ContentManagementUpdateControl()
{
}

QList<Textbook*>* ContentManagementUpdateControl::retrieveAllContent(){
  return clientComm.retrieveAllContent();
}

bool ContentManagementUpdateControl::updateContent(Textbook* text){
    return clientComm.updateContent(text);
}
