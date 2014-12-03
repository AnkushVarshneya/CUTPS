#include "StudentInterfaceWindow.h"
#include "ui_StudentInterfaceWindow.h"
#include <QDebug>

#include <QPixmap>
#include <QIcon>

StudentInterfaceWindow::StudentInterfaceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentInterfaceWindow)
{
    ui->setupUi(this);

    //Setting the icon's image to a Shopping Cart
    QPixmap shopping_img("../Images/shopping_cart_clipart.png");
    QIcon ButtonIcon(shopping_img);
    ui->viewShoppingCartOption->setIcon(ButtonIcon);
    ui->viewShoppingCartOption->setIconSize(shopping_img.rect().size());
    ui->viewShoppingCartOption->setFixedSize(shopping_img.rect().size());

    //make textbooks for testing
    Textbook    *text1 = new Textbook();
    QListWidgetItem *listItem = new QListWidgetItem(text1->getItemTitle());
    listItem->setData(0, text1->getItemID());
    listItem->setText(text1->getItemTitle());
    ui->textbookListWidget->addItem(listItem);

    qDebug() << ui->textbookListWidget->item(0)->data(0);

    //todo: dummy textbook list
    //cast to purchasable item -> std itm?
    //rep as standard items: text is some toString, data is itemID
    //treeview for chapters and sections???????????

    OurStandardItem *ourItem = new OurStandardItem(text1);
    QStandardItemModel *mod = new QStandardItemModel(this);
    mod->appendRow(ourItem);
    ui->textbookListView->setModel(mod);
    qDebug() << mod->item(0)->text();
    qDebug() << mod->item(0)->data();


//try a textbook with chapter in a tree view. make items, set one as child of the other, add to model.
    Textbook    *treeText = new Textbook("all about trees", "david suzuki","3rd ed");
    Chapter *chp1 = new Chapter();
    Chapter *chp2 = new Chapter("chp2", 2, 64, 22, true);
    Chapter *chp3 = new Chapter("chapter 3", 3, 11, 77, true);
    treeText->addChapter(chp1);
    treeText->addChapter(chp2);
    treeText->addChapter(chp3);

    Section *sec1 = new Section("1st sec");
    sec1->setSectionNumber(1);
    qDebug() << "s1 item id: " << sec1->getItemID();

    Section *sec2 = new Section("1nd sec diff chapter");
    sec2->setSectionNumber(1);
    sec2->setItemID(10);
     qDebug() << "s2 item id: " << sec2->getItemID();

    Section *sec3 = new Section("2rd sec");
    sec3->setSectionNumber(2);
    sec3->setItemID(11);
     qDebug() << "s3 item id: " << sec3->getItemID();

    chp1->addSection(sec1);
    chp2->addSection(sec2);
    chp2->addSection(sec3);


    OurStandardItem *treeItem = new OurStandardItem(treeText);
    //QStandardItemModel *treeMod = new QStandardItemModel(this);
    treeMod = new QStandardItemModel(this);
    treeMod->appendRow(treeItem);
    ui->itemsTreeView->setModel(treeMod);

   // treeMod->data(ui->itemsTreeView->currentIndex());


}

StudentInterfaceWindow::~StudentInterfaceWindow()
{
    delete ui;
}

void StudentInterfaceWindow::on_viewDetailsOption_clicked()
{
    qDebug() << "getting the key from selected item";
    qDebug() << treeMod->itemFromIndex(ui->itemsTreeView->currentIndex())->data();

}
