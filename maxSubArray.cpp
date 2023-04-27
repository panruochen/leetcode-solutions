/*
 *  Leetcode sultions
 *
 *  Copyright (c) 2022-2023, Pan Ruochen <ijkxyz@msn.com>.
 */

#include <vector>
#include <algorithm>
#include "utils.hpp"

typedef std::chrono::steady_clock std_clock;

class Solution : public SolutionUtils {
	static const int MAX_INT = 999999999;

/**
1. 如果所有数均为负数或者零，则子数组的最大和为该数组的最大值。
2. 如果数组中有正数也有负数，用sum记录当前位置的数组和，min记录数组和的最小值，max记录数组和的最大值；
   prevMin记录当前位置之前的数组和的最小值，nextMax记录位于min位置之后与min的最大差值

	------------------------------------
     min   nextMax prevMin  max

	------------------------------------
     prevMin  max     min   nextMax

    子数组的最大值应该取max - min，max - prevMin，nextMax中的最大值

**/
public:
    int maxSubArray(const std::vector<int>& nums) {
    	struct Value {
    		int index, value;
    		Value(int v) : index(-1), value(v) {}
    	};

    	const int LEN = nums.size();
    	Value min(MAX_INT), max(-MAX_INT), prevMin(MAX_INT), nextMax(-MAX_INT);
    	int sum = 0, maxV = -MAX_INT;

    	for(int i = 0; i < LEN; i++) {
	    	sum += nums[i];

	    	if(maxV < nums[i])
	    		maxV = nums[i];

	    	if(min.value > sum) {
	    		min.value = sum;
	    		min.index = i;
	    	}

	    	if(max.value < sum) {
	    		max.value = sum;
	    		max.index = i;
	    	}

    		if(max.index > min.index) {
    			prevMin.value = min.value;
    			prevMin.index = min.index;
    		}

    		if(i > min.index) {
	    		int diff = sum - min.value;
	    		if(nextMax.value < diff) {
	    			nextMax.value = diff;
	    			nextMax.index = i;
		    	}
		    }
	    }

		if(maxV <= 0)
			return maxV;
		if(min.index == max.index)
			return nums[min.index];

		int maxValue1 = max.value, maxValue2;
		if(min.index < max.index && min.value < 0) {
			maxValue1 = max.value - min.value;
		}

		if(prevMin.index >= 0) {
			maxValue2 = std::max(max.value - prevMin.value, nextMax.value);
		} else {
			maxValue2 = nextMax.value;
		}
		return std::max(maxValue1, maxValue2);
	}
};

void run(const std::vector<int>& nums)
{
	const auto t0 = std_clock::now();
	Solution sln;
	auto result = sln.maxSubArray(nums);
	int eplasedTimeMs = sln.calcElapsedTimeMs(t0);
	printf("%d ms used, max sum %d\n", eplasedTimeMs, result);
}

int main() {

	std::vector<int> arr = { 1 };
	run(arr);

	arr = std::vector<int>{-1,0};
	run(arr);

	arr = std::vector<int>{ -2,1,-3,4,-1,2,1,-5,4 };
	run(arr);

	arr = std::vector<int> { -10,-9,-8,-7,-6,-3,-4,-5, };
	run(arr);

	arr = std::vector<int> { -10,-9,-8,-7,-6,0,-3,-4,-5, };
	run(arr);

	arr = std::vector<int> { 2,3,7,1,10,5,4 };
	run(arr);

	arr = std::vector<int> { 2,3,7,1,10,0,5,4 };
	run(arr);

	printf("\nAll tests are finished\n");
	return 0;
}
