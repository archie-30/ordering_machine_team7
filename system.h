#ifndef SYSTEM_H
#define SYSTEM_H
#include <string>
#include "item.h"
using namespace std;
struct OrderRecord{
	int menuIdx;
	int quantity;
	int deliveredQty;
	int subtotal;
};
class OrderingSystem{
private:
	MenuItem menu[10];
	OrderRecord tableOrders[11][50];
	int orderCounts[11];
	int salesCounts[10];
	int totalRevenue;
public:
	OrderingSystem();
	void displayMenu() const;
	void placeOrder();
	void recordDelivery();
	void showTotalStatistics() const;
	void showTableDetails() const;
	void checkoutTable();
};
#endif
