#include "customer_class.h"

Customer::Customer()
{

}

Customer::Customer(QString name, QString surname, double budget)
{
	this->name = name;
	this->surname = surname;
	this->budget = budget;
}

void Customer::buyProduct(int ID)
{
	boughtProducts.push_back(ID);
}

