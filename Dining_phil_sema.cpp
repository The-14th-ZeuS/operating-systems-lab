#include <bits/stdc++.h>
#include <mutex>
#include <thread>


using namespace std;
const int N = 8;

//Semaphore class implementation
class Semaphore {
private:
  bool signaled;   
  pthread_mutex_t m;
  pthread_cond_t  c;

  void Lock() { pthread_mutex_lock(&m); }          
  void Unlock() { pthread_mutex_unlock(&m); }
public:
  Semaphore();
  void P();   
  void V();
};

Semaphore::Semaphore(){      
    signaled = true;
    c = PTHREAD_COND_INITIALIZER;    
    m = PTHREAD_MUTEX_INITIALIZER;   
}

void Semaphore::P(){
    Lock();              
    while (!signaled){   
        pthread_cond_wait(&c, &m);
    }
    signaled = false;
    Unlock();
}

void Semaphore::V(){
    bool previously_signaled;
    Lock();
    previously_signaled = signaled; 
    signaled = true;
    Unlock();  
    if (!previously_signaled)
      pthread_cond_signal(&c); 
}

void eat(Semaphore &left_fork, Semaphore &right_fork, int number) {
        
        left_fork.P();
        right_fork.P();

        cout << "Philosopher " << number << " is eating." << endl;
        
        this_thread::sleep_for(chrono::seconds(2));
        
        cout << "\nPhilosopher " << number << " has finished eating." << endl;
        right_fork.V();
        left_fork.V();
    }
int main()
{
    Semaphore forks[N];
    
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