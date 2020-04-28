#include "Controller.h"
#include <algorithm>
#include <iostream>


std::vector<Medicine> Controller::search_name(string str)
{
	std::vector<Medicine> match;

	if (str == "")
		match = repo.show();  // in case o a empty str => match contains all the medicines from repo

	else
		for (auto it : repo.show())
			if (it.get_name().find(str) != -1)   // if the name of a medicine contains str=> we add it to match
				match.push_back(it);

	std::sort(match.begin(), match.end());  // sort the vector match by name ,using the operator< from Medicine
	return match;
}

std::vector<Medicine> Controller::search_less_quantity(double x)
{
	std::vector<Medicine> match;


	for (auto it : repo.show())
		if (it.get_quantity() < x)   // if there is less medicine than x
			match.push_back(it);

	return match;
}

std::vector<Medicine> Controller::group_by_price(double min_price, double max_price)
{
	std::vector<Medicine> repo_sorted;

	// adding medicines with min_prince <= price <= max_price to repo_sorted
	for (auto it : repo.show())
		if (it.get_price() >= min_price && it.get_price() <= max_price)
			repo_sorted.push_back(it);

	// sort medicines by price
	for (int i = 0; i < repo_sorted.size(); i++)
		for (int j = i + 1; j < repo_sorted.size(); j++)
			if (!compare_price(repo_sorted[i], repo_sorted[j]))
			{
				Medicine aux = repo_sorted[i];
				repo_sorted[i] = repo_sorted[j];
				repo_sorted[j] = aux;
			}

	return repo_sorted;
}


