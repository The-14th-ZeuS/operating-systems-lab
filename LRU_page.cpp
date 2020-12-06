#include<bits/stdc++.h>
using namespace std;
void print_set(set < pair <int, int> > frame){
    while(frame.size()>0){
        cout<<frame.begin()->second<<" ";
        frame.erase(frame.begin());
    }
    cout<<endl;
}
int main(){
    int n, f, hit=0, fault=0;
    cout<<"Enter size of stream: "<<endl;
    cin>>n;
    cout<<"Enter number of frames: "<<endl;
    cin>>f;
    set < pair <int, int> > frame;
    cout<<"Enter stream: "<<endl;
    vector <int> arr(n);
    vector <bool> have(n+1, false);
    vector <int> last(n+1, -1);
    for(int i=0;i<n;i++) cin>>arr[i];
    for(int i=1;i<=n;i++){
        int cur=arr[i-1];
        if(!have[cur]){
            fault++;
            cout<<"Page fault occurred for page "<<arr[i-1]<<endl;
            if(frame.size()>=f){
                have[frame.begin()->second]=0;
                frame.erase(frame.begin()); 
            }
            have[cur]=1;
            frame.insert({i, cur});
            last[cur]=i;
        }
        else{
            hit++;
            auto itr=frame.find({last[cur], cur});
            frame.erase(itr++);
            last[cur]=i;
            frame.insert({last[cur], cur});
            cout<<"Page hit for page "<<arr[i-1]<<endl;
        }
        cout<<"In Physical memory: ";
        print_set(frame);
    }
    double hr=(1.0*hit)/(1.0*n), mr=((1.0*fault)/(1.0*n));
    cout<<"Hit Rate/Number of hits: "<<hr*100.0<<"%    "<<hit<<endl;
    cout<<"Miss Rate/Number of faults: "<<mr*100.0<<"%    "<<fault<<endl;
}