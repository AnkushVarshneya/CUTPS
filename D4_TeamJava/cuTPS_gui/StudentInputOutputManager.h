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
#include <ShoppingCartWidget.h>
#include "Course.h"
#include <QPair>


class StudentInputOutputManager : public QObject
{
    Q_OBJECT
public:
    StudentInputOutputManager();

private:
    StudentInterfaceWindow                      *studentInterface;
    ShoppingManagementFacade                    *shopFacade;
    TextbookDetailsWindow                       *textbookDetailsWindow;
    ShoppingCartWidget                          *cartWidget;

    ShoppingCart                                *currentCart;
    QList<QPair <PurchasableItem*, qint32> >     currentItems;


    QListView               *listView;

    QStandardItemModel      *courseAndTextbookModel;
    QStandardItemModel      *chaptersAndSectionsModel;
    QStandardItemModel      *cartModel;
    void                    setStudentInterfaceViewModel(QAbstractItemView  *view, QStandardItemModel *model);
    void                    buildCourseAndTextbookModel();
    void                    buildTextbookAndChildrenModel();
    QList<Course*>            coursesAndContent;
    Course                   *crs1;
    Course                   *crs2;
    void                     getTerms();
    QList<Term*>             terms;

    Student                 *currentStudent;


private slots:
    void    on_studentInterface_addTextbookOptionSelected();
    void    on_studentInterface_viewDetailsOptionSelected();
    void    on_studentInterface_viewCartOptionSelected();
    void    on_studentInterface_termSelected();

    void    on_textbookDetailsWindow_closeOptionSelected();
};

#endif // STUDENTINPUTOUTPUTMANAGER_H
