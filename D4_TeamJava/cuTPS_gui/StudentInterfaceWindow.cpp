#include "StudentInterfaceWindow.h"
#include "ui_StudentInterfaceWindow.h"
#include <QDebug>

#include <QPixmap>
#include <QIcon>

StudentInterfaceWindow::StudentInterfaceWindow(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentInterfaceWindow)
{
    ui->setupUi(this);

    shopView = new StudentShopView(this);
    this->setCentralWidget(shopView);
    dock = new QDockWidget(tr("Textbook"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    dock->hide();

    connect(dock, SIGNAL(visibilityChanged(bool)), this, SLOT(shrink()));

}

StudentInterfaceWindow::~StudentInterfaceWindow()
{
    delete ui;
}

//getters
//QPushButton*    StudentInterfaceWindow::getAddTextbookOption() { return ui->addTextbookToCartOption; }
//QPushButton*    StudentInterfaceWindow::getViewDetailsOption() {return ui->viewDetailsOption; }
//QPushButton*    StudentInterfaceWindow::getViewCartOption() { return ui->viewShoppingCartOption; }
//QComboBox*      StudentInterfaceWindow::getTermSelectOption() { return ui->termSelectOption;  }
//QSpinBox*       StudentInterfaceWindow::getQuantityOption() { return ui->quantityOption; }
//QListView*      StudentInterfaceWindow::getCourseView() {return ui->itemsListView; }

QPushButton*    StudentInterfaceWindow::getAddTextbookOption() { return shopView->getAddTextbookOption(); }
QPushButton*    StudentInterfaceWindow::getViewDetailsOption() {return shopView->getViewDetailsOption(); }
QPushButton*    StudentInterfaceWindow::getViewCartOption() { return shopView->getViewCartOption() ;}
QComboBox*      StudentInterfaceWindow::getTermSelectOption() { return shopView->getTermSelectOption();  }
QSpinBox*       StudentInterfaceWindow::getQuantityOption() { return shopView->getQuantityOption(); }
QListView*      StudentInterfaceWindow::getCourseView() {return shopView->getCourseView(); }


//make a dock window for a textbook
void StudentInterfaceWindow::createDockWindow(QWidget *widget)
{

    dock->setWidget(widget);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setVisible(true);

}


void StudentInterfaceWindow::shrink()
{
    //this->resize( this->minimumSize() );
    qDebug() << "dockwidg visible? " << dock->isVisible();
    qDebug() << "dockwidg ? " << dock->isHidden();
    qDebug() << "dockw is min? " << dock->isMinimized();
    qDebug() << "dockw is float?" << dock->isFloating();

    //if its hidden, destroy it?
    if (!dock->isVisible())
    {
    this->resize(this->minimumSize());
    } else this->resize(this->sizeHint());

    //if ( dock->isMinimized() || dock->isHidden() ) { this->resize(this->sizeHint()); }
}




















