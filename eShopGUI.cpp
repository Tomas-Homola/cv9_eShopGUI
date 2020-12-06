#include "eShopGUI.h"

void eShopGUI::importProducts()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", tr("Txt File (*.txt);;All files (*.)"));

    if (fileName.isEmpty())
        return;

    qDebug() << fileName;

    QFileInfo fileInfo(fileName);
    qDebug() << fileInfo.fileName();

    if (fileInfo.suffix() == "txt")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream fromFile(&file);

        int tempID = -1;
        QString tempName = "";
        QString tempProducer = "";
        int tempQuantity = -1;
        double tempPrice = -1.0;

        while (!fromFile.atEnd())
        {
            tempID = fromFile.readLine().toInt();
            tempName = fromFile.readLine();
            tempProducer = fromFile.readLine();
            tempQuantity = fromFile.readLine().toInt();
            tempPrice = fromFile.readLine().toDouble();

            allProducts.push_back(Product(tempID, tempName, tempProducer, tempQuantity, tempPrice));

        }

        if (!allProducts.isEmpty())
        {
            qDebug() << "products loaded";
        }

        qDebug() << "Num of products:" << allProducts.size();
    }
}

void eShopGUI::showProducts(QVector<Product>& products)
{
    ui.tableWidget_Catalog->clear();

    ui.tableWidget_Catalog->setRowCount(products.size());

    for (int i = 0; i < products.size(); i++)
    {
        QTableWidgetItem* ID = new QTableWidgetItem();
        QTableWidgetItem* name = new QTableWidgetItem();
        QTableWidgetItem* producer = new QTableWidgetItem();
        QTableWidgetItem* quantity = new QTableWidgetItem();
        QTableWidgetItem* price = new QTableWidgetItem();

        ID->setText(QString("%1").arg(products[i].getID()));
        name->setText(products[i].getName());
        producer->setText(products[i].getProducer());
        quantity->setText(QString("%1").arg(products[i].getQuantity()));
        price->setText(QString("%1 EUR").arg(products[i].getPrice()));

        ui.tableWidget_Catalog->setItem(i, 0, ID);
        ui.tableWidget_Catalog->setItem(i, 1, name);
        ui.tableWidget_Catalog->setItem(i, 2, producer);
        ui.tableWidget_Catalog->setItem(i, 3, quantity);
        ui.tableWidget_Catalog->setItem(i, 4, price);
    }
}

void eShopGUI::print(QVector<Product>& products)
{
    for (int i = 0; i < products.size(); i++)
    {
        qDebug() << products[i].getID() << products[i].getName() << products[i].getProducer() << products[i].getQuantity() << products[i].getPrice();
    }
}

//#################### PO SPUSTENI ####################//

eShopGUI::eShopGUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //loadProducts();

    ui.groupBox_RegistrationWindow->setVisible(false);
    ui.groupBox_ShowProducts->setEnabled(false);
    ui.groupBox_Buttom->setEnabled(false);
    ui.label_CustomerInfo->setVisible(false);
    ui.doubleSpinBox_ShowBudget->setVisible(false);
    ui.label_EUR->setVisible(false);
    ui.button_FinnishOrder->setVisible(false);
    ui.inputBox_SearchedItem->setEnabled(false);
    ui.button_CustomerRegistration->setEnabled(false);

    msgBox.setWindowTitle("Info message");
    msgBox.setText("Import products from \'File->Import products\'");
    msgBox.exec();
}

void eShopGUI::on_action_ImportProducts_triggered()
{
    importProducts();

    ui.button_CustomerRegistration->setEnabled(true);

    showProducts(allProducts);
}

void eShopGUI::on_inputBox_SearchedItem_textChanged()
{
    foundProducts.clear();

    qDebug() << "Searched: " << ui.inputBox_SearchedItem->text();
    QString toSearch = ui.inputBox_SearchedItem->text();

    bool byName = false;
    bool byProducer = false;

    for (int i = 0; i < allProducts.size(); i++)
    {
        byName = allProducts[i].getName().contains(toSearch, Qt::CaseInsensitive);
        byProducer = allProducts[i].getProducer().contains(toSearch, Qt::CaseInsensitive);

        if (byName || byProducer)
            foundProducts.push_back(allProducts[i]);
    }

    showProducts(foundProducts);
}

void eShopGUI::on_button_CustomerRegistration_clicked()
{
    ui.groupBox_RegistrationWindow->setVisible(true);
    ui.groupBox_Main->setEnabled(false);
}

void eShopGUI::on_button_Register_clicked()
{
    customer.setBudget(ui.doubleSpinBox_Budget->value());
    customer.setName(ui.lineEdit_CustomerName->text());
    customer.setSurname(ui.lineEdit_CustomerSurname->text());

    if ((customer.getName() == "") || (customer.getSurname() == ""))
    {
        msgBox.setWindowTitle("Warning message");
        msgBox.setText("Name/Surname has not been entered");
        msgBox.exec();
    }
    else
    {
        ui.groupBox_Main->setEnabled(true);
        ui.groupBox_ShowProducts->setEnabled(true);
        ui.groupBox_RegistrationWindow->setVisible(false);
        ui.groupBox_Buttom->setEnabled(true);
        ui.button_CustomerRegistration->setVisible(false);
        ui.button_FinnishOrder->setVisible(true);
        ui.inputBox_SearchedItem->setEnabled(true);
        
        // zobrazenie zadaneho mena a priezviska
        ui.label_CustomerInfo->setVisible(true);
        ui.label_CustomerInfo->setText("Customer: " + customer.getName() + " " + customer.getSurname());
        
        // zobrazenie budgetu
        ui.doubleSpinBox_ShowBudget->setVisible(true);
        ui.doubleSpinBox_ShowBudget->setValue(customer.getBudget());
        ui.label_EUR->setVisible(true);
    }
}

void eShopGUI::on_button_FinnishOrder_clicked()
{
    ui.label_CustomerInfo->setVisible(false);
    ui.doubleSpinBox_ShowBudget->setVisible(false);
    ui.label_EUR->setVisible(false);
    ui.button_FinnishOrder->setVisible(false);
    ui.inputBox_SearchedItem->setEnabled(false);
    ui.button_CustomerRegistration->setVisible(true);
    ui.tableWidget_Catalog->clear();

    msgBox.setWindowTitle(" ");
    msgBox.setText("Shopping done");
    msgBox.exec();

}