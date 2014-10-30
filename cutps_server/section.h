/*Section header class
 *Date last modified: 24/10/2014
 */
#ifndef SECTION_H
#define SECTION_H

#include <QString>
#include "PurchasableItem.h"
using namespace std;

class Section : public PurchasableItem{
public:

    Section(QString = "",qint32 = 0,
            qint32 = 0, float = 0, bool = false);

    ~Section();

    QString     getItemTitle();
    qint32      getSectionNumber();

    void        setItemTitle(QString);
    void        setSectionNumber(qint32);

    void        read(const QJsonObject &json);
    void        write(QJsonObject &json) const;

private:
    QString     title;
    qint32      sectionNumber;
};

std::ostream& operator<<(std::ostream&,  Section&);

#endif // SECTION_H
