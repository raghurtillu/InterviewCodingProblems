#include <iostream>
#include <vector>
#include <string>

using namespace std;

// https://leetcode.com/contest/leetcode-weekly-contest-2/problems/perfect-rectangle/

bool RectangleCover(const vector<vector<size_t>>& rectangles)
{
	bool isRectanglePerfect = false;
	bool isRectangleOverlap = false;
	size_t totalArea = 0;
	size_t tempArea = 0;
	size_t left_x = rectangles[0][0], left_y = rectangles[0][1];
	size_t right_x = rectangles[0][2], right_y = rectangles[0][3];

	if (rectangles.size() == 1)
	{
		return true;
	}

	for (size_t i = 0; i < rectangles.size(); i++)
	{
		if (!isRectangleOverlap)
		{
			for (size_t j = i+1; j < rectangles.size(); j++)
			{
				if ((rectangles[j][0] < rectangles[i][2] && rectangles[i][2] <= rectangles[j][2])&&
					(rectangles[j][1] < rectangles[i][3] && rectangles[i][3] <= rectangles[j][3]))
				{
					isRectangleOverlap = true;
				}
			}

			tempArea += (rectangles[i][2] - rectangles[i][0])*(rectangles[i][3] - rectangles[i][1]);
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
		}
	}
	totalArea = (right_x - left_x)*(right_y - left_y);

	if (totalArea == tempArea && !isRectangleOverlap)
	{
		isRectanglePerfect = true;
	}

	return isRectanglePerfect;
}

int main()
{
	vector<vector<size_t>> rectangles = {
		// perfect rectangle
		{ 1,1,3,3 },
		{ 3,1,4,2 },
		{ 3,2,4,4 },
		{ 1,3,2,4 },
		{ 2,3,3,4 },
		

		// Not complete, gap in between case 1
		/*
		{ 1,1,2,3 },
		{ 1,3,2,4 },
		{ 3,1,4,2 },
		{ 3,2,4,4 },
		*/

		// Not complete, gap in between case 2
		/*
		{ 1,1,3,3 },
		{ 3,1,4,2 },
		{ 1,3,2,4 },
		{ 3,2,4,4 },
		*/

		// Complete, but overlap in rectangles
		/*
		{ 1,1,3,3 },
		{ 3,1,4,2 },
		{ 1,3,2,4 },
		{ 2,2,4,4 },
		*/
	};

	bool res = RectangleCover(rectangles);
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