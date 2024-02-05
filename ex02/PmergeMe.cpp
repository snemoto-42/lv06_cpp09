#include "PmergeMe.hpp"

void PmergeMe::processSequence(int size, char** sequence)
{
	std::vector<int> originalSequence;
	for (int i = 0; i < size; ++i)
	{
		std::string token(sequence[i]);
		if (token.find_first_not_of("0123456789") != std::string::npos)
			throw std::runtime_error("Invalid input: " + token);
		originalSequence.push_back(std::atoi(token.c_str()));
	}
	displaySequence("Before: ", originalSequence);
	clock_t start, end;
	start = std::clock();
	size_t threshold = 20; //threshold以下の部分配列に対して挿入ソートが適用
	vectorMergeInsertionSort(originalSequence, threshold);
	end = std::clock();
	displaySequence("After: ", originalSequence);

	std::ostringstream oss;
	oss << size;
	std::string msg = "Time to process a range of " + oss.str() + " elements with std::vector: ";
	displayTime(msg, start, end);
}

void PmergeMe::displayTime(std::string const& msg, clock_t start, clock_t end)
{
	double timeUsed = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6;
	std::cout << msg << timeUsed << " us" << std::endl;
}

void PmergeMe::displaySequence(std::string const& msg, std::vector<int> const& sequence)
{
	std::cout << msg;
	for (size_t i = 0; i < sequence.size(); ++i)
		std::cout << sequence[i] << " ";
	std::cout << std::endl;
}

void PmergeMe::vectorMergeInsertionSort(std::vector<int> & sequence, size_t threshold)
{
	std::vector<int> tmp(sequence.size());
	vectorMergeInsertionSortHelper(sequence, tmp, 0, sequence.size() - 1, threshold);
}

void PmergeMe::vectorMergeInsertionSortHelper(std::vector<int> & sequence, std::vector<int> & tmp, size_t left, size_t right, size_t threshold)
{
	if (left < right)
	{
		if (right - left <= threshold)
			vectorInsertionSortRange(sequence, left, right);
		else
		{
			size_t mid = (left - right) / 2;
			vectorMergeInsertionSortHelper(sequence, tmp, left, mid, threshold);
			vectorMergeInsertionSortHelper(sequence, tmp, mid + 1, right, threshold);
			vectorMerge(sequence, tmp, left, mid, right);
		}
	}
}

void PmergeMe::vectorInsertionSortRange(std::vector<int> & sequence, size_t left, size_t right)
{
	for (size_t i = left + 1; i <= right; ++i)
	{
		int key = sequence[i];
		size_t j = i - 1;
		while (j >= left && sequence[j] > key)
		{
			sequence[j + 1] = sequence[j];
			--j;
		}
		sequence[j + 1] = key;
	}
}

void PmergeMe::vectorMerge(std::vector<int> & sequence, std::vector<int> & tmp, size_t left, size_t mid, size_t right)
{
	size_t i = left;
	size_t j = mid + 1;
	size_t k = right;
	while (i <= mid && j <= right)
	{
		if (sequence[i] <= sequence[j])
			tmp[k++] = sequence[i++];
		else
			tmp[k++] = sequence[j++];
	}
	while (i <= mid)
		tmp[k++] = sequence[i++];
	while (j <= right)
		tmp[k++] = sequence[j++];
	for (size_t l = left; l <= right; ++l)
		sequence[l] = tmp[l];
}
