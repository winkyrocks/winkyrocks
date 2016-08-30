#include <iostream>
#include <queue>
#include <set>

/*
Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.
Examples:

[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

    void addNum(int num) - Add a integer number from the data stream to the data structure.
    double findMedian() - Return the median of all elements so far.

For example:

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2
*/

std::priority_queue<int> left_max_heap;
std::priority_queue<int, std::vector<int>, std::greater<int> > right_min_heap;

// For dump purpose
std::multiset<int> sorted_numbers;

void dump()
{
    for (int num: sorted_numbers)
        std::cout << num << " ";

    std::cout << "L=";
    if (left_max_heap.size() > 0)
        std::cout << left_max_heap.top();
    std::cout << ",R=";
    if (right_min_heap.size() > 0)
        std::cout << right_min_heap.top();

    std::cout << std::endl;
}

void addNum(int num)
{
    sorted_numbers.emplace(num);

    if (right_min_heap.size() == 0 || right_min_heap.top() < num)
    {
        right_min_heap.emplace(num);
    }
    else
    {
        left_max_heap.emplace(num);
    }

    if (right_min_heap.size() > left_max_heap.size() + 1)
    {
        int right_min = right_min_heap.top();
        left_max_heap.emplace(right_min);
        right_min_heap.pop();
    }
    else if (left_max_heap.size() > right_min_heap.size())
    {
        int left_max = left_max_heap.top();
        right_min_heap.emplace(left_max);
        left_max_heap.pop();
    }
}

double findMedian()
{
    dump();
    if (right_min_heap.size() == left_max_heap.size())
    {
        int left_max = left_max_heap.top();
        int right_min = right_min_heap.top();
        return (double)(left_max + right_min) / 2;
    }
    else
    {
        return right_min_heap.top();
    }
}

int main()
{
    addNum(1);
    std::cout << findMedian() << std::endl;
    addNum(5);
    std::cout << findMedian() << std::endl;
    addNum(3);
    std::cout << findMedian() << std::endl;
    addNum(4);
    std::cout << findMedian() << std::endl;
    addNum(4);
    std::cout << findMedian() << std::endl;
    addNum(2);
    std::cout << findMedian() << std::endl;

    return 0;
}
