#pragma once

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

#include <iostream>
#include <sstream>
#include <ctime>
#include <vector>
#include <list>

class PmergeMe
{
	public:
		static void processSequence(int, char**);

	private:
		static void displaySequence(std::string const&, std::vector<int> const&);
		static void displayTime(std::string const&, clock_t, clock_t);

		// static std::vector<size_t> generateJacobsthalNumbers(size_t n);

		// static void vectorMainchainSort(std::vector<int> & mainchain);
		static void vectorInsertIntoMainchain(std::vector<int> & mainchain, std::vector<int>::iterator & b);
		static void vectorMergeInsertionSort(std::vector<int> & lst);

		static void listInsertIntoMainchain(std::list<int> & mainchain, std::list<int>::iterator & b);
		static void listMergeInsertionSort(std::list<int> & lst);

		// static void listMergeInsertionSort(std::list<int> &, size_t);
		// static void listMergeInsertionSortHelper(std::list<int> &, std::list<int> &, size_t);
		// static void listInsertionSortRange(std::list<int> &);
		// static void listMerge(std::list<int> &, std::list<int> &, std::list<int> &);

		// static void vectorMergeInsertionSort(std::vector<int> &, size_t);
		// static void vectorMergeInsertionSortHelper(std::vector<int> &, std::vector<int> &, size_t, size_t, size_t);
		// static void vectorInsertionSortRange(std::vector<int> &, size_t, size_t);
		// static void vectorMerge(std::vector<int> &, std::vector<int> &, size_t, size_t, size_t);

		PmergeMe();
		~PmergeMe();
		PmergeMe(PmergeMe const&);
		PmergeMe & operator=(PmergeMe const&);
};
