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

    Customer customer;

    QMessageBox msgBox;

    void loadProducts();

private slots:
    void on_action_ImportProducts_triggered();

    void on_button_CustomerRegistration_clicked();
    void on_button_Register_clicked();
    void on_button_FinnishOrder_clicked();
};
