#include "ShopUpdateControl.h"

ShopUpdateControl::ShopUpdateControl()
{
}

QList<Term*>* ShopUpdateControl::retrieveAllTerms(){
    return mc.retrieveAllTerms();
}
