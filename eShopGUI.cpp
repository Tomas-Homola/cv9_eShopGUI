#include "eShopGUI.h"

bool eShopGUI::importProducts()
{
    if (!productsLoaded)
    {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", tr("Txt File (*.txt);;All files (*.)"));

        if (fileName.isEmpty())
            return false;

        qDebug() << fileName;

        QFileInfo fileInfo(fileName);
        qDebug() << fileInfo.fileName();

        if (fileInfo.suffix() == "txt")
        {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return false;

            QTextStream fromFile(&file);

            if (fromFile.readLine() != "ProductList")
            {
                msgBox.setWindowTitle("Warning");
                msgBox.setText("Incorect txt file");
                msgBox.exec();
                
                return false;
            }

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
                productsLoaded = true;
                return true;
            }
        }
    }
    else
    {
        msgBox.setWindowTitle("Info message");
        msgBox.setText("Products already imported");
        msgBox.exec();
        return false;
    }
}

void eShopGUI::showProducts(QVector<Product>& products)
{
    ui.tableWidget_Catalog->clear();

    ui.tableWidget_Catalog->setRowCount(products.size());

    QStringList header = { "ID", "Name", "Producer", "Quantity", "Price" };
    ui.tableWidget_Catalog->setHorizontalHeaderLabels(header);

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
    msgBox.setText("Import products from \"File - Import products\"");
    msgBox.exec();
}

void eShopGUI::on_action_ImportProducts_triggered()
{
    if (importProducts())
    {
        ui.button_CustomerRegistration->setEnabled(true);

        showProducts(allProducts);
    }
}

void eShopGUI::on_inputBox_SearchedItem_textChanged() // vyhladavanie
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

void eShopGUI::on_tableWidget_Catalog_itemClicked(QTableWidgetItem* item)
{
    if (!ui.button_AddToCart->isEnabled())
        ui.button_AddToCart->setEnabled(true);
}

void eShopGUI::on_button_CustomerRegistration_clicked() // zacat registraciu zakaznika
{
    ui.groupBox_RegistrationWindow->setVisible(true);
    ui.groupBox_Main->setEnabled(false);
}

void eShopGUI::on_button_Register_clicked() // registrovat zakaznika
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
        ui.button_AddToCart->setEnabled(false);
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
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", tr("Txt File (*.txt);;All files (*.)"));

    QFile receipt(fileName);

    if (!receipt.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Error with creating a receipt");
        msgBox.exec();
        return;
    }

    QTextStream out(&receipt);

    time_t now = time(0);
    char* date = ctime(&now);
    qDebug() << "Current time:" << date;

    out << "E-Shop Tomas\nDate and time: " << date << "******************************\nBought products:\n";

    for (int i = 0; i < customer.getNumOfChosenProducts(); i++)
    {
        out << "1x ... " << allProducts[customer.getChosenProductID(i)].getName() << " - " << allProducts[customer.getChosenProductID(i)].getProducer() << ", " << QString::number(allProducts[customer.getChosenProductID(i)].getPrice(), 'f', 2) << " EUR\n";
    }

    out << "______________________________\nIn total: " << QString::number(totalSum, 'f', 2) << " EUR\n\nThank you for you visit!";

    receipt.close();
    
    ui.label_CustomerInfo->setVisible(false);
    ui.doubleSpinBox_ShowBudget->setVisible(false);
    ui.label_EUR->setVisible(false);
    ui.button_FinnishOrder->setVisible(false);
    ui.inputBox_SearchedItem->setEnabled(false);
    ui.button_CustomerRegistration->setVisible(true);
    ui.listWidget_Cart->clear(); // vycistenie kosika
    ui.inputBox_SearchedItem->setText("");
    ui.groupBox_ShowProducts->setEnabled(false);
    ui.groupBox_Buttom->setEnabled(false);

    for (int i = 0; i < customer.getNumOfChosenProducts(); i++)
    {
        qDebug() << i + 1 << "1x ..." << allProducts[customer.getChosenProductID(i)].getName();
    }

    msgBox.setWindowTitle("Info message");
    msgBox.setText("Shopping done");
    msgBox.exec();

}

void eShopGUI::on_button_AddToCart_clicked()
{
    int selectedID = ui.tableWidget_Catalog->item(ui.tableWidget_Catalog->currentItem()->row(), 0)->text().toInt();

    qDebug() << ui.tableWidget_Catalog->item(ui.tableWidget_Catalog->currentItem()->row(), 0)->text();
    
    //qDebug() << "Selected ID:" << selectedID;
    
    if (allProducts[selectedID - 1].getQuantity() > 0 && customer.getBudget() >= allProducts[selectedID - 1].getPrice())
    {
        customer.buyProduct(selectedID); // pridanie do pola vybranych produktov
        allProducts[selectedID - 1].changeQuantity(allProducts[selectedID - 1].getQuantity() - 1); // znizenie poctu o 1
        totalSum += allProducts[selectedID - 1].getPrice();

        // zapisanie noveho poctu vybraneho produktu do tabulky
        ui.tableWidget_Catalog->item(ui.tableWidget_Catalog->currentItem()->row(), 3)->setText(QString("%1").arg(allProducts[selectedID - 1].getQuantity()));

        // priradenie vybraneho produktu do kosika
        QListWidgetItem* newItem = new QListWidgetItem;
        newItem->setText(allProducts[selectedID - 1].getName());
        ui.listWidget_Cart->addItem(newItem);

        customer.removeFromBudget(allProducts[selectedID - 1].getPrice()); // odratanie ceny vybraneho produktu z rozpoctu
        ui.doubleSpinBox_ShowBudget->setValue(customer.getBudget());

    }
    else if (allProducts[selectedID - 1].getQuantity() == 0)
    {
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Item no longer available");
        msgBox.exec();
    }
    else if (customer.getBudget() < allProducts[selectedID - 1].getPrice())
    {
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Not enough money to buy this item");
        msgBox.exec();
    }
}
