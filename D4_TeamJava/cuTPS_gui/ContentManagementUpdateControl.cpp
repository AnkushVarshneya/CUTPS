#include "ContentManagementUpdateControl.h"

ContentManagementUpdateControl::ContentManagementUpdateControl()
{
}

QList<Textbook*>* ContentManagementUpdateControl::retrieveAllContent(){
  return clientComm.retrieveAllContent();
}
