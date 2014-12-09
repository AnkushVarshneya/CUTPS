/*
 *A Confirmation Dialog window that displays the message text for a given situation
 *
 *Traceability: NR-05
 */
#ifndef CONFIRMATIONDIALOGWINDOW_H
#define CONFIRMATIONDIALOGWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>

namespace Ui {
class ConfirmationDialogWindow;
}

class ConfirmationDialogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmationDialogWindow(QWidget *parent = 0);
    ~ConfirmationDialogWindow();

    QPushButton*    getYesButton();
    QPushButton*    getNoButton();

    QTextEdit*      getMessageTextBox();

private:
    Ui::ConfirmationDialogWindow *ui;
};

#endif // CONFIRMATIONDIALOGWINDOW_H
