#ifndef CREATECHAPTERFORMWINDOW_H
#define CREATECHAPTERFORMWINDOW_H

#include <QWidget>

namespace Ui {
class CreateChapterFormWindow;
}

class CreateChapterFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreateChapterFormWindow(QWidget *parent = 0);
    ~CreateChapterFormWindow();

private:
    Ui::CreateChapterFormWindow *ui;
};

#endif // CREATECHAPTERFORMWINDOW_H
