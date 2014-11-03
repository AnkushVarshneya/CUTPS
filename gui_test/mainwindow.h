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
    CreateCourse_NullCourse,
    CreateCourse_ValidCourse,
    CreateCourse_AlreadyExists,
    CreateCourse_ExistsDiffTerm,
    CreateCourse_ExistsDiffSect

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
};

#endif // MAINWINDOW_H
