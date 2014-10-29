
#include "Section.h"

Section::Section(){}

QString Section::getSectionTitle() {
    return title;
}

void Section::setTitle(QString a) {
    title = a;
}

void Section::setItemTitle(QString a){
    setSectionTitle(a);
}

void Section::setSectionTitle(QString a){
    title = a;
}

QString Section::getItemTitle(){
    return getSectionTitle();
}
