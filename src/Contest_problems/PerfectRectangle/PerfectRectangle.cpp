// StringPermutations.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// https://leetcode.com/contest/leetcode-weekly-contest-2/problems/perfect-rectangle/

bool isRectangleCover(vector<vector<int>>& rectangles) 
{
    bool flag = 0;
    bool temp_flag = 1;
    int count = rectangles.size();
    int total_area = 0;
    int temp_area = 0;
    int left_x = rectangles[0][0], left_y = rectangles[0][1];
    int right_x = rectangles[0][2], right_y = rectangles[0][3];

    if (count == 1)
    {
        return true;
    }

    for (int i = 0; i < count; i++)
    {
        if (temp_flag)
        {
        for (int j = 0; j < count; j++)
        {
            if (i != j)
            {
                if ((rectangles[j][0] < rectangles[i][2] && rectangles[i][2] <= rectangles[j][2]) 
                && 
                (rectangles[j][1] < rectangles[i][3] && rectangles[i][3] <= rectangles[j][3]))
                {
                    temp_flag = 0;
                }
            }

        }

        temp_area += (rectangles[i][2] - rectangles[i][0])*(rectangles[i][3] - rectangles[i][1]);
        if (rectangles[i][0] < left_x)
        {
            left_x = rectangles[i][0];
        }
        if (rectangles[i][1] < left_y)
        {
            left_y = rectangles[i][1];
        }
        if (rectangles[i][2] > right_x)
        {
            right_x = rectangles[i][2];
        }
        if (rectangles[i][3] > right_y) 
        {
            right_y = rectangles[i][3];
        }
        
        //else right_y = rectangles[i + 1][3];
        }
    }
    //temp_area += (rectangles[count-1][2] - rectangles[count-1][0])*(rectangles[count-1][3] - rectangles[count-1][1]);
    total_area = (right_x - left_x)*(right_y - left_y);

    if (total_area == temp_area && temp_flag == 1) 
        flag = 1;
    return flag;
}

int main()
{
    vector<vector<int>> rectangles = {
        {1,1,3,3},
        {3,1,4,2},
        {3,2,4,4},
        {1,3,2,4},
        {2,3,3,4},
    };

    bool res = isRectangleCover(rectangles);
    if (res)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    return 0;
}

