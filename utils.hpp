/*
 *  Leetcode sultions
 *
 *  Copyright (c) 2022-2023, Pan Ruochen <ijkxyz@msn.com>.
 */

#ifndef __UTILS_HPP
#define __UTILS_HPP 007

#include <vector>
#include <assert.h>

#include <chrono>
//#include <algorithm>

typedef std::chrono::steady_clock std_clock;

struct ListNode {
	 int val;
	 ListNode *next;
	 ListNode() : val(0), next(nullptr) {}
	 ListNode(int x) : val(x), next(nullptr) {}
	 ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class SolutionUtils {
public:
	static
	void printSet(const char *hint, const std::vector<int>& xSet) {
		std::string s;
		for(auto i : xSet) {
			char tmp[129];
			snprintf(tmp, sizeof(tmp), "%d,", i);
			s += tmp;
		}

		if(!s.empty())
			s.pop_back();
		::printf("%s: [%s]\n", hint, s.c_str());
	}

	template<typename _T>
	void printSet2(const char *hint, _T&& xSet) {
		std::string all;

		for(auto& x : xSet) {
			std::string s;
			for(auto i : x) {
				char tmp[129];
				snprintf(tmp, sizeof(tmp), "%d,", i);
				s += tmp;
			}

			if(!s.empty()) {
				s.pop_back();
				all += '[';
				all += s;
				all += "],";
			}
		}

		if(!all.empty())
			all.pop_back();
		::printf("%s: [%s]\n", hint, all.c_str());
	}

	void printList(const char *hint, ListNode *head, int maxCount = -1) {
		std::string s;
		int count = 0;

		while(head != nullptr) {
			char tmp[129];
			snprintf(tmp, sizeof(tmp), "%d ", head->val);
			s += tmp;
			head = head->next;
			++count;
			if(maxCount > 0 && count > maxCount) {
				s += "....";
				break;
			}
		}

		if(!s.empty())
			s.pop_back();
		::printf("%s: [%s]\n", hint, s.c_str());
	}

	void printLists(const char *hint, const std::vector<ListNode*>& lists) {
		bool first = true;

		::printf("[");
		for(auto head : lists) {
			std::string s;
			while(head != nullptr) {
				char tmp[129];
				snprintf(tmp, sizeof(tmp), "%d,", head->val);
				s += tmp;
				head = head->next;
			}

			if(!s.empty())
				s.pop_back();
			if(!first)
				::printf(",");
			::printf("[%s]", s.c_str());
			first = false;
		}
		::printf("]\n");
	}

#if !HAVE_PRINTF
	static void printf(const char *, ...) {}
#endif

	int calcElapsedTimeMs(const std::chrono::time_point<std_clock>& t0) {
		return (int) std::chrono::duration_cast<std::chrono::milliseconds>(std_clock::now() - t0).count();
	}
};

#endif
