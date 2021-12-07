

#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <mutex>
#include <vector>
#include <algorithm>

using namespace std;

mutex m;



void pcout(string out)
{
    m.lock();
    cout << out <<endl;
    m.unlock();
}


void SequencePrimeNumbers(int i,int &k)
{
    vector<int> PrimeNumbers{ 1,2,3};
    if (i > 3)
    {
        int number = 4;
        int primenumber = 3;
        int size = 3;
        while (i > size)
        {
            bool prime = true;
            for (int j = 2; j <= number / 2; j++)
            {
                if (number % j == 0)
                {
                    prime = false;
                    break;
                }
            }
            if (prime)
            {
                primenumber = number;
                
                size++;
                m.lock();
                k = size;
                m.unlock();
            }
            number++;
        }
        m.lock();
        cout << "result : " << primenumber << endl;
        m.unlock();
    }
    else
    {
        m.lock();
        cout << "result : " << PrimeNumbers[i-1] << endl;
        m.unlock();
    }
   
}

void print(int i, int& k)
{
    while (i > k)
    {
        
        m.lock();
        cout << k << ":" << i << endl;
        m.unlock();
        this_thread::sleep_for(1s);
    }
   
}

void addThings(vector<int>& things)
{
    while (things.size() != 0)
    {
        m.lock();
        things.push_back(rand() % 100);
        m.unlock();
        this_thread::sleep_for(1s);
    }

}

void deleteThings(vector<int>& things)
{
    while (things.size() != 0)
    {
        m.lock();
        auto p = max_element(things.begin(), things.end());
        things.erase(p);
        m.unlock();
        this_thread::sleep_for(500ms);
    }

}


int main()
{
    thread th1(pcout, "thread_1");
    thread th2(pcout, "thread_2");
    thread th3(pcout, "thread_3");
    th1.join();
    th2.join();
    th3.join();
    int k = 0;
    thread th4(SequencePrimeNumbers, 10000,ref(k));
    thread th5(print, 10000, ref(k));
    th4.join();
    th5.join();
    vector<int> hom{ 22,14,54,67,45,34,32,21,87,54,54,32,66 };
   
   
        thread owner(addThings, ref(hom));
        thread thief(deleteThings, ref(hom));
        owner.join();
        thief.join();
    
    

}

