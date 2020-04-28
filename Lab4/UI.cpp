#include "UI.h"
#include <iostream>

using std::cout;
using std::cin;

void UI::repeat()
{
	while (!end)
	{
		menu();
		action(input());
	}
}

void UI::menu()
{
	cout << "\n\n\t1.List all the medicines\n"
		"\t2.Update a medicine\n"
		"\t3.Add new medicine\n"
		"\t4.Delete a medicine\n"
		"\t5.List all the medicines that contain a string\n"
		"\t6.List all the medicines where quantity < x\n"
		"\t7.List all the medicines grouped by price\n"
		"\t8.Undo the last modification\n"
		"\t9.Redo the last undo\n"
		"\t10.Quit\n\n";
}

int UI::input()
{
	int n, ok = 0;
	while (!ok)
	{
		cout << "Choose a number from above: ";
		try
		{
			cin >> n;
			if (n < 1 or n>10)
				throw std::exception();
			ok = 1;
		}
		catch (std::exception&)
		{
			cout << "You must type in a number from 1 to 10\n";
		}
	}

	return n;
}

void UI::action(int n)
{

	switch (n)
	{
	case 1:
		print_all();
		break;

	case 2:
		updatename();
		print_all();
		break;

	case 3:
		add_med();
		break;

	case 4:
		remove();
		break;

	case 5:
		med_string();
		break;

	case 6:
		med_quantity();
		break;

	case 7:
		group_pr();
		break;

	case 8:
		if (undo_last())
			print_all();
		else
			cout << "There is nothing to undo.\n";
		break;

	case 9:
		if (redo_last())
			print_all();
		else
			cout << "There is nothing to redo.\n";
		break;

	case 10:
		end = true;
		break;

	}
}

void UI::print_all()
{
	if (repo.show().empty())
		cout << "There are no medicines.\n";
	else
	{
		cout << "\nAll medicines:\n";
		for (auto it : repo.show())
			cout << "  " << it.get_name() << ' ' << it.get_concentration() << ' ' << it.get_quantity() << ' ' << it.get_price() << '\n';
	}
}

void UI::updatename()
{
	string neuename, altename;
	cout << "Old name:"; cin >> altename;
	cout << "New name:"; cin >> neuename;
	repo.update_name(neuename, altename);

	undo.n = 2;
	undo.new_name = neuename;
	undo.old_name = altename;

}

void UI::add_med()
{
	string na;
	double c, q, p;
	cout << "Name of the medicine: "; cin >> na;
	cout << "Concentration: "; cin >> c;
	cout << "Quantity: "; cin >> q;
	cout << "Price: "; cin >> p;

	undo.n = 3;
	undo.old_name = na;
	undo.concentration = c;
	undo.quantity = q;
	undo.price = p;

	repo.add_medicine(Medicine(na, c, q, p));
	cout << "Medicine added!\n";
}

void UI::remove()
{
	string na;
	double c;
	cout << "Name of the medicine: "; cin >> na;
	cout << "Concentration: "; cin >> c;

	Medicine med = Medicine(na, c, 0, 0);


	if (repo.search(med) > -1)
	{
		undo.n = 4;

		med = repo.get_element(repo.search(med));

		undo.old_name = med.get_name();
		undo.concentration = med.get_concentration();
		undo.quantity = med.get_quantity();
		undo.price = med.get_price();

		repo.delete_medicine(med);
		cout << "Medicine deleted!\n";
	}
	else
		cout << "There is no such medicine!\n";

}

void UI::med_string()
{
	string str;
	cout << "What should the name contain: "; cin >> str;
	if (search_name(str).empty())
		cout << "There is no medicine with " << str << "\n";
	else
		for (auto it : search_name(str))
			cout << "  " << it.get_name() << ' ' << it.get_concentration() << ' ' << it.get_quantity() << ' ' << it.get_price() << '\n';
}

void UI::med_quantity()
{
	double x;
	cout << "Quantity less than: "; cin >> x;
	if (search_less_quantity(x).empty())
		cout << "There is no medicine with quantity < " << x << "\n";
	else
		for (auto it : search_less_quantity(x))
			cout << "  " << it.get_name() << ' ' << it.get_concentration() << ' ' << it.get_quantity() << ' ' << it.get_price() << '\n';
}

void UI::group_pr()
{
	double min, max;
	cout << "Minimum price: "; cin >> min;
	cout << "Maximum price: "; cin >> max;
	if (group_by_price(min, max).empty())
		cout << "There is no medicine in the given price-range.\n";
	else
		for (auto it : group_by_price(min, max))
			cout << "  " << it.get_name() << ' ' << it.get_concentration() << ' ' << it.get_quantity() << ' ' << it.get_price() << '\n';
}


bool UI::undo_last()
{
	if (undo.n == 2)  // last change was name_update
	{
		repo.update_name(undo.old_name, undo.new_name);
		redo.n = 2;
		redo.new_name = undo.new_name;
		redo.old_name = undo.old_name;
	}

	else
		if (undo.n == 3)  // last change was adding an element
		{
			redo.n = 3;
			redo.old_name = undo.old_name;
			redo.concentration = undo.concentration;
			redo.quantity = undo.quantity;

			Medicine med = Medicine(undo.old_name, undo.concentration, undo.quantity, undo.price);
			redo.price = repo.get_element(repo.search(med)).get_price();

			if (repo.get_element(repo.search(med)).get_quantity() == undo.quantity) // if the added quantity is equal to the quantity of the element, to undo the last change we must delete the element
				repo.delete_medicine(med);

			else // else we must only substract the added quantity
			{
				undo.quantity *= -1;
				repo.add_medicine(Medicine(undo.old_name, undo.concentration, undo.quantity, undo.price));

				redo.quantity = -1 * undo.quantity;
			}
		}
		else
			if (undo.n == 4)  // last change was deleting an element
			{
				redo.n = 4;
				redo.old_name = undo.old_name;
				redo.concentration = undo.concentration;
				redo.quantity = undo.quantity;
				redo.price = undo.price;

				repo.add_medicine(Medicine(undo.old_name, undo.concentration, undo.quantity, undo.price));
			}
			else
				return false;
	undo.n = -1;
	return true;
}

bool UI::redo_last()
{
	if (redo.n == 2)   // last undo was name_update
	{
		repo.update_name(redo.new_name, redo.old_name);
		undo.n == 2;
		undo.old_name = redo.old_name;
		undo.new_name = redo.new_name;
	}
	else
		if (redo.n == 3)  // last undo was deleting an element
		{
			repo.add_medicine(Medicine(redo.old_name, redo.concentration, redo.quantity, redo.price));
			undo.n = 3;
			undo.old_name = redo.old_name;
			undo.concentration = redo.concentration;
			undo.quantity = redo.quantity;
			undo.price = redo.price;
		}
		else
			if (redo.n == 4)  // last undo was adding an element
			{
				repo.delete_medicine(Medicine(redo.old_name, redo.concentration, redo.quantity, redo.price));

				undo.n = 4;
				undo.old_name = redo.old_name;
				undo.concentration = redo.concentration;
				undo.quantity = redo.quantity;
				undo.price = redo.price;
			}
			else
				return false;
	redo.n = -1;
	return true;
}


