#pragma once

#include <QtWidgets>
#include <ui_eShopGUI.h>
#include "product_class.h"
#include "customer_class.h"

class eShopGUI : public QMainWindow
{
    Q_OBJECT

public:
    eShopGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::eShopGUIClass ui;

    int numOfAllProducts = -1;
    int numOfFoundProducts = -1;
    QVector<Product> allProducts;
    QVector<Product> foundProducts;

    Customer customer;

    QMessageBox msgBox;

    void importProducts();
    void showProducts(QVector<Product>& products);
    void print(QVector<Product>& products);

private slots:
    void on_action_ImportProducts_triggered();

    void on_inputBox_SearchedItem_textChanged();

    void on_button_CustomerRegistration_clicked(); // button na zacatie Registracie zakaznika
    void on_button_Register_clicked(); // button  na potvrdenie registracie
    void on_button_FinnishOrder_clicked(); // button na skoncenie nakupovanie
};
