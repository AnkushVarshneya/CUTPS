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

    //this->resize(this->sizeHint());
     this->resize(shopView->frameSize());

    createStatusBar();
    this->statusBar()->setSizeGripEnabled(false);

//    dock = new QDockWidget(tr("Textbook"), this);
//    dock->setAllowedAreas(Qt::RightDockWidgetArea);
//    dock->hide();
//    connect(dock, SIGNAL(visibilityChanged(bool)), this, SLOT(shrink()));


//    cart = new QDockWidget(tr("Cart"), this);
//    cart->hide();
//    connect(cart, SIGNAL(visibilityChanged(bool)), this, SLOT(shrink()));
}

StudentInterfaceWindow::~StudentInterfaceWindow()
{
    delete ui;
}

void            StudentInterfaceWindow::createStatusBar(){  this->statusBar()->showMessage(tr("Ready")); }

//getters

QStatusBar*     StudentInterfaceWindow::getStatusBar() { return this->statusBar() ; }
QPushButton*    StudentInterfaceWindow::getAddTextbookOption() { return shopView->getAddTextbookOption(); }
QPushButton*    StudentInterfaceWindow::getViewDetailsOption() {return shopView->getViewDetailsOption(); }
QPushButton*    StudentInterfaceWindow::getViewCartOption() { return shopView->getViewCartOption() ;}
QComboBox*      StudentInterfaceWindow::getTermSelectOption() { return shopView->getTermSelectOption();  }
QSpinBox*       StudentInterfaceWindow::getQuantityOption() { return shopView->getQuantityOption(); }
QListView*      StudentInterfaceWindow::getCourseView() {return shopView->getCourseView(); }


//make a dock window for a textbook
//void StudentInterfaceWindow::createDockWindow(QWidget *widget)
//{

//    dock->setWidget(widget);
//    this->addDockWidget(Qt::RightDockWidgetArea, dock);
//    dock->setVisible(true);

//}

//void StudentInterfaceWindow::createCartWindow(QWidget *widget)
//{
//    cart->setWidget(widget);
//    this->addDockWidget(Qt::RightDockWidgetArea, cart);
//    if (dock->isVisible())
//    {
//        this->splitDockWidget(dock,cart, Qt::Vertical);
//    }

//    cart->setVisible(true);
//}

//void StudentInterfaceWindow::createCartWindow(QWidget *widget, Qt::DockWidgetArea area)
//{
//    if (area == Qt::RightDockWidgetArea)
//    {

//    }
//    cart->setWidget(widget);
//    this->addDockWidget(area, cart);
//    cart->setVisible(true);
//}





















