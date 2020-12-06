#include<bits/stdc++.h>
#include<mutex>
#include<thread>
#include<chrono>
using namespace std;

int ctr=0;
mutex mtx;


void increase(){
    for(int i=0;i<20000;i++){
        mtx.lock();
        ctr++;
        mtx.unlock();
    }
}

void increase2(){
    for(int i=0;i<20000;i++){
        if(mtx.try_lock()){
            ctr++;
            mtx.unlock();
        }
    }
}

int main(){
    cout<<ctr<<endl;
    cout<<"Start executing- "<<endl;
    thread t1(increase);
    thread t2(increase);
    this_thread::sleep_for(chrono::seconds(5));
    t1.join();
    t2.join();
    cout<<ctr<<endl;
    cout<<"Exiting from main().\n";
    return 0;
}