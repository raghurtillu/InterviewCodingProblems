#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <limits>

using namespace std;

struct Item 
{
	string name;
	double price = 0.0;

	Item(const string& _name, double _price) : name(_name), price(_price)
	{}
};

static const vector<Item> g_MenuItems = 
{
	{ "mixed fruit", 2.15 },
	{ "french fries", 2.75 },
	{ "side salad", 3.35 },
	{ "hot wings", 3.55 },
	{ "mozarella sticks", 4.20 },
	{ "sampler plate", 5.80 },

	//{ "mixed fruit", 1.00 },
	//{ "french fries", 2.00 },
	//{ "side salad", 3.00 },
	//{ "hot wings", 4.00 },
	//{ "mozarella sticks", 5.00 },
	//{ "sampler plate", 6.00 },
};

bool AreSame(double a, double b)
{
	// ref: http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.22.6768
	// ref: http://realtimecollisiondetection.net/blog/?p=89
	//return fabs(a-b) <= numeric_limits<double>::epsilon();
	return fabs(a - b) <= 0.0000000000001;
}

double GetPriceForItem(const string& name)
{
	for (const auto& it : g_MenuItems)
	{
		if (strcmp(name.c_str(), it.name.c_str()) == 0)
		{
			return it.price;
		}
	}
	return 0.0;
}

void DisplayMenuItems()
{
	const char separator = ' ';
	const int nameWidth = 20;
	const int costWidth = 20;
	cout << "Menu items" << endl << endl;
	cout << left << setw(nameWidth) << setfill(separator) << "Name";
	cout << left << setw(costWidth) << setfill(separator) << "Price";
	cout << endl;
	cout << left << setw(nameWidth) << setfill(separator) << "******************";
	cout << left << setw(costWidth) << setfill(separator) << "******";
	cout << endl;
	for (const auto& it : g_MenuItems)
	{
		cout << left << setw(nameWidth) << setfill(separator) << it.name;
		cout << left << setw(costWidth) << setfill(separator) << it.price;
		cout << endl;
	}
	cout << endl;
}

void DisplayCombination(unordered_map<string, size_t>& combinations)
{
	if (combinations.empty())
	{
		return;
	}

	static int count = 1;
	const char separator = ' ';
	const int nameWidth = 20;
	const int unitWidth = 12;
	const int costWidth = 20;
	const int totalCostWidth = 20;

	cout << "(" << count++ << ")" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << left << setw(nameWidth) << setfill(separator) << "Name";
	cout << left << setw(unitWidth) << setfill(separator) << "Units";
	cout << left << setw(costWidth) << setfill(separator) << "Cost per unit";
	cout << left << setw(totalCostWidth) << setfill(separator) << "Total item cost";
	cout << endl;

	double total = 0;
	for (auto it = combinations.cbegin(); it != combinations.cend(); it++) 
	{

		double perUnitCost = GetPriceForItem(it->first);
		double itemTotalCost = perUnitCost * it->second;

		cout << left << setw(nameWidth) << setfill(separator) << it->first;
		cout << left << setw(unitWidth) << setfill(separator) << it->second;
		cout << left << setw(costWidth) << setfill(separator) << perUnitCost;
		cout << left << setw(totalCostWidth) << setfill(separator) << itemTotalCost << endl;

		total += itemTotalCost;
	}
	cout << "Total: " << total << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << endl;
}

void _GetMenuItemsForSpecifiedAmount(const vector<Item>& itemPriceLookup, 
	size_t pos,
	double amount,
	double& amountAccrued, 
	unordered_map<string, size_t>& combinations)
{
	if (AreSame(amountAccrued, amount))
	{
		// print the combination
		DisplayCombination(combinations);
		return;
	}
	else if (itemPriceLookup.empty() || pos >= itemPriceLookup.size() || amountAccrued > amount)
	{
		return;
	}

	const string& itemName = itemPriceLookup[pos].name;
	double itemPrice = itemPriceLookup[pos].price;

	// choose the menu item
	combinations[itemName]++;
	amountAccrued += itemPrice;

	// if the item can be chosen multiple times
	_GetMenuItemsForSpecifiedAmount(itemPriceLookup, pos, amount, amountAccrued, combinations);

	// else if the item can only be chosen once
	//_GetMenuItemsForSpecifiedAmount(itemPriceLookup, pos + 1,  amount, amountAccrued, combinations);

	// undo and do not choose item
	if (--combinations[itemName] == 0)
	{
		combinations.erase(itemName);
	}
	amountAccrued -= itemPrice;
	_GetMenuItemsForSpecifiedAmount(itemPriceLookup, pos + 1, amount, amountAccrued, combinations);
}

void GetMenuItemsForSpecifiedAmount(const vector<Item>& itemPriceLookup, double amount)
{
	double amountAccrued = 0;
	unordered_map<string, size_t> combinations;

	size_t pos = 0;

	_GetMenuItemsForSpecifiedAmount(itemPriceLookup,
		pos,
		amount,
		amountAccrued,
		combinations);
}

int main()
{
	cout << setprecision(2) << fixed;
	DisplayMenuItems();

	double amount = 15.50;
	//double amount = 10.00;
	cout << "Menu Combinations for the amount: " << amount << endl << endl;

	GetMenuItemsForSpecifiedAmount(g_MenuItems, amount);
	return 0;
}

