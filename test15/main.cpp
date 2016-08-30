#include <iostream>
#include <string>
#include <vector>

/*
Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:

[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Note: Each word is guaranteed not to exceed L in length.
*/
std::vector<std::string> full_justify(std::vector<std::string>& words, int max_width)
{
    std::vector<std::string> results;
    std::vector<std::string> cur_words;
    int remaining = 1 + max_width; // padding the prefix to pretend the space for the leftmost word
    for (int cur = 0; cur <= words.size(); ++cur)
    {
        std::string cur_word = cur == words.size() ? "" : words[cur];
        if (remaining < 1 + cur_word.size() || cur == words.size())
        {
            std::string cur_line(cur_words[0]);

            if (cur_words.size() > 1)
            {
                int interval = cur_words.size() - 1;
                int avg_space = (remaining + interval) / interval;
                int left_space = avg_space + (remaining + interval) % interval;

                int space = left_space;
                for (int i = 1; i < cur_words.size(); ++i)
                {
                    for (int j = 0; j < space; ++j)
                    {
                        cur_line += " ";
                    }
                    cur_line += cur_words[i];
                    space = avg_space;
                }
            }

            results.emplace_back(cur_line);

            cur_words.clear();
            remaining = max_width + 1;
        }

        cur_words.emplace_back(cur_word);
        remaining -= 1 + cur_word.size();
    }

    return results;
}


int main()
{
    std::vector<std::string> words = {"This", "is", "an", "example", "of", "text", "justification."};
    for (auto &s : full_justify(words, 16))
        std::cout << s << std::endl;
    return 0;
}
