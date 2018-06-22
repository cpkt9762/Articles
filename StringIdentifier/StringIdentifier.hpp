/// Copyright (C) 2018-2019
/// Vincent STEHLY--CALISTO, vincentstehly@hotmail.fr
///
/// This program is free software; you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program; if not, write to the Free Software Foundation, Inc.,
/// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

/// \file       StringIdentifier.hpp
/// \date       22/06/2018
/// \project    StringIdentifier
/// \author     Vincent STEHLY--CALISTO

#ifndef ARTICLES_STRING_IDENTIFIER_HPP__
#define ARTICLES_STRING_IDENTIFIER_HPP__

#include <cstdint>
#include <iostream>

/// \namespace  impl
namespace impl
{

constexpr const int8_t   STRING_END_BYTE = nullptr;
constexpr const uint32_t STRING_BIT_SHIT = 5;

/// \brief   Magic number from string hash (k = 33)
/// \warning Do not edit
constexpr const uint32_t STRING_HASH_KEY = 5381;

/// \brief  Computes a 32 bits hash from a c string
/// \param  pTail A pointer on the c string
/// \param  hash The result
/// \return A 32 bits hash
///
/// \note   This function is tail recursive
constexpr uint32_t hash_function(const char* pTail, uint32_t hash = STRING_HASH_KEY)
{
#if __cplusplus >= 201402L
    while(*pTail != STRING_END_BYTE)
    {
        hash = (hash << STRING_BIT_SHIT) + hash + (int32_t)*pTail;
        pTail++;
    }
    return hash;
#elif __cplusplus >= 201103L
    return (pTail[0] == STRING_END_BYTE) ? hash :
           hash_function(pTail + 1, ((hash << STRING_BIT_SHIT) + hash) + (int32_t)*pTail);
#endif
}

/// \brief  Binds the constexpr tail recursive function to a template parameter
///         to force the compiler to hash the string compile time
/// \tparam the hash as a template parameter
/// \return see hash_function
template <uint32_t hash>
inline constexpr uint32_t compile_time_hash()
{
    return hash;
}

} // !namespace

/// \example DSID
///
/// DSID is the dymanic or run-time version of SSID
/// It takes in parameter a const char *
/// Example : U32 goID_1 = DSID(go.c_str());
///           U32 goID_2 = DSID("BossDoor");
///           U32 goID_3 = DSID(szP)
#define DSID(string) impl::hash_function(string)

/// \example SSID
///
/// To pre-hash all strings and get back a 32 bits unsigned int
/// at compile time, you have to call the SSID macro.
/// It takes in parameter a literal const char *
/// Example : uint32_t identifier = SSID("MyLiteralIdentifier");
#define SSID(string) impl::compile_time_hash<impl::hash_function(string)>()

#endif // !ARTICLES_STRING_IDENTIFIER_HPP__