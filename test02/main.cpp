#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>

/*
Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the word list
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
Return
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]
*/

#define WORD_LENGTH 3

typedef struct node
{
    std::string str;
    int pre;

    node(std::string _str, int _pre)
    {
        str = _str;
        pre = _pre;
    }
} bfs_node;

typedef std::vector<bfs_node> bfs_queue;
typedef std::unordered_set<std::string> word_dictionary;

void output(bfs_queue &sequence)
{
    std::stack<std::string> result;
    for (auto &node = sequence.back(); ;)
    {
        result.push(node.str);
        if (node.pre < 0) break;
        node = sequence[node.pre];
    }

    std::cout << "[";
    while (!result.empty())
    {
        std::cout << result.top() << " ";
        result.pop();
    }
    std::cout << "]" << std::endl;
}

/*
Breadth First Search
*/
void find_ladders(bfs_queue &sequence, std::string end_str, word_dictionary &dictionary)
{
    std::unordered_set<std::string> attemped;
    for (size_t cur = 0; cur < sequence.size(); ++cur)
    {
        std::string str = sequence[cur].str;
        for (int i = 0; i < WORD_LENGTH; ++i)
        {
            std::string next_str(str);
            for (char c = 'a'; c <= 'z'; ++c)
            {
                next_str.replace(i, 1, 1, c);
                if (next_str == end_str)
                {
                    sequence.emplace_back(next_str, cur);
                    output(sequence);
                }
                else if (dictionary.find(next_str) != dictionary.end() && attemped.find(next_str) == attemped.end())
                {
                    attemped.emplace(next_str);
                    sequence.emplace_back(next_str, cur);
                }
            }
        }
    }
}

int main()
{
    word_dictionary dictionary({"hot", "dot", "dog", "lot", "log"});

    bfs_queue sequence;
    sequence.emplace_back("hit", -1);

    find_ladders(sequence, "cog", dictionary);

    return 0;
}
