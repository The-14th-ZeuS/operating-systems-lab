#include<bits/stdc++.h>
#define rep(i,a,n)      for(int i=a;i<n;i++)
#define all(a)          a.begin(), a.end()
#define display(a)      for(auto x: a) cout<<x<<" "; cout<<"\n";
#define w(t)            int t; cin>>t; while(t--)
using namespace std;
typedef vector < int > vii;

int main(){
    
    cout<<"Enter number of processes: "<<endl;
	int n;
	cin>>n;
	cout<<"Enter number of resources: "<<endl;
	int m;
	cin>>m;
	vii arr(n);
	map <int, vii> maxneed, allocation;
	vii available(m), total(m);
	rep(i,0,n){
		maxneed[i].resize(m);
		allocation[i].resize(m);
	}
    /////////////////////////////////////////////
    //Input
    /////////////////////////////////////////////
	cout<<"Enter process information as PID / Maximum Need Vector / Initial Allocation Vector: "<<endl;
	cout<<"(PIDs are 0-indexed)"<<endl;
	rep(i,0,n){
		int id;
		cin>>id;
		arr[i]=id;
		rep(ii,0,m){
			int temp;
			cin>>temp;
			maxneed[id][ii]=temp;
		}
		rep(ii,0,m){
			int temp;
			cin>>temp;
			allocation[id][ii]=temp;
			available[ii]+=temp;
		}
	}
	cout<<"Enter number of resource instances: "<<endl;
	rep(i,0,m){
		cin>>total[i];
		available[i]=total[i]-available[i];
	}
	sort(all(arr));
//	cout<<"Total instances of resources: "<<endl;
//	display(total);
//	cout<<"Total instances of resources available after initial allocation: "<<endl;
//	display(available);
//	rep(i,0,n){
//		cout<<arr[i]<<" : "<<endl;
//		rep(ii,0,m){
//			cout<<maxneed[arr[i]][ii]<<" ";
//		}
//		cout<<endl;
//		rep(ii,0,m){
//			cout<<allocation[arr[i]][ii]<<" ";
//		}
//		cout<<endl;
//	}
    /////////////////////////////////////////////
    //Checking all safe sequences
    /////////////////////////////////////////////
	set <vii> s;
	vii temp=available;
	do{	
		available=temp;
		int flag=1;
		rep(idx,0,n){
			vii need(m);
			rep(i,0,m){
				need[i]=maxneed[arr[idx]][i]-allocation[arr[idx]][i];
				if(need[i]>available[i]){
					flag=0;
					break;
				}
			}
			if(flag==0) break;
			else rep(i,0,m) available[i]+=(allocation[arr[idx]][i]);
		}
		if(flag==0) continue;
		else s.insert(arr);
	}while(next_permutation(all(arr)));
	/////////////////////////////////////////////
    //Displaying all safe sequences
    /////////////////////////////////////////////
    cout<<"All possible safe sequences: "<<endl;
	for(auto i:s){
		display(i);
		rep(ii,0,n+5) cout<<"-";
		cout<<endl;
	}
	/////////////////////////////////////////////
    //Checking input sequences
    /////////////////////////////////////////////
    cout<<"Enter number of sequences to check: "<<endl;
	w(t){
		cout<<"Enter sequence: "<<endl;
		vii seq(n);
		rep(i,0,n) cin>>seq[i];
		(!(s.find(seq)==s.end())) && cout << "This is a safe sequence." || cout << "This is not a safe sequence."; cout << '\n';
	}
    return 0;
}