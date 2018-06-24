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

/// \file       TPathfinding.hpp
/// \date       18/10/2017
/// \project    Pathfinding
/// \author     Vincent STEHLY--CALISTO

#ifndef PATHFINDING_T_PATHFINDING_HPP
#define PATHFINDING_T_PATHFINDING_HPP

#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "TNode.hpp"

/// \namespace nav
namespace nav
{

/// \brief Computes the manhattan distance between two nodes
template<typename CoordinateType, typename PriorityType>
/* inline */ PriorityType Heuristic(const TNode<CoordinateType, PriorityType> &lhs,
                                    const TNode<CoordinateType, PriorityType> &rhs)
{
    return abs(lhs.X() - rhs.X()) + abs(lhs.Y() - rhs.Y());
}

/// \class  TPathfinding
/// \brief  Helper class to compute the shortest path between two points
/// \tparam Graph The graph class
/// \tparam CoordinateType The type of coordinates
/// \tparam PriorityType The type of the priority
template<typename Graph, typename CoordinateType, typename PriorityType>
class TPathfinding
{
public:

    using TTNode        =  TNode        <CoordinateType, PriorityType>;
    using TTNodeHash    =  TNodeHash    <CoordinateType, PriorityType>;
    using TTNodeCompare =  TNodeCompare <CoordinateType, PriorityType>;

    /// \brief  Finds one of the shortest path between start and end node.
    /// \param  graph The graph to perform the search on
    /// \param  path The vector to store the result (in reverse order)
    /// \param  start The start node
    /// \param  end The end node
    /// \return true if a path is found
    static bool GetPath(Graph& graph, std::vector<TTNode>& path, const TTNode& start, const TTNode& end)
    {
        // Tells if there is a path between start and end
        bool  has_path = false;

        std::vector         <TTNode> neighbors;
        std::priority_queue <TTNode> frontier;
        std::unordered_map  <TTNode, TTNode,        TTNodeHash, TTNodeCompare> came_from;
        std::unordered_map  <TTNode, PriorityType,  TTNodeHash, TTNodeCompare> cost_so_far;

        frontier.emplace   (TTNode(start));
        cost_so_far.emplace(TTNode(start), 0);
        came_from.emplace  (TTNode(start), start);

        while (!frontier.empty())
        {
            TTNode current(frontier.top());
            frontier.pop();

            // Early exit, the pathfinding has found
            // the exit for the first time
            if (current == end)
            {
                has_path = true;
                break;
            }

            neighbors.clear();
            graph.GetNeighbors(current, neighbors);

            for (TTNode& next : neighbors)
            {
                int new_cost = cost_so_far[current];

                if (!cost_so_far.count(next) || new_cost < cost_so_far[next])
                {
                    cost_so_far[next] = new_cost;
                    PriorityType priority = new_cost + Heuristic<CoordinateType, PriorityType>(next, end);

                    next.SetPriority(priority);
                    frontier.push(next);

                    came_from[next] = current;
                }
            }
        }

        if(has_path)
        {
            TTNode current = end;
            path.push_back(end);
            while (current != start)
            {
                current = came_from[current];
                path.push_back(current);
            }
        }

        return has_path;
    }
};

} // !namespace

#endif // PATHFINDING_T_PATHFINDING_HPP