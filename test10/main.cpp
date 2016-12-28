#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>

bool IsNewPillarOrReachEnd(const std::vector<int> &heights, int curr_idx, int last_pillar_idx)
{
    return curr_idx < (int)heights.size() ? heights[curr_idx] < heights[last_pillar_idx] : true;
}

int CalculateLargestRectangle(const std::vector<int> &heights)
{
    std::stack<int> pillar_indices;
    int max_rectangle_area = 0;
    for (int i = 0; i <= (int)heights.size(); ++i)
    {
        if (!pillar_indices.empty() && i < (int)heights.size() && heights[i] == heights[pillar_indices.top()])
        {
            // Replace the earlier building with the same height.
            // This ensures the later buidlings have the correct left endpoints.
            std::cout << i << ":POP=" << pillar_indices.top();
            pillar_indices.pop();
            pillar_indices.emplace(i);
            std::cout << ",PUSH=" << pillar_indices.top() << std::endl;
            continue;
        }

        while (!pillar_indices.empty() && IsNewPillarOrReachEnd(heights, i, pillar_indices.top()))
        {
            int height = heights[pillar_indices.top()];
            std::cout << i << ": POP=" << pillar_indices.top() << std::endl;
            pillar_indices.pop();
            int width = pillar_indices.empty() ? i : i - pillar_indices.top() - 1;
            max_rectangle_area = std::max(max_rectangle_area, height * width);
            std::cout << i << ": MAX=" << max_rectangle_area << ";" << height << "*" << width << std::endl;
        }

        pillar_indices.emplace(i);
        std::cout << i << ":PUSH=" << pillar_indices.top() << std::endl;
    }

    return max_rectangle_area;
}


int main()
{
    std::vector<int> heights = { 1, 4, 2, 5, 6, 3, 2, 6, 6, 5, 2, 1, 3 };
    int r = CalculateLargestRectangle(heights);
    std::cout << r << std::endl;
}
