/* CUtpsDataObject class header
 *
 *Purpose: A CUtpsDataObject is a general object that will be sent
 *over TCP/IP sockets as JSON strings. Each of the derived classes
 *need to implement their own read and write functions to serialize them
 *as JSON objects
 *
 *
 *This is an Abstract class and cannot be instantiated
 *
 *Member functions:
 *read(&json) <- Read from a JSON object and set the class attributes to the values given in the key fields
 *write(&json) <- write to a JSON object the object's attribute values
 *
 *Traceability: NR-21 (Non-functional requirement)
 *
 */

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
