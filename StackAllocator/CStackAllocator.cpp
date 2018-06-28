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

/// \file    CStackAllocator.cpp
/// \date    27/06/2018
/// \project Articles
/// \author  Vincent STEHLY--CALISTO

#include "CStackAllocator.hpp"

/// \brief Destructor
CStackAllocator::~CStackAllocator()
{
    Release(); // RAII idiom
}

/// \brief  Initializes the allocator by allocating size bytes
/// \param  size The amount of memory (in bytes) to allocate
void CStackAllocator::Initialize(std::size_t size)
{
    // Exceptions can be replaced by assertions
    // The max size be a parameter or a constant etc.
    if(size == 0 || size >= 1024 * 1024 * 64)
    {
        throw std::bad_alloc();
    }

    // Avoid memory leak
    Release();

    m_head  = 0;
    m_size  = size;
    mp_data = new uint8_t[m_size];

    if(!mp_data)
    {
        throw std::bad_alloc();
    }
}

/// \brief Releases the allocator memory
void CStackAllocator::Release()
{
    delete[] mp_data;

    m_head  = 0;
    m_size  = 0;
    mp_data = nullptr;
}

/// \brief  Resets the head
void CStackAllocator::Clear()
{
    m_head = 0;
}

/// \brief  Allocates size bytes at the top of the stack
///         and returns a pointer on the allocated memory
///         Moves the head of the stack to m_head + size
/// \param  size The amount of bytes to allocate
/// \return A pointer on the allocated memory
void* CStackAllocator::Allocate(std::size_t size)
{
    if(m_head + size >= m_size || !mp_data || size == 0)
    {
        throw std::bad_alloc();
    }

    void* pointer = mp_data + m_head;
    m_head += size;

    return pointer;
}

/// \brief  Returns the amount of allocated memory of the allocator
/// \return The amount of allocated memory in bytes
std::size_t CStackAllocator::GetSize() const
{
    return m_size;
}

/// \brief  Returns the head of the stack as an offset in bytes
/// \return The head of the stack
std::size_t CStackAllocator::GetHead() const
{
    return m_head;
}

/// \brief  Returns a read only pointer on the data
/// \return A read only pointer on the data
const uint8_t* CStackAllocator::GetData() const
{
    return mp_data;
}
