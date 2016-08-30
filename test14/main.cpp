#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

struct SubArray
{
    int start, end;
};

SubArray FindSmallestCoveringSubset(const std::vector<std::string> &paragraph, const std::vector<std::string> &keywords)
{
    std::unordered_map<std::string, int> keyword_to_count;
    for (int i = 0; i < (int)keywords.size(); ++i)
        keyword_to_count.emplace(keywords[i], 1);

    SubArray result = {-1, -1};
    int shortest_length = std::numeric_limits<int>::max();
    int left = 0, right = 0, remaining = keywords.size();

    while (right < (int)paragraph.size())
    {
        while (remaining && right < (int)paragraph.size())
        {
            auto iter = keyword_to_count.find(paragraph[right]);
            if (iter != keyword_to_count.end())
            {
                if (0 == --keyword_to_count[paragraph[right]])
                    --remaining;
            }

            ++right;
        }

        std::cout << "R=" << right;

        while (!remaining && left < (int)paragraph.size())
        {
            auto iter = keyword_to_count.find(paragraph[left]);
            if (iter != keyword_to_count.end())
            {
                if (0 < ++keyword_to_count[paragraph[left]])
                    ++remaining;
            }

            ++left;
        }

        std::cout << ",L=" << left;

        if (right - left + 1 < shortest_length)
        {
            shortest_length = right - left + 1;
            result = {left - 1, right - 1};
        }

        std::cout << ",LEN=" << shortest_length;
        std::cout << "[" << result.start << "," << result.end << "]" << std::endl;
    }

    return result;
}

SubArray FindSmallestSequentiallyCoveringSubset(const std::vector<std::string> &paragraph, const std::vector<std::string> &keywords)
{
    std::unordered_map<std::string, int> keyword_to_idx;
    for (int i = 0; i < (int)keywords.size(); ++i)
        keyword_to_idx.emplace(keywords[i], i);

    std::vector<int> lastest_occurence(keywords.size(), -1);
    std::vector<int> shortest_subarry_length(keywords.size(), std::numeric_limits<int>::max());

    int shortest_distance = std::numeric_limits<int>::max();
    SubArray result = {-1, -1};
    for (int i = 0; i < (int)paragraph.size(); ++i)
    {
        std::cout << i << ":";
        auto iter = keyword_to_idx.find(paragraph[i]);
        if (iter != keyword_to_idx.end())
        {
            int keyword_idx = iter->second;
            std::cout << " KEY=" << keyword_idx;
            if (keyword_idx == 0)
            {
                shortest_subarry_length[keyword_idx] = 1;
            }
            else if (shortest_subarry_length[keyword_idx - 1] != std::numeric_limits<int>::max())
            {
                int distance_to_previous_keyword = i - lastest_occurence[keyword_idx - 1];
                shortest_subarry_length[keyword_idx] = distance_to_previous_keyword + shortest_subarry_length[keyword_idx - 1];
                std::cout << ",LEN=D" << distance_to_previous_keyword << "+P" << shortest_subarry_length[keyword_idx - 1];
            }

            lastest_occurence[keyword_idx] = i;

            if (keyword_idx == (int)keywords.size() - 1)
            {
                if (shortest_subarry_length.back() < shortest_distance)
                {
                    shortest_distance = shortest_subarry_length.back();
                    result = {i - shortest_subarry_length.back() + 1, i};
                }
            }
        }
        std::cout << std::endl;
    }

    return result;
}

int main()
{
    std::vector<std::string> paragraph = {"apple", "banana", "cat", "orange", "banana", "apple"};
    std::vector<std::string> keywords = {"banana", "orange", "apple"};

    SubArray result = FindSmallestCoveringSubset(paragraph, keywords);
    std::cout << result.start << "," << result.end << std::endl;
    std::cout << std::endl;

    result = FindSmallestSequentiallyCoveringSubset(paragraph, keywords);
    std::cout << result.start << "," << result.end << std::endl;
    return 0;
}
