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

/// \file       Main.hpp
/// \date       18/10/2017
/// \project    Pathfinding
/// \author     Vincent STEHLY--CALISTO

#include <iostream>
#include "TSquareGrid.hpp"
#include "TPathfinding.hpp"

// Alias to make the code more readable
using CoordinateType = char;
using PriorityType   = short;
using TTNode         = nav::TNode       <CoordinateType, PriorityType>;
using TTSquareGrid   = nav::TSquareGrid <CoordinateType, PriorityType>;

const CoordinateType width  = 10;
const CoordinateType height = 10;

int main(int arc, char ** argv)
{
    TTSquareGrid square_grid;  ///< Will store our nodes
    std::vector <TTNode> path; ///< Will contains the result path

    square_grid.Initialize(width, height);

    // Connects all nodes to their direct neighbors
    for(CoordinateType x = 0; x < width; ++x)
    {
        for(CoordinateType y = 0; y < height; ++y)
        {
            square_grid.SetNodeNeighbors(x, y, TTNode::EFlag::ALL);
        }
    }

    // Removes some nodes from the graph
    for (CoordinateType y = 0; y < height / 2; y++)
    {
        square_grid.SetNodeNeighbors(width / 2, y, TTNode::EFlag::NONE);
    }

    // Tries to get a path from 0, 0 to width - 1, height - 1
    bool has_path = nav::TPathfinding<TTSquareGrid, CoordinateType, PriorityType>::GetPath(
            square_grid, path,
            square_grid.GetNode(0, 0),
            square_grid.GetNode(width - 1, height - 1));

    if (has_path)
    {
        // A path has been found
        for(const TTNode& node : path)
            std::cout << "Node[" << (int)node.X() << ", " << (int)node.Y() << "]" << std::endl;
    }
    else
    {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}