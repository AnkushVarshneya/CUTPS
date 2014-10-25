#ifndef TERM_H
#define TERM_H

#include <QString>

class Term{
public:
private:
    QString startDate;
    QString endDate;
    QList<Course*> courses;
};

#endif // TERM_H
