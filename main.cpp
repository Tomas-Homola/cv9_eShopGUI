#include "eShopGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    eShopGUI w;
    w.show();
    return a.exec();
}
