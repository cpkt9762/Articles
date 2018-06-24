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

/// \file       TSquareGrid.inl
/// \date       17/10/2017
/// \project    Pathfinding
/// \author     Vincent STEHLY--CALISTO

/// \namespace nav
namespace nav
{

/// \brief  Initializes a n x m grid
/// \param  width The width of the grid
/// \param  height The height of the grid
template <typename CoordinateType, typename PriorityType>
void TSquareGrid<CoordinateType, PriorityType>::Initialize(CoordinateType width, CoordinateType height)
{
    // Clear old grid
    m_grid.clear();

    m_width  = width;
    m_height = height;

    m_grid.reserve(m_width * m_height);
    for(CoordinateType nRow = 0; nRow < m_height; ++nRow)
    {
        for(CoordinateType nCol = 0; nCol < m_width; ++nCol)
        {
            m_grid.push_back(TTNode(nCol, nRow));
        }
    }
}

/// \brief  Puts into the current node neighbors all direct neighbors
/// \param  current The node to check
/// \param  neighbors The vector of neighbors
template <typename CoordinateType, typename PriorityType>
void TSquareGrid<CoordinateType, PriorityType>::GetNeighbors(const TTNode& current, std::vector < TTNode >& neighbors) const
{
    // Getting neighbors mask
    CoordinateType x = current.X();
    CoordinateType y = current.Y();
    unsigned char neighborFlags = current.GetNeighborFlags();

    for(unsigned char nShift = 0; nShift < 4; ++nShift)
    {
        unsigned char currentMask = static_cast<unsigned char>(1 << nShift);
        if(neighborFlags & currentMask)
        {
            // There is a neighbor in this direction
            switch(currentMask)
            {
                case TTNode::NORTH:
                    if(IsValidNode(x, y - 1) && (GetNode(x, y - 1).GetNeighborFlags() & TTNode::SOUTH))
                        neighbors.push_back(GetNode(x, y - 1));
                    break;

                case TTNode::EAST:
                    if(IsValidNode(x + 1, y) && (GetNode(x + 1, y).GetNeighborFlags() & TTNode::WEST))
                        neighbors.push_back(GetNode(x + 1, y    ));
                    break;

                case TTNode::SOUTH:
                    if(IsValidNode(x, y + 1) && (GetNode(x, y + 1).GetNeighborFlags() & TTNode::NORTH))
                        neighbors.push_back(GetNode(x, y + 1));
                    break;

                case TTNode::WEST:
                    if(IsValidNode(x - 1, y) && (GetNode(x - 1, y).GetNeighborFlags() & TTNode::EAST))
                        neighbors.push_back(GetNode(x - 1, y));
                    break;

                default: break;
            }
        }
    }

    // See with and without
    // Small optimization for squared grid
    if ((x + y) % 2 == 0)
    {
        std::reverse(neighbors.begin(), neighbors.end());
    }
}

/// \brief  Returns a read only reference on a node
/// \param  x The X coordinate of the node
/// \param  y The Y coordinate of the node
/// \return A read only reference on the wanted node
template <typename CoordinateType, typename PriorityType>
inline const TNode<CoordinateType, PriorityType>& TSquareGrid<CoordinateType, PriorityType>::GetNode(CoordinateType x, CoordinateType y) const
{
    return m_grid[y * m_width + x];
};

/// \brief  Sets the neighbors of a node
/// \param  x The X coordinate of the node
/// \param  y The Y coordinate of the node
/// \param  flag The flag to apply
template <typename CoordinateType, typename PriorityType>
inline void TSquareGrid<CoordinateType, PriorityType>::SetNodeNeighbors(CoordinateType x, CoordinateType y, unsigned char flag)
{
    m_grid[y * m_width + x].SetNeighborFlag(flag);
}

/// \brief  Tells if the node is valid or node
/// \param  x The X coordinate of the node
/// \param  y The Y coordinate of the node
/// \return True or false
template <typename CoordinateType, typename PriorityType>
inline bool TSquareGrid<CoordinateType, PriorityType>::IsValidNode(CoordinateType x, CoordinateType y) const
{
    return (x >= 0 && x < m_width && y >= 0 && y < m_height);
}

}