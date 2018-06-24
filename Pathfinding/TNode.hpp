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

/// \file       TNode.hpp
/// \date       17/10/2017
/// \project    Pathfinding
/// \author     Vincent STEHLY--CALISTO

#ifndef PATHFINDING_T_NODE_HPP
#define PATHFINDING_T_NODE_HPP

#include <memory>  ///< std::hash<T>
#include <cstdlib> ///< std::size_t

#include "TTieHelper.hpp"

/// \namespace nav
namespace nav
{

/// \class  TNode
/// \brief  Stores the node data
/// \tparam CoordinateType The type of the coordinates
/// \tparam PriorityType   The type of the priority
template <typename CoordinateType, typename PriorityType>
class TNode
{
public:

    /// \brief  Typed enum to represent in native language
    ///         all flags to test neighbor directions
    ///
    /// \enum EFlag
    enum EFlag : unsigned char
    {
        NONE  = 0x0,        ///< 0b00000000
        NORTH = 0x1 << 3,   ///< 0b00001000
        EAST  = 0x1 << 2,   ///< 0b00000100
        SOUTH = 0x1 << 1,   ///< 0b00000010
        WEST  = 0x1 << 0,   ///< 0b00000001
        ALL   = 0xF         ///< 0b00001111
    };

    using TTNode = TNode<CoordinateType, PriorityType>;

    /// \brief  Default constructor
    explicit /* inline */ TNode() : xy(0), m_priority(0), m_neighbors(TNode::EFlag ::NONE)
    { /* None */ }

    /// \brief  Constructs a node from 2 coordinates
    /// \param  X The x coordinate
    /// \param  Y The y coordinate
    explicit /* inline */ TNode(CoordinateType X, CoordinateType Y) : x(X), y(Y), m_priority(0), m_neighbors(TNode::EFlag::NONE)
    { /* None */ }

    /// \brief  Constructs a node from the packed coordinates
    /// \param  XY The xy coordinate
    explicit /* inline */ TNode(typename TTieTypeHelper<CoordinateType>::TieType XY) : xy(XY), m_priority(0), m_neighbors(TNode::EFlag::NONE)
    { /* None */ }

    /// \brief  Copy Constructor
    /// \param  other The node to copy
    /* inline */ TNode(const TNode& other) : xy(other.xy), m_priority(other.m_priority), m_neighbors(other.m_neighbors)
    { /* None */ }

    /// \brief  Default destructor
    /* inline */ ~TNode() = default;

    /// \brief   Returns the X coordinate of the node
    /// \return  The X coordinate
    /* inline */ CoordinateType X() const
    { return x; }

    /// \brief   Returns the Y coordinate of the node
    /// \return  The Y coordinate
    /* inline */ CoordinateType Y() const
    { return y; }

    /// \brief   Returns the XY coordinate of the node
    /// \return  The XY coordinate
    /* inline */ typename TTieTypeHelper<CoordinateType>::TieType XY() const
    { return xy; }

    /// \brief  Sets the X coordinate
    /// \param  X The X coordinate
    /* inline */ void X(CoordinateType X)
    { x = X; }

    /// \brief  Sets the Y coordinate
    /// \param  Y The Y coordinate
    /* inline */ void Y(CoordinateType Y)
    { y = Y; }

    /// \brief  Sets the XY coordinate
    /// \param  XY The XY coordinate
    /* inline */ void XY(typename TTieTypeHelper<CoordinateType>::TieType XY)
    { xy = XY; }

    /// \brief  Tells if the given node is equal of the current node
    /// \return Returns true or false
    /* inline */ bool operator==(const TTNode & other) const
    { return xy == other.xy; }

    /// \brief  Tells if the given node is different of the current node
    /// \return True or false
    /* inline */ bool operator!=(const TTNode & other) const
    { return xy != other.xy; }

    /// \brief  Sets the priority of the node
    /// \param  cost The new priority
    /* inline */ void SetPriority(PriorityType priority)
    { m_priority = priority; }

    /// \brief  Returns the priority of the node
    /// \return The priority of the node
    /* inline */ PriorityType GetPriority() const
    { return m_priority; }

    /// \brief  Overload of operator < for priority queue
    ///         Note : This operator makes sense only for queue
    /// \return True or false
    /* inline */ bool operator<(const TTNode & other) const
    { return m_priority > other.m_priority; }

    /// \brief  Adds a neighbor to the current node
    /// \param  neighborMask The flags corresponding to the neighbors to add
    /* inline */ void AddNeighborFlags(EFlag neighborFlags)
    { m_neighbors |= neighborFlags; }

    /// \brief  Sets the neighbors from flags
    /// \param  neighborFlags The flags corresponding to neighbors
    /* inline */ void SetNeighborFlag(unsigned char neighborFlags)
    { m_neighbors = neighborFlags; }

    /// \brief  Returns the neighbor flags
    /// \return The neighbors flags
    /* inline */ unsigned char GetNeighborFlags() const
    { return m_neighbors; }

private:

    /// \brief  Coordinates aren't store in a Coordinate class anymore
    ///         to avoid automatic constructor calls
    union
    {
        struct
        {
            CoordinateType x;   ///< The X coordinate
            CoordinateType y;   ///< The Y coordinate
        };

        typename TTieTypeHelper<CoordinateType>::TieType xy; ///< The XY coordinate
    };

    PriorityType m_priority; ///< The priority of the node

    /// \brief  Stores the positions of all neighbors
    ///         of the current node in binary
    unsigned char m_neighbors;
};

/// \brief  Functor to hash a node
/// \tparam CoordinateType The type used in the coordinate system
/// \tparam CostType The type used for cost
template <typename CoordinateType, typename CostType>
struct TNodeHash
{
    /* inline */ std::size_t operator() (const TNode<CoordinateType, CostType>& current) const
    {
        return ((std::hash<CoordinateType>()(current.X()) ^
                (std::hash<CoordinateType>()(current.Y()) << 1)) >> 1);
    }
};

/// \brief  Functor to compare two nodes
/// \tparam CoordinateType The type used in the coordinate system
/// \tparam CostType The type used for cost
template <typename CoordinateType, typename CostType>
struct TNodeCompare
{
    /* inline */ bool operator() (const TNode<CoordinateType, CostType>& lhs,
                                  const TNode<CoordinateType, CostType>& rhs) const
    {
        return (lhs.XY() == rhs.XY());
    }
};

} // !namespace nav

#endif // PATHFINDING_T_NODE_HPP
