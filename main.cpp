#include <iostream>
#include "system.h"
using namespace std;
int main(){
	OrderingSystem pos;
	int mode;
	while(true){
		cout<<"\n\n============================"<<endl;
		cout<<"[ 櫃檯 POS 收銀工作站 ]"<<endl;
		cout<<"1. 點餐 / 加點作業"<<endl;
		cout<<"2. 查看各桌詳情與待出餐總量"<<endl;
		cout<<"3. 紀錄出餐進度"<<endl;
		cout<<"4. 瀏覽菜單"<<endl;
		cout<<"5. 結帳作業"<<endl;
		cout<<"0. 退出並關機結算"<<endl;
		cout<<"============================"<<endl;
		cout<<"請選擇操作項目:";
		if(!(cin>>mode)){
			cin.clear();
			cin.ignore(1000,'\n');
			cout<<"⚠️ 無效輸入，請選擇選單編號。"<<endl;
			continue;
		}
		if(mode==0){
			pos.showTotalStatistics();
			break;
		}
		switch(mode){
			case 1: pos.placeOrder(); break;
			case 2: pos.showTableDetails(); break;
			case 3: pos.recordDelivery(); break;
			case 4: pos.displayMenu(); break;
			case 5: pos.checkoutTable(); break;
			default:cout<<"⚠️ 指令無效，請重新選擇。"<<endl;
		}
	}
	cout<<"系統關閉成功 ☕"<<endl;
	return 0;
}
