/*Purpose: Provide a window to edit a section. A form to fill out section information
 *Is presented.
 *
 *Traceability: SS-02-01 (Part of Content Manager Interface Subsystem)
 */
#ifndef CREATESECTIONFORMWINDOW_H
#define CREATESECTIONFORMWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>

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

    QPushButton* getBackButton();
    QPushButton* getCreateButton();

    QLineEdit*      getTitleTextbox();
    QSpinBox*       getSectionNumberSpinBox();
    QDoubleSpinBox* getPriceSpinBox();
    QCheckBox*      getAvailabilityCheckBox();

private:
    Ui::EditSectionFormWindow *ui;
};

#endif // CREATESECTIONFORMWINDOW_H
