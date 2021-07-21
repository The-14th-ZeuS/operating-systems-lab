#include<bits/stdc++.h>
#define mkp make_pair
#define pb push_back
using namespace std;
int u, v, x;


bool comp(pair < int, pair < int, int> > a, pair < int, pair < int, int> > b)
{
    if (a.second.second < b.second.second) return true;
    else return a.second.first <= b.second.first;
}
int main() {
    vector < pair < int, pair < int, int> > > arr;
    multiset < pair < int, pair <int, int> > > s;
    cout << "Enter number of processes: " << endl;
    int n;
    cin >> n;
    cout << "Enter the process information for the processes as PID/Arrival Time/Burst Time: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> u >> v >> x;
        // u = PID
        // v = arrival time
        // x = Burst time
        arr.pb(mkp(x, mkp(u, v)));
    }
    //sort based on arrival time
    sort(arr.begin(), arr.end(), comp);


    int ct = 0, idx = 0, idx2 = 0;
    int ans[4][n];
    while (true)
    {
        if (idx2 >= n) break;
        if (idx < n) {
            if (arr[idx].second.second > ct) {
                s.insert(arr[idx++]);
            }
            else {
                while (idx < n && arr[idx].second.second <= ct) {
                    s.insert(arr[idx++]);
                }
            }
        }
        pair < int, pair <int, int> > temp = *s.begin();
        s.erase(s.begin());
        ct += temp.first;
        ans[0][idx2] = ct;
        ans[1][idx2] = ct - temp.second.second;
        ans[2][idx2] = ans[1][idx2] - temp.first;
        ans[3][idx2] = temp.second.first;
        idx2++;
    }
    double avg = 0.0, avg2 = 0.0;
    for (int i = 0; i < n; i++) {
        cout << "Process ID: " << ans[3][i] << " CT: " << ans[0][i] << " TAT: " << ans[1][i] << " WT: " << ans[2][i] << endl;
        avg += ans[1][i];
        avg2 += ans[2][i];
    }
    cout << "Avg TAT: " << (avg / n) << endl << "Avg WT: " << (avg2 / n) << endl;
    return 0;
}