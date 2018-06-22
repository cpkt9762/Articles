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

/// \file       Main.cpp
/// \date       22/06/2018
/// \project    StringIdentifier
/// \author     Vincent STEHLY--CALISTO

#include "StringIdentifier.hpp"

int main()
{
	// Compile time hash
	uint32_t identifier_1 = SSID("MyIdentifier");

	// Runtime hash
	std::string foo("MyIdentifier"); 
	uint32_t identifier_2 = DSID(foo.c_str());
}