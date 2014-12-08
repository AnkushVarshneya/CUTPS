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

    dock = new QDockWidget(tr("Textbook"), this);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);
    dock->hide();
    connect(dock, SIGNAL(visibilityChanged(bool)), this, SLOT(shrink()));


    cart = new QDockWidget(tr("Cart"), this);
    cart->hide();
    connect(cart, SIGNAL(visibilityChanged(bool)), this, SLOT(shrink()));
}

StudentInterfaceWindow::~StudentInterfaceWindow()
{
    delete ui;
}

void            StudentInterfaceWindow::createStatusBar(){  this->statusBar()->showMessage(tr("Ready")); }

//getters
//QPushButton*    StudentInterfaceWindow::getAddTextbookOption() { return ui->addTextbookToCartOption; }
//QPushButton*    StudentInterfaceWindow::getViewDetailsOption() {return ui->viewDetailsOption; }
//QPushButton*    StudentInterfaceWindow::getViewCartOption() { return ui->viewShoppingCartOption; }
//QComboBox*      StudentInterfaceWindow::getTermSelectOption() { return ui->termSelectOption;  }
//QSpinBox*       StudentInterfaceWindow::getQuantityOption() { return ui->quantityOption; }
//QListView*      StudentInterfaceWindow::getCourseView() {return ui->itemsListView; }

QStatusBar*     StudentInterfaceWindow::getStatusBar() { return this->statusBar() ; }
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

void StudentInterfaceWindow::createCartWindow(QWidget *widget)
{
    cart->setWidget(widget);
    this->addDockWidget(Qt::RightDockWidgetArea, cart);
    if (dock->isVisible())
    {
        this->splitDockWidget(dock,cart, Qt::Vertical);
    }

    cart->setVisible(true);
}

void StudentInterfaceWindow::createCartWindow(QWidget *widget, Qt::DockWidgetArea area)
{
    if (area == Qt::RightDockWidgetArea)
    {

    }
    cart->setWidget(widget);
    this->addDockWidget(area, cart);
    cart->setVisible(true);
}


void StudentInterfaceWindow::shrink()
{
    //this->resize( this->minimumSize() );
    qDebug() << "dockwidg visible? " << dock->isVisible();
    qDebug() << "dockwidg ? " << dock->isHidden();
    qDebug() << "dockw is min? " << dock->isMinimized();
    qDebug() << "dockw is float?" << dock->isFloating();


    if (!dock->isVisible() && !cart->isVisible())
    {
    this->resize(this->minimumSize());
    } else this->resize(this->sizeHint());


}




















