
#include "Section.h"

Section::Section()
{

}

Section::Section(QString a)
{
    setTitle(a);
}

Section::~Section()
{

}

QString Section::getSectionTitle()
{
    return title;
}

void Section::setTitle(QString a)
{
    title = a;
}
