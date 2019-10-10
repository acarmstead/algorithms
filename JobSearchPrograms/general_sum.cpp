//
//  Given a list of numbers and a target sum,
//  determine if a subset of the numbers in the list
//  has a sum equal to target.
//  Uses the "meet in the middle" optimization.
//  Implementation by Ashton Armstead.

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using std::vector;

void genSubsets(vector<vector<int>>& subsets, vector<int>& nums,
                vector<int>& cur, int index) {
    if (index == nums.size()) {
        // process this subset
        subsets.push_back(cur);
        return;
    }
    
    // Don't include num in subset
    genSubsets(subsets, nums, cur, index + 1);
    
    // Include num in subset
    cur.push_back(nums[index]);
    genSubsets(subsets, nums, cur, index + 1);
    cur.pop_back();
}

vector<int> subsetSum(const vector<int>& nums, int target) {
    // Split input into two halves
    vector<int> front(nums.begin(), nums.begin() + nums.size() / 2);
    vector<int> back(nums.begin() + nums.size() / 2, nums.end());
    
    // All subset sums in first half of |nums|
    vector<vector<int>> front_subsets;
    vector<int> cur;
    genSubsets(front_subsets, front, cur, 0);
    
    // All subsets in back half of |nums|
    vector<vector<int>> back_subsets;
    cur.clear();
    genSubsets(back_subsets, back, cur, 0);
    
    // Cross check subset sums to see if there's a match.
    // The runtime of this portion can be improved, however,
    // given the overall runtime of this algorithm is O(2^(n/2)),
    // I chose to omit this optimization.
    for (vector<int>& subset : front_subsets) {
        int sum = std::accumulate(subset.begin(), subset.end(), 0);
        for (vector<int>& other_subset : back_subsets) {
            if (std::accumulate(other_subset.begin(), other_subset.end(), 0) + sum == target) {
                other_subset.insert(other_subset.end(),
                                    std::make_move_iterator(subset.begin()),
                                                            std::make_move_iterator(subset.end()));
                return other_subset;
            }
        }
    }
    
    return {};
}

int main(int argc, const char * argv[]) {
    vector<int> sample_input = {5, 4, 2, 9};
    int sample_target = 15;
    
    vector<int> subset = subsetSum(sample_input, sample_target);
    std::cout << "Solution subset, if found:\n";
    for (int x : subset) {
        std::cout << x << "\t";
    }
    std::cout << std::endl;
    
    return 0;
}
