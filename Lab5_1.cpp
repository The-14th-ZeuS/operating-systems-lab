#include<bits/stdc++.h>
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
using namespace std;
bool cmp(pair < pair <int, int>  , pair <int, int> > a, pair < pair <int, int>  , pair <int, int> > b){
    if(a.fi.se<b.fi.se) return true;
    else if(a.fi.se==b.fi.se && a.fi.fi<=b.fi.fi) return true;
    else return false; 
}
int main(){
    int n;
    cout<<"Enter the number of processes: "<<endl;
    cin>>n;
    vector < pair < pair <int, int>  , pair <int, int> > > arr;
    vector <int> burst(n+1), ct(n+1), tat(n+1), wt(n+1), arrival(n+1);
    cout<<"Enter process information as : PID/ Arrival Time/ Burst Time/ Process Type(0 for system | 1 for user) - "<<endl;
    for(int i=0;i<n;i++){
        int u,v,x,y;
        cin>>u>>v>>x>>y;
        arr.pb(mkp(mkp(y,v), mkp(u,x)));
        arrival[u] = v;
        burst[u] = x;
    }
    sort(arr.begin(), arr.end(), cmp);
    // cout<<"Type\tArrival\tPID\tBurst"<<endl;
    // for(int i=0;i<n;i++){
    //     cout<<arr[i].fi.fi<<" "<<arr[i].fi.se<<" "<<arr[i].se.fi<<" "<<arr[i].se.se<<endl;
    // }
    multiset < pair < pair <int, int>  , pair <int, int> > > s;
    int idx = 0, time = 0;
    cout<<"Sequence of execution: "<<endl;
    while(true){
        while(idx<n && arr[idx].fi.se<=time){
            s.insert(arr[idx++]);
        }
        if(s.empty()) break;
        pair < pair <int, int>  , pair <int, int> >  temp = *s.begin();
        // cout<<time<<endl;
        s.erase(s.begin());
        // cout<<temp.fi.fi<<" "<<temp.fi.se<<" "<<temp.se.fi<<" "<<temp.se.se<<endl;
        if(temp.fi.fi==0){
            time+=temp.se.se;
            for(int i=0;i<temp.se.se;i++) cout<<"P"<<temp.se.fi<<" ";
            ct[temp.se.fi]=time;
        }
        else{
            time++;
            temp.se.se--;
            cout<<"P"<<temp.se.fi<<" ";
            if(temp.se.se>0){
                s.insert(temp);
            }
            else ct[temp.se.fi]=time;
        }
    }
    cout<<endl;
    for(int i=1;i<=n;i++){
        tat[i]=ct[i]-arrival[i];
        wt[i]=tat[i]-burst[i];
    }
    double avgp=0.0, avgp2=0.0;
    for(int i=1;i<n+1;i++){
        cout<<"Process ID:\t"<<i<<" CT:\t"<<ct[i]<<" TAT:\t"<<tat[i]<<" WT:\t"<<wt[i]<<endl;
        avgp+=tat[i];
        avgp2+=wt[i];
    }
    avgp/=n;
    avgp2/=n;
    cout<<"Avg TAT: "<<(avgp)<<endl<<"Avg WT: "<<(avgp2)<<endl;
}