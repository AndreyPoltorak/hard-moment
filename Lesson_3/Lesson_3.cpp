

#include <iostream>
#include <list>
#include <vector>

using namespace std;

void AddArithmeticMean(list<double> &ls) 
{
    double ArithmeticMean{};
    for (const auto& l : ls)
    {
        ArithmeticMean += l;
    }
    ls.push_back(double(ArithmeticMean / ls.size()));

}

int Matrix2Order(vector<vector<int>> matrix)
{
    return  matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

vector<vector<int>> TransformationMatrix(vector<vector<int>> matrix, int k)
{
    vector<vector<int>> newMatrix{};
    for (int i=1;i<matrix.size();i++)
    {
        vector<int> V{};
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (j != k)
            {
                V.push_back(matrix[i][j]);
            }
        }
        newMatrix.push_back(V);
    }

    return newMatrix;
}

int MatrixNOrder(vector<vector<int>> matrix)
{
    int N = matrix.size();
    if ( N == 2)
    {
        return Matrix2Order(matrix);
    }
    else
    {
        int result{};
        for (int i = 0; i < N; i++)
        {
            result += matrix[0][i] * pow(-1, 1 + i) * MatrixNOrder(TransformationMatrix(matrix,i));
        }
        return result;
    }
}

class MyItterator 
{
    vector<int> v{};
public:
    MyItterator(vector<int>& vec)
    {
        v = vec;
    }

    vector <int> ::iterator begin()
    {
        return v.begin();
    }

    vector <int> ::iterator end()
    {
        return v.end();
    }
};



int main()
{
    list<double> ls{ 1.2,4.3,5.7,2.2 };

    AddArithmeticMean(ls);

    vector<vector<int>> Matrix{
        {-2,1,3,2},
        {3,0,-1,2},
        {-5,2,3,0},
        {4,-1,2,-3}
    };

    int k = MatrixNOrder(Matrix);

    vector<int> v{ 1,2,3,4,5,6,7,8,9 };
    MyItterator it(v);

    for (const auto& p : it)
    {
        cout << p << " ";
    }

    std::cout << "Hello World!\n";
}

