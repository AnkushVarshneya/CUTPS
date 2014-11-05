#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QWidget>

#include <QString>

#include "connectionmanager.h"
#include "cuTPSTestAPIControl.h"

namespace Ui {
class MainWindow;

}

enum Selected {

    StudentViewShoppingCart_hasitems,
    StudentViewShoppingCart_noitems,
    StudentViewShoppingCart_studentnotfound,

    ContentManagerCreateCourse_NullCourse,
    ContentManagerCreateCourse_ValidCourse,
    ContentManagerCreateCourse_AlreadyExists,
    ContentManagerCreateCourse_ExistsDiffTerm,
    ContentManagerCreateCourse_ExistsDiffSect,

    StudentViewTextbooks_unenrolled,
    StudentViewTextbooks_notextbooks,
    StudentViewTextbooks_hastextbooks,
    StudentViewTextbooks_studentnotfound,
    StudentViewTextbooks_termnotfound,

    ContentManagerCreateTextbook_textbookexists,
    ContentManagerCreateTextbook_nulltextbook,
    ContentManagerCreateTextbook_withchaptersandsections,

    ContentManagerLinkTextbook_alreadylinked,
    ContentManagerLinkTextbook_nulltextbook,
    ContentManagerLinkTextbook_nullcourse,
    ContentManagerLinkTextbook_validlink

};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    cuTPSTestAPIControl* getControl();

private:

    QStatusBar *statusBar;
    Ui::MainWindow *ui;
    QTcpSocket *tcpConnection;
    QNetworkSession *networkSession;
    void connectTcp();

    Selected behaviour;
    cuTPSTestAPIControl* control;

    void update_pass(QString);
    void update_fail(QString);


private slots:
    //void displayError(QAbstractSocket::SocketError socketError);


    void on_actionStudent_ViewShoppingCart_hasitems_triggered();
    void on_actionStudent_ViewShoppingCart_noitems_triggered();
    void on_actionStudent_ViewTextbooks_unenrolled_triggered();
    void on_actionStudent_ViewTextbooks_notextbooks_triggered();
    void on_actionStudent_ViewTextbooks_hastextbooks_triggered();
    void on_actionStudent_ViewTextbooks_studentnotfound_triggered();
    void on_actionStudent_ViewTextbooks_termnotfound_triggered();
    void on_actionContentManager_CreateCourse_nullcourse_triggered();
    void on_actionContentManager_CreateCourse_validcourse_triggered();
    void on_actionContentManager_CreateCourse_coursealreadyexists_triggered();
    void on_actionContentManager_CreateCourse_existsdiffterm_triggered();
    void on_actionContentManager_CreateCourse_existsdiffsection_triggered();
    void on_actionContentManager_CreateTextbook_textbookexists_triggered();
    void on_actionContentManager_CreateTextbook_nulltextbook_triggered();


    void on_pushButton_clicked();
    void on_actionContentManager_CreateTextbook_withchaptersandsections_triggered();
    void on_actionContentManager_LinkTextbook_alreadylinked_triggered();
    void on_actionContentManager_LinkTextbook_nulltextbook_triggered();
    void on_actionContentManager_LinkTextbook_nullcourse_triggered();
    void on_actionContentManager_LinkTextbook_validlink_triggered();
    void on_actionContentManager_ViewTextbooksByTerm_notextbooks_triggered();
    void on_actionContentManager_ViewTextbooksByTerm_hastextbooks_triggered();
    void on_actionContentManager_ViewCourses_nocourses_triggered();
    void on_actionContentManager_ViewCourses_hascourses_triggered();
    void on_actionStudent_ViewShoppingCart_studentnotfound_triggered();
};

#endif // MAINWINDOW_H
