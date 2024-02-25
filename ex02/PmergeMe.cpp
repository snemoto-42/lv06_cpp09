#include "PmergeMe.hpp"

void PmergeMe::processSequence(int size, char** sequence)
{
	std::vector<int> vec;
	std::list<int> lst;

	for (int i = 0; i < size; ++i)
	{
		std::string token(sequence[i]);
		if (token.find_first_not_of("0123456789") != std::string::npos)
			throw std::runtime_error("Invalid input: " + token);
		vec.push_back(std::atoi(token.c_str()));
		lst.push_back(std::atoi(token.c_str()));
	}
	displaySequence("Before: ", vec);
	clock_t start, end;
	std::string msg;
	std::ostringstream oss;
	oss << size;

	// size_t threshold = 20; //threshold以下の部分配列に対して挿入ソートが適用

	start = std::clock();
	vectorMergeInsertionSort(vec);
	// vectorMergeInsertionSort(vec, threshold);
	end = std::clock();

	displaySequence("After: ", vec);

	msg = "Time to process a range of " + oss.str() + " elements with std::vector: ";
	displayTime(msg, start, end);

	start = std::clock();
	listMergeInsertionSort(lst);
	// listMergeInsertionSort(lst, threshold);
	end = std::clock();

	msg = "Time to process a range of " + oss.str() + " elements with std::list: ";
	displayTime(msg, start, end);
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

std::vector<size_t> PmergeMe::generateJacobsthalNumbers(size_t n)
{
	std::vector<size_t> jNumbers(n + 1, 0);
	jNumbers[1] = 1;
	for (size_t i = 2; i <= n; ++i)
		jNumbers[i] = jNumbers[i - 1] + 2 * jNumbers[i - 2];
	return jNumbers;
}

void PmergeMe::vectorInsertIntoMainchain(std::vector<int> & mainchain, std::vector<int>::iterator & b)
{
	for (std::vector<int>::iterator it = mainchain.begin(); it != mainchain.end(); ++it)
	{
		if (*it > *b)
		{
			mainchain.insert(it, *b);
			return ;
		}
	}
	mainchain.push_back(*b);
}

void PmergeMe::vectorMergeInsertionSort(std::vector<int>& lst)
{
	if (lst.size() < 2)
		return ;
	std::vector<int> mainchain, bElements;
	std::vector<int>::iterator it = lst.begin();
	while (it != lst.end())
	{
		int a = *it;
		++it;
		if (it != lst.end())
		{
			int b = *it;
			++it;
			if (a > b)
				std::swap(a, b);
			mainchain.push_back(a);
			bElements.push_back(b);
		}
		else
			bElements.push_back(a); //奇数の場合、ペアにならない最後の要素はbに追加
	}
	std::vector<size_t> jNumbers = generateJacobsthalNumbers(lst.size());
	for (size_t i = 0; i < lst.size(); ++i)
	{
		size_t j = jNumbers[i];
		if (j < bElements.size())
		{
			std::vector<int>::iterator b = lst.begin();
			std::advance(b, j);
			vectorInsertIntoMainchain(mainchain, b);
		}
	}
	// for (std::vector<int>::iterator it = bElements.begin(); it != bElements.end(); ++it)
	// {
	// 	std::vector<int>::iterator b = std::find(lst.begin(), lst.end(), *it);
	// 	vectorInsertIntoMainchain(mainchain, b);
	// }
	lst = mainchain;
}

void PmergeMe::listInsertIntoMainchain(std::list<int> & mainchain, std::list<int>::iterator & b)
{
	for (std::list<int>::iterator it = mainchain.begin(); it != mainchain.end(); ++it)
	{
		if (*it > *b)
		{
			mainchain.insert(it, *b);
			return ;
		}
	}
	mainchain.push_back(*b);
}

void PmergeMe::listMergeInsertionSort(std::list<int>& lst)
{
	if (lst.size() < 2)
		return ;
	std::list<int> mainchain, bElements;
	std::list<int>::iterator it = lst.begin();
	while (it != lst.end())
	{
		int a = *it;
		++it;
		if (it != lst.end())
		{
			int b = *it;
			++it;
			if (a > b)
				std::swap(a, b);
			mainchain.push_back(a);
			bElements.push_back(b);
		}
		else
			bElements.push_back(a); //奇数の場合、ペアにならない最後の要素はbに追加
	}
	std::vector<size_t> jNumbers = generateJacobsthalNumbers(lst.size());
	for (size_t i = 0; i < lst.size(); ++i)
	{
		size_t j = jNumbers[i];
		if (j < bElements.size())
		{
			std::list<int>::iterator b = lst.begin();
			std::advance(b, j);
			listInsertIntoMainchain(mainchain, b);
		}
	}
	// for (std::list<int>::iterator it = bElements.begin(); it != bElements.end(); ++it)
	// {
	// 	std::list<int>::iterator b = std::find(lst.begin(), lst.end(), *it);
	// 	listInsertIntoMainchain(mainchain, b);
	// }
	lst = mainchain;
}

// for list

// void PmergeMe::listMergeInsertionSort(std::list<int> & sequence, size_t threshold)
// {
// 	std::list<int> tmp;
// 	listMergeInsertionSortHelper(sequence, tmp, threshold);
// }

// void PmergeMe::listMergeInsertionSortHelper(std::list<int> & sequence, std::list<int> & tmp, size_t threshold)
// {
// 	if (sequence.size() <= threshold)
// 		listInsertionSortRange(sequence);
// 	else
// 	{
// 		std::list<int>::iterator half = sequence.begin();
// 		std::advance(half, std::distance(sequence.begin(), sequence.end()) / 2); //std::next()
// 		std::list<int> leftHalf(sequence.begin(), half);
// 		std::list<int> rightHalf(half, sequence.end());
// 		listMergeInsertionSortHelper(leftHalf, tmp, threshold);
// 		listMergeInsertionSortHelper(rightHalf, tmp, threshold);
// 		listMerge(sequence, leftHalf, rightHalf);
// 	}
// }

// void PmergeMe::listInsertionSortRange(std::list<int> & sequence)
// {
// 	for (std::list<int>::iterator it = sequence.begin(); it != sequence.end(); ++it)
// 	{
// 		int key = *it;
// 		std::list<int>::iterator j = it;
// 		--j; //std::prev()
// 		while (j != sequence.end() && *j > key)
// 		{
// 			std::list<int>::iterator k = j;
// 			++k; //std::next()
// 			std::iter_swap(j, k);
// 			--j;
// 		}
// 		std::list<int>::iterator k = j;
// 		++k; //std::next()
// 		std::iter_swap(k, it);
// 	}
// }

// void PmergeMe::listMerge(std::list<int> & sequence, std::list<int> & leftHalf, std::list<int> & rightHalf)
// {
// 	sequence.clear();
// 	std::list<int>::iterator leftIt = leftHalf.begin();
// 	std::list<int>::iterator rightIt = rightHalf.begin();
// 	while (leftIt != leftHalf.end() && rightIt != rightHalf.end())
// 	{
// 		if (*leftIt <= *rightIt)
// 		{
// 			sequence.push_back(*leftIt);
// 			++leftIt;
// 		}
// 		else
// 		{
// 			sequence.push_back(*rightIt);
// 			++rightIt;
// 		}
// 	}
// 	sequence.insert(sequence.end(), leftIt, leftHalf.end());
// 	sequence.insert(sequence.end(), rightIt, rightHalf.end());
// }

// for vector

// void PmergeMe::vectorMergeInsertionSort(std::vector<int> & sequence, size_t threshold)
// {
// 	std::vector<int> tmp(sequence.size());
// 	vectorMergeInsertionSortHelper(sequence, tmp, 0, sequence.size() - 1, threshold);
// }

// void PmergeMe::vectorMergeInsertionSortHelper(std::vector<int> & sequence, std::vector<int> & tmp, size_t left, size_t right, size_t threshold)
// {
// 	if (left < right)
// 	{
// 		if (right - left <= threshold)
// 			vectorInsertionSortRange(sequence, left, right);
// 		else
// 		{
// 			size_t mid = (left - right) / 2;
// 			vectorMergeInsertionSortHelper(sequence, tmp, left, mid, threshold);
// 			vectorMergeInsertionSortHelper(sequence, tmp, mid + 1, right, threshold);
// 			vectorMerge(sequence, tmp, left, mid, right);
// 		}
// 	}
// }

// void PmergeMe::vectorInsertionSortRange(std::vector<int> & sequence, size_t left, size_t right)
// {
// 	for (size_t i = left + 1; i <= right; ++i)
// 	{
// 		int key = sequence[i];
// 		size_t j = i - 1;
// 		while (j >= left && sequence[j] > key)
// 		{
// 			sequence[j + 1] = sequence[j];
// 			--j;
// 		}
// 		sequence[j + 1] = key;
// 	}
// }

// void PmergeMe::vectorMerge(std::vector<int> & sequence, std::vector<int> & tmp, size_t left, size_t mid, size_t right)
// {
// 	size_t i = left;
// 	size_t j = mid + 1;
// 	size_t k = right;
// 	while (i <= mid && j <= right)
// 	{
// 		if (sequence[i] <= sequence[j])
// 			tmp[k++] = sequence[i++];
// 		else
// 			tmp[k++] = sequence[j++];
// 	}
// 	while (i <= mid)
// 		tmp[k++] = sequence[i++];
// 	while (j <= right)
// 		tmp[k++] = sequence[j++];
// 	for (size_t l = left; l <= right; ++l)
// 		sequence[l] = tmp[l];
// }

PmergeMe::PmergeMe()
{
	std::cout << GREEN << "Default constructor called" << RESET << std::endl;
}

PmergeMe::~PmergeMe()
{
	std::cout << GREEN << "Destructor called" << RESET << std::endl;	
}

PmergeMe::PmergeMe(PmergeMe const& other)
{
	std::cout << GREEN << "Copy constructor called" << RESET << std::endl;
	*this = other;
}

PmergeMe& PmergeMe::operator=(PmergeMe const& other)
{
	std::cout << GREEN << "Copy assignment operator called" << RESET << std::endl;
	if (this != &other)
	{
		*this = other;
	}
	return (*this);		
}
