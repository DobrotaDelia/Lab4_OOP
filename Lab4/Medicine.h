#pragma once
#include <string>

using std::string;

class Medicine
{
private:
	string name;
	double concentration;
	double quantity;
	double price;

public:
	
	/*Constructor with name, concentration, quantity and price given*/
	Medicine(string name, double concentration, double quantity, double price);
	//Medicine();


	
	//Gets the name
	string get_name() { return this->name; }


	
	//Sets the name
	void set_name(string n) { this->name = n; }


	
	//Gets the concentration
	double get_concentration() { return this->concentration; }


	//Sets the concentration
	void set_concentration(double c) { this->concentration = c; }


	//Gets the quantity
	double get_quantity() { return this->quantity; }


	//Sets the quantity
	void set_quantity(double q) { this->quantity = q; }


	//Gets the price
	double get_price() { return this->price; }


	//Sets the price
	void set_price(double p) { this->price = p; }


	//Adds quantity to the medicine
	void add_quantity(double q) { this->quantity += q; }


	//Equality operator verifies if the two medicines are the same
	bool operator== (Medicine med2) const;


	//Less-than comparison operator: verifies if this->name is smaller than med2->name
	bool operator< (Medicine med2) const;


	//Destructor
	~Medicine() {};

};

