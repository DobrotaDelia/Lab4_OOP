#pragma once
#include "Controller.h"

class UI : protected Controller
{
private:
	bool end = false;
	struct modification {
		int n = -1;  //storing the last users command
		string new_name = "", old_name = "";
		double concentration = 0, quantity = 0, price = 0;
	}undo, redo;


	
	//menu on screen	
	void menu();



	//returns the users input
    int input();



	//directs the result of input() to a certain function

	void action(int n);

	//Update name
	void updatename();



	//Print all medicines on the screen

	void print_all();



	//adds a medicine to the list
	void add_med();



	//Removes a medicine from list
	void remove();



	//prints all medicines that contain a given string
	void med_string();



	//prints all medicines with quantity < x

	void med_quantity();



	//prints the medicines between a price-range
    void group_pr();


	//Determines if we can undo last modification
	bool undo_last();

	//Determines if we can redo last undo
	bool redo_last();

public:


	//calls the menu repeatedly until the user calls the exit-function
	void repeat();

};

