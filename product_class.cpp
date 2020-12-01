#include "product_class.h"

Product::Product(int ID, QString name, QString producer, int quantity, double price)
{
	this->ID = ID;
	this->name = name;
	this->producer = producer;
	this->quantity = quantity;
	this->price = price;
}
