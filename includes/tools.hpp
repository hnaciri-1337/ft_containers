/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:57:09 by hnaciri-          #+#    #+#             */
/*   Updated: 2022/12/08 15:52:35 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef TOOLS_HPP
# define TOOLS_HPP

# include <iostream>

namespace	ft
{

    // ENABLE_IF
    template <bool Cond, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    // IS_INTEGRAL
    template<class T, class U = void>
    struct is_integral
    {
        static const bool value = false;
    };

    template<class T>
    struct is_integral<bool, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<char, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<char16_t, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<char32_t, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<wchar_t, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<signed char, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<short int, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<int, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<long int, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<long long int, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<unsigned char, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<unsigned short int, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<unsigned int, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<unsigned long int, T>
    {
        static const bool value = true;
    };
    template<class T>
    struct is_integral<unsigned long long int, T>
    {
        static const bool value = true;
    };
    
}

# endif
