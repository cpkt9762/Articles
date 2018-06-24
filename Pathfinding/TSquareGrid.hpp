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

/// \file       TSquareGrid.hpp
/// \date       17/10/2017
/// \project    Pathfinding
/// \author     Vincent STEHLY--CALISTO

#ifndef PATHFINDING_T_SQUARE_GRID_HPP
#define PATHFINDING_T_SQUARE_GRID_HPP

#include <vector>
#include <algorithm>

#include "TNode.hpp"

/// \namespace nav
namespace nav
{

/// \class  TSquareGrid
/// \brief  Stores a 2D square grid
/// \tparam CoordinateType The type of the coordinate system
/// \tparam PriorityType   The type of the priority
template <typename CoordinateType, typename PriorityType>
class TSquareGrid
{
public:

    using TTNode = TNode<CoordinateType, PriorityType>;

    /// \brief  Initializes a grid width x height
    /// \param  width The width of the grid
    /// \param  height The height of the grid
    void Initialize(CoordinateType width, CoordinateType height);

    /// \brief  Puts into the current node neighbors all direct neighbors
    /// \param  current The node to check
    /// \param  neighbors The vector of neighbors
    inline void GetNeighbors(const TTNode& current, std::vector < TTNode >& neighbors) const;

    /// \brief  Returns a read only reference on a node
    /// \param  x The X coordinate of the node
    /// \param  y The Y coordinate of the node
    /// \return A reference on a node
    inline const TTNode & GetNode (CoordinateType x, CoordinateType y) const;

    /// \brief  Sets the neighbors of a node
    /// \param  x The X coordinate of the node
    /// \param  y The Y coordinate of the node
    /// \param  flag The flag to apply
    inline void SetNodeNeighbors(CoordinateType x, CoordinateType y, unsigned char flag);

    /// \brief  Tells if the node is valid or node
    /// \param  x The X coordinate of the node
    /// \param  y The Y coordinate of the node
    /// \return True or false
    inline bool IsValidNode(CoordinateType x, CoordinateType y) const;

private:

    CoordinateType m_width;  ///< The width of the grid
    CoordinateType m_height; ///< The height of the grid

    std::vector < TTNode >  m_grid; ///< The 2D grid
};

} // !namespace

#include "TSquareGrid.inl"

#endif // PATHFINDING_T_SQUARE_GRID_HPP