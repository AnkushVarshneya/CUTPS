#include "ServerListenerControl.h"

ServerListenerControl::ServerListenerControl()
{
}


ServerListenerControl* ServerListenerControl::instance = 0;

QJsonObject ServerListenerControl::processCommand(QJsonObject){

}

ServerListenerControl* ServerListenerControl::getInstance(){
    if (instance == 0){
        instace = new ServerListenerControl();
    }
    return instance;
}
