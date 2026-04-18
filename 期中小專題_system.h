#ifndef SYSTEM_H
#define SYSTEM_H
#include "item.h"
using namespace std;
class System{
private:
	Item m[10];
	int data_id[11][50]; //桌號,點了什麼
	int data_n[11][50];  //桌號,點了幾份
	int data_p[11][50];  //桌號,該項目的小計
	int count[11];       //計每桌點了幾筆某個品項
	int salesCount[10];  //計每樣菜各賣出幾份
	int totalM;          //總營收
public:
	System();
	void show()const;  //顯示菜單
	void add();        //點餐
	void view()const;  //查看各桌
	void sum()const;   //結算
};
#endif