#include<iostream>
#include<string>
#include<vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include<algorithm>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

        if (std::find(wordList.begin(), wordList.end(),endWord) == wordList.end())
        {
            return 0;
        }

        unordered_map<string,vector<string>> adjacency_list;

        unordered_set<string> visited;
        deque<string> q({beginWord});
        wordList.push_back(beginWord);

        for(const auto word:wordList)
        {
            for(int i=0;i<word.length();i++)
            {
                string temp_word = word;
                temp_word[i] = '*';
                adjacency_list[temp_word].push_back(word);
            }
        }

        int min_transformation = 1;

        while(!q.empty())
        {
            int n = q.size();
            for(int i=0;i<n;i++)
            {
                string word = q.front();
                q.pop_front();

                if(word == endWord)
                    return min_transformation;

                for(int i=0;i<word.length();i++)
                {
                    string temp_word = word;
                    temp_word[i] = '*';

                    for(const auto pattern: adjacency_list[temp_word])
                    {
                        if(visited.find(pattern) == visited.end())
                        {   visited.insert(pattern);
                            q.push_back(pattern);
                        }
                    }
                }
            }
            min_transformation++;
        }
        
        return 0; 
    }
};


int main()
{
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList{"hot","dot","dog","lot","log","cog"};

    Solution solver;

    int min_count = solver.ladderLength(beginWord, endWord, wordList);

    std::cout<<"Minimum transformation sequence: "<<min_count<<std::endl;

    return 0;
}