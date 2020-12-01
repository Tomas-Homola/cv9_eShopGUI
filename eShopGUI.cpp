#include "eShopGUI.h"

void eShopGUI::loadProducts()
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

        numOfAllProducts = fromFile.readLine().toInt();
        qDebug() << "pocet produktov:\n" << numOfAllProducts;

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

        for (int i = 0; i < numOfAllProducts; i++)
        {
            qDebug() << allProducts[i].getID() << allProducts[i].getName() << allProducts[i].getProducer() << allProducts[i].getQuantity() << allProducts[i].getPrice() << " EUR";
        }

        ui.tableWidget->setRowCount(allProducts.size());

        for (int i = 0; i < allProducts.size(); i++)
        {
            QTableWidgetItem* ID = new QTableWidgetItem();
            QTableWidgetItem* name = new QTableWidgetItem();
            QTableWidgetItem* producer = new QTableWidgetItem();
            QTableWidgetItem* quantity = new QTableWidgetItem();
            QTableWidgetItem* price = new QTableWidgetItem();

            ID->setText(QString("%1").arg(allProducts[i].getID()));
            name->setText(allProducts[i].getName());
            producer->setText(allProducts[i].getProducer());
            quantity->setText(QString("%1").arg(allProducts[i].getQuantity()));
            price->setText(QString("%1 EUR").arg(allProducts[i].getPrice()));

            ui.tableWidget->setItem(i, 0, ID);
            ui.tableWidget->setItem(i, 1, name);
            ui.tableWidget->setItem(i, 2, producer);
            ui.tableWidget->setItem(i, 3, quantity);
            ui.tableWidget->setItem(i, 4, price);
        }

    }
}

eShopGUI::eShopGUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //loadProducts();

    ui.groupBox_RegistrationWindow->setVisible(false);
    ui.groupBox_ShowProducts->setEnabled(false);
    ui.label_CustomerInfo->setVisible(false);
    ui.doubleSpinBox_ShowBudget->setVisible(false);
    ui.label_EUR->setVisible(false);
    ui.button_FinnishOrder->setVisible(false);
    ui.inputBox_SearchedItem->setEnabled(false);
    ui.button_Search->setEnabled(false);
    ui.button_CustomerRegistration->setEnabled(false);

    msgBox.setWindowTitle("Info message");
    msgBox.setText("Import products from \'File->Import products\'");
    msgBox.exec();
}

void eShopGUI::on_action_ImportProducts_triggered()
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

        numOfAllProducts = fromFile.readLine().toInt();
        qDebug() << "pocet produktov:\n" << numOfAllProducts;

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
            ui.button_CustomerRegistration->setEnabled(true);
        }

        for (int i = 0; i < numOfAllProducts; i++)
        {
            qDebug() << allProducts[i].getID() << allProducts[i].getName() << allProducts[i].getProducer() << allProducts[i].getQuantity() << allProducts[i].getPrice() << " EUR";
        }

        ui.tableWidget->setRowCount(allProducts.size());

        for (int i = 0; i < allProducts.size(); i++)
        {
            QTableWidgetItem* ID = new QTableWidgetItem();
            QTableWidgetItem* name = new QTableWidgetItem();
            QTableWidgetItem* producer = new QTableWidgetItem();
            QTableWidgetItem* quantity = new QTableWidgetItem();
            QTableWidgetItem* price = new QTableWidgetItem();

            ID->setText(QString("%1").arg(allProducts[i].getID()));
            name->setText(allProducts[i].getName());
            producer->setText(allProducts[i].getProducer());
            quantity->setText(QString("%1").arg(allProducts[i].getQuantity()));
            price->setText(QString("%1 EUR").arg(allProducts[i].getPrice()));

            ui.tableWidget->setItem(i, 0, ID);
            ui.tableWidget->setItem(i, 1, name);
            ui.tableWidget->setItem(i, 2, producer);
            ui.tableWidget->setItem(i, 3, quantity);
            ui.tableWidget->setItem(i, 4, price);
        }
        
    }
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
        ui.button_CustomerRegistration->setVisible(false);
        ui.button_FinnishOrder->setVisible(true);
        ui.inputBox_SearchedItem->setEnabled(true);
        ui.button_Search->setEnabled(true);
        
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
    ui.button_Search->setEnabled(false);
    ui.button_CustomerRegistration->setVisible(true);
    ui.tableWidget->clear();

    msgBox.setWindowTitle(" ");
    msgBox.setText("Shopping done");
    msgBox.exec();

}
