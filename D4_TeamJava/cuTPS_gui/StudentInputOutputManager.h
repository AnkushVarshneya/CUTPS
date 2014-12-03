/*The input output mediator for the Student interface for all its boundary objects accross all windows and forms for the Student Interface
 *
 *Traceability: SS-01-01 (Part of Student Interface subsystem)
 *
 *
 */
#ifndef STUDENTINPUTOUTPUTMANAGER_H
#define STUDENTINPUTOUTPUTMANAGER_H

#include <QObject>

class StudentInputOutputManager : public QObject
{
    Q_OBJECT
public:
    StudentInputOutputManager();
};

#endif // STUDENTINPUTOUTPUTMANAGER_H
