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
	std::vector<int> sequenceCopy(originalSequence);
	
	clock_t start, end;

	start = std::clock();
	std::vector<int> tmp(originalSequence.size());
	mergeSort(originalSequence, tmp, 0, originalSequence.size() - 1);
	end = std::clock();
	displaySequence("After: ", originalSequence);
	displayTime("Time to process with merge sort: ", start, end);

	start = std::clock();
	insertionSort(sequenceCopy);
	end = std::clock();
	displaySequence("After: ", originalSequence);
	displayTime("Time to process with insertion sort: ", start, end);
}

void PmergeMe::displaySequence(std::string const& msg, std::vector<int> const& sequence)
{
	std::cout << msg;
	for (size_t i = 0; i < sequence.size(); ++i)
		std::cout << sequence[i] << " ";
	std::cout << std::endl;
}

void PmergeMe::displayTime(std::string const& msg, clock_t start, clock_t end)
{
	double timeUsed = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6;
	std::cout << msg << timeUsed << " us" << std::endl;
}

void PmergeMe::mergeSort(std::vector<int> & sequence, std::vector<int> & tmp, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		mergeSort(sequence, tmp, left, mid);
		mergeSort(sequence, tmp, mid + 1, right);
		merge(sequence, tmp, left, mid, right);
	}
}

void PmergeMe::merge(std::vector<int> & sequence, std::vector<int> & tmp, int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int k = right;
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
	for (int l = left; l <= right; ++l)
		sequence[l] = tmp[l];
}

void PmergeMe::insertionSort(std::vector<int> & sequence)
{
	int n = sequence.size();
	for (int i = 1; i < n; ++i)
	{
		int key = sequence[i];
		int j = i - 1;
		while (j >= 0 && sequence[j] > key)
		{
			sequence[j + 1] = sequence[j];
			--j;
		}
		sequence[j + 1] = key;
	}
}
