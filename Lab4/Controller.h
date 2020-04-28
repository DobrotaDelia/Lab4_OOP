#pragma once
#include "Repository.h"

class Controller
{
protected:
	Repository repo = Repository("input.txt");

	
	
	/* Compare price of 2 medicines: a and b
	True if it succeeds, false if it fails*/
	bool compare_price(Medicine a, Medicine b) { return (a.get_price() <= b.get_price()); }

public:

	
	///Default constructor
	Controller() {}


	
	/*Searches all medicines which names contain the param str
	Vector with all the found medicines*/
	std::vector<Medicine> search_name(string str);


	
	/*Searches all medicines where quantity is less than the param x
	Vector with all the found medicines*/
	std::vector<Medicine> search_less_quantity(double x);


	
	/*Searches all medicines grouped by price, i.e. all medicines between min_price and	max_price
	Vector with all the found medicines*/
	std::vector<Medicine> group_by_price(double min_price, double max_price);

};

