#pragma once

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

#include <iostream>
#include <sstream>
#include <ctime>
#include <vector>

class PmergeMe
{
	public:
		static void processSequence(int, char**);

	private:
		static void displaySequence(std::string const&, std::vector<int> const&);
		static void displayTime(std::string const&, clock_t, clock_t);

		static void vectorMergeInsertionSort(std::vector<int> &, size_t);
		static void vectorMergeInsertionSortHelper(std::vector<int> &, std::vector<int> &, size_t, size_t, size_t);
		static void vectorInsertionSortRange(std::vector<int> &, size_t, size_t);
		static void vectorMerge(std::vector<int> &, std::vector<int> &, size_t, size_t, size_t);
};
