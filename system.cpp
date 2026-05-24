#include "system.h"
#include <iostream>
#include <iomanip>
using namespace std;
OrderingSystem::OrderingSystem():totalRevenue(0){
	for(int i=0;i<11;i++){
        orderCounts[i]=0;
    }
	for(int i=0;i<10;i++){
        salesCounts[i]=0;
    }
	initMenu(menu);
}
void OrderingSystem::displayMenu() const{
	cout<<"\n===================================="<<endl;
	cout<<"[ 櫃檯商品快查清單 ]"<<endl;
	cout<<"------------------------------------"<<endl;
	cout<<left<<setw(6)<<"編號"<<setw(20)<<"品項名稱"<<"單價"<<endl;
	cout<<"------------------------------------"<<endl;
	for(int i=0;i<10;i++){
		cout<<left<<setw(6)<<i+1<<setw(20)<<menu[i].getName()<<"$"<<menu[i].getPrice()<<endl;
	}
	cout<<"===================================="<<endl;
}
void OrderingSystem::placeOrder(){
	int tableNum;
	while(true){
		cout<<"\n[收銀點餐] 請輸入桌號(1-10,輸入0返回主選單):";
		if(!(cin>>tableNum)){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"⚠️ 錯誤：請輸入數字。"<<endl;
            continue;
        }
		if(tableNum==0)return;
		if(tableNum<1||tableNum>10){cout<<"⚠️ 錯誤：桌號無效。"<<endl;continue;}
		int sessionTotal=0;
		while(true){
			int choice,qty;
			cout<<"桌["<<tableNum<<"]-輸入「編號 數量」(輸入0返回桌號):";
			if(!(cin>>choice)){
                cin.clear();
                cin.ignore(1000,'\n');
                cout<<"⚠️ 錯誤：無效輸入。"<<endl;
                continue;
            }
			if(choice==0) break;
			if(choice<1||choice>10){
                cout<<"⚠️ 錯誤：編號不存在。"<<endl;continue;
            }
			if(!(cin>>qty)){
                cin.clear();
            	cin.ignore(1000,'\n');
            	cout<<"⚠️ 錯誤：數量無效。"<<endl;continue;
            }
			if(qty<=0) continue;
			if(orderCounts[tableNum]>=50){
                cout<<"⚠️ 錯誤：點單量已滿。"<<endl;
                break;
            }
			int cost=menu[choice-1].getPrice()*qty;
			salesCounts[choice-1]+=qty;
			totalRevenue+=cost;
			int idx=orderCounts[tableNum];
			tableOrders[tableNum][idx].menuIdx=choice-1;
			tableOrders[tableNum][idx].quantity=qty;
			tableOrders[tableNum][idx].deliveredQty=0;
			tableOrders[tableNum][idx].subtotal=cost;
			orderCounts[tableNum]++;
			sessionTotal+=cost;
			cout<<">> 已加入:"<<menu[choice-1].getName()<<" x"<<qty<<endl;
		}
		if(sessionTotal>0){
			cout<<"\n************************************"<<endl;
			cout<<"📝 桌號 "<<tableNum<<" - 點餐紀錄已儲存"<<endl;
			cout<<"本次加點小計:$"<<sessionTotal<<endl;
			int grandTotal=0;
			for(int i=0;i<orderCounts[tableNum];i++){
                grandTotal+=tableOrders[tableNum][i].subtotal;
            }
			cout<<"該桌累積總額:$"<<grandTotal<<endl;
			cout<<"************************************"<<endl;
		}
	}
}
void OrderingSystem::recordDelivery(){
	int tableNum,choice,qty;
	while(true){
		cout<<"\n[出餐作業] 請輸入桌號(1-10,輸入0返回主選單):";
		if(!(cin>>tableNum)){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"⚠️ 錯誤：請輸入數字。"<<endl;
            continue;
        }
		if(tableNum==0) return;
		if(tableNum<1||tableNum>10){
            cout<<"⚠️ 錯誤：桌號無效。"<<endl;
            continue;
        }
		if(orderCounts[tableNum]==0){
            cout<<"⚠️ 錯誤：該桌無點餐紀錄。"<<endl;
            continue;
    	}
		while(true){
			cout<<"\n--- 桌號 ["<<tableNum<<"] 待出餐清單 ---"<<endl;
			bool hasPending=false;
			for(int i=0;i<orderCounts[tableNum];i++){
				int p=tableOrders[tableNum][i].quantity-tableOrders[tableNum][i].deliveredQty;
				if(p>0){
					cout<<tableOrders[tableNum][i].menuIdx+1<<". "<<left<<setw(18)<<menu[tableOrders[tableNum][i].menuIdx].getName()<<"(尚欠:"<<p<<")"<<endl;
					hasPending=true;
				}
			}
			if(!hasPending){cout<<"此桌餐點已全數送達！"<<endl;break;}
			cout<<"------------------------------------"<<endl;
			cout<<"請輸入「編號 數量」(輸入0返回桌號):";
			if(!(cin>>choice)){
                cin.clear();
                cin.ignore(1000,'\n');
                cout<<"⚠️ 錯誤：無效輸入。"<<endl;
                continue;
            }
			if(choice==0) break;
			if(choice<1||choice>10){
                cout<<"⚠️ 錯誤：編號無效。"<<endl;
                continue;
            }
			if(!(cin>>qty)){
                cin.clear();
                cin.ignore(1000,'\n');
                cout<<"⚠️ 錯誤：數量無效。"<<endl;
                continue;
            }
			if(qty<=0) continue;
			int targetIdx=choice-1,remaining=qty;
			for(int i=0;i<orderCounts[tableNum]&&remaining>0;i++){
				if(tableOrders[tableNum][i].menuIdx==targetIdx){
					int canDeliver=tableOrders[tableNum][i].quantity-tableOrders[tableNum][i].deliveredQty;
					if(canDeliver>0){
						int toAdd=(remaining>canDeliver)?canDeliver:remaining;
						tableOrders[tableNum][i].deliveredQty+=toAdd;
						remaining-=toAdd;
					}
				}
			}
			cout<<"✅ 出餐紀錄更新成功！"<<endl;
		}
	}
}
void OrderingSystem::showPendingList() const{
	cout<<"\n------------------------------------"<<endl;
	cout<<"[ 全場待出餐總量統計 ]"<<endl;
	cout<<"------------------------------------"<<endl;
	bool somethingToDo=false;
	for(int i=0;i<10;i++){
		int totalPending=0;
		for(int t=1;t<=10;t++){
			for(int o=0;o<orderCounts[t];o++){
				if(tableOrders[t][o].menuIdx==i){
					totalPending+=(tableOrders[t][o].quantity-tableOrders[t][o].deliveredQty);
				}
			}
		}
		if(totalPending>0){
			cout<<i+1<<". "<<left<<setw(18)<<menu[i].getName()<<"待做:"<<totalPending<<" 份"<<endl;
			somethingToDo=true;
		}
	}
	if(!somethingToDo)cout<<"🎉 賀！目前全場餐點皆已出齊！"<<endl;
	cout<<"------------------------------------"<<endl;
}
void OrderingSystem::showTableDetails() const{
	cout<<"\n####################################"<<endl;
	cout<<"[ 各桌詳情與出餐進度 ]"<<endl;
	cout<<"####################################"<<endl;
	bool active=false;
	for(int i=1;i<=10;i++){
		if(orderCounts[i]==0) continue;
		active=true;
		int tableSum=0;
		cout<<"[ 桌號 "<<i<<" ]"<<endl;
		for(int j=0;j<orderCounts[i];j++){
			string statusIcon="❌";
			if(tableOrders[i][j].deliveredQty==tableOrders[i][j].quantity) statusIcon="✅";
			else if(tableOrders[i][j].deliveredQty>0) statusIcon="⚠️";
			cout<<tableOrders[i][j].menuIdx+1<<". "<<statusIcon<<" "<<left<<setw(16)<<menu[tableOrders[i][j].menuIdx].getName()<<"x"<<setw(3)<<tableOrders[i][j].quantity<<"$"<<tableOrders[i][j].subtotal<<endl;
			tableSum+=tableOrders[i][j].subtotal;
		}
		cout<<" > 應收合計:$"<<tableSum<<endl;
		cout<<"------------------------------------"<<endl;
	}
	if(!active) cout<<"目前沒有點單紀錄。"<<endl;
}
void OrderingSystem::showTotalStatistics() const{
	cout<<"\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	cout<<"[ 今日收班銷售結算報表 ]"<<endl;
	cout<<"------------------------------------"<<endl;
	for(int i=0;i<10;i++){
		cout<<i+1<<". "<<left<<setw(20)<<menu[i].getName()<<salesCounts[i]<<" 份"<<endl;
	}
	cout<<"------------------------------------"<<endl;
	cout<<"今日總營業額:$"<<totalRevenue<<endl;
	cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
}
