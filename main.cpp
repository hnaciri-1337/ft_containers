/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:04:40 by hnaciri-          #+#    #+#             */
/*   Updated: 2023/01/16 15:46:51 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>  
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <stack>
#include "includes/vector.hpp"
#include "includes/stack.hpp"
#include "includes/set.hpp"
#include "includes/map.hpp"
#include "includes/equal.hpp"

template <class T>
bool operator == (const ft::vector<T>& ft_vec, const std::vector<T>& std_vec)
{
	if (ft_vec.size() != std_vec.size() || ft_vec.capacity() != std_vec.capacity())
		return (false);
	for (size_t i = 0; i < std_vec.size(); i++)
	{
		if (std_vec[i] != ft_vec[i])
			return (false);
	}
	return (true);
}

template <class T>
bool operator == (ft::stack<T> ft_stack, std::stack<T> std_stack)
{
	if (ft_stack.size() != std_stack.size())
		return (false);
	while (!ft_stack.empty())
	{
		if (ft_stack.top() != std_stack.top())
			return (false);
		ft_stack.pop();
		std_stack.pop();
	}
	return (true);
}

template <class key, class val>
bool operator == (const ft::pair<key, val>& ft_pair, const std::pair<key, val>& std_pair)
{
	return (ft_pair.first == std_pair.first && ft_pair.second == std_pair.second);
}

template <class key, class val>
bool operator != (const ft::pair<key, val>& ft_pair, const std::pair<key, val>& std_pair)
{
	return (!(ft_pair == std_pair));
}

template <class key, class val>
bool operator == (ft::map<key, val>& ft_map, std::map<key, val>& std_map)
{
	if (ft_map.size() != std_map.size())
		return (false);
	return (true);
	typename ft::map<key, val>::iterator first1 = ft_map.begin();
	typename ft::map<key, val>::iterator last1 = ft_map.end();
	typename std::map<key, val>::iterator first2 = std_map.begin();
	for (; first1 != last1; first1++, first2++)
		if (*first1 != *first2)
			return (false);
	return (true);
}

template <class key>
bool operator == (ft::set<key>& ft_map, std::set<key>& std_map)
{
	if (ft_map.size() != std_map.size())
		return (false);
	return (true);
	typename ft::set<key>::iterator first1 = ft_map.begin();
	typename ft::set<key>::iterator last1 = ft_map.end();
	typename std::set<key>::iterator first2 = std_map.begin();
	for (; first1 != last1; first1++, first2++)
		if (*first1 != *first2)
			return (false);
	return (true);
}

#define EQUAL(s, x) {std::cout << "\t\t\t\t\t\t" << s << "\t["; if (x) std::cout << "\033[32mOK\033[0m";else std::cout << "\033[31mKO\033[0m";std::cout << "]" << std::endl;}

int	main()
{
	{
		std::cout << "\t\t\t\t|\t\t\tTESTING VECTOR\t\t\t|" << std::endl << std::endl;
		sleep(1);
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;

			EQUAL("Default constructor", ft_vec == std_vec);
		}
		{
			ft::vector<int>		ft_vec1(5);
			std::vector<int>	std_vec1(5);
			ft::vector<int>		ft_vec2(5, 10);
			std::vector<int>	std_vec2(5, 10);

			EQUAL("Paramitrized constructor", ft_vec2 == std_vec2 && ft_vec1 == std_vec1);
		}
		{
			std::vector<int>	_vec;
			
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
				_vec.push_back(rand());

			ft::vector<int>		ft_vec(_vec.begin(), _vec.end());
			std::vector<int>	std_vec(_vec.begin(), _vec.end());
			EQUAL("Iterator constructor", ft_vec == std_vec);
		}
		{
			std::vector<int>	_vec1;
			ft::vector<int>		_vec2;
			
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	a = rand();
				_vec1.push_back(a);
				_vec2.push_back(a);
			}
				
			ft::vector<int>		ft_vec(_vec2);
			std::vector<int>	std_vec(_vec1);
			EQUAL("Copy constructor", ft_vec == std_vec);
		}
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;

			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_vec.push_back(_a);
				std_vec.push_back(_a);
			}
			size_t	a = 0;
			for (ft::vector<int>::iterator fit = ft_vec.begin(); fit != ft_vec.end(); fit++)
				a += *fit;
			size_t	b = 0;
			for (std::vector<int>::iterator sit = std_vec.begin(); sit != std_vec.end(); sit++)
				b += *sit;
			EQUAL("Iterator test", ft_vec == std_vec && a == b);
		}
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;

			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_vec.push_back(_a);
				std_vec.push_back(_a);
			}
			size_t	a = 0;
			for (ft::vector<int>::reverse_iterator fit = ft_vec.rbegin(); fit != ft_vec.rend(); fit++)
				a += *fit;
			size_t	b = 0;
			for (std::vector<int>::reverse_iterator sit = std_vec.rbegin(); sit != std_vec.rend(); sit++)
				b += *sit;
			EQUAL("Reverse_Iterator test", ft_vec == std_vec && a == b);
		}
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;

			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_vec.push_back(_a);
				std_vec.push_back(_a);
			}
			EQUAL("Size, Capacity, Max_size test", (ft_vec == std_vec) && (ft_vec.size() == std_vec.size()) && (ft_vec.max_size() == std_vec.max_size()) && (ft_vec.capacity() == std_vec.capacity()));
		}
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;

			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_vec.push_back(_a);
				std_vec.push_back(_a);
			}
			for (int i = 0; i < 1000; i++)
			{
				int	a = rand() % 100;
				ft_vec.resize(a);
				std_vec.resize(a);
			}
			for (int i = 0; i < 1000; i++)
			{
				int	a = rand() % 100;
				int	b = rand() % 1000;
				ft_vec.resize(a, b);
				std_vec.resize(a, b);
			}
			EQUAL("Resize test", (ft_vec == std_vec) && (ft_vec.size() == std_vec.size()) && (ft_vec.max_size() == std_vec.max_size()) && (ft_vec.capacity() == std_vec.capacity()));
		}
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;

			srand(time(nullptr));
			EQUAL("Empty test", ft_vec == std_vec && ft_vec.empty() == std_vec.empty());
			ft_vec.push_back(1);
			std_vec.push_back(1);
			EQUAL("Empty test", ft_vec == std_vec && ft_vec.empty() == std_vec.empty());
		}
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;

			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_vec.push_back(_a);
				std_vec.push_back(_a);
			}
			for (int i = 0; i < 1000; i++)
			{
				int	a = rand() % 100;
				ft_vec.resize(a);
				std_vec.resize(a);
			}
			EQUAL("Reserve test", (ft_vec == std_vec) && (ft_vec.size() == std_vec.size()) && (ft_vec.max_size() == std_vec.max_size()) && (ft_vec.capacity() == std_vec.capacity()));
		}
		{
			ft::vector<int>		ft_vec(100);
			std::vector<int>	std_vec(100);

			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_vec[i] = _a;
				std_vec[i] = _a;
			}
			EQUAL("[] operator test", (ft_vec == std_vec) && (ft_vec.size() == std_vec.size()) && (ft_vec.max_size() == std_vec.max_size()) && (ft_vec.capacity() == std_vec.capacity()));
		}
		{
			ft::vector<int>		ft_vec(100);
			std::vector<int>	std_vec(100);

			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_vec.at(i) = _a;
				std_vec.at(i) = _a;
			}
			EQUAL("At test", (ft_vec == std_vec) && (ft_vec.size() == std_vec.size()) && (ft_vec.max_size() == std_vec.max_size()) && (ft_vec.capacity() == std_vec.capacity()));
		}
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;

			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_vec.push_back(_a);
				std_vec.push_back(_a);
			}
			EQUAL("Front, Back test", (ft_vec == std_vec) && (ft_vec.front() == std_vec.front()) && (ft_vec.back() && std_vec.back()));
		}
		{
			std::vector<int>	_vec;
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;
		
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
				_vec.push_back(rand());

			ft_vec.assign(_vec.begin(), _vec.end());
			std_vec.assign(_vec.begin(), _vec.end());
			for (int i  = 0; i < 100; i++)
			{
				int	a = rand() % 1000;
				int	b = rand() % 1000;
				ft_vec.assign(a, b);
				std_vec.assign(a, b);
			}
			EQUAL("Assign test", ft_vec == std_vec);
		}
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;
		
			srand(time(nullptr));

			for (int i  = 0; i < 10000; i++)
			{
				int	a = rand() % 1000;
				ft_vec.push_back(a);
				std_vec.push_back(a);
			}
			for (int i = 0; i < 1500; i++)
			{
				ft_vec.pop_back();
				std_vec.pop_back();
			}
			EQUAL("Push_back, pop_back test", ft_vec == std_vec);
		}
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;
		
			srand(time(nullptr));
			for (int i  = 0; i < 10000; i++)
			{
				int	a = rand() % 1000;
				ft_vec.push_back(a);
				std_vec.push_back(a);
			}
			for (int i = 0; i < 100; i++)
			{
				int a = rand() % 10000;
				ft::vector<int>::iterator	ft_it = ft_vec.begin() + a;
				std::vector<int>::iterator	std_it = std_vec.begin() + a;
				int	val = rand() % 1000;
				ft_vec.insert(ft_it, 100, val);
				std_vec.insert(std_it, 100, val);
			}
			for (int i = 0; i < 100; i++)
			{
				int a = rand() % 10000;
				ft::vector<int>::iterator	ft_it = ft_vec.begin() + a;
				std::vector<int>::iterator	std_it = std_vec.begin() + a;
				int	val = rand() % 1000;
				ft_vec.insert(ft_it, val);
				std_vec.insert(std_it, val);
			}
			EQUAL("Insert test", ft_vec == std_vec);
		}
		{
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;
		
			srand(time(nullptr));

			for (int i  = 0; i < 10000; i++)
			{
				int	a = rand() % 1000;
				ft_vec.push_back(a);
				std_vec.push_back(a);
			}
			for (int i = 0; i < 1500; i++)
			{
				int a = rand() % ft_vec.size();
				ft::vector<int>::iterator	ft_it = ft_vec.begin() + a;
				std::vector<int>::iterator	std_it = std_vec.begin() + a;

				ft_vec.erase(ft_it);
				std_vec.erase(std_it);
			}
			EQUAL("Erase test", ft_vec == std_vec);
		}
		{
			ft::vector<int>		ft_vec1, ft_vec2;
			std::vector<int>	std_vec1, std_vec2;
		
			srand(time(nullptr));

			for (int i  = 0; i < 10000; i++)
			{
				int	a = rand() % 1000;
				ft_vec1.push_back(a);
				std_vec1.push_back(a);
				a = rand() % 1000;
				ft_vec2.push_back(a);
				std_vec2.push_back(a);
			}
			ft_vec1.swap(ft_vec2);
			std_vec1.swap(std_vec2);
			EQUAL("Swap test", (ft_vec1 == std_vec1 && ft_vec2 == std_vec2));
		}
		{
			ft::vector<int>		ft_vec1;
			std::vector<int>	std_vec1;
		
			srand(time(nullptr));

			for (int i  = 0; i < 10000; i++)
			{
				int	a = rand() % 1000;
				ft_vec1.push_back(a);
				std_vec1.push_back(a);
			}
			ft_vec1.clear();
			std_vec1.clear();
			EQUAL("Clear test", ft_vec1 == std_vec1);
		}
	}
	std::cout << "----------------------------------------------------" << std::endl;
	{
		std::cout << "\t\t\t\t|\t\t\tTESTING MAP\t\t\t|" << std::endl << std::endl;
		sleep(1);
		{
			ft::map<int, int>		ft_map;
			std::map<int, int>		std_map;

			EQUAL("Default constructor", ft_map == std_map);
		}
		{
			std::map<int, int>	_map1;
			ft::map<int, int>	_map2;
			
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int a = rand();
				_map1.insert(std::make_pair(a, a));
				_map2.insert(ft::make_pair(a, a));
			}

			std::map<int, int>	std_map(_map1.begin(), _map1.end());
			ft::map<int, int>	ft_map(_map2.begin(), _map2.end());
			EQUAL("Iterator constructor", ft_map == std_map);
		}
		{
			std::map<int, int>	_map1;
			ft::map<int, int>	_map2;
			
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	a = rand();
				_map1.insert(std::make_pair(a, a));
				_map2.insert(ft::make_pair(a, a));
			}
				
			ft::map<int, int>	ft_map(_map2);
			std::map<int, int>	std_map(_map1);
			EQUAL("Copy constructor", ft_map == std_map);
		}
		{
			std::map<int, int>	_map1, std_map;
			ft::map<int, int>	_map2, ft_map;
			
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	a = rand();
				_map1.insert(std::make_pair(a, a));
				_map2.insert(ft::make_pair(a, a));
			}
			std_map = _map1;
			ft_map = _map2;
			EQUAL("Assignment operator", ft_map == std_map);
		}
		{
			ft::map<int, int>		ft_map;
			std::map<int, int>		std_map;

			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_map.insert(ft::make_pair(_a, _a));
				std_map.insert(std::make_pair(_a, _a));
			}
			size_t	a = 0;
			for (ft::map<int, int>::iterator fit = ft_map.begin(); fit != ft_map.end(); fit++)
				a += fit->second;
			size_t	b = 0;
			for (std::map<int, int>::iterator sit = std_map.begin(); sit != std_map.end(); sit++)
				b += sit->second;
			EQUAL("Iterator test", ft_map == std_map && a == b);
		}
		{
			ft::map<int, int>		ft_map;
			std::map<int, int>		std_map;

			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_map.insert(ft::make_pair(_a, _a));
				std_map.insert(std::make_pair(_a, _a));
			}
			size_t	a = 0;
			for (ft::map<int, int>::reverse_iterator fit = ft_map.rbegin(); fit != ft_map.rend(); fit++)
				a += fit->second;
			size_t	b = 0;
			for (std::map<int, int>::reverse_iterator sit = std_map.rbegin(); sit != std_map.rend(); sit++)
				b += sit->second;
			EQUAL("Reverse_iterator test", ft_map == std_map && a == b);
		}
		{
			ft::map<int, int>		ft_map;
			std::map<int, int>		std_map;

			srand(time(nullptr));
			EQUAL("Empty test", ft_map == std_map && ft_map.empty() == std_map.empty());
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_map.insert(ft::make_pair(_a, _a));
				std_map.insert(std::make_pair(_a, _a));
			}
			EQUAL("Empty test", ft_map == std_map && ft_map.empty() == std_map.empty());
		}
		{
			ft::map<int, int>		ft_map;
			std::map<int, int>		std_map;
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_map.insert(ft::make_pair(_a, _a));
				std_map.insert(std::make_pair(_a, _a));
			}
			
			EQUAL("Size test", ft_map == std_map);
		}
		{
			ft::map<int, int>		ft_map;
			std::map<int, int>		std_map;
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	a = rand() % 100;
				ft_map[i] = a;
				std_map[i] = a;
			}
			
			EQUAL("[] operator test", ft_map == std_map);
		}
		{
			ft::map<int, int>		ft_map;
			std::map<int, int>		std_map;
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	a = rand() % 100;
				ft_map.insert(ft::make_pair(i, a));
				std_map.insert(std::make_pair(i, a));
			}
			for(int i = 0; i < 100; i++)
			{
				int a = rand() % 100;
				ft_map.at(i) = a;
				std_map.at(i) = a;
			}
			EQUAL("At test", ft_map == std_map);
		}
		{
			ft::map<int, int>		ft_map;
			std::map<int, int>		std_map;
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	a = rand() % 100;
				ft_map.insert(ft::make_pair(i, a));
				std_map.insert(std::make_pair(i, a));
			}
			EQUAL("Insert test", ft_map == std_map);
		}
		{
			ft::map<int, int>		ft_map;
			std::map<int, int>		std_map;
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	a = rand() % 100;
				ft_map.insert(ft::make_pair(i, a));
				std_map.insert(std::make_pair(i, a));
			}
			for(int i = 0; i < 50; i++)
			{
				int	a = rand() % 100;
				ft_map.erase(a);
				std_map.erase(a);
			}
			EQUAL("Erase test", ft_map == std_map);
		}
		{
			ft::map<int, int>	ft_map1, ft_map2;
			std::map<int, int>	std_map1, std_map2;
		
			srand(time(nullptr));

			for (int i  = 0; i < 10000; i++)
			{
				int	a = rand() % 1000;
				ft_map1.insert(ft::make_pair(a, a));
				std_map1.insert(std::make_pair(a, a));
				a = rand() % 1000;
				ft_map2.insert(ft::make_pair(a, a));
				std_map2.insert(std::make_pair(a, a));
			}
			ft_map1.swap(ft_map2);
			std_map1.swap(std_map2);
			EQUAL("Swap test", (ft_map1 == std_map1 && ft_map2 == std_map2));
		}
		{
			ft::map<int, int>	ft_map;
			std::map<int, int>	std_map;
		
			srand(time(nullptr));

			for (int i  = 0; i < 10000; i++)
			{
				int	a = rand() % 1000;
				ft_map.insert(ft::make_pair(a, a));
				std_map.insert(std::make_pair(a, a));
			}
			ft_map.clear();
			std_map.clear();
			EQUAL("Clear test", (ft_map == std_map));
		}
		{
			ft::map<int, int>					ft_map;
			std::map<int, int>					std_map;
			ft::vector<std::pair<int, int> >		ft_vec;
			std::vector<std::pair<int, int> >	std_vec;
	
			srand(time(nullptr));
			for (int i  = 0; i < 1000; i++)
			{
				int	a = rand() % 1000;
				ft_map.insert(ft::make_pair(a, a));
				std_map.insert(std::make_pair(a, a));
			}
			for (int i = 0; i < 100; i++)
			{
				int	a = rand() % 1000;
				if (std_map.find(a) != std_map.end())
				{
					ft::map<int, int>::iterator it = ft_map.find(a);
					std::pair<int, int>	t(std::make_pair(it->first, it->second));
					ft_vec.push_back(t);
					std_vec.push_back(*std_map.find(a));
				}
			}
			EQUAL("Find test", (ft_vec == std_vec));
		}
		{
			ft::map<int, int>					ft_map;
			std::map<int, int>					std_map;
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;
	
			srand(time(nullptr));
			for (int i  = 0; i < 1000; i++)
			{
				int	a = rand() % 1000;
				ft_map.insert(ft::make_pair(a, a));
				std_map.insert(std::make_pair(a, a));
			}
			for (int i = 0; i < 100; i++)
			{
				int	a = rand() % 1000;
				ft_vec.push_back(ft_map.count(a));
				std_vec.push_back(std_map.count(a));
			}
			EQUAL("Count test", (ft_vec == std_vec));
		}
		{
			ft::map<int, int>					ft_map;
			std::map<int, int>					std_map;
			ft::vector<std::pair<int, int> >		ft_vec;
			std::vector<std::pair<int, int> >	std_vec;
	
			srand(time(nullptr));
			for (int i  = 0; i < 1000; i++)
			{
				int	a = rand() % 1000;
				ft_map.insert(ft::make_pair(a, a));
				std_map.insert(std::make_pair(a, a));
			}
			for (int i = 0; i < 100; i++)
			{
				int	a = rand() % 1000;
				if (std_map.lower_bound(a) != std_map.end())
				{
					ft::map<int, int>::iterator it = ft_map.lower_bound(a);
					std::pair<int, int>	t(std::make_pair(it->first, it->second));
					ft_vec.push_back(t);
					std_vec.push_back(*std_map.lower_bound(a));
				}
			}
			EQUAL("Lowerbound test", (ft_vec == std_vec));
		}
		{
			ft::map<int, int>					ft_map;
			std::map<int, int>					std_map;
			ft::vector<std::pair<int, int> >	ft_vec;
			std::vector<std::pair<int, int> >	std_vec;
	
			srand(time(nullptr));
			for (int i  = 0; i < 1000; i++)
			{
				int	a = rand() % 1000;
				ft_map.insert(ft::make_pair(a, a));
				std_map.insert(std::make_pair(a, a));
			}
			for (int i = 0; i < 100; i++)
			{
				int	a = rand() % 1000;
				if (std_map.upper_bound(a) != std_map.end())
				{
					ft::map<int, int>::iterator it = ft_map.upper_bound(a);
					std::pair<int, int>	t(std::make_pair(it->first, it->second));
					ft_vec.push_back(t);
					std_vec.push_back(*std_map.upper_bound(a));
				}
			}
			EQUAL("Upperbound test", (ft_vec == std_vec));
		}
	}
	std::cout << "----------------------------------------------------" << std::endl;
	{
		std::cout << "\t\t\t\t|\t\t\tTESTING STACK\t\t\t|" << std::endl << std::endl;
		sleep(1);
		{
			ft::stack<int>	ft_stack;
			std::stack<int>	std_stack;

			EQUAL("Default constructor", ft_stack == std_stack);
		}
		{
			ft::stack<int>	ft_stack;
			std::stack<int>	std_stack;

			for (int i = 0; i < 10000; i++)
			{
				int a = rand();
				ft_stack.push(a);
				std_stack.push(a);
			}
			EQUAL("Push, top test", ft_stack == std_stack);
			for (int i = 0; i < 1000; i++)
			{
				ft_stack.pop();
				std_stack.pop();
			}
			EQUAL("Pop, empty test", ft_stack == std_stack && ft_stack.empty() == std_stack.empty());
		}
	}
	std::cout << "----------------------------------------------------" << std::endl;
	{
		std::cout << "\t\t\t\t|\t\t\tTESTING SET\t\t\t|" << std::endl << std::endl;
		sleep(1);
		{
			ft::set<int>		ft_set;
			std::set<int>		std_set;

			EQUAL("Default constructor", ft_set == std_set);
		}
		{
			std::set<int>	_set1;
			ft::set<int>	_set2;
			
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int a = rand();
				_set1.insert(a);
				_set2.insert(a);
			}

			std::set<int>	std_set(_set1.begin(), _set1.end());
			ft::set<int>	ft_set(_set2.begin(), _set2.end());
			EQUAL("Iterator constructor", ft_set == std_set);
		}
		{
			std::set<int>	_set1;
			ft::set<int>	_set2;
			
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	a = rand();
				_set1.insert(a);
				_set2.insert(a);
			}
				
			ft::set<int>	ft_set(_set2);
			std::set<int>	std_set(_set1);
			EQUAL("Copy constructor", ft_set == std_set);
		}
		{
			std::set<int>	_map1, std_map;
			ft::set<int>	_map2, ft_map;
			
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	a = rand();
				_map1.insert(a);
				_map2.insert(a);
			}
			std_map = _map1;
			ft_map = _map2;
			EQUAL("Assignment operator", ft_map == std_map);
		}
		{
			ft::set<int>		ft_set;
			std::set<int>		std_set;

			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_set.insert(_a);
				std_set.insert(_a);
			}
			size_t	a = 0;
			for (ft::set<int>::iterator fit = ft_set.begin(); fit != ft_set.end(); fit++)
				a += *fit;
			size_t	b = 0;
			for (std::set<int>::iterator sit = std_set.begin(); sit != std_set.end(); sit++)
				b += *sit;
			EQUAL("Iterator test", ft_set == std_set && a == b);
		}
		{
			ft::set<int>		ft_set;
			std::set<int>		std_set;

			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_set.insert(_a);
				std_set.insert(_a);
			}
			size_t	a = 0;
			for (ft::set<int>::reverse_iterator fit = ft_set.rbegin(); fit != ft_set.rend(); fit++)
				a += *fit;
			size_t	b = 0;
			for (std::set<int>::reverse_iterator sit = std_set.rbegin(); sit != std_set.rend(); sit++)
				b += *sit;
			EQUAL("Reverse_Iterator test", ft_set == std_set && a == b);
		}
		{
			ft::set<int>		ft_set;
			std::set<int>		std_set;

			srand(time(nullptr));
			EQUAL("Empty test", ft_set == std_set && ft_set.empty() == std_set.empty());
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_set.insert(_a);
				std_set.insert(_a);
			}
			EQUAL("Empty test", ft_set == std_set && ft_set.empty() == std_set.empty());
		}
		{
			ft::set<int>		ft_set;
			std::set<int>		std_set;
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	_a = rand() % 100;
				ft_set.insert(_a);
				std_set.insert(_a);
			}
			
			EQUAL("Size test", ft_set == std_set);
		}
		{
			ft::set<int>		ft_set;
			std::set<int>		std_set;
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	a = rand() % 100;
				ft_set.insert(a);
				std_set.insert(a);
			}
			EQUAL("Insert test", ft_set == std_set);
		}
		{
			ft::set<int>		ft_set;
			std::set<int>		std_set;
			srand(time(nullptr));
			for(int i = 0; i < 100; i++)
			{
				int	a = rand() % 100;
				ft_set.insert(a);
				std_set.insert(a);
			}
			for(int i = 0; i < 50; i++)
			{
				int	a = rand() % 100;
				ft_set.erase(a);
				std_set.erase(a);
			}
			EQUAL("Erase test", ft_set == std_set);
		}
		{
			ft::set<int>	ft_set1, ft_set2;
			std::set<int>	std_set1, std_set2;
		
			srand(time(nullptr));

			for (int i  = 0; i < 10000; i++)
			{
				int	a = rand() % 1000;
				ft_set1.insert(a);
				std_set1.insert(a);
				a = rand() % 1000;
				ft_set2.insert(a);
				std_set2.insert(a);
			}
			ft_set1.swap(ft_set2);
			std_set1.swap(std_set2);
			EQUAL("Swap test", (ft_set1 == std_set1 && ft_set2 == std_set2));
		}
		{
			ft::set<int>	ft_set;
			std::set<int>	std_set;
		
			srand(time(nullptr));

			for (int i  = 0; i < 10000; i++)
			{
				int	a = rand() % 1000;
				ft_set.insert(a);
				std_set.insert(a);
			}
			ft_set.clear();
			std_set.clear();
			EQUAL("Clear test", (ft_set == std_set));
		}
		{
			ft::set<int>		ft_set;
			std::set<int>		std_set;
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;
	
			srand(time(nullptr));
			for (int i  = 0; i < 1000; i++)
			{
				int	a = rand() % 1000;
				ft_set.insert(a);
				std_set.insert(a);
			}
			for (int i = 0; i < 100; i++)
			{
				int	a = rand() % 1000;
				if (std_set.find(a) != std_set.end())
				{
					ft_vec.push_back(*ft_set.find(a));
					std_vec.push_back(*std_set.find(a));
				}
			}
			EQUAL("Find test", (ft_vec == std_vec));
		}
		{
			ft::set<int>					ft_set;
			std::set<int>					std_set;
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;
	
			srand(time(nullptr));
			for (int i  = 0; i < 1000; i++)
			{
				int	a = rand() % 1000;
				ft_set.insert(a);
				std_set.insert(a);
			}
			for (int i = 0; i < 100; i++)
			{
				int	a = rand() % 1000;
				ft_vec.push_back(ft_set.count(a));
				std_vec.push_back(std_set.count(a));
			}
			EQUAL("Count test", (ft_vec == std_vec));
		}
		{
			ft::set<int>		ft_set;
			std::set<int>		std_set;
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;
	
			srand(time(nullptr));
			for (int i  = 0; i < 1000; i++)
			{
				int	a = rand() % 1000;
				ft_set.insert(a);
				std_set.insert(a);
			}
			for (int i = 0; i < 100; i++)
			{
				int	a = rand() % 1000;
				if (std_set.lower_bound(a) != std_set.end())
				{
					ft_vec.push_back(*ft_set.lower_bound(a));
					std_vec.push_back(*std_set.lower_bound(a));
				}
			}
			EQUAL("Lowerbound test", (ft_vec == std_vec));
		}
		{
			ft::set<int>		ft_set;
			std::set<int>		std_set;
			ft::vector<int>		ft_vec;
			std::vector<int>	std_vec;
	
			srand(time(nullptr));
			for (int i  = 0; i < 1000; i++)
			{
				int	a = rand() % 1000;
				ft_set.insert(a);
				std_set.insert(a);
			}
			for (int i = 0; i < 100; i++)
			{
				int	a = rand() % 1000;
				if (std_set.upper_bound(a) != std_set.end())
				{
					ft_vec.push_back(*ft_set.upper_bound(a));
					std_vec.push_back(*std_set.upper_bound(a));
				}
			}
			EQUAL("Upperbound test", (ft_vec == std_vec));
		}
	}
}
