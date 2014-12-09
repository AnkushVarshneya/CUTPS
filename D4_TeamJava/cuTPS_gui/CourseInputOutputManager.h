#ifndef COURSEINPUTOUTPUTMANAGER_H
#define COURSEINPUTOUTPUTMANAGER_H

#include "ManageCoursesInterfaceWindow.h"
#include "CourseManagementFacade.h"
#include "ModifyCourseFormWindow.h"
#include "LinkTextbookFormWindow.h"

#include "ConfirmationDialogWindow.h"

#include <QAbstractItemView>
#include "OurStandardItem.h"

class CourseInputOutputManager : public QObject
{
    Q_OBJECT
public:
    CourseInputOutputManager();

private slots:
    void on_manageCoursesInterface_back_button();
    void on_manageCoursesInterface_createCourse_button();
    void on_manageCoursesInterface_editCourse_button();
    void on_manageCoursesInterface_deleteCourse_button();
    void on_manageCoursesInterface_termSelected();

    void on_manageCoursesInterface_selectCourse();

    void on_editCourseForm_backButton();
    void on_editCourseForm_createButton();
    void on_editCourseForm_linkTextbookButton();

    void on_linkTextbookForm_backButton();
    void on_linkTextbookForm_linkTextbookButton();
    void on_linkTextbookForm_selectTextbook();
    void on_linkTextbookForm_selectRegisteredTextbook();

    void on_deleteCourseConfirmationForm_yesButton();
    void on_deleteCourseConfirmationForm_noButton();
private:
    ManageCoursesInterfaceWindow* manageCoursesInterface;
    ModifyCourseFormWindow*       editCourseForm;
    LinkTextbookFormWindow*       linkTextbookForm;

    ConfirmationDialogWindow*     confirmationForm;

    CourseManagementFacade*       courseManagementFacade;

    QStandardItemModel*           courseModel;
    QStandardItemModel*           textbookModel;
    QStandardItemModel*           linkedTextbookModel;

    QList<Course*>*               courses;
    QList<Textbook*>*             assignedTextbooks;

    QList<Textbook*>*             fakeTextbooks;
    QList<Textbook*>*             fakeLinkedTextbooks;
    QList<Course*>*               fakeCourses;
    QList<Term*>*                 fakeTerms;

    Term*                         selectedTerm;
    Course*                       selectedCourse;


    //0: Create
    //1: Edit
    int                           createOrEditCFlag;

    void        setCourseManagementInterfaceViewModel(QAbstractItemView*, QStandardItemModel*);

    void        buildCourseModel();
    void        buildTextbookModel();
    void        buildLinkedTextbookModel();
    void        populateTermComboBox(QComboBox*);

    Course*     editCourses_getSelectedCourse();

    Textbook*   linkTextbookForm_getSelectedTextbook();


    void    connect_manageCoursesInterface();
    void    connect_editCourseForm();
    void    connect_linkTextbookForm();

    void    connect_deleteCourseConfirmationForm();
};

#endif // COURSEINPUTOUTPUTMANAGER_H
