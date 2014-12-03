#ifndef CREATESECTIONFORMWINDOW_H
#define CREATESECTIONFORMWINDOW_H

#include <QWidget>

class EditChapterFormWindow;

namespace Ui {
class EditSectionFormWindow;
}

class EditSectionFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditSectionFormWindow(QWidget *parent = 0);
    ~EditSectionFormWindow();


    EditChapterFormWindow *parentWindow;

private slots:
    void on_backButton_clicked();

private:
    Ui::EditSectionFormWindow *ui;
};

#endif // CREATESECTIONFORMWINDOW_H
