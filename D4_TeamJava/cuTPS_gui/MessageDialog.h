/*Provide a message dialog with some text for the user (used in error handling)
 *
 *Traceability: NR-05 (Error messages will be descriptive and suggest proper solutions)
 *
 */
#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>
#include <QTextEdit>

namespace Ui {
class MessageDialog;
}

class MessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MessageDialog(QWidget *parent = 0);
    ~MessageDialog();

    QTextEdit*  getMessageTextBox();

private:
    Ui::MessageDialog *ui;
};

#endif // MESSAGEDIALOG_H
