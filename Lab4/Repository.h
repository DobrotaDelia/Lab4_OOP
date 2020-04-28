#pragma once
#include "Medicine.h"
#include <vector>
#include <string>

using std::string;

class Repository
{
private:
	std::vector<Medicine> vektorelemente;



public:

	//Default constructor
	Repository();

	//Constructor that initializes the vector with the values from file
	Repository(string file);



	//Returns position of a Vektor or -1 if the vektor a is not to find
	int search(Medicine a);


	//Gets the element from the given position
	Medicine get_element(int position);

	//add e new Tableten in the vektor
    void add_medicine(Medicine a);



	
	//delete a Tablete from the vektor
	void delete_medicine(Medicine a);



	
	//return all elements of a vector
	std::vector<Medicine> show();

	
	//Updates name
	void update_name(string neuename, string altename);

};

