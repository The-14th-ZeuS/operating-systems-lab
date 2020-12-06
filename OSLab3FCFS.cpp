#include<bits/stdc++.h>
using namespace std;
bool comp(pair < int, pair < int, int> > a, pair < int, pair < int, int> > b){
    if(a.second.first<b.second.first) return true;
    else return a.first<=b.first;
}
int main(){
    vector < pair < int, pair < int, int> > > arr;
    cout<<"Enter number of processes: "<<endl;
    int n;
    cin>>n;
    arr.resize(n);
    cout<<"Enter the process information for the processes as PID/Arrival Time/Burst Time: "<<endl;
    for(int i=0;i<n;i++)    cin>>arr[i].first>>arr[i].second.first>>arr[i].second.second;
    sort(arr.begin(), arr.end(), comp);
    vector <int> ct(n), tat(n), wt(n);
    wt[0]=0;
    tat[0]=ct[0]=arr[0].second.second;
    for(int i=1;i<n;i++){
        ct[i]=max(ct[i-1],arr[i].second.first)+arr[i].second.second;
        tat[i]=ct[i]-arr[i].second.first;
        wt[i]=tat[i]-arr[i].second.second;
    }
    for(int i=0;i<n;i++){
        cout<<"Process ID- "<<arr[i].first<<" /CT-"<<ct[i]<<" /TAT-"<<tat[i]<<" /WT- "<<wt[i]<<endl;
    }
    double avg1, avg2;
    avg1=accumulate(wt.begin(), wt.end(),0.0);
    avg2=accumulate(tat.begin(), tat.end(),0.0);
    cout<<"Avg TAT: "<<(avg2/n)<<endl;
    cout<<"Avg WT: "<<(avg1/n)<<endl;
    return 0;
}