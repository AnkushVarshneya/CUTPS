#ifndef CREATESECTIONFORMWINDOW_H
#define CREATESECTIONFORMWINDOW_H

#include <QWidget>

class CreateChapterFormWindow;

namespace Ui {
class CreateSectionFormWindow;
}

class CreateSectionFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreateSectionFormWindow(QWidget *parent = 0);
    ~CreateSectionFormWindow();


    CreateChapterFormWindow *parentWindow;

private slots:
    void on_backButton_clicked();

private:
    Ui::CreateSectionFormWindow *ui;
};

#endif // CREATESECTIONFORMWINDOW_H
