#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "Course.h"
#include "PaymentInformation.h"
#include "Term.h"
#include "Textbook.h"
#include "Chapter.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    Ui::Login *ui;
    QList<Course*>& studentViewTextbooks(QString, qint32) const;
    PaymentInformation& getExistingBillingInfo(QString) const;
    bool saveBillingInformation(const QString, PaymentInformation*);

    bool createTextbook(Textbook*);
    bool createCourse(Course*, qint32);
    bool linkTextbook(Textbook*, Course*, qint32);
    QList<Textbook*>& viewAllTextbooks(qint32);
    QList<Course*>& viewCourses(qint32);

};

#endif // LOGIN_H
