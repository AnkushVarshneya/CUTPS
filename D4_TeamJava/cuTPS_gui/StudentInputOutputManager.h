/*The input output mediator for the Student interface for all its boundary objects accross all windows and forms for the Student Interface
 *
 *Traceability: SS-01-01 (Part of Student Interface subsystem)
 *
 *
 */
#ifndef STUDENTINPUTOUTPUTMANAGER_H
#define STUDENTINPUTOUTPUTMANAGER_H

#include <QObject>
#include "TextbookDetailsWindow.h"
#include "StudentInterfaceWindow.h"
#include "ShoppingManagementFacade.h"
#include "OurStandardItem.h"
#include <QAbstractItemView>
#include "Course.h"


class StudentInputOutputManager : public QObject
{
    Q_OBJECT
public:
    StudentInputOutputManager();

private:
    StudentInterfaceWindow  *studentInterface;
    ShoppingManagementFacade *shopFacade;
    TextbookDetailsWindow   *textbookDetailsWindow;

    QStandardItemModel      *courseAndTextbookModel;
    QStandardItemModel      *chaptersAndSectionsModel;
    void                    setStudentInterfaceViewModel(QAbstractItemView  *view, QStandardItemModel *model);
    void                    buildCourseAndTextbookModel();
    void                    buildTextbookAndChildrenModel();
    QList<Course*>            fakeCourses;
    Course                   *crs1;
    Course                   *crs2;
    void                     getTerms();
    QList<Term*>             terms;
    Student                 *fakeStudent;


private slots:
    void    on_studentInterface_addTextbookOptionSelected();
    void    on_studentInterface_viewDetailsOptionSelected();
    void    on_studentInterface_viewCartOptionSelected();
    void    on_studentInterface_termSelected();
    //QList<Course*>          fakeViewContent(Student *student, Term *term);
};

#endif // STUDENTINPUTOUTPUTMANAGER_H
