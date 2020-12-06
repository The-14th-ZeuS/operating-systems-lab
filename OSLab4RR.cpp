#include<bits/stdc++.h>
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
using namespace std;
bool cmp(pair <int, pair <int,int> > a, pair <int, pair <int,int> > b){
    if(a.se.fi<b.se.fi) return true;
    else return a.fi<b.fi;
}
int main(){
    cout<<"Enter number of processes: "<<endl;
    int n; cin>>n;
    vector < pair <int, pair <int, int> > > arr;
    vector <int> btemp(n+1), ct(n+1), tat(n+1), wt(n+1), rt(n+1,-1), bt(n+1), at(n+1);
    cout<<"Enter process information as PID/ Arrival Time/ Burst Time: "<<endl;
    for(int i=0;i<n;i++){
        int u,v,x;
        cin>>u>>v>>x;
        arr.pb(mkp(u,mkp(v,x)));
        btemp[u]=x;
        bt[u]=x;
        at[u]=v;
    }
    sort(arr.begin(), arr.end(), cmp);
    // for(int i=0;i<n;i++){
    //     cout<<arr[i].fi<<" "<<arr[i].se.fi<<" "<<arr[i].se.se<<endl;
    // }
    queue < pair <int, pair <int, int> > > q;
    pair <int, pair <int, int> > temp2;
    temp2.fi=-1;
    int time=0, tq=1, idx=0;
    while(true){
        while(idx<n && arr[idx].se.fi<=time){
            q.push(arr[idx]);
            idx++;
        }
        if(temp2.fi!=-1){
            q.push(temp2);
        }
        if(q.empty()) break;
        pair <int, pair <int, int> > temp=q.front();
        q.pop();
        if(rt[temp.fi]==-1){
            rt[temp.fi]=time;
        }
        if(btemp[temp.fi]<tq){
            time+=btemp[temp.fi];
            ct[temp.fi]=time;
            temp2.fi=-1;
        }
        else{
            btemp[temp.fi]-=tq;
            if(btemp[temp.fi]){
                temp2=temp;
            }
            else{
                ct[temp.fi]=time+tq;
                temp2.fi=-1;
            }
            time+=tq;
        }
    }
    for(int i=1;i<n+1;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        rt[i]-=at[i];
    }
    double avgq11, avgq12;
    avgq11=accumulate(tat.begin(), tat.end(), 0.0);
    avgq12=accumulate(wt.begin(), wt.end(), 0.0);
    avgq11/=n;
    avgq12/=n;
    for(int i=1;i<n+1;i++){
        rt[i]=-1;
        ct[i]=0;
        tat[i]=0;
        
    }
    btemp=bt;
    time=0;tq=2;idx=0;
    temp2.fi=-1;
    while(true){
        while(idx<n && arr[idx].se.fi<=time){
            q.push(arr[idx]);
            idx++;
        }
        if(temp2.fi!=-1){
            q.push(temp2);
        }
        if(q.empty()) break;
        pair <int, pair <int, int> > temp=q.front();
        q.pop();
        if(rt[temp.fi]==-1){
            rt[temp.fi]=time;
        }
        if(btemp[temp.fi]<tq){
            time+=btemp[temp.fi];
            ct[temp.fi]=time;
            temp2.fi=-1;
        }
        else{
            btemp[temp.fi]-=tq;
            if(btemp[temp.fi]){
                temp2=temp;
            }
            else{
                ct[temp.fi]=time+tq;
                temp2.fi=-1;
            }
            time+=tq;
        }
    }
    for(int i=1;i<n+1;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        rt[i]-=at[i];
    }
    cout<<"PID\tCT\tTAT\tWT\tRT"<<endl;
    cout<<"-------------------------------------"<<endl;
    for(int i=1;i<=n;i++){
        cout<<i<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\t"<<rt[i]<<endl;
    }
    double avgq21, avgq22;
    avgq21=accumulate(tat.begin(), tat.end(), 0.0);
    avgq22=accumulate(wt.begin(), wt.end(), 0.0);
    avgq21/=n;
    avgq22/=n;
    cout<<"Average TAT: "<<avgq21<<endl;
    cout<<"Average WT: "<<avgq22<<endl;
    cout<<"Throughput: "<<((1.0*n)/(1.0*time))<<endl;
    cout<<"Difference between Avg TAT at Q=1 & Q=2: "<<avgq21-avgq11<<endl;
    cout<<"Difference between Avg WT at Q=1 & Q=2: "<<avgq12-avgq22<<endl;
}