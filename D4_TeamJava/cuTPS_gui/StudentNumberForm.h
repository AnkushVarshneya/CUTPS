#ifndef STUDENTNUMBERFORM_H
#define STUDENTNUMBERFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class StudentNumberForm;
}

class StudentNumberForm : public QWidget
{
    Q_OBJECT

public:
    explicit StudentNumberForm(QWidget *parent = 0);
    ~StudentNumberForm();

    QPushButton*    getOkButton();
    QPushButton*    getCancelButton();
    QLineEdit*      getStudentNumberTextBox();

private:
    Ui::StudentNumberForm *ui;
};

#endif // STUDENTNUMBERFORM_H
