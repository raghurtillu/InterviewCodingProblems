#include <iostream>
#include <vector>

using namespace std;

// Compute array product without using division
// e.g. input [1, 2, 3, 4, 5]
// output:    [(2*3*4*5), (1*3*4*5), (1*2*4*5), (1*2*3*5), (1*2*3*4) ]
//
// this procedure uses O(n) space
vector<int> ArrayProduct(const vector<int>& inputs)
{
    if (inputs.empty())
    {
        return inputs;
    }

    // left: [(1),        (1),     (1*2), (1*2*3), (1*2*3*4)]
    // rite: [(2*3*4*5),  (3*4*5), (4*5), (5),     (1)]

    // create 2 vectors, left and right
    vector<int> left(inputs.size()), right(inputs.size());
    
    // populate left
    int leftProd = left[0] = 1;
    for (size_t i = 1; i < inputs.size(); ++i)
    {
        leftProd = leftProd * inputs[i-1];
        left[i] = leftProd;
    }

    int rightProd = right[right.size()-1] = 1;
    for (size_t i = right.size()-2; i != SIZE_MAX; --i) 
    {
        rightProd = rightProd * inputs[i+1];
        right[i] = rightProd;
    }

    vector<int> products(inputs.size());
    for (size_t i = 0; i < inputs.size(); ++i)
    {
        products[i] = left[i] * right[i];
    }

    return products;
}

// this procedure uses O(n) space
vector<int> ArrayProductOpt(const vector<int>& inputs)
{
    if (inputs.empty())
    {
        return inputs;
    }

    vector<int> product(inputs.size());
    
    // iterate on the product array left to right
    int prod = product[0] = 1;    
    for (size_t i = 1; i < product.size(); ++i)
    {
        prod = prod * inputs[i-1];
        product[i] = prod;
    }

    // now iterate on the product array right to left
    prod = 1;
    //product[product.size()-1] = product[product.size()-1] * 1;
    for (size_t i = product.size()-2; i != SIZE_MAX; --i)
    {
        prod = prod * inputs[i+1];
        product[i] = product[i] * prod;
    }

    return product;
}

int main()
{
    vector<vector<int>> values = {
        {},
        {1},
        {1, 3},
        {1, 1, 1, 1, 1},
        {1, 2, 3, 4, 5},        
        {-1, -5, 3, 1, 2},
    };

    for (const auto& inputs : values)
    {
        cout << "For the inputs: ";
        for (size_t i = 0; i < inputs.size(); ++i)
        {
            cout << inputs[i] << " ";
        }
        cout << endl;
    
        auto product = ArrayProductOpt(inputs);
        cout << "the product array is: ";
        for (size_t i = 0; i < product.size(); ++i)
        {
            cout << product[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
