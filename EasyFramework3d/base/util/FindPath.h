/**
 * @file FindPath.h
 * @author sizilium
 * @date 04.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef FINDPATH_H
#define FINDPATH_H

// includes
#include <vs/Build.hpp>
#include <vs/base/cont/Matrix.hpp>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <assert.h>

namespace vs
{
namespace base
{
namespace util
{
using namespace std;

/**
 * Find path function implemented with the dijkstra algorithm.\n
 * The function find the shortest path between two points. 
 * It requires a 2d adjacency matrix and way informations.
 * The graph (wich represented by the matrix) can be directed or undirected.
 * 
 * @param matrix first pass the adjacency matrix (as refrence for more
 * performanse)
 * @param startPoint Row of the given matrix (start node)
 * @param endPoint Column of the given matrix (target node)
 * @param waypoints This return value (as reference) returns the finding
 * in a std::stack<int>. Element on top represents the first waypoint have
 * to go etc. Last element in stack is equal the endPoint (target node).
 * @return Complete lengths from startPoint to endPoint. -1 when there is no
 * possible way between the points!
 * @see ma::Matrix
 */
VS_EXPORT int findShortestPath(const cont::Matrix<int> &matrix,
                               int startPoint, int endPoint, stack<int> &waypoints);

} // util
} // base
} // vs

#endif
