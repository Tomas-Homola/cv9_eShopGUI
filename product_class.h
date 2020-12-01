#pragma once

#include <qstring.h>

class Product
{
private:
	int ID = -1;
	QString name = "";
	QString producer = "";
	int quantity = -1;
	double price = -1.0;

public:
	Product() {}
	Product(int ID, QString name, QString producer, int quantity, double price);

	int getID() { return ID; } // funkcia na vratenie ID produktu
	QString getName() { return name; } // funkcia na vratenie nazvu produktu
	QString getProducer() { return producer; } // funkcia na vratenie vyrobcu produktu
	int getQuantity() { return quantity; } // funkcia na vratenie mnozstva na sklade
	double getPrice() { return price; } // funkcia na vratenie ceny produktu

	void changeID(int newID) { ID = newID; } // funkcia na zmenu ID produktu
	void changeName(QString newName) { name = newName; } // funkcia na zmenu nazvu produktu
	void changeProducer(QString newProducer) { producer = newProducer; } // funkcia na zmenu vyrobcu produktu
	void changeQuantity(int newQuantity) { quantity = newQuantity; } // funkcia na zmenu mnozstva na sklade
	void changePrice(double newPrice) { price = newPrice; } // funkcia na zmenu ceny produktu

};