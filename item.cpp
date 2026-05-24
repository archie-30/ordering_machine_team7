#include "item.h"
using namespace std;
MenuItem::MenuItem(){
    name="";
    price=0;
}
MenuItem::MenuItem(string n,int p){
    name=n;
    price=p;
}
string MenuItem::getName() const{
	return name;
}
int MenuItem::getPrice() const{
	return price;
}
void initMenu(MenuItem m[]){
	m[0]=MenuItem("卡拉雞腿堡",85);
	m[1]=MenuItem("起司牛排堡",110);
	m[2]=MenuItem("黃金脆雞塊",60);
	m[3]=MenuItem("現炸厚薯條",45);
	m[4]=MenuItem("特調冰奶茶",30);
	m[5]=MenuItem("研磨熱咖啡",50);
	m[6]=MenuItem("起司蛋吐司",40);
	m[7]=MenuItem("玉米濃湯",35);
	m[8]=MenuItem("辣味雞翅",75);
	m[9]=MenuItem("鮮果沙拉",65);
}
