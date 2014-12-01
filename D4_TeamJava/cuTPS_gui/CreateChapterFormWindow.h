#ifndef CREATECHAPTERFORMWINDOW_H
#define CREATECHAPTERFORMWINDOW_H

#include <QWidget>
#include "CreateSectionFormWindow.h"

class CreateTextbookFormWindow;

namespace Ui {
class CreateChapterFormWindow;
}

class CreateChapterFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreateChapterFormWindow(QWidget *parent = 0);
    ~CreateChapterFormWindow();

    CreateTextbookFormWindow *parentWindow;

private slots:

    void on_viewEditSectionButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::CreateChapterFormWindow *ui;
    CreateSectionFormWindow createSectionForm;
};

#endif // CREATECHAPTERFORMWINDOW_H
