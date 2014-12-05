#include "ShopUpdateControl.h"

ShopUpdateControl::ShopUpdateControl()
{
}

QList<Term*>* ShopUpdateControl::retrieveAllTerms(){
    return mc.retrieveAllTerms();
}

QList<Course*>* ShopUpdateControl::retrieveContent(Student *stu, Term *term){
    return mc.retrieveContent(stu,term);
}
