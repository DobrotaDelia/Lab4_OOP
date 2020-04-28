#include "Medicine.h"


Medicine::Medicine(string name, double concentration, double quantity, double price)
{
	this->name = name;
	this->concentration = concentration;
	this->quantity = quantity;
	this->price = price;
}

bool Medicine::operator==(Medicine med2) const
{
	// two medicine are the same if they have the same name and concentration
	return ((this->name == med2.get_name()) && (this->concentration == med2.get_concentration()));
}

bool Medicine::operator<(Medicine med2) const
{
	// sort the medicines by name
	return this->name < med2.get_name();
}

