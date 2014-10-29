#ifndef CUTPSDATAOBJECT_H
#define CUTPSDATAOBJECT_H


#include <QDataStream>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

class CUtpsDataObject
{


public:
    virtual void read(const QJsonObject &json) = 0;
    virtual void write(QJsonObject &json) const = 0;

};


#endif // CUTPSDATAOBJECT_H
