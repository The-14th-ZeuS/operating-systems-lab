#include<bits/stdc++.h>
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
using namespace std;
int u,v,x;
bool comp(pair < int, pair < int, int> > a, pair < int, pair < int, int> > b){
    if(a.second.second<b.second.second) return true;
    else return a.second.first<=b.second.first;
}
int main(){
    vector < pair < int, pair < int, int> > > arr;
    multiset < pair < int, pair <int, int> > > s, s2;
    cout<<"Enter number of processes: "<<endl;
    int n;
    cin>>n;
    cout<<"Enter the process information for the processes as PID/Arrival Time/Burst Time: "<<endl;
    for(int i=0;i<n;i++){
        cin>>u>>v>>x;
        arr.pb(mkp(x,mkp(u,v)));
    }
    sort(arr.begin(), arr.end(),comp);
    int ct=0,idx=0,idx2=0;
    int ans[4][n];
    while(true){
        if(idx2>=n) break;
        if(idx<n){
            if(arr[idx].second.second>ct){
            s.insert(arr[idx++]);
        }
        else{
            while(idx<n && arr[idx].second.second<=ct){
                s.insert(arr[idx++]);
            }
        }
        }
        pair < int, pair <int,int> > temp=*s.begin();
        s.erase(s.begin());
        ct+=temp.first;
        ans[0][idx2]=ct;
        ans[1][idx2]=ct-temp.second.second;
        ans[2][idx2]=ans[1][idx2]-temp.first;
        ans[3][idx2]=temp.second.first;
        idx2++;
    }
    double avg=0.0, avg2=0.0;
    for(int i=0;i<n;i++){
        cout<<"Process ID:\t"<<ans[3][i]<<" CT:\t"<<ans[0][i]<<" TAT:\t"<<ans[1][i]<<" WT:\t"<<ans[2][i]<<endl;
        avg+=ans[1][i];
        avg2+=ans[2][i];
    }
    avg/=n;
    avg2/=n;
    cout<<"Avg TAT for non-preemptive: "<<(avg)<<endl<<"Avg WT for non-preemptive: "<<(avg2)<<endl;
    cout<<"--------------------------------------------------------------------------------------"<<endl;
    ct=0,idx=0,idx2=0;
    int tq=1;
    vector <int> burst(n+1), ct2(n+1), tat(n+1), wt(n+1), arrival(n+1);
    for(int i=0;i<n;i++) burst[arr[i].se.fi]=arr[i].fi, arrival[arr[i].se.fi]=arr[i].se.se;
    for(int i=1;i<n+1;i++) cout<<arrival[i]<<" "<<burst[i]<<endl;
    while(true){
        while(idx<n && arr[idx].se.se<=ct){
            s2.insert(arr[idx]);
            idx++;
        }
        if(s2.empty()) break;
        pair <int, pair <int, int> > temp = *s2.begin();
        s2.erase(s2.begin());
        if(temp.fi>=tq){
            temp.fi-=tq;
            ct+=tq;
            if(temp.fi){
                s2.insert(temp);
            }
            else ct2[temp.se.fi]=ct;
        }
        else{
            ct+=temp.fi;
            ct2[temp.se.fi]=ct;
        }
    }
    for(int i=1;i<=n;i++){
        tat[i]=ct2[i]-arrival[i];
        wt[i]=tat[i]-burst[i];
    }
    double avgp=0.0, avgp2=0.0;
    for(int i=1;i<n+1;i++){
        cout<<"Process ID:\t"<<i<<" CT:\t"<<ct2[i]<<" TAT:\t"<<tat[i]<<" WT:\t"<<wt[i]<<endl;
        avgp+=tat[i];
        avgp2+=wt[i];
    }
    avgp/=n;
    avgp2/=n;
    cout<<"Avg TAT for preemptive: "<<(avgp)<<endl<<"Avg WT for preemptive: "<<(avgp2)<<endl;
    cout<<"Difference between TAT and WT: "<<abs(avg-avgp)<<" & "<<abs(avg2-avgp2)<<" respectively."<<endl;
    return 0;
}