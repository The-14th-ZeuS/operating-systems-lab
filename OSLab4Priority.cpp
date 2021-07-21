#include<bits/stdc++.h>


//Some macros to make my life easier - please do not mind :D
#define fi first
#define se second
#define mkp make_pair
#define pb push_back


using namespace std;
bool cmp(pair <int, pair <int, int> > a, pair <int, pair <int, int> > b)
{
    if (a.se.se < b.se.se) return true;
    else return a.se.fi < b.se.fi;
}
int main()
{
    vector < pair <int, pair <int, int> > > arr;
    vector <int> arrival, burst, ct;
    cout << "Enter number of processes: " << endl;
    int n;
    cin >> n;
    arrival.resize(n + 1);
    burst.resize(n + 1);
    ct.resize(n + 1);
    cout << "Enter process information as PID / Priority / Arrival Time / Burst time: " << endl;
    for (int i = 0; i < n; i++) {
        int u, v, x, y;
        cin >> v >> u >> x >> y;
        // v = PID
        // u = Priority
        // x = Arrival time
        // y = Burst time
        arr.pb(mkp(u, mkp(v, x)));
        arrival[v] = x;
        burst[v] = y;
    }
    //Sort based on arrival time, then priority
    sort(arr.begin(), arr.end(), cmp);
    // for(int i=0;i<n;i++){
    //     cout<<arr[i].fi<<" "<<arr[i].se.fi<<" "<<arr[i].se.se<<endl;
    // }
    vector <int> btemp = burst;
    multiset < pair < int, pair <int, int> > > s;
    int time = 0, idx = 0;
    while (true)
    {
        while (idx < n && arr[idx].se.se <= time)
        {
            s.insert(mkp(arr[idx].fi, mkp(arr[idx].se.se, arr[idx].se.fi)));
            idx++;
        }
        if (s.empty()) break;
        auto itr = s.end();
        itr--;
        pair < int, pair <int, int> > temp = *itr;
        s.erase(itr);
        btemp[temp.se.se]--;
        if (btemp[temp.se.se] > 0) {
            s.insert(temp);
        }
        else {
            ct[temp.se.se] = time + 1;
        }
        time++;
    }

    vector <int> tat, wt;
    tat = ct, wt = ct;
    for (int i = 0; i < n + 1; i++) {
        tat[i] -= arrival[i];
        wt[i] = tat[i] - burst[i];
    }
    cout << "PID\tCT\tTAT\tWT" << endl << "------------------------------------" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << i << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }
    cout << endl;
    double avg1, avg2;
    avg1 = accumulate(tat.begin(), tat.end(), 0.0);
    avg2 = accumulate(wt.begin(), wt.end(), 0.0);
    avg1 /= n;
    avg2 /= n;
    cout << "Average TAT: " << avg1 << "\nAverage WT: " << avg2 << endl;
    cout << "Throughput: " << ((double)n / (1.0 * time)) << endl;
    cout << endl;
}