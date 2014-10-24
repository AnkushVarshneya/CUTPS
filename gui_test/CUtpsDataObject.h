#ifndef CUTPSDATAOBJECT_H
#define CUTPSDATAOBJECT_H

#include <QObject>
#include <QDataStream>

class CUtpsDataObject : public QObject
{
    Q_OBJECT

public:
    void insertToDataStream(QDataStream& dataStream);

};


#endif // CUTPSDATAOBJECT_H
