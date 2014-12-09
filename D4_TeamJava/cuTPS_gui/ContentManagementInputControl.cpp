#include "ContentManagementInputControl.h"

ContentManagementInputControl::ContentManagementInputControl()
{
}


void ContentManagementInputControl::validateUpdateContent(Textbook* text) throw(QString){
    if(text == NULL){
        throw QString("No Textbook");
    }

    if(text->getISBN() == NULL || text->getISBN().length()<1){
        throw QString("Invalid ISBN: %1").arg(text->getISBN());
    }

    if(text->getAuthor() == NULL || text->getAuthor().length()<1){
        throw QString("No author specified");
    }

    if(text->getEdition() == NULL || text->getEdition().length()<1){
        throw QString("No edition specified");
    }

    if(text->getPublisher() == NULL || text->getPublisher().length()<1){
        throw QString("No publisher Specified");
    }

    if(text->getDesc() == NULL || text->getDesc().length()<1){
        throw QString("No description specified");
    }

    if(text->getItemTitle() == NULL || text->getItemTitle().length()<1){
        throw QString("No title specified");
    }

    if(text->getCoverImageLoc() == NULL || text->getCoverImageLoc().length()<1){
        throw QString("No cover image location specified");
    }

    if(text->getPrice()<0){
        throw QString("Invalid price: %1").arg(text->getPrice());
    }

    foreach(Chapter *chapter, text->getChapterList()){
        if(chapter->getChapterNumber()<1){
            throw QString("Invalid chapter number: %1").arg(chapter->getChapterNumber());
        }

        if(chapter->getItemTitle() == NULL || chapter->getItemTitle().length()<1){
            throw QString("No title specified");
        }

        if(chapter->getPrice()<0){
            throw QString("Invalid price: %1").arg(chapter->getPrice());
        }

        foreach(Section *section, chapter->getChapterSections()){
            if(section->getSectionNumber()<1){
                throw QString("Invalid section number: %1").arg(section->getSectionNumber());
            }

            if(section->getItemTitle() == NULL || section->getItemTitle().length()<1){
                throw QString("No title specified");
            }

            if(section->getPrice()<0){
                throw QString("Invalid price: %1").arg(section->getPrice());
            }
        }
    }
}

void ContentManagementInputControl::validateDeleteContent(PurchasableItem* item) throw(QString){
    if(item == NULL){
        throw QString("No purchasable item");
    }
    if(item->getItemID() < 0){
        throw QString("Invalid itemID: ").append(item->getItemID());
    }
}
