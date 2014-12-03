/*The input output mediator for the Student interface for all its boundary objects accross all windows and forms for the Student Interface
 *
 *Traceability: SS-01-01 (Part of Student Interface subsystem)
 *
 *
 */
#ifndef STUDENTINPUTOUTPUTMANAGER_H
#define STUDENTINPUTOUTPUTMANAGER_H

#include <QObject>
#include "StudentInterfaceWindow.h"
#include "ShoppingManagementFacade.h"
#include "OurStandardItem.h"

class StudentInputOutputManager : public QObject
{
    Q_OBJECT
public:
    StudentInputOutputManager();

private:
    StudentInterfaceWindow  *studentInterface;
    ShoppingManagementFacade *shopFacade;

    QList<Course*>            fakeCourses;
    Course                   *crs1;
    Course                   *crs2;


private slots:
    void    on_studentInterface_addTextbookOptionSelected();
    void    on_studentInterface_viewDetailsOptionSelected();
    void    on_studentInterface_viewCartOptionSelected();
    void    on_studentInterface_termSelected();
};

#endif // STUDENTINPUTOUTPUTMANAGER_H
