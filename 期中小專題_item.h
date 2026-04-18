#ifndef ITEM_H
#define ITEM_H
#include <string>
using namespace std;
class Item{
private:
	string name;
	int price;
public:
	Item();
	Item(string,int);
	string getN()const;
	int getP()const;
};
void set(Item m[]);  //初始化菜單,是全域的
#endif