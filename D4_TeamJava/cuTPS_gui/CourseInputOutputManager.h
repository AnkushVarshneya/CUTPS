#ifndef COURSEINPUTOUTPUTMANAGER_H
#define COURSEINPUTOUTPUTMANAGER_H

#include "ManageCoursesInterfaceWindow.h"
#include "CourseManagementFacade.h"
#include "ModifyCourseFormWindow.h"
#include "LinkStudentFormWindow.h"
#include "LinkTextbookFormWindow.h"

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
    void on_manageCoursesInterface_enrollStudent_button();
    void on_manageCoursesInterface_assignTextbook_button();

    void on_manageCoursesInterface_selectCourse();

    void on_editCourseForm_backButton();
    void on_editCourseForm_createButton();
    void on_editCourseForm_enrollButton();
    void on_editCourseForm_linkTextbookButton();

    void on_linkTextbookForm_backButton();
    void on_linkTextbookForm_linkTextbookButton();
    void on_linkTextbookForm_selectTextbook();
    void on_linkTextbookForm_selectRegisteredTextbook();
private:
    ManageCoursesInterfaceWindow* manageCoursesInterface;
    ModifyCourseFormWindow*       editCourseForm;
    LinkStudentFormWindow*        linkStudentForm;
    LinkTextbookFormWindow*       linkTextbookForm;
    CourseManagementFacade*       courseManagementFacade;

    QStandardItemModel*           courseModel;
    QStandardItemModel*           studentModel;
    QStandardItemModel*           textbookModel;

    QList<Course*>*               courses;
    QList<Textbook*>*             assignedTextbooks;
    QList<Student*>*              registeredStudents;

    QList<Textbook*>*             allTextbooks;
    QList<Student*>*              allStudents;

    void        setCourseManagementInterfaceViewModel(QAbstractItemView*, QStandardItemModel*);

    void        buildCourseModel();
    void        buildStudentModel();
    void        buildSectionModel();

    void        enrollStudentForm_buildStudentModel();

    Course*     editCourses_getSelectedCourse();

    Student*    enrollStudentForm_getSelectedStudent();

    Textbook*   linkTextbookForm_getSelectedTextbook();


    void    connect_manageCoursesInterface();
    void    connect_editCourseForm();
    void    connect_linkTextbookForm();
};

#endif // COURSEINPUTOUTPUTMANAGER_H
