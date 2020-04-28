#include "Repository.h"
#include "Medicine.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

int Repository::search(Medicine a)
{ // search the position of a medicine
	for (int i = 0; i < vektorelemente.size(); i++)
		if (vektorelemente[i] == a)
			return i;
	return -1;
}

Repository::Repository() {}

Repository::Repository(std::string file)
{

	string name, concentration, quantity, price;
	std::ifstream infile;
	infile.open(file);




	while (infile >> name)
	{
		infile >> concentration >> quantity >> price;

		Medicine medicine = Medicine(name, std::stod(concentration), std::stod(quantity), std::stod(price));

		add_medicine(medicine);
	}

}

Medicine Repository::get_element(int position)
{
	return vektorelemente[position];
}

void Repository::add_medicine(Medicine a)
{ /* when we add a medicine, we have 2 options:
       if the medicine is already in the array=> add to the quantity of the medicine,
        the quantity of the object we wanted to add
       if the medicine does not appear in our array =>add a new medicine to our array*/
	int pos = search(a);
	if (pos > -1)
		vektorelemente[pos].add_quantity(a.get_quantity());
	else
		vektorelemente.push_back(a);
}

void Repository::delete_medicine(Medicine a)
{
	int position = search(a);
	if (position > -1)
		vektorelemente.erase(vektorelemente.begin() + position);


}

std::vector<Medicine> Repository::show()
{
	return vektorelemente;
}

void Repository::update_name(string neuname, string altename)
{
	for (int i = 0; i < vektorelemente.size(); i++)
		if (vektorelemente[i].get_name() == altename)

			vektorelemente[i].set_name(neuname);

}
