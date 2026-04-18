#include "system.h"
#include <iostream>
#include <iomanip>
using namespace std;
System::System(){
    totalM=0;  //總收入歸零
	for(int i=0;i<11;i++) count[i]=0; //每桌點的歸零
	for(int i=0;i<10;i++) salesCount[i]=0;  //每樣菜售出數量歸零
	set(m);  //設定菜單
}
void System::show()const{  //顯示菜單
	cout<<"\n--- 菜單列表 ---"<<endl;
	for(int i=0;i<10;i++){
		cout<<i+1<<"."<<m[i].getN()<<" $"<<m[i].getP()<<endl;
	}
}
void System::add(){  //點餐
	int t,c,q;  //t:桌號,c:餐點編號,q:數量
	while(true){
		cout<<"請輸入桌號(1~10):";
        cin>>t;
        if(t>=1&&t<=10){
            break;
        }else{
            cout<<"錯誤：請輸入1~10之間的數字桌號！"<<endl;
            cin.clear();
			cin.ignore(1000,'\n');
            return;
        }
	}
	while(true){
		cout<<"輸入餐點編號(1~10)與數量 (輸入0結束點餐):";
		if(!(cin>>c)){  //如果c是字母之類的
			cout<<"錯誤：編號必須為數字！"<<endl;
			cin.clear();
			cin.ignore(1000,'\n');
			continue;
		}
		if(c==0)break;
		if(!(cin>>q)||c<1||c>10||q<=0){  //驗證餐點編號跟數量(最多50)
			cout<<"錯誤：餐點編號或數量錯誤！"<<endl;
			cin.clear();
			cin.ignore(1000,'\n');
			continue;
		}
		int s=m[c-1].getP()*q;  //s:計算該項金額
		totalM+=s;
		salesCount[c-1]+=q;
        
		int i=count[t];
        count[t]++;
		data_id[t][i]=c-1;
		data_n[t][i]=q;
		data_p[t][i]=s;
		cout<<">> 已點："<<m[c-1].getN()<<" x "<<q<<endl;
	}
}
void System::view()const{  //查看各桌
	bool empty=true;
	for(int i=1;i<=10;i++){
		if(count[i]==0) continue;
		empty=false;
		int total=0;
		cout<<"[桌號 "<<i<<"]"<<endl;
		for(int j=0;j<count[i];j++){
			cout<<" - "<<m[data_id[i][j]].getN()<<" x "<<data_n[i][j]<<endl;
			total+=data_p[i][j];
		}
		cout<<" 桌小計:"<<total<<endl;
	}
	if(empty) cout<<"目前無任何桌況資料。"<<endl;  //如果全部都沒有的話
}
void System::sum()const{  //結算
	cout<<"\n======== 今日銷售結算 ========"<<endl;
	for(int i=0;i<10;i++){
		cout<<m[i].getN()<<": 售出 "<<salesCount[i]<<" 份"<<endl;
	}
	cout<<"----------------------------"<<endl;
	cout<<"今日總營收: $"<<totalM<<endl;
	cout<<"============================"<<endl;
}