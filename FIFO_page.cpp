#include<bits/stdc++.h>
using namespace std;
void print_list(list <int> frame){
    while(frame.size()>0){
        cout<<frame.front()<<" ";
        frame.pop_front();
    }
    cout<<endl;
}
int main(){
    int n, f, hit=0, fault=0;
    cout<<"Enter size of stream: "<<endl;
    cin>>n;
    cout<<"Enter number of frames: "<<endl;
    cin>>f;
    list <int> frame;
    set <int> have;
    cout<<"Enter stream: "<<endl;
    vector <int> arr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    for(int i=1;i<=n;i++){
        int cur=arr[i-1];
        if(have.find(cur)==have.end()){
            fault++;
            cout<<"Page fault occurred for page "<<arr[i-1]<<endl;
            if(frame.size()>=f){
                int rem=frame.front();
                frame.pop_front();
                have.erase(rem);  
            }
            frame.push_back(cur);
            have.insert(cur);
        }
        else{
            hit++;
            cout<<"Page hit for page "<<arr[i-1]<<endl;
        }
        cout<<"In Physical memory: ";
        print_list(frame);
    }
    double hr=(1.0*hit)/(1.0*n), mr=((1.0*fault)/(1.0*n));
    cout<<"Hit Rate/Number of hits: "<<hr*100.0<<"%    "<<hit<<endl;
    cout<<"Miss Rate/Number of faults: "<<mr*100.0<<"%    "<<fault<<endl;
}