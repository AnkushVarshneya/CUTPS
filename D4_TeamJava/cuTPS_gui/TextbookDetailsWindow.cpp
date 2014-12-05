#include "TextbookDetailsWindow.h"
#include "ui_TextbookDetailsWindow.h"

TextbookDetailsWindow::TextbookDetailsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextbookDetailsWindow)
{
    this->setWindowModality(Qt::WindowModal);
    ui->setupUi(this);
}

TextbookDetailsWindow::TextbookDetailsWindow(Textbook &textbook, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextbookDetailsWindow)
//TODO: also pass in a model and model index to get children?
{

    qDebug() << "inside textbook details window constructor";
    qDebug() << textbook.getItemTitle();
    ui->setupUi(this);
    ui->textbookTitleLabel->setText(textbook.getItemTitle());

}

TextbookDetailsWindow::TextbookDetailsWindow(Textbook &textbook, QModelIndex idx, QStandardItemModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextbookDetailsWindow)
{
        ui->setupUi(this);
        chaptersAndSectionsModel = new QStandardItemModel(this);

        QList<Chapter*>::iterator it;
        for(it = textbook.getChapterList().begin(); it != textbook.getChapterList().end(); it++)
        {
            OurStandardItem *chaptersAndSectionsItem = new OurStandardItem((*it),static_cast<OurStandardItem*>(chaptersAndSectionsModel->invisibleRootItem()) );
            chaptersAndSectionsModel->appendRow(chaptersAndSectionsItem);
        }

       //todo: chaptersAndSectionsModel->setHorizontalHeaderLabels();
        ui->chaptersAndSectionsTreeView->setModel(chaptersAndSectionsModel);
        ui->textbookTitleLabel->setText(textbook.getItemTitle());
}


TextbookDetailsWindow::~TextbookDetailsWindow()
{
    delete ui;
}
