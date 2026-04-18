#include "item.h"
using namespace std;
Item::Item(){
	name="";
	price=0;
}
Item::Item(string n,int p){
	name=n;
	price=p;
}
string Item::getN()const{
	return name;
}
int Item::getP()const{
	return price;
}
void set(Item m[]){  //初始化菜單,是全域的
	m[0]=Item("卡拉雞腿堡",85);
	m[1]=Item("起司牛排堡",110);
	m[2]=Item("黃金脆雞塊",60);
	m[3]=Item("現炸厚薯條",45);
	m[4]=Item("特調冰奶茶",30);
	m[5]=Item("研磨熱咖啡",50);
	m[6]=Item("起司蛋吐司",40);
	m[7]=Item("玉米濃湯",35);
	m[8]=Item("辣味雞翅",75);
	m[9]=Item("鮮果沙拉",65);
}