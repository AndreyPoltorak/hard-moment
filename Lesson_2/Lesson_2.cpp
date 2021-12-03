

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Timer.h"

using namespace std;

void Swap(int *&p1, int *&p2)
{
    int* p3 = p1;
    p1 = p2;
    p2 = p3;
    
}

void SortPointers(vector<int>*vec)
{
    sort(vec->begin(), vec->end());
}

bool findFirstWay(unsigned char h)
{
    h = toupper(h);
    if (h == 'A' || h == 'E' || h == 'I' || h == 'O' || h == 'U')
    {
        return true;
    }
    return false;
}

int  firstWay(vector<unsigned char> &vec)
{
    
    return count_if(vec.begin(), vec.end(), findFirstWay);
}

bool findFirstWay1(unsigned char h)
{
    string s = "AEIOU";
    h = toupper(h);
    for (auto s1 : s)
    {
        if (h == s1)
            return true;
    }
    return false;
}

int  firstWay1(vector<unsigned char>& vec)
{

    return count_if(vec.begin(), vec.end(), findFirstWay1);
}

int  firstWay2(vector<unsigned char>& vec)
{
    int count = 0;
    string s = "AEIOU";
    for (auto& c : vec)
    {
       
        c = toupper(c);
        for (auto s1 : s)
        {
            if (c == s1)
            {
                count++;
                break;
            }
               
        }
    }
    return count;
}

int main()
{
    int* p1 = new int(10);
    int* p2 = new int(30);
    
    cout << "p1 = " << *p1 << "  p2 = " << *p2 <<endl;
    Swap(p1, p2);
    cout << "p1 = " << *p1 << "  p2 = " << *p2 <<endl;

    vector<int>* vec = new vector<int>{1,2,23,33,32,545,4,3,5,};
    for (auto& p : *vec)
    {
        cout << p << " ";
    }
    cout << endl;
    SortPointers(vec);
    for (auto& p : *vec)
    {
        cout << p << " ";
    }
    cout << endl;


    ifstream file("Book.txt");
    file.seekg(0, ios::end); // перемещаемся в конец файла
    int size_file = file.tellg();
    file.seekg(0, ios::beg);
    vector<unsigned char> book(size_file);
    file.read((char*)&book[0], size_file);
    
    Timer timer;
    timer.start("test1");
    cout << firstWay(book) << endl; // my way of solving
    timer.print();
    timer.start("test2");
    cout << firstWay1(book) << endl; // count_if and for
    timer.print();
    timer.start("test3");
    cout << firstWay1(book) << endl; // for and for
    timer.print();

}

