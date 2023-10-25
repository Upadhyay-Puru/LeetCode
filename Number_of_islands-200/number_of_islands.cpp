#include <iostream>
#include<vector>
#include <unordered_set>
#include <deque>
using namespace std;

struct PairHash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int island_count = 0;

        int rows = grid.size();
        int cols = grid[0].size();
        
        unordered_set<pair<int,int>, PairHash> visited;
        deque<pair<int,int>> q;
        vector<pair<int,int>> connection{{1,0}, {-1,0}, {0,-1},{0,1}};
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                if(grid[i][j] == '1' && visited.find({i,j}) == visited.end())
                {
                    island_count++;

                    visited.insert({i,j});
                    q.push_back({i,j});

                    while(!q.empty())
                    {
                        auto curr = q.front();
                        q.pop_front();

                        for(auto next:connection)
                        {
                            int new_x = next.first + curr.first;
                            int new_y = next.second + curr.second;

                            if(new_x>=0 && new_x<rows && new_y>=0 && new_y < cols && grid[new_x][new_y] == '1' && visited.find({new_x, new_y}) == visited.end())
                            {
                                q.push_back({new_x, new_y});
                                visited.insert({new_x, new_y});
                            }
                        }
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    return island_count;
    }
};

int main()
{
    vector<vector<char>> grid ({{'1','1','0','0','0'},{'1','1','0','0','0'},{'0','0','1','0','0'},{'0','0','0','1','1'}});

    Solution solver;
    int island_Count = solver.numIslands(grid);

    std::cout<<"Number of Islands: "<<island_Count<<std::endl;
}