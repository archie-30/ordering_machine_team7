#include <iostream>
#include "system.h"
using namespace std;

int main(){
	System p;
	int m;
	while(true){
		cout<<"\n[ 簡易收銀系統 ]"<<endl;
		cout<<"1.點餐 2.桌況 3.菜單 0.今日結算"<<endl;
		cout<<"項目:";
        cin>>m;
		if(m==0||m==1||m==2||m==3){
			switch(m){
				case 1:
                    p.add();
                    break;
				case 2:
                    p.view();
                    break;
				case 3:
                    p.show();
                    break;
				case 0:
                    p.sum();
                    break;
			}
			if(m==0)break;
		}else{
			cout<<"錯誤：請輸入0到3的有效功能數字！"<<endl;
            cin.clear();
			cin.ignore(1000,'\n');
		}
	}
	return 0;
}