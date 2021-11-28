
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime> 
#include <numeric>
using namespace std;

template <typename T1,typename T2>
bool insert_sorted(T1& vec, T2 i)
{
	vector<T2> v(vec.size());
	copy(vec.begin(), vec.end(), v.begin());
	if (v[0] > v[v.size() - 1])
	{
		sort(v.begin(), v.end());
		v.insert(lower_bound(v.begin(), v.end(), i), i);
		sort(v.rbegin(), v.rend());

	}
	else
	{
		v.insert(lower_bound(v.begin(), v.end(), i), i);
	}
	vec.resize(v.size());
	copy(v.begin(), v.end(), vec.begin());
	
	return true;
}


/*bool insert_sorted(vector<int>& v, int i)
{
   int n = v.size();
   switch (n)
   {
   case (0):
   {
	   return false;
   }
   case(1):
   {
	   if (i>v[0])
	   {
		   v.push_back(i);
	   }
	   else
	   {
		   v.insert(v.begin(), i);
	   }

	   return true;
   }
   default:
	   if (v[0] > v[v.size()-1])
	   {
		   sort(v.begin(), v.end());
		   v.insert(lower_bound(v.begin(), v.end(), i), i);
		   sort(v.rbegin(), v.rend());
		  
	   }
	   else
	   {
		   v.insert(lower_bound(v.begin(), v.end(), i), i);
	   }
	   return true;
   }
   
   
}*/



int main()
{
   
	list<double> v1{ 1,1,2,2,4,4,5,5 };
	insert_sorted(v1, 3);
	for (auto& i : v1)
	{
		cout << i << " ";
	}
	cout << endl;
	vector<int> v2{ 5,5,4,4,2,2,1,1,0,0 };
	insert_sorted(v2, 3);
	for (auto& i : v2)
	{
		cout << i << " ";
	}
	cout << endl;

	srand(time(NULL));
	vector<double> A(100);
	generate(A.begin(), A.end(), []() {return double((rand() % 100) + double((rand() % 100) / 100.0)); });
	vector<int> B(100);
	int i = 0;
	generate(B.begin(), B.end(), [A,&i]() {
		return int(A[i++]); 
		});
	i = 0;
	auto summ = accumulate(A.begin(), A.end(), 0.0, [B,&i](double x, double y) 
		{
			auto s = powf(double(y - B[i++]), 2);
			return double(x+s); 
		});

	

    std::cout <<"Task_2: "<< summ << endl;
}

