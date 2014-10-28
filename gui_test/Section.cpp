
#include "Section.h"


QString Section::getSectionTitle() {
    return title;
}

void Section::setTitle(QString a) {
    title = a;
}

QString Section::getItemTitle(){
    return getSectionTitle();
}
