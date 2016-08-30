#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>

int find_longest_subarray_less_equal_k(const std::vector<int> &arr, int k)
{
    // Build prefix sum array P
    std::vector<int> prefix_sum;
    std::partial_sum(arr.cbegin(), arr.cend(), std::back_inserter(prefix_sum));
    for (int x: prefix_sum)
        std::cout << x << " ";
    std::cout << std::endl;

    int len = arr.size();
    if (prefix_sum.back() <= k)
    {
        // sum of arr is less or equal to K
        return len;
    }

    // Build min prefix sum array Q
    std::vector<int> min_prefix_sum(len);
    min_prefix_sum.back() = prefix_sum.back();
    for (int i = len - 2; i >= 0; --i)
        min_prefix_sum[i] = std::min(prefix_sum[i], min_prefix_sum[i + 1]);
    for (int x: min_prefix_sum)
        std::cout << x << " ";
    std::cout << std::endl;

    // Check for min possible sum of A[a,b} - starting at a and extending to b or beyond
    int a = 0, b = 0, max_length = 0;
    while (a < len && b < len)
    {
        int min_curr_sum = a > 0 ? min_prefix_sum[b] - prefix_sum[a - 1] : min_prefix_sum[b];
        std::cout << "[" << a << "," << b << "} " << min_curr_sum;
        if (min_curr_sum <= k)
        {
            int curr_length = b - a + 1;
            if (curr_length > max_length)
                max_length = curr_length;
            ++b;
            std::cout << " MAX=" << max_length << ";" << curr_length;
        }
        else
        {
            ++a;
        }
        std::cout << std::endl;
    }

    return max_length;
}

int main()
{
    std::vector<int> arr = { 431, -15, 639, 342, -14, 565, -924, 635, 167, -70 };
    int max = find_longest_subarray_less_equal_k(arr, 184);
    std::cout << "MAX=" << max << std::endl;
}
