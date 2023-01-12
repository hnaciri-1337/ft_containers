// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.cpp                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/11/01 17:04:40 by hnaciri-          #+#    #+#             */
// /*   Updated: 2023/01/11 22:42:22 by hnaciri-         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include<unistd.h>  
// #include <vector>
// #include <iostream>
// #include "includes/includes.hpp"
// #include "file.hpp"
// #include <map>

// template<class T>
// void	ft_print_vector(ft::vector<T> &_vec)
// {
// 	std::cout << "[";
// 	for (size_t i = 0; i < _vec.size() - 1; i++)
// 		std::cout << _vec[i] << ",";
// 	std::cout << _vec[_vec.size() - 1] << "]" << std::endl;
// }

// template<class T>
// void	std_print_vector(std::vector<T> &_vec)
// {
// 	std::cout << "[";
// 	for (size_t i = 0; i < _vec.size() - 1; i++)
// 		std::cout << _vec[i] << ",";
// 	std::cout << _vec[_vec.size() - 1] << "]" << std::endl;
// }

// void _print(const int& x)
// {
//     std::cout << x << '\n';
// }

// std::string gen_random(const int len)
// {
//     static const char alphanum[] =
//         "0123456789"
//         "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//         "abcdefghijklmnopqrstuvwxyz";
//     std::string tmp_s;
//     tmp_s.reserve(len);

//     for (int i = 0; i < len; ++i) {
//         tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
//     }
    
//     return tmp_s;
// }

// // struct student
// // {
// // 	std::string login;
// // 	struct student *next;
// // };

// int	main()
// {
// 	// {
// 	// 	ft::vector<int>		ft_vec;
// 	// 	std::vector<int>	std_vec;

// 	// 	for(int i = 0; i < 10; i++)
// 	// 	{
// 	// 		int	_a = rand() % 100;
// 	// 		ft_vec.push_back(_a);
// 	// 		std_vec.push_back(_a);
// 	// 	}
// 	// 	std::cout << std_vec.size() << "|" << std_vec.capacity() << std::endl;
// 	// 	std_print_vector(std_vec);
// 	// 	std::cout << ft_vec.size() << "|" << ft_vec.capacity() << std::endl;
// 	// 	ft_print_vector(ft_vec);
// 	// 	std_vec.resize(18, -8748);
// 	// 	ft_vec.resize(18, -8748);
// 	// 	std::cout << "--------------------" << std::endl;
// 	// 	std::cout << std_vec.size() << "|" << std_vec.capacity() << std::endl;
// 	// 	std_print_vector(std_vec);
// 	// 	std::cout << ft_vec.size() << "|" << ft_vec.capacity() << std::endl;
// 	// 	ft_print_vector(ft_vec);
// 	// }
// 	// std::cout << "______________________________________________" << std::endl;
// 	// {
// 	// 	std::vector<int>	_vec1(21, 3);
// 	// 	ft::vector<int>		_vec2(21, 3);

// 	// 	std_print_vector(_vec1);
// 	// 	ft_print_vector(_vec2);
// 	// 	_vec1.assign(17, 1);
// 	// 	_vec2.assign(17, 1);
// 	// 	std::cout << _vec1.capacity() << " | " << _vec1.size() << std::endl;
// 	// 	std_print_vector(_vec1);
// 	// 	std::cout << _vec2.capacity() << " | " << _vec2.size() << std::endl;
// 	// 	ft_print_vector(_vec2);
// 	// }
// 	// std::cout << "______________________________________________" << std::endl;
// 	// {
// 	// 	std::vector<int>	_vec1;
// 	// 	ft::vector<int>		_vec2;

// 	// 	for(int i = 0; i < 7; i++)
// 	// 	{
// 	// 		int	_a = rand() % 100;
// 	// 		_vec1.push_back(_a);
// 	// 		_vec2.push_back(_a);
// 	// 	}
// 	// 	std::cout << "size : " << _vec1.size() << "| capacity : " << _vec1.capacity() << std::endl;
// 	// 	std_print_vector(_vec1);
// 	// 	std::vector<int>::iterator _it = _vec1.insert(_vec1.begin() + 3, 7, 9);
// 	// 	std::cout << "size : " << _vec1.size() << "| capacity : " << _vec1.capacity() << std::endl;
// 	// 	std_print_vector(_vec1);
// 	// 	std::cout << *_it << std::endl;
// 	// 	std::cout << "--------------------" << std::endl;
// 	// 	std::cout << "size : " << _vec2.size() << "| capacity : " << _vec2.capacity() << std::endl;
// 	// 	ft_print_vector(_vec2);
// 	// 	ft::vector<int>::iterator __it = _vec2.insert(_vec2.begin() + 3, 7, 9);
// 	// 	std::cout << "size : " << _vec2.size() << "| capacity : " << _vec2.capacity() << std::endl;
// 	// 	ft_print_vector(_vec2);
// 	// 	std::cout << *__it << std::endl;
// 	// }
// 	// {
// 	// 	std::vector<int>	_vec1, _vec2;
// 	// 	ft::vector<int>		_vec3, _vec4;

// 	// 	for (int i = 0; i < 10; i++)
// 	// 	{
// 	// 		int	a = rand() % 100;

// 	// 		_vec1.push_back(a);
// 	// 		_vec3.push_back(a);
// 	// 	}
// 	// 	for (int i = 0; i < 10; i++)
// 	// 	{
// 	// 		int	a = rand() % 100;

// 	// 		_vec2.push_back(a);
// 	// 		_vec4.push_back(a);
// 	// 	}
// 	// 	std_print_vector(_vec1);
// 	// 	ft_print_vector(_vec3);
// 	// 	std::cout << "-----------------------" << std::endl;
// 	// 	std_print_vector(_vec2);
// 	// 	ft_print_vector(_vec4);
// 	// 	std::cout << "-----------------------" << std::endl;
// 	// 	_vec1.insert(_vec1.begin() + 3, _vec2.begin() + 2 , _vec2.end() - 3);
// 	// 	_vec3.insert(_vec3.begin() + 3, _vec4.begin() + 2 , _vec4.end() - 3);
// 	// 	std_print_vector(_vec1);
// 	// 	ft_print_vector(_vec3);
// 	// }
// 	// {
// 	// 	ft::vector<std::string>	_vec;

// 	// 	std::string s_string[32] =
// 	// 	{                                                                   \
// 	// 		"QExoqp0nICr0sXsHqty2", "naax9QcpJhvaL7DezsNQ", "25ZTtB6wbptfbxM8AvHB",                    \
// 	// 		"tShYNtc0MkdjqLrOatgz", "7Z3kf1Qec0NnsLSEpbOt", "WhkSNrKJC966fvjZ2Or1",                    \
// 	// 		"8vlxlFRRgW7yYj4GO7dt", "5sq1aoT8zP0HaHj3nFOK", "61Dv31GYZhkgjKCErpng",                    \
// 	// 		"l0IIcWWHhOcPzoxEamQM", "bE1RYclskwXlhCm46YFs", "kXeoi5qz94JYPqSDTs79",                    \
// 	// 		"TFsQP1dz8VVos9KzUpY0", "b3wYQR7An193gjgYuRj3", "xSmyNsnSJ47jLqrvbpyr",                    \
// 	// 		"guAIP2Wq43Gf8VhHsyu5", "yT6c2loPebHovnq9BQog", "3qvU1xcVm2g1DKFDlqh4",                    \
// 	// 		"L0q8RR9P41VD4sVjdnWl", "YdjESsIZM4b1oGQPjpBe", "l1ZVQbWKw7brHUSimJgq",                    \
// 	// 		"xdn0cf4vqRzpfXWtl10G", "lYnZvpqaV0s8DowMZwzV", "8P1cyKrwJNLoJyvLjYqO",                    \
// 	// 		"4MhOXNbAX23CEijO5cRT", "tHe3miAwCOVQbuoLaEP2", "l6uNLsc8fiLl3eWoG6j6",                    \
// 	// 		"477xt6l0lph9ALQdr4HX", "D9UJNe4s8YF02LhrwOdl", "dLCisBNOdE8yugntu6cj",                    \
// 	// 		"YvY4aQFHgAuagn4dFLO1", "eGR6Dtv7LW75qlV5Fkik"                                             \
//     // 	};
// 	// 	_vec.insert(_vec.begin(), s_string, s_string + 32);
// 	// 	ft_print_vector(_vec);
// 	// }
// 	// {
// 	// 	ft::vector<int> foo (3,100);   // three ints with a value of 100
// 	// 	ft::vector<int> bar (5,200);   // five ints with a value of 200

// 	// 	foo.swap(bar);

// 	// 	std::cout << "foo contains:";
// 	// 	ft_print_vector(foo);
// 	// 	std::cout << "bar contains:";
// 	// 	ft_print_vector(bar);
// 	// }
// 	// {
// 	// 	{
// 	// 		std::cout << "char : " << std::vector<char>().max_size() << std::endl;
// 	// 		std::cout << "char : " << ft::vector<char>().max_size() << std::endl;
// 	// 	}
// 	// 	{
// 	// 		std::cout << "unsigned char : " << std::vector<unsigned char>().max_size() << std::endl;
// 	// 		std::cout << "unsigned char : " << ft::vector<unsigned char>().max_size() << std::endl;
// 	// 	}
// 	// 	{
// 	// 		std::cout << "int : " << std::vector<int>().max_size() << std::endl;
// 	// 		std::cout << "int : " << ft::vector<int>().max_size() << std::endl;
// 	// 	}
// 	// 	{
// 	// 		std::cout << "unsigned int : " << std::vector<unsigned int>().max_size() << std::endl;
// 	// 		std::cout << "unsigned int : " << ft::vector<unsigned int>().max_size() << std::endl;
// 	// 	}
// 	// 	{
// 	// 		std::cout << "std::string : " << std::vector<std::string>().max_size() << std::endl;
// 	// 		std::cout << "std::string : " << ft::vector<std::string>().max_size() << std::endl;
// 	// 	}
// 	// 	{
// 	// 		std::cout << "long : " << std::vector<long>().max_size() << std::endl;
// 	// 		std::cout << "long : " << ft::vector<long>().max_size() << std::endl;
// 	// 	}
// 	// 	{
// 	// 		std::cout << "unsigned long long : " << std::vector<unsigned long long>().max_size() << std::endl;
// 	// 		std::cout << "unsigned long long : " << ft::vector<unsigned long long>().max_size() << std::endl;
// 	// 	}
// 	// }
// 	// {
// 	// 	ft::vector<int> v(5, 1);
// 	// 	v.insert(v.begin(), 5, 2);
//     //     std::for_each(v.rbegin(), v.rend(), _print);
// 	// }
// 	// std::cout << "++++++++++++++++++++++++++++\n";
// 	// {
// 	// 	std::vector<int> v(5, 1);
// 	// 	v.insert(v.begin(), 5, 2);
//     //     std::for_each(v.rbegin(), v.rend(), _print);
// 	// }
// 	// {
// 	// 	ft::vector<int>					_vec;
		
// 	// 	for (int i = 0; i < 10; i++)
// 	// 		_vec.push_back(rand() % 100);
// 	// 	_vec.clear ();
// 	// 	std::cout << _vec.size() << std::endl;
// 	// }
// 	// {
// 	// 	std::vector<int>					_vec;
		
// 	// 	for (int i = 0; i < 10; i++)
// 	// 		_vec.push_back(rand() % 100);
// 	// 	_vec.clear ();
// 	// 	std::cout << _vec.size() << std::endl;
// 	// }
// 	// {
// 		// srand((unsigned)time(NULL));     
// 		// ft::map <std::string, int>	_map;
// 		// std::map <std::string, int>	__map;
// 		// ft::vector<int>		_vec;
	
// 		// for (int i = 0; i < 11; ++i)
// 		// {
// 		// 	_vec.push_back ((rand() % 100));
// 		// 	std::string	s = gen_random(10);
// 		// 	__map.insert (std::make_pair(s, _vec[i]));
// 		// 	_map.insert (ft::make_pair(s, _vec[i]));
// 		// }
// 		// __map["Hello"] = 99;
// 		// _map["Hello"] = 99;
// 		// for (ft::map<std::string, int>::iterator i = _map.begin(); i != _map.end(); i++)
// 		// 	std::cout << i->first << " " << i->second << "|";
// 		// std::cout << std::endl;
// 		// for (std::map<std::string, int>::iterator i = __map.begin(); i != __map.end(); i++)
// 		// 	std::cout << i->first << " " << i->second << "|";
// 		// std::cout << std::endl;
// 	// }
// 	// {
// 	// 	srand((unsigned)time(NULL));     
// 	// 	ft::map <std::string, int>	_map, b;
// 	// 	ft::vector<int>		_vec;
	
// 	// 	for (int i = 0; i < 11; ++i)
// 	// 	{
// 	// 		_vec.push_back ((rand() % 100));
// 	// 		std::string	s = gen_random(10);
// 	// 		_map.insert (ft::make_pair(s, _vec[i]));
// 	// 	}
// 	// 	b.insert(_map.begin(), _map.end());
// 	// 	_map.print();
// 	// 	std::cout << std::endl;
// 	// 	b.print();
// 	// 	std::cout << std::endl;
// 	// }
// 	// {
// 	// 	ft::map <int, int>	_map;
// 	// 	ft::vector<int>		_vec;
// 	// 	_vec.push_back(60);
// 	// 	_vec.push_back(35);
// 	// 	_vec.push_back(28);
// 	// 	_vec.push_back(90);
// 	// 	_vec.push_back(71);
// 	// 	_vec.push_back(17);
// 	// 	_vec.push_back(40);
// 	// 	_vec.push_back(29);
// 	// 	_vec.push_back(41);
// 	// 	_vec.push_back(51);
// 	// 	for (int i = 0; i < 10; ++i)
// 	// 	{
// 	// 		_map.insert (ft::make_pair(_vec[i], _vec[i]));
// 	// 		std::cout << _vec[i] << " ";
// 	// 	}
// 	// 	std::cout << std::endl;
// 	// 	while (1)
// 	// 	{
// 	// 		std::cout << std::endl;
// 	// 		printTree (_map._map.get_root(), nullptr, false);
// 	// 		std::cout << "enter :";
// 	// 		int a; std::cin >> a;
// 	// 		if (a == -1) break ;
// 	// 		_map.erase (a);
// 	// 	}
// 	// 	printTree (_map._map.get_root(), nullptr, false);
// 	// 	while (1);
// 	// }
// 	// {
// 	// 	ft::map<int, std::string> m;
// 	// 	m.insert(ft::make_pair(23, "23n"));
// 	// 	m.insert(ft::make_pair(25, "asdasdfsdfsafdsf"));
// 	// 	m.insert(ft::make_pair(1, "asdssdfdfdffffff"));
// 	// 	m.insert(ft::make_pair(2, "dsfdffffdfdfdsdfdffa"));
// 	// 	m.insert(ft::make_pair(3, "sssdfs"));
// 	// 	m.insert(ft::make_pair(75, "dfse"));
// 	// 	m.insert(ft::make_pair(30, "sefsadfasdfasdfsadfasdfsf"));
// 	// 	m.insert(ft::make_pair(-22, "dfhkihgbnfbcx5reterjhd"));
// 	// 	m.insert(ft::make_pair(-23, "sdffgdfgrefet34thfgheewt"));
// 	// 	m.insert(ft::make_pair(0, "98y4rtuohwidsjusdossefsse"));
		
// 	// 	printTree (m._map.get_root(), nullptr, false); std::cout << std::endl;
//     //     m.erase(0);
//     //     m.erase(75);
//     //     m.erase(1);
//     //     m.erase(2);
// 	// 	m.erase(3);
// 	// 	m.erase(23);
// 	// 	printTree (m._map.get_root(), nullptr, false); std::cout << std::endl;
// 	// 	m.erase(30);
// 	// 	printTree (m._map.get_root(), nullptr, false); std::cout << std::endl;
// 	// 	m.erase(-23);
// 	// 	printTree (m._map.get_root(), nullptr, false); std::cout << std::endl;
// 	// 	m.erase(-22);
// 	// 	m.erase(25);
// 	// }
// 	// {
// 	// 	ft::map<int, int>	_map;
// 	// 	try
// 	// 	{
// 	// 		_map.at(5);
// 	// 	}
// 	// 	catch(const std::exception& e)
// 	// 	{
// 	// 		std::cerr << e.what() << '\n';
// 	// 	}
// 	// }
// 	// {
// 	// 	ft::map<int, std::string>	m;
// 	// 	m.insert(ft::make_pair(23, "23n"));
//     //     m.insert(ft::make_pair(25, "asdasdfsdfsafdsf"));
//     //     m.insert(ft::make_pair(1, "asdssdfdfdffffff"));
//     //     m.insert(ft::make_pair(2, "dsfdffffdfdfdsdfdffa"));
//     //     m.insert(ft::make_pair(3, "sssdfs"));
//     //     m.insert(ft::make_pair(75, "dfse"));
//     //     m.insert(ft::make_pair(30, "sefsadfasdfasdfsadfasdfsf"));
//     //     m.insert(ft::make_pair(-22, "dfhkihgbnfbcx5reterjhd"));
//     //     m.insert(ft::make_pair(-23, "sdffgdfgrefet34thfgheewt"));
//     //     m.insert(ft::make_pair(0, "98y4rtuohwidsjusdossefsse"));

// 	// 	while (1)
// 	// 	{
// 	// 		printTree (m._map.get_root(), nullptr, false);
// 	// 		int	a;
// 	// 		std::cout << "\nenter : ";
// 	// 		cin >> a;
// 	// 		if (a == -1)
// 	// 			break ;
// 	// 		m.erase (a);
// 	// 	}
// 	// 	printTree (m._map.get_root(), nullptr, false);
// 	// }
// 	// {
// 	// 	srand(time(nullptr));
// 	// 	int	array[] = {61, 27, 64, 75, 1, 81, 16, 7, 84, 39, 87, 31, 50, 57, 24, 31, 72, 48, 15, 67};
// 	// 	ft::map <char, int>	_map;
// 	// 	ft::vector<int>		_vec(array, array + 20);
// 	// 	for (int i = 0; i < 10; i++)
// 	// 	{
// 	// 		_map.insert (ft::make_pair(gen_random(7)[0], _vec[i]));
// 	// 	}
// 	// 	while (1)
// 	// 	{
// 	// 		// std::cout << _map._map.get_root()->value->first << std::endl;
// 	// 		printTree (_map._map.get_root(), nullptr, false);
// 	// 		std::cout << "enter :";
// 	// 		std::string a; std::cin >> a;
// 	// 		if (a == "-1") break ;
// 	// 		_map.erase (a[0]);
// 	// 	}
// 	// 	printTree (_map._map.get_root(), nullptr, false);
// 	// 	while (1);
// 	// }
// 	{
// 		ft::map<int, std::string>	_map;

// 		std::cout << ((_map.empty()) ? "true" : "false") << std::endl;
// 	}
// }

#include <iostream>
#include <string>
#include <deque>

#ifdef STD //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
#include "includes/map.hpp"
#include "includes/stack.hpp"
#include "includes/vector.hpp"
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}
