#ifndef CREATETEXTBOOKFORMWINDOW_H
#define CREATETEXTBOOKFORMWINDOW_H

#include <QWidget>
#include "EditChapterFormWindow.h"

#include "Textbook.h"
#include "Chapter.h"

#include <QPushButton>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QTextEdit>
#include <QListView>

class ManageTextbooksInterfaceWindow;

namespace Ui {
class EditTextbookFormWindow;
}

class EditTextbookFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditTextbookFormWindow(QWidget *parent = 0);
    ~EditTextbookFormWindow();

    Ui::EditTextbookFormWindow *getUI();

    QPushButton* getBackButton();
    QPushButton* getViewEditChaptersButton();
    QPushButton* getAddChapterButton();
    QPushButton* getCreateButton();
    QPushButton* getDeleteChapterButton();

    QLineEdit*      getTitleTextbox();
    QLineEdit*      getAuthorTextbox();
    QLineEdit*      getEditionTextbox();
    QLineEdit*      getPublisherTextbox();
    QLineEdit*      getISBNTextbox();
    QLineEdit*      getCoverImageTextbox();
    QDoubleSpinBox* getPriceSpinBox();
    QCheckBox*      getAvailabilityCheckBox();
    QTextEdit*      getDescriptionTextbox();

    QListView*      getChaptersListView();



private:
    Ui::EditTextbookFormWindow *ui;
    EditChapterFormWindow editChapterForm;
};

#endif // CREATETEXTBOOKFORMWINDOW_H
