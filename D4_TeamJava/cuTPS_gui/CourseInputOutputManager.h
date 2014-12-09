#ifndef COURSEINPUTOUTPUTMANAGER_H
#define COURSEINPUTOUTPUTMANAGER_H

#include "ManageCoursesInterfaceWindow.h"
#include "CourseManagementFacade.h"
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


private:
    ManageCoursesInterfaceWindow* manageCoursesInterface;
    CourseManagementFacade*       courseManagementFacade;

    void    connect_manageCoursesInterface();
};

#endif // COURSEINPUTOUTPUTMANAGER_H
