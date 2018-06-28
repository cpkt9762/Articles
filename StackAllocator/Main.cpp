/// Copyright (C) 2018-2019
/// Vincent STEHLY--CALISTO, vincentstehly@hotmail.fr
/// See https://vincentcalisto.com/
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

/// \file    Main.cpp
/// \date    28/06/2018
/// \project Articles
/// \author  Vincent STEHLY--CALISTO

#include "CStackAllocator.hpp"

int main()
{
    // Creates the allocator and initializes the stack size to 1024 bytes
    CFrameAllocator frame_allocator;
    frame_allocator.Initialize(1024);

    // Frame begin
    // Allocating 512 raw bytes
    void* p_data = frame_allocator.Allocate(512);

    // Frame end
    // Clearing the stack
    // All memory is available again
    frame_allocator.Clear();

    // Releasing manually the memory
    frame_allocator.Release();

    return 0;
}