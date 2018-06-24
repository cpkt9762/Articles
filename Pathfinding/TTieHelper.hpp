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

/// \file       TTieHelper.hpp
/// \date       17/10/2017
/// \project    Pathfinding
/// \author     Vincent STEHLY--CALISTO

#ifndef PATHFINDING_T_TIE_HELPER_HPP
#define PATHFINDING_T_TIE_HELPER_HPP

/// \namespace nav
namespace nav
{

/// \brief  Deduces the type of the coordinates pack
/// \tparam CoordinateType The type of the coordinates
///         must be char, short or int
template<typename CoordinateType>
struct TTieTypeHelper
{
    // Should generate an error
};

template</* Specialized for type char */>
struct TTieTypeHelper<char>
{
    typedef short TieType;
    static constexpr unsigned char TypeShift = 8;
};

template</* Specialized for type short */>
struct TTieTypeHelper<short>
{
    typedef int TieType;
    static constexpr unsigned char TypeShift = 16;
};

template</* Specialized for type int */>
struct TTieTypeHelper<int>
{
    typedef long long TieType;
    static constexpr unsigned char TypeShift = 32;
};

} // !namespace

#endif // PATHFINDING_T_TIE_HELPER_HPP