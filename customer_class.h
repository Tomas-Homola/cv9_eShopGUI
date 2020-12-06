#pragma once

#include <QtWidgets>
#include "product_class.h"

class Customer
{
private:
	QString name = "";
	QString surname = "";
	double budget = -1.0;
	QVector<int> chosenProducts;

public:
	Customer();
	Customer(QString name, QString surname, double budget);

	QString getName() { return name; } // funkcia na vratenie mena
	QString getSurname() { return surname; } // funkcia na vratenie priezviska
	double getBudget() { return budget; } // funkcia na vratenie rozpoctu
	int getNumOfChosenProducts() { return chosenProducts.size(); }
	int getChosenProductID(int i) { return chosenProducts[i]; }

	void setName(QString newName) { name = newName; } // zmena mena
	void setSurname(QString newSurname) { surname = newSurname; } // zmena priezviska
	void setBudget(double newBudget) { budget = newBudget; }
	void removeFromBudget(double productPrice) { budget -= productPrice; } // pridanie penazi do rozpoctu
	void buyProduct(int ID);
};