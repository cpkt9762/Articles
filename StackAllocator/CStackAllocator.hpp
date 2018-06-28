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

/// \file    CStackAllocator.hpp
/// \date    27/06/2018
/// \project Articles
/// \author  Vincent STEHLY--CALISTO

#ifndef ARTICLES_C_STACK_ALLOCATOR_HPP__
#define ARTICLES_C_STACK_ALLOCATOR_HPP__

#include <cstddef>   ///< std::size_t
#include <cstdint>   ///< uint8_t
#include <stdexcept> ///< std::bad_alloc

/// \class StackAllocator
/// \brief Simple stack allocator
class CStackAllocator
{
public:

    /// \brief Default constructor
    CStackAllocator() = default;

    /// \brief Destructor
    ~CStackAllocator();

    /// \brief  Initializes the allocator by allocating size bytes
    /// \param  size The amount of memory (in bytes) to allocate
    void Initialize(std::size_t size);

    /// \brief Releases the allocator memory
    void Release();

    /// \brief  Resets the head
    void Clear();

    /// \brief  Allocates size bytes at the top of the stack
    ///         and returns a pointer on the allocated memory
    ///         Moves the head of the stack to m_head + size
    /// \param  size The amount of bytes to allocate
    /// \return A pointer on the allocated memory
    void * Allocate(std::size_t size);

    /// \brief  Returns the amount of allocated memory of the allocator
    /// \return The amount of allocated memory in bytes
    std::size_t GetSize() const;

    /// \brief  Returns the head of the stack as an offset in bytes
    /// \return The head of the stack
    std::size_t GetHead() const;

    /// \brief  Returns a read only pointer on the data
    /// \return A read only pointer on the data
    const uint8_t * GetData() const;

private:

    std::size_t  m_size  = 0;       ///< The size in bytes of the allocator
    std::size_t  m_head  = 0;       ///< The current position in the stack
    uint8_t *    mp_data = nullptr; ///< The memory buffer
};

using CFrameAllocator = CStackAllocator; ///< This is also a frame allocator

#endif // !ARTICLES_C_STACK_ALLOCATOR_HPP__