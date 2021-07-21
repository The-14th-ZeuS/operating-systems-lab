#include <bits/stdc++.h>
#include <mutex>
#include <thread>

using namespace std;
const int N = 8;
    
    
struct fork{
    public:
        fork(){;}
        mutex mu;
};

void eat(fork &left_fork, fork &right_fork, int number) {
        
        left_fork.mu.lock();
        right_fork.mu.lock();

        cout << "Philosopher " << number << " is eating." << endl;
        
        this_thread::sleep_for(chrono::seconds(2));
        
        cout << "\nPhilosopher " << number << " has finished eating." << endl;
        
        right_fork.mu.unlock();
        left_fork.mu.unlock();
    }
int main()
{
    fork forks[N];
    
    thread philosopher[N];
    
    cout << "Philosopher " << 1 << " is thinking." << endl;
    philosopher[0] = thread(eat, ref(forks[0]), ref(forks[N-1]), 1);
    
    for(int i = 1; i < N; ++i) {
        cout << "Philosopher " << (i+1) << " is thinking." << endl;
        philosopher[i] = thread(eat, ref(forks[i]), ref(forks[i-1]), (i+1));
    }
    
    for(auto &ph: philosopher) ph.join();
    
    
    return 0;
}