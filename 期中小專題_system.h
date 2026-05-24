#ifndef ITEM_H
#define ITEM_H
#include <string>
using namespace std;
class MenuItem{
private:
	string name;
	int price;
public:
	MenuItem();
	MenuItem(string n,int p);
	string getName() const;
	int getPrice() const;
};
void initMenu(MenuItem m[]);
#endif
