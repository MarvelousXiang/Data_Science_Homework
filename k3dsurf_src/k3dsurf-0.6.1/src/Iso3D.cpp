/***************************************************************************
 *   Copyright (C) 2006 by Abderrahman Taha                                *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

#include "Iso3D.h"

using std::vector;
using std::list;
   static Voxel GridVoxel[60][60][60];
static int triTable[256][16] = {

 {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1},
 {3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1},
 {3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1},
 {3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1},
 {9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1},
 {1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1},
 {9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
 {2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1},
 {8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1},
	{9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
	{4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1},
	{3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1},
	{1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1},
	{4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1},
	{4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1},
	{9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
	{5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1},
	{2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1},
	{9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
	{0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
	{2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1},
	{10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1},
	{4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1},
	{5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1},
	{5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1},
	{9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1},
	{0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1},
	{1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1},
	{10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1},
	{8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1},
	{2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
	{7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1},
	{9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1},
	{2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1},
	{11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1},
	{9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1},
	{5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1},
	{11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1},
	{11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
	{1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1},
	{9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1},
	{5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1},
	{2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
	{0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
	{5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1},
	{6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1},
	{3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1},
	{6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1},
	{5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1},
	{1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
	{10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1},
	{6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1},
	{8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1},
	{7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1},
	{3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
	{5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1},
	{0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1},
	{9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1},
	{8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1},
	{5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1},
	{0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1},
	{6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1},
	{10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1},
	{10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1},
	{8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1},
	{1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1},
	{3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1},
	{0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1},
	{10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1},
	{3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1},
	{6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1},
	{9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1},
	{8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1},
	{3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1},
	{6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1},
	{0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1},
	{10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1},
	{10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1},
	{2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1},
	{7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1},
	{7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1},
	{2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1},
	{1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1},
	{11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1},
	{8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1},
	{0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1},
	{7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
	{10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
	{2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
	{6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1},
	{7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1},
	{2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1},
	{1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1},
	{10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1},
	{10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1},
	{0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1},
	{7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1},
	{6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},
	{8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1},
	{9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1},
	{6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1},
	{4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1},
	{10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1},
	{8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1},
	{0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1},
	{1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},
	{8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1},
	{10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1},
	{4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1},
	{10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
	{5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
	{11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1},
	{9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
	{6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1},
	{7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1},
	{3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1},
	{7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1},
	{9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1},
	{3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1},
	{6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1},
	{9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1},
	{1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1},
	{4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1},
	{7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1},
	{6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1},
	{3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1},
	{0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1},
	{6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1},
	{0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1},
	{11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1},
	{6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1},
	{5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1},
	{9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1},
	{1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1},
	{1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1},
	{10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1},
	{0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1},
	{5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1},
	{10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1},
	{11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1},
	{9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1},
	{7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1},
	{2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1},
	{8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1},
	{9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1},
	{9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1},
	{1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1},
	{9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1},
	{9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1},
	{5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1},
	{0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1},
	{10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1},
	{2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1},
	{0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1},
	{0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1},
	{9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1},
	{5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1},
	{3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1},
	{5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1},
	{8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1},
	{0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1},
	{9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1},
	{1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1},
	{3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1},
	{4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1},
	{9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1},
	{11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1},
	{11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1},
	{2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1},
	{9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1},
	{3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1},
	{1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1},
	{4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1},
	{4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1},
	{0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1},
	{3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1},
	{3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1},
	{0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1},
	{9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1},
	{1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};


///+++++++++++++++++++++++++++++++++++++++++
void Iso3D::scalex(int coeff) {
 newscalex = (double)coeff/(double)10; ///(double)(oldcoeff);
 QString after;

 after = "(x/"+QString::number(newscalex)+")";
/// Generate the new Implicit expression...
 if(newscalex != 1) {
ImplicitFunction = ImplicitFunction_save;


ImplicitFunction.replace(QChar('x'), after);

XlimitSup = XlimitSup_save+"*"+QString::number(newscalex);
XlimitInf = XlimitInf_save+"*"+QString::number(newscalex);

YlimitSup = YlimitSup_save;
YlimitInf = YlimitInf_save;
ZlimitSup = ZlimitSup_save;
ZlimitInf = ZlimitInf_save;


}
/// Process the new IsoSurface...
 ComputeIsoMap();
}

///+++++++++++++++++++++++++++++++++++++++++
void Iso3D::scaley(int coeff) {
 newscaley = (double)coeff/(double)10; ///(double)(oldcoeff);
 QString after;

 after = "(y/"+QString::number(newscaley)+")";
/// Generate the new Implicit expression...
 if(newscaley != 1) {
ImplicitFunction = ImplicitFunction_save;
ImplicitFunction.replace(QChar('y'), after);

YlimitSup = YlimitSup_save+"*"+QString::number(newscaley);
YlimitInf = YlimitInf_save+"*"+QString::number(newscaley);

XlimitSup = XlimitSup_save;
XlimitInf = XlimitInf_save;
ZlimitSup = ZlimitSup_save;
ZlimitInf = ZlimitInf_save;
}
/// Process the new IsoSurface...
 ComputeIsoMap();
}

///+++++++++++++++++++++++++++++++++++++++++
void Iso3D::scalez(int coeff) {
 newscalez = (double)coeff/(double)10; ///(double)(oldcoeff);
 QString after;

 after = "(z/"+QString::number(newscalez)+")";
/// Generate the new Implicit expression...
 if(newscalez != 1) {
ImplicitFunction = ImplicitFunction_save;
ImplicitFunction.replace(QChar('z'), after);

ZlimitSup = ZlimitSup_save+"*"+QString::number(newscalez);
ZlimitInf = ZlimitInf_save+"*"+QString::number(newscalez);

YlimitSup = YlimitSup_save;
YlimitInf = YlimitInf_save;
XlimitSup = XlimitSup_save;
XlimitInf = XlimitInf_save;
}
/// Process the new IsoSurface...
 ComputeIsoMap();
}

///+++++++++++++++++++++++++++++++++++++++++
  void Iso3D::twistex(double newtwistex, double newscalex){

 double vals[2]={0,0};
 QString after_1, after_2, angle;
 double tmp;



 if(newtwistex != 0  ||  newscalex !=1) {
angle = "1/("+XlimitSup+"-"+XlimitInf+")";
/// WE EVALUATE THIS PART TO OPTIMASE THE FINAL EQUATION...
ExpressionEvaluator.Parse(angle, "t");
tmp = ExpressionEvaluator.Eval(vals);

tmp *= newtwistex*2*3.14159265/newscalex;
angle = QString::number(tmp)+"*x";

after_1 = "(y*cos("+angle+") - z*sin("+angle+"))";
after_2 = "(y*sin("+angle+") + z*cos("+angle+"))";

ImplicitFunction = ImplicitFunction_save;

ImplicitFunction.replace(QChar('y'), "u");
ImplicitFunction.replace(QChar('z'), "v");


ImplicitFunction.replace(QChar('u'), after_1);
ImplicitFunction.replace(QChar('v'), after_2);
/*
/// We calculate the new cube that contain the distorted object:
///Y :
angle = YlimitSup+"-"+YlimitInf;
ExpressionEvaluator.Parse(angle, "t");
tmp = ExpressionEvaluator.Eval(vals);
tmpy = tmp/2;

///Z:

angle = ZlimitSup+"-"+ZlimitInf;
ExpressionEvaluator.Parse(angle, "t");
tmp = ExpressionEvaluator.Eval(vals);
tmpz = tmp/2;

rayon = sqrt (tmpy*tmpy + tmpz*tmpz);
*/


}
ComputeIsoMap();
}



///+++++++++++++++++++++++++++++++++++++++++
  void Iso3D::twistey(double newtwistey, double newscaley){
 QString after_1, after_2, angle;
 double tmp;
 double vals[1]={0};

 if(newtwistey != 0) {
angle = "1/("+YlimitSup+"-"+YlimitInf+")";
/// WE EVALUATE THIS PART TO OPTIMASE THE FINAL EQUATION...
ExpressionEvaluator.Parse(angle, "t");
tmp = ExpressionEvaluator.Eval(vals);

angle = QString::number(newtwistey*tmp*2*3.14159265/newscaley)+"*y";
after_1 = "(x*cos("+angle+") - z*sin("+angle+"))";
after_2 = "(x*sin("+angle+") + z*cos("+angle+"))";

ImplicitFunction = ImplicitFunction_save;

ImplicitFunction.replace(QChar('x'), "u");
ImplicitFunction.replace(QChar('z'), "v");
ImplicitFunction.replace(QChar('u'), after_1);
ImplicitFunction.replace(QChar('v'), after_2);

YlimitSup = YlimitSup_save+"*"+QString::number(newscaley);
YlimitInf = YlimitInf_save+"*"+QString::number(newscaley);
}
ComputeIsoMap();
};

///+++++++++++++++++++++++++++++++++++++++++
  void Iso3D::twistez(double newtwistez, double newscalez){
 QString after_1, after_2, angle;
 double tmp;
 double vals[1]={0};

 if(newtwistez != 0) {
angle = "1/("+ZlimitSup+"-"+ZlimitInf+")";
/// WE EVALUATE THIS PART TO OPTIMASE THE FINAL EQUATION...
ExpressionEvaluator.Parse(angle, "t");
tmp = ExpressionEvaluator.Eval(vals);
angle = QString::number(newtwistez*tmp*2*3.14159265/newscalez)+"*z";

after_1 = "(x*cos("+angle+") - y*sin("+angle+"))";
after_2 = "(x*sin("+angle+") + y*cos("+angle+"))";

ImplicitFunction = ImplicitFunction_save;
ImplicitFunction.replace(QChar('x'), "u");
ImplicitFunction.replace(QChar('y'), "v");
ImplicitFunction.replace(QChar('u'), after_1);
ImplicitFunction.replace(QChar('v'), after_2);

ZlimitSup = ZlimitSup_save+"*"+QString::number(newscalez);
ZlimitInf = ZlimitInf_save+"*"+QString::number(newscalez);

}
ComputeIsoMap();
};

///+++++++++++++++++++++++++++++++++++++++++
 void Iso3D::PaletteInit(){

 double  coef;
 for(i=0; i<256; i++) {
 coef = (double)i/256;

 palette_front_face[i] = QBrush(QColor((int)((double)(frontsurfr)*coef), (int)((double)(frontsurfg)*coef), (int)((double)(frontsurfb)*coef)));


  palette_back_face[i] = QBrush(QColor((int)((double)(backsurfr)*coef), (int)((double)(backsurfg)*coef),(int)((double)(backsurfb)*coef)));

  palette_CND[i] = QBrush(QColor((int)((double)(CNDsurfr)*coef), (int)((double)(CNDsurfg)*coef),(int)((double)(CNDsurfb)*coef)));

 palette_grid[i] = QColor((int)((double)(gridr)*coef), (int)((double)(gridg)*coef),(int)((double)(gridb)*coef));


 if(fronttrans == 1)  palette_front_face[i].setStyle(Qt::HorPattern);
 if(backtrans  == 1)  palette_back_face[i].setStyle(Qt::HorPattern);
 if(CNDtrans   == 1)  palette_CND[i].setStyle(Qt::HorPattern);
 }

///+++++++++++++++++++++++++++++++++++++++++
 }
   Iso3D::Iso3D(){
       Oprime[0]=(double)0.0;
       Oprime[1]=(double)0.0;
       Oprime[2]=(double)800.0;
       D=460;

       MatGen.unit();
       MatRot.unit();
       MatRotSave.unit();

       NbPointIsoMap = 0;
       NbTriangleIsoSurface = 0;

       morph_param = 1;
       step = 0.05;

       //ImplicitFunction ="1-((1/2)^2*(x^2 + y^2 + z^2) )-6- ((1/2)^8 *((x^8 + y^8 + z^8) )^6)" ;
       //ImplicitFunction ="x^4 - x^3 + y^2 + z^2";
       //ImplicitFunction ="x^4 + y^4 + z^4 -1";
       //ImplicitFunction ="x*x + y*y + z*z - 1";
       ImplicitFunction = ImplicitFunction_save = "cos(x) + cos(y) + cos(z)";
       IsoCondition = "(x^2 + y^2 > 0.05) & ( x+y+z > -1)";
       IsoConditionRequired  = -1;
       //ImplicitFunction ="cos(x*y) - z^2";
       //ImplicitFunction ="cos(x)*sin(y) - z";
       //ImplicitFunction ="4*x*exp(-x^2-y^2) -z";

XlimitSup = XlimitSup_save = "4";
YlimitSup = YlimitSup_save = "4";
ZlimitSup = ZlimitSup_save = "4";
XlimitInf = XlimitInf_save = "-4";
YlimitInf = YlimitInf_save = "-4";
ZlimitInf = ZlimitInf_save = "-4";

       X_Start = 4; X_End = -4;
       Y_Start = 4; Y_End = -4;
       Z_Start = 4; Z_End = -4;

       nb_ligne = nb_colon = nb_depth = 26;
       IsoValue = 0;

        backsurfr = 249;
        backsurfg = 170;
        backsurfb = 0;

        frontsurfr = 0;
        frontsurfg = 210;
        frontsurfb = 0;

        CNDsurfr = 210;
        CNDsurfg = 0;
        CNDsurfb = 0;

       fronttrans = backtrans = CNDtrans = -1;

       NbPolygonImposedLimit =99000;
       DrawAxe_Ok = -1;

       gridr = 0;
       gridg = 100;
       gridb = 4;
       gridtransparent = 1;
       IsoMesh = -1;
       IsoInfos = 1; /// To show infos
       Borderlimite = 0;

       CNDMesh = 1; CNDDraw = 1; BorderDraw = 1;

       axe_width  = 2;
       axe_size   = 1;
       axe_center = 1;

       PovActivate = -1; /// To save the shape for the output file
       hauteur_fenetre = 650;
       demi_hauteur = demi_largeur = hauteur_fenetre/2;

       ImplicitFunctionParser.AddConstant ("pi", 3.14159265);
       for (int i=0; i < 10000; i++)
           tableaureferences[i] = new QPointArray(3);

       tableau = new IsoTriangle[10000];

       InitParser();
       ParseExpression();
       PaletteInit();
/*
       VoxelEvaluation ();
       PointEdgeComputation();
       SignatureComputation();
       //BoxIsoMap();
       ConstructIsoSurface();
       ConstructIsoNormale(); BoxIsoMap();
       ApplicateTransform(); /// On applique la matrice principale
*/
   };

///+++++++++++++++++++++++++++++++++++++++++
  void Iso3D::ParseExpression() {
      double vals[] = {0, 0, 0, 0, 0, 0};
       ImplicitFunctionParser.Parse(ImplicitFunction, "x,y,z,t");

       IsoConditionParser.Parse(IsoCondition, "x,y,z,t");

       XSupParser.Parse(XlimitSup, "x,y,z,t");
       X_Start = XSupParser.Eval(vals);

       YSupParser.Parse(YlimitSup, "x,y,z,t");
       Y_Start = YSupParser.Eval(vals);

       ZSupParser.Parse(ZlimitSup, "x,y,z,t");
       Z_Start = ZSupParser.Eval(vals);

       XInfParser.Parse(XlimitInf, "x,y,z,t");
       X_End = XInfParser.Eval(vals);

       YInfParser.Parse(YlimitInf, "x,y,z,t");
       Y_End = YInfParser.Eval(vals);

       ZInfParser.Parse(ZlimitInf, "x,y,z,t");
       Z_End = ZInfParser.Eval(vals);
 };


///+++++++++++++++++++++++++++++++++++++++++
   void Iso3D::InitParser (){

       ImplicitFunctionParser.AddConstant("pi", 3.14159265);
       IsoConditionParser.AddConstant("pi", 3.14159265);
       XSupParser.AddConstant("pi", 3.14159265);
       YSupParser.AddConstant("pi", 3.14159265);
       ZSupParser.AddConstant("pi", 3.14159265);
       XInfParser.AddConstant("pi", 3.14159265);
       YInfParser.AddConstant("pi", 3.14159265);
       ZInfParser.AddConstant("pi", 3.14159265);
       ExpressionEvaluator.AddConstant("pi", 3.14159265);
   };

///+++++++++++++++++++++++++++++++++++++++++
  void Iso3D::ComputeIsoMap() {
       ParseExpression();
       VoxelEvaluation ();
       PointEdgeComputation();
       SignatureComputation();
       //BoxIsoMap();
       ConstructIsoSurface();
       ConstructIsoNormale();
       BoxIsoMap();
       ApplicateTransform(); /// On applique la matrice principale
}


///+++++++++++++++++++++++++++++++++++++++++
   void Iso3D::AnimMorph(){

       ///ParseExpression();
       VoxelEvaluation ();
       PointEdgeComputation();
       SignatureComputation();
       //BoxIsoMap();
       ConstructIsoSurface();
       ConstructIsoNormale();BoxIsoMap();
       Rotate();
       ApplicateTransform(); /// On applique la matrice principal


};
///++++++++++++++++++++++++++++++++++++++++
   void Iso3D::CutIsoSurface(){
       ConstructIsoSurface();
       ConstructIsoNormale();
       ApplicateTransform(); /// On applique la matrice principal
};
///+++++++++++++++++++++++++++++++++++++++++
   void Iso3D::ConstructIsoNormale(){
double val1, val2, val3, val4, val5, val6,
       pt1_x, pt1_y, pt1_z,
       pt2_x, pt2_y, pt2_z,
       pt3_x, pt3_y, pt3_z,
       scalar;
int ThreeTimesI, IndexFirstPoint, IndexSecondPoint, IndexThirdPoint;

for(i = 0; i<NbTriangleIsoSurface; ++i) {

 ThreeTimesI   = i*3;

IndexFirstPoint  = 3*IsoSurfaceTriangleListe[ThreeTimesI  ];
IndexSecondPoint = 3*IsoSurfaceTriangleListe[ThreeTimesI+1];
IndexThirdPoint  = 3*IsoSurfaceTriangleListe[ThreeTimesI+2];


 pt1_x= IsoPointMapOriginal[IndexFirstPoint  ];
 pt1_y= IsoPointMapOriginal[IndexFirstPoint+1];
 pt1_z= IsoPointMapOriginal[IndexFirstPoint+2];

 pt2_x= IsoPointMapOriginal[IndexSecondPoint  ];
 pt2_y= IsoPointMapOriginal[IndexSecondPoint+1];
 pt2_z= IsoPointMapOriginal[IndexSecondPoint+2];

 pt3_x= IsoPointMapOriginal[IndexThirdPoint  ];
 pt3_y= IsoPointMapOriginal[IndexThirdPoint+1];
 pt3_z= IsoPointMapOriginal[IndexThirdPoint+2];

val1 = pt2_y - pt1_y;
val2 = pt3_z - pt1_z;
val3 = pt2_z - pt1_z;
val4 = pt3_y - pt1_y;
val5 = pt3_x - pt1_x;
val6 = pt2_x - pt1_x;

NormOriginal[ThreeTimesI  ] = val1*val2 - val3*val4;
NormOriginal[ThreeTimesI+1] = val3*val5 - val6*val2;
NormOriginal[ThreeTimesI+2] = val6*val4 - val1*val5;

scalar = (double)sqrt((NormOriginal[ThreeTimesI  ]*NormOriginal[ThreeTimesI  ]) +
                      (NormOriginal[ThreeTimesI+1]*NormOriginal[ThreeTimesI+1]) +
                      (NormOriginal[ThreeTimesI+2]*NormOriginal[ThreeTimesI+2]));

if(scalar < 0.000000001)  scalar  = 0.000000001;
NormTransfrm[ThreeTimesI  ] = (NormOriginal[ThreeTimesI  ]/=scalar);
NormTransfrm[ThreeTimesI+1] = (NormOriginal[ThreeTimesI+1]/=scalar);
NormTransfrm[ThreeTimesI+2] = (NormOriginal[ThreeTimesI+2]/=scalar);
}

};

///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
   void Iso3D::BoxIsoMap(){
int ThreeTimesI;
//double stepx, stepy, stepz;

MINX = 999999999;
MINY = 999999999;
MINZ = 999999999;

MAXX =-999999999;
MAXY =-999999999;
MAXZ =-999999999;

 for (i=0; i < NbPointIsoMap   ; i++){
 ThreeTimesI = 3*i;
          if(MINX > IsoPointMapOriginal[ThreeTimesI  ] ) MINX = IsoPointMapOriginal[ThreeTimesI  ] ;

     else if(MINY > IsoPointMapOriginal[ThreeTimesI+1] ) MINY = IsoPointMapOriginal[ThreeTimesI+1] ;

     else if(MINZ > IsoPointMapOriginal[ThreeTimesI+2] ) MINZ = IsoPointMapOriginal[ThreeTimesI+2] ;

     else if(MAXX < IsoPointMapOriginal[ThreeTimesI  ] ) MAXX = IsoPointMapOriginal[ThreeTimesI  ] ;

     else if(MAXY < IsoPointMapOriginal[ThreeTimesI+1] ) MAXY = IsoPointMapOriginal[ThreeTimesI+1] ;

     else if(MAXZ < IsoPointMapOriginal[ThreeTimesI+2] ) MAXZ = IsoPointMapOriginal[ThreeTimesI+2] ;
                                  }


  DIFX = MAXX - MINX ;
  DIFY = MAXY - MINY ;
  DIFZ = MAXZ - MINZ ;

// Recherche du maximum :
  DIFMAXIMUM = DIFX;

  if (DIFY > DIFMAXIMUM) {DIFMAXIMUM = DIFY;};
  if (DIFZ > DIFMAXIMUM) {DIFMAXIMUM = DIFZ;};


/// On va inclure cet objet dans un cube de langueur maximum
/// egale a "hauteur_fenetre"

double decalage_xo = -(MINX +MAXX)/2 ;
double decalage_yo = -(MINY +MAXY)/2 ;
double decalage_zo = -(MINZ +MAXZ)/2 ;

 for (i=0; i < NbPointIsoMap ; i++) {
 ThreeTimesI = 3*i;
IsoPointMapOriginal[ThreeTimesI  ] = hauteur_fenetre*(IsoPointMapOriginal[ThreeTimesI  ] + decalage_xo)/DIFMAXIMUM ;

IsoPointMapOriginal[ThreeTimesI+1] = hauteur_fenetre*(IsoPointMapOriginal[ThreeTimesI+1] + decalage_yo)/DIFMAXIMUM ;

IsoPointMapOriginal[ThreeTimesI+2] = hauteur_fenetre*(IsoPointMapOriginal[ThreeTimesI+2] + decalage_zo)/DIFMAXIMUM ;

}

/// We generate the points af the 3D axes by using the limits of the Cube.
/// Axes are centered on the original point O(0,0,0):
if(DrawAxe_Ok == 1)
for(i = 0; i <42; i++) {
ThreeTimesI = 3*i;

AxeArrayOriginal[0][ThreeTimesI  ] = hauteur_fenetre*(AxeArrayOriginal[0][ThreeTimesI  ] + decalage_xo)/DIFMAXIMUM ;
AxeArrayOriginal[0][ThreeTimesI+1] = hauteur_fenetre*(AxeArrayOriginal[0][ThreeTimesI+1] + decalage_yo)/DIFMAXIMUM ;
AxeArrayOriginal[0][ThreeTimesI+2] = hauteur_fenetre*(AxeArrayOriginal[0][ThreeTimesI+2] + decalage_zo)/DIFMAXIMUM ;


AxeArrayOriginal[1][ThreeTimesI  ] = hauteur_fenetre*(AxeArrayOriginal[1][ThreeTimesI  ] + decalage_xo)/DIFMAXIMUM ;
AxeArrayOriginal[1][ThreeTimesI+1] = hauteur_fenetre*(AxeArrayOriginal[1][ThreeTimesI+1] + decalage_yo)/DIFMAXIMUM ;
AxeArrayOriginal[1][ThreeTimesI+2] = hauteur_fenetre*(AxeArrayOriginal[1][ThreeTimesI+2] + decalage_zo)/DIFMAXIMUM ;


AxeArrayOriginal[2][ThreeTimesI  ] = hauteur_fenetre*(AxeArrayOriginal[2][ThreeTimesI  ] + decalage_xo)/DIFMAXIMUM ;
AxeArrayOriginal[2][ThreeTimesI+1] = hauteur_fenetre*(AxeArrayOriginal[2][ThreeTimesI+1] + decalage_yo)/DIFMAXIMUM ;
AxeArrayOriginal[2][ThreeTimesI+2] = hauteur_fenetre*(AxeArrayOriginal[2][ThreeTimesI+2] + decalage_zo)/DIFMAXIMUM ;


}
 /// End of if(DrawAxe_Ok == 1)...


};
///++++++++++++++++++++ OutPut The IsoSurface +++++++++++++++++++++++

   void Iso3D::SaveIsoGLMap() {
     int IndexFirstPoint, IndexSecondPoint, IndexThirdPoint, ThreeTimesI;
     double scalar;



/// Put the object Inside a Cube :

MINX = 999999999;
MINY = 999999999;
MINZ = 999999999;

MAXX =-999999999;
MAXY =-999999999;
MAXZ =-999999999;

 for (i=0; i < NbPointIsoMap   ; i++){
 ThreeTimesI = 3*i;
          if(MINX > IsoPointMapOriginal[ThreeTimesI  ] ) MINX = IsoPointMapOriginal[ThreeTimesI  ] ;

     else if(MINY > IsoPointMapOriginal[ThreeTimesI+1] ) MINY = IsoPointMapOriginal[ThreeTimesI+1] ;

     else if(MINZ > IsoPointMapOriginal[ThreeTimesI+2] ) MINZ = IsoPointMapOriginal[ThreeTimesI+2] ;

     else if(MAXX < IsoPointMapOriginal[ThreeTimesI  ] ) MAXX = IsoPointMapOriginal[ThreeTimesI  ] ;

     else if(MAXY < IsoPointMapOriginal[ThreeTimesI+1] ) MAXY = IsoPointMapOriginal[ThreeTimesI+1] ;

     else if(MAXZ < IsoPointMapOriginal[ThreeTimesI+2] ) MAXZ = IsoPointMapOriginal[ThreeTimesI+2] ;
                                  }


  DIFX = MAXX - MINX ;
  DIFY = MAXY - MINY ;
  DIFZ = MAXZ - MINZ ;

// Recherche du maximum :
  DIFMAXIMUM = DIFX;

  if (DIFY > DIFMAXIMUM) {DIFMAXIMUM = DIFY;};
  if (DIFZ > DIFMAXIMUM) {DIFMAXIMUM = DIFZ;};


/// On va inclure cet objet dans un cube de langueur maximum
/// egale a "hauteur_fenetre"

double decalage_xo = -(MINX +MAXX)/2 ;
double decalage_yo = -(MINY +MAXY)/2 ;
double decalage_zo = -(MINZ +MAXZ)/2 ;

 for (i=0; i < NbPointIsoMap ; i++) {
 ThreeTimesI = 3*i;
IsoPointMapOriginal[ThreeTimesI  ] = hauteur_fenetre*(IsoPointMapOriginal[ThreeTimesI  ] + decalage_xo)/DIFMAXIMUM ;

IsoPointMapOriginal[ThreeTimesI+1] = hauteur_fenetre*(IsoPointMapOriginal[ThreeTimesI+1] + decalage_yo)/DIFMAXIMUM ;

IsoPointMapOriginal[ThreeTimesI+2] = hauteur_fenetre*(IsoPointMapOriginal[ThreeTimesI+2] + decalage_zo)/DIFMAXIMUM ;

}

/// Recalculate the normals so we have one for each Point (like for Pov Mesh) :
   for (i=0; i < NbPointIsoMap ; i++){
        ThreeTimesI = 3*i;
        IsoNormMapTransfrm[ThreeTimesI  ] = 0;
        IsoNormMapTransfrm[ThreeTimesI+1] = 0;
        IsoNormMapTransfrm[ThreeTimesI+2] = 0;
}

for(i = 0; i<NbTriangleIsoSurface; ++i) {
ThreeTimesI   = i*3;

IndexFirstPoint  = 3*IsoSurfaceTriangleListe[ThreeTimesI  ];
IndexSecondPoint = 3*IsoSurfaceTriangleListe[ThreeTimesI+1];
IndexThirdPoint  = 3*IsoSurfaceTriangleListe[ThreeTimesI+2];

IsoNormMapTransfrm[IndexFirstPoint  ] += NormTransfrm[ThreeTimesI  ];
IsoNormMapTransfrm[IndexFirstPoint+1] += NormTransfrm[ThreeTimesI+1];
IsoNormMapTransfrm[IndexFirstPoint+2] += NormTransfrm[ThreeTimesI+2];

IsoNormMapTransfrm[IndexSecondPoint  ] += NormTransfrm[ThreeTimesI  ];
IsoNormMapTransfrm[IndexSecondPoint+1] += NormTransfrm[ThreeTimesI+1];
IsoNormMapTransfrm[IndexSecondPoint+2] += NormTransfrm[ThreeTimesI+2];

IsoNormMapTransfrm[IndexThirdPoint  ] += NormTransfrm[ThreeTimesI  ];
IsoNormMapTransfrm[IndexThirdPoint+1] += NormTransfrm[ThreeTimesI+1];
IsoNormMapTransfrm[IndexThirdPoint+2] += NormTransfrm[ThreeTimesI+2];
}

/// Normalisation of theses resulting normales
 for (i=0; i < NbPointIsoMap   ; i++){
 ThreeTimesI = 3*i;

scalar = (double)sqrt((IsoNormMapTransfrm[ThreeTimesI  ]*IsoNormMapTransfrm[ThreeTimesI  ]) +
                      (IsoNormMapTransfrm[ThreeTimesI+1]*IsoNormMapTransfrm[ThreeTimesI+1]) +
                      (IsoNormMapTransfrm[ThreeTimesI+2]*IsoNormMapTransfrm[ThreeTimesI+2]));

if(scalar < 0.000000001)  scalar  = 0.000000001;
IsoNormMapTransfrm[ThreeTimesI  ] /= scalar;
IsoNormMapTransfrm[ThreeTimesI+1] /= scalar;
IsoNormMapTransfrm[ThreeTimesI+2] /= scalar;
}


}









///+++++++++++++++++++++++++++++++++++++++++
  void Iso3D::SpecialMorph_2(GLfloat *NormVertexTabPt, GLuint *IndexPolyTabPt, GLuint *NbPolygnNbVertexPt, int *TypeIsoSurfaceTriangleListeCNDPt, int *VertexNumberpt, int NbStep) {
    int TmpMorphStep, NbVertexTmp = 0, SixTimesNbVertexTmp=0,
        ThreeTimesNbPolygnTmp=0, ThreeTimesI, i, l;
    double step_local;


//ParseExpression();

morph_param = 0.0; // The starting point of the morph effect.
step_local = step; // To save this value
step = 1.0/(double)NbStep;

for(TmpMorphStep=0; TmpMorphStep<NbStep; TmpMorphStep++) {

CurrentStep = TmpMorphStep; // To store infos NbPointIsoMap and NbTriangleIsoSurface
       ParseExpression();
       VoxelEvaluation ();
       PointEdgeComputation();
       SignatureComputation();
       ConstructIsoSurface();
       ConstructIsoNormale();
       SaveIsoGLMap();

/// Save results :
// Save the Map:
 l = 0;
 for (i=0; i < NbPointIsoMap   ; i++){
 ThreeTimesI = 3*i;

NormVertexTab[l  +SixTimesNbVertexTmp] = IsoNormMapTransfrm[ThreeTimesI  ];
NormVertexTab[l+1+SixTimesNbVertexTmp] = IsoNormMapTransfrm[ThreeTimesI+1];
NormVertexTab[l+2+SixTimesNbVertexTmp] = IsoNormMapTransfrm[ThreeTimesI+2];

NormVertexTab[l+3+SixTimesNbVertexTmp] = IsoPointMapOriginal[ThreeTimesI  ];
NormVertexTab[l+4+SixTimesNbVertexTmp] = IsoPointMapOriginal[ThreeTimesI+1];
NormVertexTab[l+5+SixTimesNbVertexTmp] = IsoPointMapOriginal[ThreeTimesI+2];
l+=6;
}

/// Save the Starting of the first Triangles for this specific Morph Step :

// Save the Index:
l = 0;
for ( i=0; i < NbTriangleIsoSurface ; ++i) {
ThreeTimesI = 3*i;
IndexPolyTab[l  + ThreeTimesNbPolygnTmp] = IsoSurfaceTriangleListe[ThreeTimesI  ] + NbVertexTmp;
IndexPolyTab[l+1+ ThreeTimesNbPolygnTmp] = IsoSurfaceTriangleListe[ThreeTimesI+1] + NbVertexTmp;
IndexPolyTab[l+2+ ThreeTimesNbPolygnTmp] = IsoSurfaceTriangleListe[ThreeTimesI+2] + NbVertexTmp;
l+=3;
}

// Save Number of Polys and vertex :
NbPolygnNbVertex[2*CurrentStep  ] = 3*NbTriangleIsoSurface;
NbPolygnNbVertex[2*CurrentStep+1] = ThreeTimesNbPolygnTmp /*NbPointIsoMap*/;

NbVertexTmp += NbPointIsoMap;
SixTimesNbVertexTmp  = 6*NbVertexTmp;
ThreeTimesNbPolygnTmp += 3*NbTriangleIsoSurface;
}
/// restaure the right value for step var:
step = step_local; // To save this value

//std::cout << "Poly = "<< NbTriangleIsoSurface <<" ;  Vertex = "<< NbVertexTmp <<"\n";

/// Vertex :
memcpy(NormVertexTabPt, NormVertexTab, SixTimesNbVertexTmp*sizeof(GLfloat));
*VertexNumberpt = NbVertexTmp;
/// Index Triangles:
memcpy(IndexPolyTabPt, IndexPolyTab, ThreeTimesNbPolygnTmp*sizeof(GLuint));

/// Nb Poly & Vertex :
memcpy(NbPolygnNbVertexPt, NbPolygnNbVertex, 2*NbStep*sizeof(GLuint));

///Poly Type :
/*if(IsoConditionRequired == 1 )*/
memcpy(TypeIsoSurfaceTriangleListeCNDPt, TypeIsoSurfaceTriangleListeCND, NbTriangleIsoSurface*sizeof(int));
}
///+++++++++++++++++++++++++++++++++++++++++
  void Iso3D::RotateIsoMap() {
     Rotate();
     ApplicateTransform();
}

///+++++++++++++++++++++++++++++++++++++++++
   void Iso3D::Rotate(){
        MatRot.unit();
// Construction de la matrice de transformation
        MatRot.xrot(anglex);
        MatRot.yrot(angley);
//        MatGen.xrot(anglex);
//        MatGen.yrot(angley);
// On applique cette transformation a la matrice principale "mat"
        MatGen.mult(MatRot);
        MatRotSave.mult(MatRot);
}

///+++++++++++++++++++++++++++++++++++++++++
   void Iso3D::Scale(){
        MatSca.unit();
   // Construction de la matrice de transformation
        MatSca.xx = MatSca.yy = MatSca.zz = ScalCoeff;
   // On applique cette transformation a la matrice principale "mat"
        MatGen.mult(MatSca);
}

///++++++++++++++++++++++++++++++++++++++++
   void Iso3D::ScaleIsoMap(){
     Scale();
     ApplicateTransform();
}

///+++++++++++++++++++++++++++++++++++++++++
   Iso3D::~Iso3D(){

    delete tableau;
    for (i=0; i < 10000; i++)  {delete  tableaureferences[i];};
}

///+++++++++++++++++++++++++++++++++++++++++
   void Iso3D::ApplicateTransform(){
    double tp1, tp2, tp3;
    int ThreeTimesI;

/// Applicate Transformation to all points
   for (i=0; i < NbPointIsoMap ; i++){
        ThreeTimesI = 3*i;
        tp1 = IsoPointMapOriginal[ThreeTimesI    ];
        tp2 = IsoPointMapOriginal[ThreeTimesI + 1];
        tp3 = IsoPointMapOriginal[ThreeTimesI + 2];

IsoPointMapTransfrm[ThreeTimesI  ] = MatGen.xx*tp1 + MatGen.xy*tp2 +MatGen.xz*tp3 + MatGen.xo;

IsoPointMapTransfrm[ThreeTimesI+1] = MatGen.yx*tp1 + MatGen.yy*tp2 +MatGen.yz*tp3 + MatGen.yo;

IsoPointMapTransfrm[ThreeTimesI+2] = MatGen.zx*tp1 + MatGen.zy*tp2 +MatGen.zz*tp3 + MatGen.zo;
                                    }

/// Now, we transform Axes :
if (DrawAxe_Ok  == 1)
   for (i=0; i < 42 ; i++) {
        ThreeTimesI = 3*i;

/// X Axe :
        tp1 = AxeArrayOriginal[0][ThreeTimesI  ];
        tp2 = AxeArrayOriginal[0][ThreeTimesI+1];
        tp3 = AxeArrayOriginal[0][ThreeTimesI+2];
AxeArrayTransfrm[0][ThreeTimesI  ] = MatGen.xx*tp1 + MatGen.xy*tp2 +MatGen.xz*tp3 + MatGen.xo;
AxeArrayTransfrm[0][ThreeTimesI+1] = MatGen.yx*tp1 + MatGen.yy*tp2 +MatGen.yz*tp3 + MatGen.yo;
AxeArrayTransfrm[0][ThreeTimesI+2] = MatGen.zx*tp1 + MatGen.zy*tp2 +MatGen.zz*tp3 + MatGen.zo;

/// Y Axe :
        tp1 = AxeArrayOriginal[1][ThreeTimesI  ];
        tp2 = AxeArrayOriginal[1][ThreeTimesI+1];
        tp3 = AxeArrayOriginal[1][ThreeTimesI+2];
AxeArrayTransfrm[1][ThreeTimesI  ] = MatGen.xx*tp1 + MatGen.xy*tp2 +MatGen.xz*tp3 + MatGen.xo;
AxeArrayTransfrm[1][ThreeTimesI+1] = MatGen.yx*tp1 + MatGen.yy*tp2 +MatGen.yz*tp3 + MatGen.yo;
AxeArrayTransfrm[1][ThreeTimesI+2] = MatGen.zx*tp1 + MatGen.zy*tp2 +MatGen.zz*tp3 + MatGen.zo;

/// Z Axe :
        tp1 = AxeArrayOriginal[2][ThreeTimesI  ];
        tp2 = AxeArrayOriginal[2][ThreeTimesI+1];
        tp3 = AxeArrayOriginal[2][ThreeTimesI+2];
AxeArrayTransfrm[2][ThreeTimesI  ] = MatGen.xx*tp1 + MatGen.xy*tp2 +MatGen.xz*tp3 + MatGen.xo;
AxeArrayTransfrm[2][ThreeTimesI+1] = MatGen.yx*tp1 + MatGen.yy*tp2 +MatGen.yz*tp3 + MatGen.yo;
AxeArrayTransfrm[2][ThreeTimesI+2] = MatGen.zx*tp1 + MatGen.zy*tp2 +MatGen.zz*tp3 + MatGen.zo;
                                    }

//++++++++++++++++++++++++++++++++++++++++++
/// Now, we transform the Normal vectors :

   for (i=0; i < NbTriangleIsoSurface ; i++){
        ThreeTimesI = 3*i;
        tp1 = NormOriginal[ThreeTimesI    ];
        tp2 = NormOriginal[ThreeTimesI + 1];
        tp3 = NormOriginal[ThreeTimesI + 2];
NormTransfrm[ThreeTimesI  ] = MatRotSave.xx*tp1 + MatRotSave.xy*tp2 +MatRotSave.xz*tp3 + MatRotSave.xo;
NormTransfrm[ThreeTimesI+1] = MatRotSave.yx*tp1 + MatRotSave.yy*tp2 +MatRotSave.yz*tp3 + MatRotSave.yo;
NormTransfrm[ThreeTimesI+2] = MatRotSave.zx*tp1 + MatRotSave.zy*tp2 +MatRotSave.zz*tp3 + MatRotSave.zo;
                                      }
}

///++++++++++++++++++++++++++++ Projection +++++++++++++++++++++++
   void Iso3D::ApplicateProjection(){
    double coefficient;
    int ThreeTimesI;

    for ( i=0; i < NbPointIsoMap; ++i) {
ThreeTimesI = 3*i;
coefficient = D/(IsoPointMapTransfrm[ThreeTimesI + 2]-Oprime[2]);
IsoPointMapProjectd[ThreeTimesI  ] = coefficient*IsoPointMapTransfrm[ThreeTimesI  ]  + demi_hauteur;
IsoPointMapProjectd[ThreeTimesI+1] = coefficient*IsoPointMapTransfrm[ThreeTimesI+1]  + demi_largeur;
IsoPointMapProjectd[ThreeTimesI+2] = IsoPointMapTransfrm[ThreeTimesI+2];
                                        }
}




///++++++++++++++++++++ ConstructIsoSurface +++++++++++++++++++++++++++

   void Iso3D::ConstructIsoSurface(){
    int IndexNbTriangle, Alfa, Index, IndexPoint, IndexFirstPoint,
        IndexSeconPoint, IndexThirdPoint,
        IndexAprime, IndexBprime, IndexCprime;
    double  Aprime[4], Bprime[4], Cprime[4],
            DiffX, DiffY, DiffZ;

NbTriangleIsoSurface = 0;
NbPointIsoMapCND = 0;
NbTriangleIsoSurfaceCND = 0;



if(IsoConditionRequired == -1 )
     for(i=0; i < nb_ligne-1 - CutLigne; i++)
     for(k=0; k < nb_depth-1 - CutDepth; k++)
     for(j=0; j < nb_colon-1 - CutColon; j++)
 {
       Index = GridVoxel[i][j][k].Signature;
for (l = 0; triTable[Index][l] != -1 && NbTriangleIsoSurface < NbPolygonImposedLimit; l += 3) {

IndexFirstPoint = GridVoxel[i][j][k].Edge_Points[triTable[Index][l  ]];
IndexSeconPoint = GridVoxel[i][j][k].Edge_Points[triTable[Index][l+1]];
IndexThirdPoint = GridVoxel[i][j][k].Edge_Points[triTable[Index][l+2]];
if(IndexFirstPoint != -20 && IndexSeconPoint != -20 && IndexThirdPoint != -20 ) {
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexFirstPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexSeconPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexThirdPoint;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 1; /// Normals Triangles
NbTriangleIsoSurface++;                                                                                }
}
}











/// Here we have to compute some missing points...
else
     for(i=0; i < nb_ligne-1 - CutLigne; i++)
     for(k=0; k < nb_depth-1 - CutDepth; k++)
     for(j=0; j < nb_colon-1 - CutColon; j++)
 {
       Index = GridVoxel[i][j][k].Signature;
for (l = 0; triTable[Index][l] != -1 && NbTriangleIsoSurface < NbPolygonImposedLimit; l += 3) {

IndexFirstPoint = GridVoxel[i][j][k].Edge_Points[triTable[Index][l  ]];
IndexSeconPoint = GridVoxel[i][j][k].Edge_Points[triTable[Index][l+1]];
IndexThirdPoint = GridVoxel[i][j][k].Edge_Points[triTable[Index][l+2]];


if(IndexFirstPoint != -20 && IndexSeconPoint != -20 && IndexThirdPoint != -20){

///++++++++++++++++First Case +++++++++++++++++++++++++++++++++++++++++++///
/// All points verifient the condition
if(WichPointVeryCond[IndexFirstPoint]*WichPointVeryCond[IndexSeconPoint]*WichPointVeryCond[IndexThirdPoint] !=0) {
IsoSurfaceTriangleListe[NbTriangleIsoSurface*3  ] = IndexFirstPoint;
IsoSurfaceTriangleListe[NbTriangleIsoSurface*3+1] = IndexSeconPoint;
IsoSurfaceTriangleListe[NbTriangleIsoSurface*3+2] = IndexThirdPoint;
///All points in this triangle verify the condition. Type = 1
/// There is no new Isopoints to Add.
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 1;
NbTriangleIsoSurface++;
    }/// End if(WichPointVeryCond[IndexFirstPoint]...

///+++++++++++++++++ Second Case ++++++++++++++++++++++++++++++++++++++++++///
/// All points don't verify the condition
else if (WichPointVeryCond[IndexFirstPoint] == 0 &&
         WichPointVeryCond[IndexSeconPoint] == 0 &&
         WichPointVeryCond[IndexThirdPoint] == 0) {


IsoSurfaceTriangleListe[NbTriangleIsoSurface*3  ] = IndexFirstPoint;
IsoSurfaceTriangleListe[NbTriangleIsoSurface*3+1] = IndexSeconPoint;
IsoSurfaceTriangleListe[NbTriangleIsoSurface*3+2] = IndexThirdPoint;

///All points in this triangle verify the condition. Type = 0
/// There is no new Isopoints to Add.
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 0;
NbTriangleIsoSurface++;
}


///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
/// We still have 6 cases to treat here

else {
if(WichPointVeryCond[IndexFirstPoint] == 0) {
 if(WichPointVeryCond[IndexSeconPoint] == 0){
  if(WichPointVeryCond[IndexThirdPoint] != 0){
///  First Case : A == 0; B == 0; C != 0
/// Compute 2 points : Aprime and Bprime
/// Aprime
Aprime[0] = IsoPointMapOriginal[3*IndexThirdPoint  ];
Aprime[1] = IsoPointMapOriginal[3*IndexThirdPoint+1];
Aprime[2] = IsoPointMapOriginal[3*IndexThirdPoint+2];

DiffX = (IsoPointMapOriginal[3*IndexFirstPoint  ] - IsoPointMapOriginal[3*IndexThirdPoint  ])/10.;
DiffY = (IsoPointMapOriginal[3*IndexFirstPoint+1] - IsoPointMapOriginal[3*IndexThirdPoint+1])/10.;
DiffZ = (IsoPointMapOriginal[3*IndexFirstPoint+2] - IsoPointMapOriginal[3*IndexThirdPoint+2])/10.;
Alfa = 0;

while((IsoConditionParser.Eval(Aprime) == 1) && (Alfa < 10)) {
Aprime[0] += DiffX;
Aprime[1] += DiffY;
Aprime[2] += DiffZ;
Alfa += 1;
}

/// Bprime
Bprime[0] = IsoPointMapOriginal[3*IndexThirdPoint  ];
Bprime[1] = IsoPointMapOriginal[3*IndexThirdPoint+1];
Bprime[2] = IsoPointMapOriginal[3*IndexThirdPoint+2];

DiffX = (IsoPointMapOriginal[3*IndexSeconPoint  ] - IsoPointMapOriginal[3*IndexThirdPoint  ])/10.;
DiffY = (IsoPointMapOriginal[3*IndexSeconPoint+1] - IsoPointMapOriginal[3*IndexThirdPoint+1])/10.;
DiffZ = (IsoPointMapOriginal[3*IndexSeconPoint+2] - IsoPointMapOriginal[3*IndexThirdPoint+2])/10.;
Alfa = 0;

while((IsoConditionParser.Eval(Bprime) == 1) && (Alfa < 10)) {
Bprime[0] += DiffX;
Bprime[1] += DiffY;
Bprime[2] += DiffZ;
Alfa += 1;
}


///+++++++++++++++++++++++++///
/// Save theses points  and the triangles here
/// We have to new points to add

/// Add Aprime
IndexPoint = 3*NbPointIsoMap;
IsoPointMapOriginal[IndexPoint  ] = Aprime[0];
IsoPointMapOriginal[IndexPoint+1] = Aprime[1];
IsoPointMapOriginal[IndexPoint+2] = Aprime[2];
IndexAprime = NbPointIsoMap;
NbPointIsoMap++;

/// Add Bprime
IndexPoint = 3*NbPointIsoMap;
IsoPointMapOriginal[IndexPoint  ] = Bprime[0];
IsoPointMapOriginal[IndexPoint+1] = Bprime[1];
IsoPointMapOriginal[IndexPoint+2] = Bprime[2];
IndexBprime = NbPointIsoMap;
NbPointIsoMap++;

/// Add two new triangles :



///(Aprime, Bprime,C)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexAprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexThirdPoint;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 1;
NbTriangleIsoSurface++;

///(A, B, Bprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexFirstPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexSeconPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexBprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 0;
NbTriangleIsoSurface++;

///(A, Bprime, Aprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexFirstPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexAprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 0;
NbTriangleIsoSurface++;

///(Aprime, Bprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexAprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexBprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 4;
NbTriangleIsoSurface++;



///+++++++++++++++++++++++++///

} /// End of if(WichPointVeryCond[IndexThirdPoint] != 0)...
}/// End of if(WichPointVeryCond[IndexSeconPoint] == 0)
else {
/// Second case : A == 0; B != 0; C == 0;
  if(WichPointVeryCond[IndexThirdPoint] == 0){
/// Aprime
Aprime[0] = IsoPointMapOriginal[3*IndexSeconPoint  ];
Aprime[1] = IsoPointMapOriginal[3*IndexSeconPoint+1];
Aprime[2] = IsoPointMapOriginal[3*IndexSeconPoint+2];
DiffX = (IsoPointMapOriginal[3*IndexFirstPoint  ] - IsoPointMapOriginal[3*IndexSeconPoint  ])/10;
DiffY = (IsoPointMapOriginal[3*IndexFirstPoint+1] - IsoPointMapOriginal[3*IndexSeconPoint+1])/10;
DiffZ = (IsoPointMapOriginal[3*IndexFirstPoint+2] - IsoPointMapOriginal[3*IndexSeconPoint+2])/10;
Alfa = 0;
while(IsoConditionParser.Eval(Aprime) == 1 && (Alfa < 10)) {
Aprime[0] += DiffX;
Aprime[1] += DiffY;
Aprime[2] += DiffZ;
//std::cout <<DiffX <<", X = "<< Aprime[0] <<"\n";
Alfa += 1;
}
/// Cprime
Cprime[0] = IsoPointMapOriginal[3*IndexSeconPoint  ];
Cprime[1] = IsoPointMapOriginal[3*IndexSeconPoint+1];
Cprime[2] = IsoPointMapOriginal[3*IndexSeconPoint+2];
DiffX = (IsoPointMapOriginal[3*IndexThirdPoint  ] - IsoPointMapOriginal[3*IndexSeconPoint  ])/10;
DiffY = (IsoPointMapOriginal[3*IndexThirdPoint+1] - IsoPointMapOriginal[3*IndexSeconPoint+1])/10;
DiffZ = (IsoPointMapOriginal[3*IndexThirdPoint+2] - IsoPointMapOriginal[3*IndexSeconPoint+2])/10;
Alfa = 0;
while(IsoConditionParser.Eval(Cprime) == 1 && (Alfa < 10)) {
Cprime[0] += DiffX;
Cprime[1] += DiffY;
Cprime[2] += DiffZ;
Alfa += 1;
}

///+++++++++++++++++++++++++///
/// Save theses points  and the triangle here

/// Add Aprime
IndexPoint = 3*NbPointIsoMap;
IsoPointMapOriginal[IndexPoint  ] = Aprime[0];
IsoPointMapOriginal[IndexPoint+1] = Aprime[1];
IsoPointMapOriginal[IndexPoint+2] = Aprime[2];
NbPointIsoMap++;

/// Add Cprime
IndexPoint = 3*NbPointIsoMap;
IsoPointMapOriginal[IndexPoint  ] = Cprime[0];
IsoPointMapOriginal[IndexPoint+1] = Cprime[1];
IsoPointMapOriginal[IndexPoint+2] = Cprime[2];
NbPointIsoMap++;

/// Add Three new triangles :
IndexAprime = (NbPointIsoMap-2);
IndexCprime = (NbPointIsoMap-1);

///(Aprime, B, Cprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexAprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexSeconPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexCprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 1;
NbTriangleIsoSurface++;

/// (A , Aprime, Cprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexFirstPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexAprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexCprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 0;
NbTriangleIsoSurface++;

/// (A, Cprime, C)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexFirstPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexCprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexThirdPoint;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 0;
NbTriangleIsoSurface++;

/// (Aprime, Cprime) --> The border
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexAprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexCprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexCprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 4;
NbTriangleIsoSurface++;






///+++++++++++++++++++++++++///

}

/// Thid Case : : A == 0; B != 0; C != 0;
else {

/// Bprime
Bprime[0] = IsoPointMapOriginal[3*IndexSeconPoint  ];
Bprime[1] = IsoPointMapOriginal[3*IndexSeconPoint+1];
Bprime[2] = IsoPointMapOriginal[3*IndexSeconPoint+2];
DiffX = (IsoPointMapOriginal[3*IndexFirstPoint  ] - IsoPointMapOriginal[3*IndexSeconPoint  ])/10;
DiffY = (IsoPointMapOriginal[3*IndexFirstPoint+1] - IsoPointMapOriginal[3*IndexSeconPoint+1])/10;
DiffZ = (IsoPointMapOriginal[3*IndexFirstPoint+2] - IsoPointMapOriginal[3*IndexSeconPoint+2])/10;
Alfa = 0;
while(IsoConditionParser.Eval(Bprime) == 1 && (Alfa < 10)) {
Bprime[0] += DiffX;
Bprime[1] += DiffY;
Bprime[2] += DiffZ;
Alfa += 1;
}

/// Cprime

Cprime[0] = IsoPointMapOriginal[3*IndexThirdPoint  ];
Cprime[1] = IsoPointMapOriginal[3*IndexThirdPoint+1];
Cprime[2] = IsoPointMapOriginal[3*IndexThirdPoint+2];
DiffX = (IsoPointMapOriginal[3*IndexFirstPoint  ] - IsoPointMapOriginal[3*IndexThirdPoint  ])/10;
DiffY = (IsoPointMapOriginal[3*IndexFirstPoint+1] - IsoPointMapOriginal[3*IndexThirdPoint+1])/10;
DiffZ = (IsoPointMapOriginal[3*IndexFirstPoint+2] - IsoPointMapOriginal[3*IndexThirdPoint+2])/10;
Alfa = 0;
while(IsoConditionParser.Eval(Cprime) == 1 && (Alfa < 10)) {
Cprime[0] += DiffX;
Cprime[1] += DiffY;
Cprime[2] += DiffZ;
Alfa += 1;
}


///+++++++++++++++++++++++++///
/// Save theses points  and the triangle here


/// Add Bprime
IndexPoint = 3*NbPointIsoMap;
IsoPointMapOriginal[IndexPoint  ] = Bprime[0];
IsoPointMapOriginal[IndexPoint+1] = Bprime[1];
IsoPointMapOriginal[IndexPoint+2] = Bprime[2];
NbPointIsoMap++;

/// Add Cprime
IndexPoint = 3*NbPointIsoMap;
IsoPointMapOriginal[IndexPoint  ] = Cprime[0];
IsoPointMapOriginal[IndexPoint+1] = Cprime[1];
IsoPointMapOriginal[IndexPoint+2] = Cprime[2];
NbPointIsoMap++;



/// Add Three new triangles :
IndexBprime = (NbPointIsoMap-2);
IndexCprime = (NbPointIsoMap-1);

/// (A, Bprime, Cprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexFirstPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexCprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 0;
NbTriangleIsoSurface++;

/// (Bprime, B, C)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexSeconPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexThirdPoint;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 1;
NbTriangleIsoSurface++;

/// (Bprime, C, Cprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexThirdPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexCprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 1;
NbTriangleIsoSurface++;

/// (Bprime, Cprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexCprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexCprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 4;
NbTriangleIsoSurface++;

///+++++++++++++++++++++++++///


}
}
}
else {
/// Fourth Case : A != 0; B == 0, C == 0
if(WichPointVeryCond[IndexSeconPoint] == 0 && WichPointVeryCond[IndexThirdPoint] == 0) {


/// Bprime
Bprime[0] = IsoPointMapOriginal[3*IndexFirstPoint  ];
Bprime[1] = IsoPointMapOriginal[3*IndexFirstPoint+1];
Bprime[2] = IsoPointMapOriginal[3*IndexFirstPoint+2];
DiffX = (IsoPointMapOriginal[3*IndexSeconPoint  ] - IsoPointMapOriginal[3*IndexFirstPoint  ])/10;
DiffY = (IsoPointMapOriginal[3*IndexSeconPoint+1] - IsoPointMapOriginal[3*IndexFirstPoint+1])/10;
DiffZ = (IsoPointMapOriginal[3*IndexSeconPoint+2] - IsoPointMapOriginal[3*IndexFirstPoint+2])/10;
Alfa = 0;
while(IsoConditionParser.Eval(Bprime) == 1 && (Alfa < 10)) {
Bprime[0] += DiffX;
Bprime[1] += DiffY;
Bprime[2] += DiffZ;
Alfa += 1;
}

/// Cprime

Cprime[0] = IsoPointMapOriginal[3*IndexFirstPoint  ];
Cprime[1] = IsoPointMapOriginal[3*IndexFirstPoint+1];
Cprime[2] = IsoPointMapOriginal[3*IndexFirstPoint+2];
DiffX = (IsoPointMapOriginal[3*IndexThirdPoint  ] - IsoPointMapOriginal[3*IndexFirstPoint  ])/10;
DiffY = (IsoPointMapOriginal[3*IndexThirdPoint+1] - IsoPointMapOriginal[3*IndexFirstPoint+1])/10;
DiffZ = (IsoPointMapOriginal[3*IndexThirdPoint+2] - IsoPointMapOriginal[3*IndexFirstPoint+2])/10;
Alfa = 0;
while(IsoConditionParser.Eval(Cprime) == 1 && (Alfa < 10)) {
Cprime[0] += DiffX;
Cprime[1] += DiffY;
Cprime[2] += DiffZ;
Alfa += 1;
}


///+++++++++++++++++++++++++///
/// Save theses points  and the triangle here


/// Add Bprime
IndexPoint = 3*NbPointIsoMap;
IsoPointMapOriginal[IndexPoint  ] = Bprime[0];
IsoPointMapOriginal[IndexPoint+1] = Bprime[1];
IsoPointMapOriginal[IndexPoint+2] = Bprime[2];
NbPointIsoMap++;

/// Add Cprime
IndexPoint = 3*NbPointIsoMap;
IsoPointMapOriginal[IndexPoint  ] = Cprime[0];
IsoPointMapOriginal[IndexPoint+1] = Cprime[1];
IsoPointMapOriginal[IndexPoint+2] = Cprime[2];
NbPointIsoMap++;


/// Add Three new triangles :
IndexBprime = (NbPointIsoMap-2);
IndexCprime = (NbPointIsoMap-1);

/// (A, Bprime, Cprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexFirstPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexCprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 1;
NbTriangleIsoSurface++;

/// (Bprime, B, C)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexSeconPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexThirdPoint;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 0;
NbTriangleIsoSurface++;

/// (Bprime, C, Cprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexThirdPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexCprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 0;
NbTriangleIsoSurface++;

/// (Bprime, Cprime) --> the border
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexCprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexCprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 4; /// Type = 4-->Border
NbTriangleIsoSurface++;


///+++++++++++++++++++++++++///

}
/// Fifth Case : A != 0; B == 0, C != 0
/// We generate Two Triangles
else if (WichPointVeryCond[IndexSeconPoint] == 0 && WichPointVeryCond[IndexThirdPoint] != 0) {
/// Aprime :
Aprime[0] = IsoPointMapOriginal[3*IndexFirstPoint  ];
Aprime[1] = IsoPointMapOriginal[3*IndexFirstPoint+1];
Aprime[2] = IsoPointMapOriginal[3*IndexFirstPoint+2];
DiffX = (IsoPointMapOriginal[3*IndexSeconPoint  ] - IsoPointMapOriginal[3*IndexFirstPoint  ])/10;
DiffY = (IsoPointMapOriginal[3*IndexSeconPoint+1] - IsoPointMapOriginal[3*IndexFirstPoint+1])/10;
DiffZ = (IsoPointMapOriginal[3*IndexSeconPoint+2] - IsoPointMapOriginal[3*IndexFirstPoint+2])/10;
Alfa = 0;
while(IsoConditionParser.Eval(Aprime) == 1 && (Alfa < 10)) {
Aprime[0] += DiffX;
Aprime[1] += DiffY;
Aprime[2] += DiffZ;
Alfa += 1;
}

/// Cprime
Cprime[0] = IsoPointMapOriginal[3*IndexThirdPoint  ];
Cprime[1] = IsoPointMapOriginal[3*IndexThirdPoint+1];
Cprime[2] = IsoPointMapOriginal[3*IndexThirdPoint+2];
DiffX = (IsoPointMapOriginal[3*IndexSeconPoint  ] - IsoPointMapOriginal[3*IndexThirdPoint  ])/10;
DiffY = (IsoPointMapOriginal[3*IndexSeconPoint+1] - IsoPointMapOriginal[3*IndexThirdPoint+1])/10;
DiffZ = (IsoPointMapOriginal[3*IndexSeconPoint+2] - IsoPointMapOriginal[3*IndexThirdPoint+2])/10;
Alfa = 0;
while(IsoConditionParser.Eval(Cprime) == 1 && (Alfa < 10)) {
Cprime[0] += DiffX;
Cprime[1] += DiffY;
Cprime[2] += DiffZ;
Alfa += 1;
}

///+++++++++++++++++++++++++///
/// Save theses points  and the triangle here

/// Save theses points  and the triangle here


/// Add Aprime
IndexPoint = 3*NbPointIsoMap;
IsoPointMapOriginal[IndexPoint  ] = Aprime[0];
IsoPointMapOriginal[IndexPoint+1] = Aprime[1];
IsoPointMapOriginal[IndexPoint+2] = Aprime[2];
NbPointIsoMap++;

/// Add Cprime
IndexPoint = 3*NbPointIsoMap;
IsoPointMapOriginal[IndexPoint  ] = Cprime[0];
IsoPointMapOriginal[IndexPoint+1] = Cprime[1];
IsoPointMapOriginal[IndexPoint+2] = Cprime[2];
NbPointIsoMap++;


/// Add Three new triangles :
IndexAprime = (NbPointIsoMap-2);
IndexCprime = (NbPointIsoMap-1);

/// (B, Cprime, Aprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexSeconPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexCprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexAprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 0;
NbTriangleIsoSurface++;

/// (Aprime, Cprime, C)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexAprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexCprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexThirdPoint;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 1;
NbTriangleIsoSurface++;

/// (Aprime, C, A)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexAprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexThirdPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexFirstPoint;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 1;
NbTriangleIsoSurface++;

/// (Aprime, Cprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexAprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexCprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexCprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 4;
NbTriangleIsoSurface++;

///+++++++++++++++++++++++++///

}
/// Sixth Case : A != 0; B != 0, C == 0
/// We generate Two Triangles
else if (WichPointVeryCond[IndexSeconPoint] != 0 && WichPointVeryCond[IndexThirdPoint] == 0) {
/// Aprime

Aprime[0] = IsoPointMapOriginal[3*IndexFirstPoint  ];
Aprime[1] = IsoPointMapOriginal[3*IndexFirstPoint+1];
Aprime[2] = IsoPointMapOriginal[3*IndexFirstPoint+2];
DiffX = (IsoPointMapOriginal[3*IndexThirdPoint  ] - IsoPointMapOriginal[3*IndexFirstPoint  ])/10;
DiffY = (IsoPointMapOriginal[3*IndexThirdPoint+1] - IsoPointMapOriginal[3*IndexFirstPoint+1])/10;
DiffZ = (IsoPointMapOriginal[3*IndexThirdPoint+2] - IsoPointMapOriginal[3*IndexFirstPoint+2])/10;
Alfa = 0;
while(IsoConditionParser.Eval(Aprime) == 1 && (Alfa < 10)) {
Aprime[0] += DiffX;
Aprime[1] += DiffY;
Aprime[2] += DiffZ;
Alfa += 1;
}

/// Bprime

Bprime[0] = IsoPointMapOriginal[3*IndexSeconPoint  ];
Bprime[1] = IsoPointMapOriginal[3*IndexSeconPoint+1];
Bprime[2] = IsoPointMapOriginal[3*IndexSeconPoint+2];
DiffX = (IsoPointMapOriginal[3*IndexThirdPoint  ] - IsoPointMapOriginal[3*IndexSeconPoint  ])/10;
DiffY = (IsoPointMapOriginal[3*IndexThirdPoint+1] - IsoPointMapOriginal[3*IndexSeconPoint+1])/10;
DiffZ = (IsoPointMapOriginal[3*IndexThirdPoint+2] - IsoPointMapOriginal[3*IndexSeconPoint+2])/10;
Alfa = 0;
while(IsoConditionParser.Eval(Bprime) == 1 && (Alfa < 10)) {
Bprime[0] += DiffX;
Bprime[1] += DiffY;
Bprime[2] += DiffZ;
Alfa += 1;
}


///+++++++++++++++++++++++++///
/// Save theses points  and the triangle here


/// Add Aprime
IndexPoint = 3*NbPointIsoMap;
IsoPointMapOriginal[IndexPoint  ] = Aprime[0];
IsoPointMapOriginal[IndexPoint+1] = Aprime[1];
IsoPointMapOriginal[IndexPoint+2] = Aprime[2];
NbPointIsoMap++;

/// Add Bprime
IndexPoint = 3*NbPointIsoMap;
IsoPointMapOriginal[IndexPoint  ] = Bprime[0];
IsoPointMapOriginal[IndexPoint+1] = Bprime[1];
IsoPointMapOriginal[IndexPoint+2] = Bprime[2];
NbPointIsoMap++;
/// Add Three new triangles :
IndexAprime = (NbPointIsoMap-2);
IndexBprime = (NbPointIsoMap-1);

/// (Aprime, Bprime, C)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexAprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexThirdPoint;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 0;
NbTriangleIsoSurface++;

/// (A, B, Bprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexFirstPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexSeconPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexBprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 1;
NbTriangleIsoSurface++;

/// (A, Bprime, Aprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexFirstPoint;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexAprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 1;
NbTriangleIsoSurface++;

/// (Aprime, Bprime)
IndexNbTriangle = NbTriangleIsoSurface*3;
IsoSurfaceTriangleListe[IndexNbTriangle  ] = IndexAprime;
IsoSurfaceTriangleListe[IndexNbTriangle+1] = IndexBprime;
IsoSurfaceTriangleListe[IndexNbTriangle+2] = IndexBprime;
TypeIsoSurfaceTriangleListeCND[NbTriangleIsoSurface] = 4;
NbTriangleIsoSurface++;
///+++++++++++++++++++++++++///

}



}






}/// End if if(IndexFirstPoint != -20...

}

}
}



}



///+++++++++++++++++++++++++++++++++++++++++
   void Iso3D::VoxelEvaluation (){
     double vals[] = {0,0,0,0};
     double XLocal[200], YLocal[200], ZLocal[200]; //Up to 200x200x200 voxels



/// this is for the morph effect...
if(morph_param >= 0.0)  vals[3] = morph_param;
else  vals[3] = -morph_param;
morph_param += step;
if( morph_param == 1) morph_param = 0;

//Can be optimised by considering Three array of 30 values each
// Each array contain the 30 value of one axe...
     X_Step = (X_Start - X_End)/(nb_ligne-1);
     Y_Step = (Y_Start - Y_End)/(nb_colon-1);
     Z_Step = (Z_Start - Z_End)/(nb_depth-1);
for (i= 0; i < nb_ligne; i++) XLocal[i] = X_Start - i*X_Step;
for (j= 0; j < nb_colon; j++) YLocal[j] = Y_Start - j*Y_Step;
for (k= 0; k < nb_depth; k++) ZLocal[k] = Z_Start - k*Z_Step;


     for(i=0; i<nb_ligne; i++) {
         vals[0] = XLocal[i];
      for(j=0; j<nb_colon; j++) {
         vals[1] = YLocal[j];
       for(k=0; k<nb_depth; k++) {
         vals[2] = ZLocal[k];
        GridVoxel[i][j][k].PositionX = vals[0] ;
        GridVoxel[i][j][k].PositionY = vals[1] ;
        GridVoxel[i][j][k].PositionZ = vals[2] ;

        GridVoxel[i][j][k].Value = ImplicitFunctionParser.Eval(vals);

        GridVoxel[i][j][k].Signature   = 0; // Signature initialisation
        GridVoxel[i][j][k].NbEdgePoint = 0; // No EdgePoint yet!
        GridVoxel[i][j][k].Index[0] = i;
        GridVoxel[i][j][k].Index[1] = j;
        GridVoxel[i][j][k].Index[2] = k;

for(l=0; l<12; l++) GridVoxel[i][j][k].Edge_Points[l] = -20; /// just for verification
                                  }
}
}
};

///+++++++++++++++++++++++++++++++++++++++++
   void Iso3D::PointEdgeComputation(){
    int index, i_Start, i_End, j_Start, j_End, k_Start, k_End;
    double vals[4], IsoValue_1, IsoValue_2, rapport;
    double factor;

/// We have to compute the edges for the Grid limits ie: i=0, j=0 and k=0
NbPointIsoMap = 0;

i_Start = 1;
j_Start = 1;
k_Start = 1;

i_End = nb_ligne-1;
j_End = nb_colon-1;
k_End = nb_depth-1;
/// The code is doubled to eliminate conditions tests

     for(i = i_Start; i < i_End; i++)
      for(j = j_Start; j < j_End; j++)
       for(k = k_Start; k < k_End; k++)
 {
        IsoValue_1 = GridVoxel[i][j][k].Value;

/// First Case P(i+1)(j)(k)

        IsoValue_2 = GridVoxel[i+1][j][k].Value;
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0 ) {


          // Edge Point computation and  save in IsoPointMap
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][j][k].PositionX + factor * (GridVoxel[i+1][j][k].PositionX - GridVoxel[i][j][k].PositionX);

          vals[1] = GridVoxel[i][j][k].PositionY + factor * (GridVoxel[i+1][j][k].PositionY - GridVoxel[i][j][k].PositionY);

          vals[2] = GridVoxel[i][j][k].PositionZ + factor * (GridVoxel[i+1][j][k].PositionZ - GridVoxel[i][j][k].PositionZ);
///===========================================================///
IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][j][k].Edge_Points[0] = NbPointIsoMap;
          GridVoxel[i][j][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
          GridVoxel[i][j-1][k].Edge_Points[4] = NbPointIsoMap;
          GridVoxel[i][j-1][k].NbEdgePoint += 1;

          GridVoxel[i][j][k-1].Edge_Points[2]   = NbPointIsoMap;
          GridVoxel[i][j][k-1].NbEdgePoint += 1;

          GridVoxel[i][j-1][k-1].Edge_Points[6] = NbPointIsoMap;
          GridVoxel[i][j-1][k-1].NbEdgePoint += 1;


if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;


NbPointIsoMap++;





        }
///+++++++++++++++++++++++++++++++++++++++++
/// Second Case P(i)(j+1)(k)

        IsoValue_2 = GridVoxel[i][j+1][k].Value;
          // Edge Point computation and  save in IsoPointMap
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][j][k].PositionX + factor * (GridVoxel[i][j+1][k].PositionX - GridVoxel[i][j][k].PositionX);

          vals[1] = GridVoxel[i][j][k].PositionY + factor * (GridVoxel[i][j+1][k].PositionY - GridVoxel[i][j][k].PositionY);

          vals[2] = GridVoxel[i][j][k].PositionZ + factor * (GridVoxel[i][j+1][k].PositionZ - GridVoxel[i][j][k].PositionZ);

IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][j][k].Edge_Points[8] = NbPointIsoMap;
          GridVoxel[i][j][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
          GridVoxel[i-1][j][k].Edge_Points[9]    = NbPointIsoMap;
          GridVoxel[i-1][j][k].NbEdgePoint += 1;

          GridVoxel[i][j][k-1].Edge_Points[11]   = NbPointIsoMap;
          GridVoxel[i][j][k-1].NbEdgePoint += 1;

          GridVoxel[i-1][j][k-1].Edge_Points[10] = NbPointIsoMap;
          GridVoxel[i-1][j][k-1].NbEdgePoint += 1;


if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;

NbPointIsoMap++;


}

// Third Case P(i)(j)(k+1)

        IsoValue_2 = GridVoxel[i][j][k+1].Value;
          // Edge Point computation and  save in IsoPointMap
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][j][k].PositionX + factor * (GridVoxel[i][j][k+1].PositionX - GridVoxel[i][j][k].PositionX);

          vals[1] = GridVoxel[i][j][k].PositionY + factor * (GridVoxel[i][j][k+1].PositionY - GridVoxel[i][j][k].PositionY);

          vals[2] = GridVoxel[i][j][k].PositionZ + factor * (GridVoxel[i][j][k+1].PositionZ - GridVoxel[i][j][k].PositionZ);



IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][j][k].Edge_Points[3] = NbPointIsoMap;
          GridVoxel[i][j][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
          GridVoxel[i-1][j][k].Edge_Points[1]   = NbPointIsoMap;
          GridVoxel[i-1][j][k].NbEdgePoint += 1;

          GridVoxel[i][j-1][k].Edge_Points[7]   = NbPointIsoMap;
          GridVoxel[i][j-1][k].NbEdgePoint += 1;

          GridVoxel[i-1][j-1][k].Edge_Points[5] = NbPointIsoMap;
          GridVoxel[i-1][j-1][k].NbEdgePoint += 1;



if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;

NbPointIsoMap++;

}
}



/// Now we have to compute the Grid's limits...
/// The code is quite big but this is much more easy to compute




/// 1) First case : i =0;

 i =0;
      for(j=0; j < nb_colon; j++)
       for(k=0; k < nb_depth; k++) {

        IsoValue_1 = GridVoxel[0][j][k].Value;

// First Case P(1)(j)(k)

        IsoValue_2 = GridVoxel[1][j][k].Value;
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          // Edge Point computation and  save in IsoPointMap
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[0][j][k].PositionX + factor * (GridVoxel[1][j][k].PositionX - GridVoxel[0][j][k].PositionX);

          vals[1] = GridVoxel[0][j][k].PositionY + factor * (GridVoxel[1][j][k].PositionY - GridVoxel[0][j][k].PositionY);

          vals[2] = GridVoxel[0][j][k].PositionZ + factor * (GridVoxel[1][j][k].PositionZ - GridVoxel[0][j][k].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[0][j][k].Edge_Points[0] = NbPointIsoMap;
          GridVoxel[0][j][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if( j != 0){
          GridVoxel[0][j-1][k].Edge_Points[4] = NbPointIsoMap;
          GridVoxel[0][j-1][k].NbEdgePoint += 1;
}
if ( k != 0 ) {
          GridVoxel[0][j][k-1].Edge_Points[2]   = NbPointIsoMap;
          GridVoxel[0][j][k-1].NbEdgePoint += 1;
}
if( j != 0 && k != 0) {
          GridVoxel[0][j-1][k-1].Edge_Points[6] = NbPointIsoMap;
          GridVoxel[0][j-1][k-1].NbEdgePoint += 1;
}



if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;

 NbPointIsoMap++;

        }


// Second Case P(0)(j+1)(k)
if ( j != (nb_colon -1)){
        IsoValue_2 = GridVoxel[0][j+1][k].Value;
          // Edge Point computation and  save in IsoPointMap
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[0][j][k].PositionX + factor * (GridVoxel[0][j+1][k].PositionX - GridVoxel[0][j][k].PositionX);

          vals[1] = GridVoxel[0][j][k].PositionY + factor * (GridVoxel[0][j+1][k].PositionY - GridVoxel[0][j][k].PositionY);

          vals[2] = GridVoxel[0][j][k].PositionZ + factor * (GridVoxel[0][j+1][k].PositionZ - GridVoxel[0][j][k].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[0][j][k].Edge_Points[8] = NbPointIsoMap;
          GridVoxel[0][j][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if ( k != 0){
          GridVoxel[0][j][k-1].Edge_Points[11]   = NbPointIsoMap;
          GridVoxel[0][j][k-1].NbEdgePoint += 1;
}


if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;

          NbPointIsoMap++;

        }
} /// If ( j != nb_colon -1) ...

// Third Case P(0)(j)(k+1)
if ( k != (nb_depth-1)){
        IsoValue_2 = GridVoxel[0][j][k+1].Value;
          // Edge Point computation and  save in IsoPointMap
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[0][j][k].PositionX + factor * (GridVoxel[0][j][k+1].PositionX - GridVoxel[0][j][k].PositionX);

          vals[1] = GridVoxel[0][j][k].PositionY + factor * (GridVoxel[0][j][k+1].PositionY - GridVoxel[0][j][k].PositionY);

          vals[2] = GridVoxel[0][j][k].PositionZ + factor * (GridVoxel[0][j][k+1].PositionZ - GridVoxel[0][j][k].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[0][j][k].Edge_Points[3] = NbPointIsoMap;
          GridVoxel[0][j][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if ( j != 0) {
          GridVoxel[0][j-1][k].Edge_Points[7]   = NbPointIsoMap;
          GridVoxel[0][j-1][k].NbEdgePoint += 1;
}


if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;


          NbPointIsoMap++;

        }
} /// End of ( if ( k != nb_depth -1)....
   }










/// 2) Case i = nb_ligne-1

i = nb_ligne-1;

      for(j=0; j < nb_colon; j++)
       for(k=0; k < nb_depth; k++)
 {

        IsoValue_1 = GridVoxel[i][j][k].Value;


// Second Case P(i)(j+1)(k)
if ( j != (nb_colon -1)){
        IsoValue_2 = GridVoxel[i][j+1][k].Value;
          // Edge Point computation and  save in IsoPointMap
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][j][k].PositionX + factor * (GridVoxel[i][j+1][k].PositionX - GridVoxel[i][j][k].PositionX);

          vals[1] = GridVoxel[i][j][k].PositionY + factor * (GridVoxel[i][j+1][k].PositionY - GridVoxel[i][j][k].PositionY);

          vals[2] = GridVoxel[i][j][k].PositionZ + factor * (GridVoxel[i][j+1][k].PositionZ - GridVoxel[i][j][k].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][j][k].Edge_Points[8] = NbPointIsoMap;
          GridVoxel[i][j][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if(i != 0){
          GridVoxel[i-1][j][k].Edge_Points[9]    = NbPointIsoMap;
          GridVoxel[i-1][j][k].NbEdgePoint += 1;
}
if(k != 0){
          GridVoxel[i][j][k-1].Edge_Points[11]   = NbPointIsoMap;
          GridVoxel[i][j][k-1].NbEdgePoint += 1;
}
if(i != 0 && k != 0){
          GridVoxel[i-1][j][k-1].Edge_Points[10] = NbPointIsoMap;
          GridVoxel[i-1][j][k-1].NbEdgePoint += 1;
}

if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;

          NbPointIsoMap++;

        }
} /// End of if (j != nb_colon -1)...

// Third Case P(i)(j)(k+1)
if ( k != (nb_depth -1)){
        IsoValue_2 = GridVoxel[i][j][k+1].Value;
          // Edge Point computation and  save in IsoPointMap
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][j][k].PositionX + factor * (GridVoxel[i][j][k+1].PositionX - GridVoxel[i][j][k].PositionX);

          vals[1] = GridVoxel[i][j][k].PositionY + factor * (GridVoxel[i][j][k+1].PositionY - GridVoxel[i][j][k].PositionY);

          vals[2] = GridVoxel[i][j][k].PositionZ + factor * (GridVoxel[i][j][k+1].PositionZ - GridVoxel[i][j][k].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][j][k].Edge_Points[3] = NbPointIsoMap;
          GridVoxel[i][j][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if( i != 0) {
          GridVoxel[i-1][j][k].Edge_Points[1]   = NbPointIsoMap;
          GridVoxel[i-1][j][k].NbEdgePoint += 1;
}
if(j != 0) {
          GridVoxel[i][j-1][k].Edge_Points[7]   = NbPointIsoMap;
          GridVoxel[i][j-1][k].NbEdgePoint += 1;
}
if( i !=0 && j != 0) {
          GridVoxel[i-1][j-1][k].Edge_Points[5] = NbPointIsoMap;
          GridVoxel[i-1][j-1][k].NbEdgePoint += 1;
}

if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;

          NbPointIsoMap++;

        }
} /// End of if ( k != nb_depth -1)...
     }







/// 3) Case j = 0
j= 0;

     for(i=0; i < nb_ligne; i++)
       for(k=0; k < nb_depth; k++)
 {

        IsoValue_1 = GridVoxel[i][0][k].Value;


// First Case P(i+1)(j)(k)
if( i != (nb_ligne -1)){
        IsoValue_2 = GridVoxel[i+1][0][k].Value;
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {

          // Edge Point computation and  save in IsoPointMap
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][0][k].PositionX + factor * (GridVoxel[i+1][0][k].PositionX - GridVoxel[i][0][k].PositionX);

          vals[1] = GridVoxel[i][0][k].PositionY + factor * (GridVoxel[i+1][0][k].PositionY - GridVoxel[i][0][k].PositionY);

          vals[2] = GridVoxel[i][0][k].PositionZ + factor * (GridVoxel[i+1][0][k].PositionZ - GridVoxel[i][0][k].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][0][k].Edge_Points[0] = NbPointIsoMap;
          GridVoxel[i][0][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if( k!=0){
          GridVoxel[i][0][k-1].Edge_Points[2]   = NbPointIsoMap;
          GridVoxel[i][0][k-1].NbEdgePoint += 1;
}


if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;

          NbPointIsoMap++;


        }
} /// End of if ( i != nb_ligne -1)...

// Second Case P(i)(j+1)(k)

        IsoValue_2 = GridVoxel[i][1][k].Value;
          // Edge Point computation and  save in IsoPointMap
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][0][k].PositionX + factor * (GridVoxel[i][1][k].PositionX - GridVoxel[i][0][k].PositionX);

          vals[1] = GridVoxel[i][0][k].PositionY + factor * (GridVoxel[i][1][k].PositionY - GridVoxel[i][0][k].PositionY);

          vals[2] = GridVoxel[i][0][k].PositionZ + factor * (GridVoxel[i][1][k].PositionZ - GridVoxel[i][0][k].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][0][k].Edge_Points[8] = NbPointIsoMap;
          GridVoxel[i][0][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if( i !=0 ){
          GridVoxel[i-1][0][k].Edge_Points[9]    = NbPointIsoMap;
          GridVoxel[i-1][0][k].NbEdgePoint += 1;
}
if(k !=0){
          GridVoxel[i][0][k-1].Edge_Points[11]   = NbPointIsoMap;
          GridVoxel[i][0][k-1].NbEdgePoint += 1;
}
if( i !=0 && k !=0){
          GridVoxel[i-1][0][k-1].Edge_Points[10] = NbPointIsoMap;
          GridVoxel[i-1][0][k-1].NbEdgePoint += 1;
}

if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;

          NbPointIsoMap++;

        }


// Third Case P(i)(j)(k+1)
if(k != (nb_depth -1)){
        IsoValue_2 = GridVoxel[i][0][k+1].Value;
          // Edge Point computation and  save in IsoPointMap
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][0][k].PositionX + factor * (GridVoxel[i][0][k+1].PositionX - GridVoxel[i][0][k].PositionX);

          vals[1] = GridVoxel[i][0][k].PositionY + factor * (GridVoxel[i][0][k+1].PositionY - GridVoxel[i][0][k].PositionY);

          vals[2] = GridVoxel[i][0][k].PositionZ + factor * (GridVoxel[i][0][k+1].PositionZ - GridVoxel[i][0][k].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][0][k].Edge_Points[3] = NbPointIsoMap;
          GridVoxel[i][0][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if( i != 0) {
          GridVoxel[i-1][0][k].Edge_Points[1]   = NbPointIsoMap;
          GridVoxel[i-1][0][k].NbEdgePoint += 1;
}

if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;

          NbPointIsoMap++;

        }
} /// End of if(k != (nb_depth -1))...
     }







/// 4) Case j = nb_colon -1
j = nb_colon-1;

     for(i=0; i < nb_ligne; i++)
       for(k=0; k < nb_depth; k++)
 {

        IsoValue_1 = GridVoxel[i][j][k].Value;


// First Case P(i+1)(j)(k)
if( i != (nb_ligne-1)) {
        IsoValue_2 = GridVoxel[i+1][j][k].Value;
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {

          // Edge Point computation and  save in IsoPointMap
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][j][k].PositionX + factor * (GridVoxel[i+1][j][k].PositionX - GridVoxel[i][j][k].PositionX);

          vals[1] = GridVoxel[i][j][k].PositionY + factor * (GridVoxel[i+1][j][k].PositionY - GridVoxel[i][j][k].PositionY);

          vals[2] = GridVoxel[i][j][k].PositionZ + factor * (GridVoxel[i+1][j][k].PositionZ - GridVoxel[i][j][k].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][j][k].Edge_Points[0] = NbPointIsoMap;
          GridVoxel[i][j][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if( j != 0){
          GridVoxel[i][j-1][k].Edge_Points[4] = NbPointIsoMap;
          GridVoxel[i][j-1][k].NbEdgePoint += 1;
}
if(k != 0){
          GridVoxel[i][j][k-1].Edge_Points[2]   = NbPointIsoMap;
          GridVoxel[i][j][k-1].NbEdgePoint += 1;
}
if(j != 0 && k != 0) {
          GridVoxel[i][j-1][k-1].Edge_Points[6] = NbPointIsoMap;
          GridVoxel[i][j-1][k-1].NbEdgePoint += 1;
}

if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;

          NbPointIsoMap++;


        }
} /// End of if( i != (nb_ligne-1))...

// Third Case P(i)(j)(k+1)
if( k != (nb_depth -1)){
        IsoValue_2 = GridVoxel[i][j][k+1].Value;
          // Edge Point computation and  save in IsoPointMap
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][j][k].PositionX + factor * (GridVoxel[i][j][k+1].PositionX - GridVoxel[i][j][k].PositionX);

          vals[1] = GridVoxel[i][j][k].PositionY + factor * (GridVoxel[i][j][k+1].PositionY - GridVoxel[i][j][k].PositionY);

          vals[2] = GridVoxel[i][j][k].PositionZ + factor * (GridVoxel[i][j][k+1].PositionZ - GridVoxel[i][j][k].PositionZ);



IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][j][k].Edge_Points[3] = NbPointIsoMap;
          GridVoxel[i][j][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if(i !=0){
          GridVoxel[i-1][j][k].Edge_Points[1]   = NbPointIsoMap;
          GridVoxel[i-1][j][k].NbEdgePoint += 1;
}
if( j!=0){
          GridVoxel[i][j-1][k].Edge_Points[7]   = NbPointIsoMap;
          GridVoxel[i][j-1][k].NbEdgePoint += 1;
}
if(i != 0 && j !=0){
          GridVoxel[i-1][j-1][k].Edge_Points[5] = NbPointIsoMap;
          GridVoxel[i-1][j-1][k].NbEdgePoint += 1;
}

if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;
          NbPointIsoMap++;

        }
     } /// End of if (k != nb_depth)...
}





/// 5) Case k = 0

k =0;

     for(i=0; i < nb_ligne; i++)
      for(j=0; j < nb_colon; j++)
 {

        IsoValue_1 = GridVoxel[i][j][0].Value;
// First Case P(i+1)(j)(k)
if(i != (nb_ligne -1)){
        IsoValue_2 = GridVoxel[i+1][j][0].Value;
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {

          // Edge Point computation and  save in IsoPointMap
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][j][0].PositionX + factor * (GridVoxel[i+1][j][0].PositionX - GridVoxel[i][j][0].PositionX);

          vals[1] = GridVoxel[i][j][0].PositionY + factor * (GridVoxel[i+1][j][0].PositionY - GridVoxel[i][j][0].PositionY);

          vals[2] = GridVoxel[i][j][0].PositionZ + factor * (GridVoxel[i+1][j][0].PositionZ - GridVoxel[i][j][0].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][j][0].Edge_Points[0] = NbPointIsoMap;
          GridVoxel[i][j][0].NbEdgePoint += 1;

          // The same Point is used in one other Voxel
 if(j !=0){         GridVoxel[i][j-1][0].Edge_Points[4] = NbPointIsoMap;
                    GridVoxel[i][j-1][0].NbEdgePoint += 1;
}

if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;
          NbPointIsoMap++;


        }
} /// End of if(i != (nb_ligne -1))

// Second Case P(i)(j+1)(k)
if(j != nb_colon -1) {
        IsoValue_2 = GridVoxel[i][j+1][0].Value;
          // Edge Point computation and  save in IsoPointMap
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][j][0].PositionX + factor * (GridVoxel[i][j+1][0].PositionX - GridVoxel[i][j][0].PositionX);

          vals[1] = GridVoxel[i][j][0].PositionY + factor * (GridVoxel[i][j+1][0].PositionY - GridVoxel[i][j][0].PositionY);

          vals[2] = GridVoxel[i][j][0].PositionZ + factor * (GridVoxel[i][j+1][0].PositionZ - GridVoxel[i][j][0].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][j][0].Edge_Points[8] = NbPointIsoMap;
          GridVoxel[i][j][0].NbEdgePoint += 1;

          // The same Point is used in one other Voxels
if ( i !=0 ) {
          GridVoxel[i-1][j][0].Edge_Points[9]    = NbPointIsoMap;
          GridVoxel[i-1][j][0].NbEdgePoint += 1;
}

if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;
          NbPointIsoMap++;

        }
}/// End of if(j != nb_colon -1)...

// Third Case P(i)(j)(k+1)

        IsoValue_2 = GridVoxel[i][j][1].Value;
          // Edge Point computation and  save in IsoPointMap
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][j][0].PositionX + factor * (GridVoxel[i][j][1].PositionX - GridVoxel[i][j][0].PositionX);

          vals[1] = GridVoxel[i][j][0].PositionY + factor * (GridVoxel[i][j][1].PositionY - GridVoxel[i][j][0].PositionY);

          vals[2] = GridVoxel[i][j][0].PositionZ + factor * (GridVoxel[i][j][1].PositionZ - GridVoxel[i][j][0].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][j][0].Edge_Points[3] = NbPointIsoMap;
          GridVoxel[i][j][0].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if ( i !=0 ) {
          GridVoxel[i-1][j][0].Edge_Points[1]   = NbPointIsoMap;
          GridVoxel[i-1][j][0].NbEdgePoint += 1;
}
if (j != 0 ) {
          GridVoxel[i][j-1][0].Edge_Points[7]   = NbPointIsoMap;
          GridVoxel[i][j-1][0].NbEdgePoint += 1;
}
if ( i !=0 && j != 0 ) {
          GridVoxel[i-1][j-1][0].Edge_Points[5] = NbPointIsoMap;
          GridVoxel[i-1][j-1][0].NbEdgePoint += 1;
}

if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;
          NbPointIsoMap++;

        }
     }




/// 6) Case k = nb_depth -1

k = nb_depth -1;

     for(i=0; i < nb_ligne; i++)
      for(j=0; j < nb_colon; j++)
 {

        IsoValue_1 = GridVoxel[i][j][k].Value;


// First Case P(i+1)(j)(k)
if( i != (nb_ligne -1) ){
        IsoValue_2 = GridVoxel[i+1][j][k].Value;
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {

          // Edge Point computation and  save in IsoPointMap
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][j][k].PositionX + factor * (GridVoxel[i+1][j][k].PositionX - GridVoxel[i][j][k].PositionX);

          vals[1] = GridVoxel[i][j][k].PositionY + factor * (GridVoxel[i+1][j][k].PositionY - GridVoxel[i][j][k].PositionY);

          vals[2] = GridVoxel[i][j][k].PositionZ + factor * (GridVoxel[i+1][j][k].PositionZ - GridVoxel[i][j][k].PositionZ);


IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][j][k].Edge_Points[0] = NbPointIsoMap;
          GridVoxel[i][j][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if(j !=0) {
          GridVoxel[i][j-1][k].Edge_Points[4] = NbPointIsoMap;
          GridVoxel[i][j-1][k].NbEdgePoint += 1;
}
if(k !=0){
          GridVoxel[i][j][k-1].Edge_Points[2]   = NbPointIsoMap;
          GridVoxel[i][j][k-1].NbEdgePoint += 1;
}
if(j !=0 && k != 0) {
          GridVoxel[i][j-1][k-1].Edge_Points[6] = NbPointIsoMap;
          GridVoxel[i][j-1][k-1].NbEdgePoint += 1;
}

if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;
          NbPointIsoMap++;


        }
} /// End of if(i != nb_ligne-1)...

// Second Case P(i)(j+1)(k)
if( j != (nb_colon -1) ){
        IsoValue_2 = GridVoxel[i][j+1][k].Value;
          // Edge Point computation and  save in IsoPointMap
         if(IsoValue_1 * IsoValue_2 <= 0 && (rapport=IsoValue_2 - IsoValue_1)!=0) {
          factor = (IsoValue - IsoValue_1)/rapport;
          index = NbPointIsoMap *3;

          vals[0] = GridVoxel[i][j][k].PositionX + factor * (GridVoxel[i][j+1][k].PositionX - GridVoxel[i][j][k].PositionX);

          vals[1] = GridVoxel[i][j][k].PositionY + factor * (GridVoxel[i][j+1][k].PositionY - GridVoxel[i][j][k].PositionY);

          vals[2] = GridVoxel[i][j][k].PositionZ + factor * (GridVoxel[i][j+1][k].PositionZ - GridVoxel[i][j][k].PositionZ);
///

IsoPointMapOriginal[index  ] = vals[0];
IsoPointMapOriginal[index+1] = vals[1];
IsoPointMapOriginal[index+2] = vals[2];

          // save The reference to this point
          GridVoxel[i][j][k].Edge_Points[8] = NbPointIsoMap;
          GridVoxel[i][j][k].NbEdgePoint += 1;

          // The same Point is used in three other Voxels
if( i !=0 ){
          GridVoxel[i-1][j][k].Edge_Points[9]    = NbPointIsoMap;
          GridVoxel[i-1][j][k].NbEdgePoint += 1;
}
if( k !=0 ){
          GridVoxel[i][j][k-1].Edge_Points[11]   = NbPointIsoMap;
          GridVoxel[i][j][k-1].NbEdgePoint += 1;
}
if( i !=0 && k !=0 ){
          GridVoxel[i-1][j][k-1].Edge_Points[10] = NbPointIsoMap;
          GridVoxel[i-1][j][k-1].NbEdgePoint += 1;
}

if (IsoConditionRequired != 1) WichPointVeryCond[NbPointIsoMap] = 1;
else (IsoConditionParser.Eval(vals) == 1) ? WichPointVeryCond[NbPointIsoMap] = 1 : WichPointVeryCond[NbPointIsoMap] = 0;
          NbPointIsoMap++;

        }
} /// End of if( j != (nb_colon -1) )...



     }

///+++++++++ Here we have to take care of the imposed condition++++///




/// We generate the points af the 3D axes by using the limits of the Cube.
/// Axes are centered on the original point O(0,0,0):
double stepx, stepy, stepz, center_x, center_y, center_z;;
int ThreeTimesI;
if(DrawAxe_Ok == 1) {




MINX = 999999999;
MINY = 999999999;
MINZ = 999999999;

MAXX =-999999999;
MAXY =-999999999;
MAXZ =-999999999;

 for (i=0; i < NbPointIsoMap   ; i++){
 ThreeTimesI = 3*i;
          if(MINX > IsoPointMapOriginal[ThreeTimesI  ] ) MINX = IsoPointMapOriginal[ThreeTimesI  ] ;

     else if(MINY > IsoPointMapOriginal[ThreeTimesI+1] ) MINY = IsoPointMapOriginal[ThreeTimesI+1] ;

     else if(MINZ > IsoPointMapOriginal[ThreeTimesI+2] ) MINZ = IsoPointMapOriginal[ThreeTimesI+2] ;

     else if(MAXX < IsoPointMapOriginal[ThreeTimesI  ] ) MAXX = IsoPointMapOriginal[ThreeTimesI  ] ;

     else if(MAXY < IsoPointMapOriginal[ThreeTimesI+1] ) MAXY = IsoPointMapOriginal[ThreeTimesI+1] ;

     else if(MAXZ < IsoPointMapOriginal[ThreeTimesI+2] ) MAXZ = IsoPointMapOriginal[ThreeTimesI+2] ;
                                  }


  DIFX = MAXX - MINX ;
  DIFY = MAXY - MINY ;
  DIFZ = MAXZ - MINZ ;







stepx = (2./3.)*DIFX*axe_size/40.;
stepy = (2./3.)*DIFY*axe_size/40.;
stepz = (2./3.)*DIFZ*axe_size/40.;

if(axe_center == -1) {
 center_x = (MAXX + MINX)/2.;
 center_y = (MAXY + MINY)/2.;
 center_z = (MAXZ + MINZ)/2.;
}
else center_x = center_y = center_z = 0;


for(i = 0; i <40; i++) {
ThreeTimesI = 3*i;
AxeArrayOriginal[0][ThreeTimesI  ] = i*stepx + center_x;
AxeArrayOriginal[0][ThreeTimesI+1] = center_y;
AxeArrayOriginal[0][ThreeTimesI+2] = center_z;

AxeArrayOriginal[1][ThreeTimesI  ] = center_x;
AxeArrayOriginal[1][ThreeTimesI+1] = i*stepy + center_y;
AxeArrayOriginal[1][ThreeTimesI+2] = center_z;

AxeArrayOriginal[2][ThreeTimesI  ] = center_x;
AxeArrayOriginal[2][ThreeTimesI+1] = center_y;
AxeArrayOriginal[2][ThreeTimesI+2] = i*stepz + center_z;
}


/// Here we add two points in every axe for the drawing of the arrow...

///X Axe :
AxeArrayOriginal[0][40*3  ] = AxeArrayOriginal[0][38*3  ];
AxeArrayOriginal[0][40*3+1] = AxeArrayOriginal[0][38*3+1] + 2*stepy ;
AxeArrayOriginal[0][40*3+2] = AxeArrayOriginal[0][38*3+2];

AxeArrayOriginal[0][41*3  ] = AxeArrayOriginal[0][38*3  ];
AxeArrayOriginal[0][41*3+1] = AxeArrayOriginal[0][38*3+1] - 2*stepy ;
AxeArrayOriginal[0][41*3+2] = AxeArrayOriginal[0][38*3+2];

///Y Axe :
AxeArrayOriginal[1][40*3  ] = AxeArrayOriginal[1][38*3  ] + 2*stepx;
AxeArrayOriginal[1][40*3+1] = AxeArrayOriginal[1][38*3+1];
AxeArrayOriginal[1][40*3+2] = AxeArrayOriginal[1][38*3+2];

AxeArrayOriginal[1][41*3  ] = AxeArrayOriginal[1][38*3  ] - 2*stepx;
AxeArrayOriginal[1][41*3+1] = AxeArrayOriginal[1][38*3+1];
AxeArrayOriginal[1][41*3+2] = AxeArrayOriginal[1][38*3+2];
///Z Axe :
AxeArrayOriginal[2][40*3  ] = AxeArrayOriginal[2][38*3  ] + 2*stepx;
AxeArrayOriginal[2][40*3+1] = AxeArrayOriginal[2][38*3+1];
AxeArrayOriginal[2][40*3+2] = AxeArrayOriginal[2][38*3+2];

AxeArrayOriginal[2][41*3  ] = AxeArrayOriginal[2][38*3  ] - 2*stepx;
AxeArrayOriginal[2][41*3+1] = AxeArrayOriginal[2][38*3+1];
AxeArrayOriginal[2][41*3+2] = AxeArrayOriginal[2][38*3+2];


} /// End of if(DrawAxe_Ok == 1)...



///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///+++++++++++++++++++ Normals Calculation : +++++++++++++++++++++///



   };


///+++++++++++++++++++++++++++++++++++++++++++++++++++++///
   void Iso3D::SignatureComputation(){

     for(i=0; i < nb_ligne; i++)
      for(j=0; j < nb_colon; j++)
       for(k=0; k < nb_depth; k++)
        /*if (GridVoxel[i][j][k].NbEdgePoint != 0)*/{
///GridVoxel[i][j][k].Signature =0; /// Done now in
if(GridVoxel[i  ][j  ][k  ].Value <= 0) GridVoxel[i][j][k].Signature +=1;

if(i != (nb_ligne-1))
if(GridVoxel[i+1][j  ][k  ].Value <= 0) GridVoxel[i][j][k].Signature +=2;

if(i != (nb_ligne-1) && k != (nb_depth-1))
if(GridVoxel[i+1][j  ][k+1].Value <= 0) GridVoxel[i][j][k].Signature +=4;

if(k != (nb_depth-1))
if(GridVoxel[i  ][j  ][k+1].Value <= 0) GridVoxel[i][j][k].Signature +=8;

if(j != (nb_colon-1))
if(GridVoxel[i  ][j+1][k  ].Value <= 0) GridVoxel[i][j][k].Signature +=16;

if(i != (nb_ligne-1) && j != (nb_colon-1))
if(GridVoxel[i+1][j+1][k  ].Value <= 0) GridVoxel[i][j][k].Signature +=32;

if(i != (nb_ligne-1) && j != (nb_colon-1) && k != (nb_depth-1))
if(GridVoxel[i+1][j+1][k+1].Value <= 0) GridVoxel[i][j][k].Signature +=64;

if(j != (nb_colon-1) && k != (nb_depth-1))
if(GridVoxel[i  ][j+1][k+1].Value <= 0) GridVoxel[i][j][k].Signature +=128;
        } // End if(Grid...
   }

///++++++++++++++++++++ OutPut The IsoSurface +++++++++++++++++++++++

   void Iso3D::SaveIsoMap() {
     int IndexFirstPoint, IndexSecondPoint, IndexThirdPoint, ThreeTimesI,
         ValIndex;
     double z_tmp, scalar;





   for (i=0; i < NbPointIsoMap ; i++){
        ThreeTimesI = 3*i;
        IsoNormMapTransfrm[ThreeTimesI  ] = 0;
        IsoNormMapTransfrm[ThreeTimesI+1] = 0;
        IsoNormMapTransfrm[ThreeTimesI+2] = 0;
}


for(i = 0; i<NbTriangleIsoSurface; ++i) {

 ThreeTimesI   = i*3;

IndexFirstPoint  = 3*IsoSurfaceTriangleListe[ThreeTimesI  ];
IndexSecondPoint = 3*IsoSurfaceTriangleListe[ThreeTimesI+1];
IndexThirdPoint  = 3*IsoSurfaceTriangleListe[ThreeTimesI+2];



IsoNormMapTransfrm[IndexFirstPoint  ] += NormTransfrm[ThreeTimesI  ];
IsoNormMapTransfrm[IndexFirstPoint+1] += NormTransfrm[ThreeTimesI+1];
IsoNormMapTransfrm[IndexFirstPoint+2] += NormTransfrm[ThreeTimesI+2];

IsoNormMapTransfrm[IndexSecondPoint  ] += NormTransfrm[ThreeTimesI  ];
IsoNormMapTransfrm[IndexSecondPoint+1] += NormTransfrm[ThreeTimesI+1];
IsoNormMapTransfrm[IndexSecondPoint+2] += NormTransfrm[ThreeTimesI+2];

IsoNormMapTransfrm[IndexThirdPoint  ] += NormTransfrm[ThreeTimesI  ];
IsoNormMapTransfrm[IndexThirdPoint+1] += NormTransfrm[ThreeTimesI+1];
IsoNormMapTransfrm[IndexThirdPoint+2] += NormTransfrm[ThreeTimesI+2];

}


/// Normalisation of theses resulting normales
 for (i=0; i < NbPointIsoMap   ; i++){
 ThreeTimesI = 3*i;

scalar = (double)sqrt((IsoNormMapTransfrm[ThreeTimesI  ]*IsoNormMapTransfrm[ThreeTimesI  ]) +
                      (IsoNormMapTransfrm[ThreeTimesI+1]*IsoNormMapTransfrm[ThreeTimesI+1]) +
                      (IsoNormMapTransfrm[ThreeTimesI+2]*IsoNormMapTransfrm[ThreeTimesI+2]));

if(scalar < 0.000000001)  scalar  = 0.000000001;
IsoNormMapTransfrm[ThreeTimesI  ] /= scalar;
IsoNormMapTransfrm[ThreeTimesI+1] /= scalar;
IsoNormMapTransfrm[ThreeTimesI+2] /= scalar;



}



NbTriangleUsed = 0;
for ( i=0; i < NbTriangleIsoSurface ; ++i) {

ThreeTimesI = 3*i;
IndexFirstPoint  = 3*IsoSurfaceTriangleListe[ThreeTimesI  ];
IndexSecondPoint = 3*IsoSurfaceTriangleListe[ThreeTimesI+1];
IndexThirdPoint  = 3*IsoSurfaceTriangleListe[ThreeTimesI+2];

z_tmp = (IsoPointMapTransfrm[IndexFirstPoint +2]+
         IsoPointMapTransfrm[IndexSecondPoint+2]+
         IsoPointMapTransfrm[IndexThirdPoint +2])/3;
if(z_tmp < 460 )
{
ValIndex = 18*NbTriangleUsed;
/// Save the 3 point of the vector
 FileOutput[ValIndex  ] = IsoPointMapTransfrm[IndexFirstPoint  ];
 FileOutput[ValIndex+1] = IsoPointMapTransfrm[IndexFirstPoint+1];
 FileOutput[ValIndex+2] = IsoPointMapTransfrm[IndexFirstPoint+2];

 FileOutput[ValIndex+3] = IsoPointMapTransfrm[IndexSecondPoint  ];
 FileOutput[ValIndex+4] = IsoPointMapTransfrm[IndexSecondPoint+1];
 FileOutput[ValIndex+5] = IsoPointMapTransfrm[IndexSecondPoint+2];

 FileOutput[ValIndex+6] = IsoPointMapTransfrm[IndexThirdPoint  ];
 FileOutput[ValIndex+7] = IsoPointMapTransfrm[IndexThirdPoint+1];
 FileOutput[ValIndex+8] = IsoPointMapTransfrm[IndexThirdPoint+2];

/// Save the normal vector
 FileOutput[ValIndex+9 ] = -IsoNormMapTransfrm[IndexFirstPoint  ];
 FileOutput[ValIndex+10] = -IsoNormMapTransfrm[IndexFirstPoint+1];
 FileOutput[ValIndex+11] = -IsoNormMapTransfrm[IndexFirstPoint+2];

 FileOutput[ValIndex+12] = -IsoNormMapTransfrm[IndexSecondPoint  ];
 FileOutput[ValIndex+13] = -IsoNormMapTransfrm[IndexSecondPoint+1];
 FileOutput[ValIndex+14] = -IsoNormMapTransfrm[IndexSecondPoint+2];

 FileOutput[ValIndex+15] = -IsoNormMapTransfrm[IndexThirdPoint  ];
 FileOutput[ValIndex+16] = -IsoNormMapTransfrm[IndexThirdPoint+1];
 FileOutput[ValIndex+17] = -IsoNormMapTransfrm[IndexThirdPoint+2];

NbTriangleUsed++;

}
}
}

///++++++++++++++++++++ OutPut The IsoSurface +++++++++++++++++++++++

   void Iso3D::SaveIsoMapUnifColor() {
     int ThreeTimesI;
     double pt1_x, pt1_y, pt1_z,
            pt2_x, pt2_y, pt2_z,
            XStep, YStep, ZStep,
            tp1, tp2, tp3,
            X_Val, Y_Val, Z_Val, ray;
     double vals[3];


     XStep = fabs((X_Start - X_End)/(100*(nb_ligne-1)));
     YStep = fabs((Y_Start - Y_End)/(100*(nb_colon-1)));
     ZStep = fabs((Z_Start - Z_End)/(100*(nb_depth-1)));


   for (i=0; i < NbPointIsoMap ; i++){
        ThreeTimesI = 3*i;

/// Normal at this Point :

        X_Val = IsoPointMapOriginal[ThreeTimesI  ];
        Y_Val = IsoPointMapOriginal[ThreeTimesI+1];
        Z_Val = IsoPointMapOriginal[ThreeTimesI+2];

        vals[0] = X_Val + XStep;
        vals[1] = Y_Val;
        vals[2] = Z_Val;
        pt1_x = ImplicitFunctionParser.Eval(vals);
        vals[0] = X_Val - XStep;
        pt2_x = ImplicitFunctionParser.Eval(vals);
IsoNormMapOriginal[ThreeTimesI  ] = pt1_x - pt2_x;

        vals[0] = X_Val;
        vals[1] = Y_Val + YStep;
        vals[2] = Z_Val;
        pt1_y = ImplicitFunctionParser.Eval(vals);
        vals[1] = Y_Val - YStep;
        pt2_y = ImplicitFunctionParser.Eval(vals);
IsoNormMapOriginal[ThreeTimesI+1] = pt1_y - pt2_y;

        vals[0] = X_Val;
        vals[1] = Y_Val;
        vals[2] = Z_Val + ZStep;
        pt1_z = ImplicitFunctionParser.Eval(vals);
        vals[2] = Z_Val - ZStep;
        pt2_z = ImplicitFunctionParser.Eval(vals);
IsoNormMapOriginal[ThreeTimesI+2] = pt1_z - pt2_z;

ray = sqrt(IsoNormMapOriginal[ThreeTimesI  ]*IsoNormMapOriginal[ThreeTimesI  ] +
      IsoNormMapOriginal[ThreeTimesI+1]*IsoNormMapOriginal[ThreeTimesI+1] +
      IsoNormMapOriginal[ThreeTimesI+2]*IsoNormMapOriginal[ThreeTimesI+2]);

IsoNormMapOriginal[ThreeTimesI  ] /= ray;
IsoNormMapOriginal[ThreeTimesI+1] /= ray;
IsoNormMapOriginal[ThreeTimesI+2] /= ray;
}




///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
/// Now, we transform the Normal vectors :

   for (i=0; i < NbPointIsoMap ; i++){
        ThreeTimesI = 3*i;
        tp1 = IsoNormMapOriginal[ThreeTimesI    ];
        tp2 = IsoNormMapOriginal[ThreeTimesI + 1];
        tp3 = IsoNormMapOriginal[ThreeTimesI + 2];
IsoNormMapTransfrm[ThreeTimesI  ] = MatRotSave.xx*tp1 + MatRotSave.xy*tp2 +MatRotSave.xz*tp3 + MatRotSave.xo;
IsoNormMapTransfrm[ThreeTimesI+1] = MatRotSave.yx*tp1 + MatRotSave.yy*tp2 +MatRotSave.yz*tp3 + MatRotSave.yo;
IsoNormMapTransfrm[ThreeTimesI+2] = MatRotSave.zx*tp1 + MatRotSave.zy*tp2 +MatRotSave.zz*tp3 + MatRotSave.zo;
                                      }
}

///++++++++++++++++++++ Draw The IsoSurface +++++++++++++++++++++++

void Iso3D::DrawIsoMap(QPainter & g) {
     int CurrentTriangle, tmp, nb_triangle, ThreeTimesI /*, TriangleIndex*/;
     double VectorScalar, cosinus, z_tmp, coefficient;
     vector<IsoTriangle *>::iterator itVectorData;
    int IndexFirstPoint, IndexSecondPoint, IndexThirdPoint;


/// memory reservation for 10.000 IsoTriangles
VectorIsoTriangle.reserve(10000);


/// Projection of the Iso Surface :

    for ( i=0; i < NbPointIsoMap; ++i) {

ThreeTimesI = 3*i;

coefficient = D/(IsoPointMapTransfrm[ThreeTimesI + 2]-Oprime[2]);
IsoPointMapProjectd[ThreeTimesI  ] = coefficient*IsoPointMapTransfrm[ThreeTimesI  ]  + demi_hauteur;
IsoPointMapProjectd[ThreeTimesI+1] = coefficient*IsoPointMapTransfrm[ThreeTimesI+1]  + demi_largeur;
IsoPointMapProjectd[ThreeTimesI+2] = IsoPointMapTransfrm[ThreeTimesI+2];

                                        }



///+++++++++++++++++++++++++++++ New Stuff for Axes ++++++++++++++++++++++++++++///
/// Projection of the Iso Axes :
    for ( i=0; i < 42; ++i) {
ThreeTimesI = 3*i;

/// X Axe :
coefficient = D/(AxeArrayTransfrm[0][ThreeTimesI + 2]-Oprime[2]);
AxeArrayProjectd[0][ThreeTimesI  ] = coefficient*AxeArrayTransfrm[0][ThreeTimesI  ]  + demi_hauteur;
AxeArrayProjectd[0][ThreeTimesI+1] = coefficient*AxeArrayTransfrm[0][ThreeTimesI+1]  + demi_largeur;
AxeArrayProjectd[0][ThreeTimesI+2] =             AxeArrayTransfrm[0][ThreeTimesI+2];

/// y Axe :
coefficient = D/(AxeArrayTransfrm[1][ThreeTimesI + 2]-Oprime[2]);
AxeArrayProjectd[1][ThreeTimesI  ] = coefficient*AxeArrayTransfrm[1][ThreeTimesI  ]  + demi_hauteur;
AxeArrayProjectd[1][ThreeTimesI+1] = coefficient*AxeArrayTransfrm[1][ThreeTimesI+1]  + demi_largeur;
AxeArrayProjectd[1][ThreeTimesI+2] =             AxeArrayTransfrm[1][ThreeTimesI+2];

/// Z Axe :
coefficient = D/(AxeArrayTransfrm[2][ThreeTimesI + 2]-Oprime[2]);
AxeArrayProjectd[2][ThreeTimesI  ] = coefficient*AxeArrayTransfrm[2][ThreeTimesI  ]  + demi_hauteur;
AxeArrayProjectd[2][ThreeTimesI+1] = coefficient*AxeArrayTransfrm[2][ThreeTimesI+1]  + demi_largeur;
AxeArrayProjectd[2][ThreeTimesI+2] =             AxeArrayTransfrm[2][ThreeTimesI+2];

                                        }
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///






/// Claculation of the Cosinus

NbTriangleUsed = 0;
for ( i=0; i < NbTriangleIsoSurface ; ++i) {

ThreeTimesI = 3*i;
IndexFirstPoint  = 3*IsoSurfaceTriangleListe[ThreeTimesI  ];
IndexSecondPoint = 3*IsoSurfaceTriangleListe[ThreeTimesI+1];
IndexThirdPoint  = 3*IsoSurfaceTriangleListe[ThreeTimesI+2];

z_tmp = (IsoPointMapTransfrm[IndexFirstPoint +2]+
         IsoPointMapTransfrm[IndexSecondPoint+2]+
         IsoPointMapTransfrm[IndexThirdPoint +2])/3;
if(z_tmp < 460 )
{

VectorScalar = (double)sqrt(
(Oprime[0]- IsoPointMapTransfrm[IndexFirstPoint  ])*
(Oprime[0]- IsoPointMapTransfrm[IndexFirstPoint  ]) +
(Oprime[1]- IsoPointMapTransfrm[IndexFirstPoint+1])*
(Oprime[1]- IsoPointMapTransfrm[IndexFirstPoint+1]) +
(Oprime[2]- IsoPointMapTransfrm[IndexFirstPoint+2])*
(Oprime[2]- IsoPointMapTransfrm[IndexFirstPoint+2]));

/// reduce the normals to the Unit vector

Obser[0]=(Oprime[0]-IsoPointMapTransfrm[IndexFirstPoint  ])/VectorScalar;
Obser[1]=(Oprime[1]-IsoPointMapTransfrm[IndexFirstPoint+1])/VectorScalar;
Obser[2]=(Oprime[2]-IsoPointMapTransfrm[IndexFirstPoint+2])/VectorScalar;



/// Cosinus computation:

cosinus=
(Obser[0]*NormTransfrm[ThreeTimesI  ] +
 Obser[1]*NormTransfrm[ThreeTimesI+1] +
 Obser[2]*NormTransfrm[ThreeTimesI+2] );

/*
/// This cosinus works also but it's not as accurate as the one before
cosinus=
(Obser[0]*(IsoNormMapTransfrm[IndexFirstPoint  ]+IsoNormMapTransfrm[IndexSecondPoint  ]+IsoNormMapTransfrm[IndexThirdPoint  ])/3 +
 Obser[1]*(IsoNormMapTransfrm[IndexFirstPoint+1]+IsoNormMapTransfrm[IndexSecondPoint+1]+IsoNormMapTransfrm[IndexThirdPoint+1])/3 +
 Obser[2]*(IsoNormMapTransfrm[IndexFirstPoint+2]+IsoNormMapTransfrm[IndexSecondPoint+2]+IsoNormMapTransfrm[IndexThirdPoint+2])/3 );
*/
/// Just in case...must be changed
if(cosinus >  1) cosinus = 1;
if(cosinus < -1) cosinus =-1;

///                      TRIAGE des POLYGONES
///========== triage des polygone selon leurs veleurs Z et creation d'une liste
///========== de polygones TRIES qu'on utilisera apres pour l'affichage final.

CurrentTriangle = i;
/*
//TriangleIndex = 3*IsoSurfaceTriangleListe[ThreeTimesI  ];
tableaureferences[CurrentTriangle]->setPoint(0,
  (int)(IsoPointMapProjectd[IndexFirstPoint  ]  ),
  (int)(IsoPointMapProjectd[IndexFirstPoint+1]));

//TriangleIndex = 3*IsoSurfaceTriangleListe[ThreeTimesI+1];
tableaureferences[CurrentTriangle]->setPoint(1,
  (int)(IsoPointMapProjectd[IndexSecondPoint  ]  ),
  (int)(IsoPointMapProjectd[IndexSecondPoint+1]  ));

tableaureferences[CurrentTriangle]->setPoint(2,
  (int)(IsoPointMapProjectd[IndexThirdPoint  ]  ),
  (int)(IsoPointMapProjectd[IndexThirdPoint+1]  ));
*/
tableaureferences[CurrentTriangle]->putPoints(0, 3,
(int)(IsoPointMapProjectd[IndexFirstPoint  ]),
(int)(IsoPointMapProjectd[IndexFirstPoint+1]),
(int)(IsoPointMapProjectd[IndexSecondPoint  ]),
(int)(IsoPointMapProjectd[IndexSecondPoint+1]),
(int)(IsoPointMapProjectd[IndexThirdPoint  ]),
(int)(IsoPointMapProjectd[IndexThirdPoint+1]));



///=============  Triage des Triangles selon la valeurs de leurs profondeurs Z ====

 itVectorData = VectorIsoTriangle.begin();
 tmp=0;
 nb_triangle = VectorIsoTriangle.size();

if( nb_triangle > 0)
{
           while( tmp < nb_triangle) {
               if( z_tmp < VectorIsoTriangle[tmp]->valeur_z )
  {
  tableau[CurrentTriangle].pl = tableaureferences[CurrentTriangle];
  tableau[CurrentTriangle].valeur_z = z_tmp;
  tableau[CurrentTriangle].valeur_cos = cosinus;
  tableau[CurrentTriangle].TypeCND = TypeIsoSurfaceTriangleListeCND[i];

  VectorIsoTriangle.insert(itVectorData, &tableau[CurrentTriangle]);
  tmp = nb_triangle ;
  }

  else   {
      if( tmp==(nb_triangle -1)) {

  tableau[CurrentTriangle].pl = tableaureferences[CurrentTriangle];
  tableau[CurrentTriangle].valeur_z = z_tmp;
  tableau[CurrentTriangle].valeur_cos = cosinus;
  tableau[CurrentTriangle].TypeCND = TypeIsoSurfaceTriangleListeCND[i];

  VectorIsoTriangle.push_back(&tableau[CurrentTriangle]);
  tmp = nb_triangle ;
                             }
      else    {
      tmp++ ;
      itVectorData++;
      }
                      }
                      }
}
else {
  tableau[CurrentTriangle].pl = tableaureferences[CurrentTriangle];
  tableau[CurrentTriangle].valeur_z =  z_tmp;
  tableau[CurrentTriangle].valeur_cos = cosinus;
  tableau[CurrentTriangle].TypeCND = TypeIsoSurfaceTriangleListeCND[i];

  VectorIsoTriangle.push_back(&tableau[CurrentTriangle]);
}

} /// End of if(z_tmp < 460 || clipping == -1)
} /// End of for ( i=0; i < NbTriangleIsoSurface ...




///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
/// Now we add the axe to the Iso Surface...











if(DrawAxe_Ok == 1) {
for(j = 0; j <3; j++)
for ( i=0; i < 38 ; ++i) {

ThreeTimesI = 3*i;

z_tmp = (AxeArrayTransfrm[j][i*3 + 2]+
         AxeArrayTransfrm[j][(i+1)*3 +2])/2;
if(z_tmp < 460 )
{


/// All 3D Axes are placed at the end of of the 'tableaureferences' Array

CurrentTriangle = (j*50) + i + 8000;

tableaureferences[CurrentTriangle]->putPoints(0, 3,
(int)(AxeArrayProjectd[j][i*3      ]),
(int)(AxeArrayProjectd[j][i*3    +1]),
(int)(AxeArrayProjectd[j][(i+1)*3  ]),
(int)(AxeArrayProjectd[j][(i+1)*3+1]),
(int)(AxeArrayProjectd[j][(i+1)*3  ]),
(int)(AxeArrayProjectd[j][(i+1)*3+1]));



///=============  Triage des Triangles selon la valeurs de leurs profondeurs Z ====

 itVectorData = VectorIsoTriangle.begin();
 tmp=0;
 nb_triangle = VectorIsoTriangle.size();

if( nb_triangle > 0)
{
           while( tmp < nb_triangle) {
               if( z_tmp < VectorIsoTriangle[tmp]->valeur_z )
  {
  tableau[CurrentTriangle].pl = tableaureferences[CurrentTriangle];
  tableau[CurrentTriangle].valeur_z = z_tmp;
  //tableau[CurrentTriangle].valeur_cos = 0.000333777 + (j*0.111);
  tableau[CurrentTriangle].TypeCND = 10+j;

  VectorIsoTriangle.insert(itVectorData, &tableau[CurrentTriangle]);
  tmp = nb_triangle ;
  }

  else   {
      if( tmp==(nb_triangle -1)) {

  tableau[CurrentTriangle].pl = tableaureferences[CurrentTriangle];
  tableau[CurrentTriangle].valeur_z = z_tmp;
  //tableau[CurrentTriangle].valeur_cos = 0.000333777 + (j*0.111);
  tableau[CurrentTriangle].TypeCND = 10+j;

  VectorIsoTriangle.push_back(&tableau[CurrentTriangle]);
  tmp = nb_triangle ;
                             }
      else    {
      tmp++ ;
      itVectorData++;
      }
                      }
                      }
}
else {
  tableau[CurrentTriangle].pl = tableaureferences[CurrentTriangle];
  tableau[CurrentTriangle].valeur_z =  z_tmp;
  //tableau[CurrentTriangle].valeur_cos = 0.000333777 + (j*0.111);
  tableau[CurrentTriangle].TypeCND = 10+j;

  VectorIsoTriangle.push_back(&tableau[CurrentTriangle]);
}

} /// End of if (z_tmp < 460)
}

///++++++++++++++++++++++++++++++++++++++++++++++++++///

/// Now we add the arrows for the 3D axes :

for(j = 0; j <3; j++) {


z_tmp = (AxeArrayTransfrm[j][39*3+2]+
         AxeArrayTransfrm[j][40*3+2]+
         AxeArrayTransfrm[j][41*3+2])/3;
if(z_tmp < 460 )
{


/// All 3D Axes are placed at the end of of the 'tableaureferences' Array

CurrentTriangle = (j*50) + 39 + 8000;

tableaureferences[CurrentTriangle]->putPoints(0, 3,
(int)(AxeArrayProjectd[j][39*3  ]),
(int)(AxeArrayProjectd[j][39*3+1]),
(int)(AxeArrayProjectd[j][40*3  ]),
(int)(AxeArrayProjectd[j][40*3+1]),
(int)(AxeArrayProjectd[j][41*3  ]),
(int)(AxeArrayProjectd[j][41*3+1]));



///=============  Triage des Triangles selon la valeurs de leurs profondeurs Z ====

 itVectorData = VectorIsoTriangle.begin();
 tmp=0;
 nb_triangle = VectorIsoTriangle.size();

if( nb_triangle > 0)
{
           while( tmp < nb_triangle) {
               if( z_tmp < VectorIsoTriangle[tmp]->valeur_z )
  {
  tableau[CurrentTriangle].pl = tableaureferences[CurrentTriangle];
  tableau[CurrentTriangle].valeur_z = z_tmp;
  //tableau[CurrentTriangle].valeur_cos = 0.0000000001 +j*0.0000000001;
  tableau[CurrentTriangle].TypeCND = 13+j;

  VectorIsoTriangle.insert(itVectorData, &tableau[CurrentTriangle]);
  tmp = nb_triangle ;
  }

  else   {
      if( tmp==(nb_triangle -1)) {

  tableau[CurrentTriangle].pl = tableaureferences[CurrentTriangle];
  tableau[CurrentTriangle].valeur_z = z_tmp;
  //tableau[CurrentTriangle].valeur_cos = 0.0000000001 +j*0.0000000001;
  tableau[CurrentTriangle].TypeCND = 13+j;

  VectorIsoTriangle.push_back(&tableau[CurrentTriangle]);
  tmp = nb_triangle ;
                             }
      else    {
      tmp++ ;
      itVectorData++;
      }
                      }
                      }
}
else {
  tableau[CurrentTriangle].pl = tableaureferences[CurrentTriangle];
  tableau[CurrentTriangle].valeur_z =  z_tmp;
  //tableau[CurrentTriangle].valeur_cos = 0.0000000001 +j*0.0000000001;
  tableau[CurrentTriangle].TypeCND = 13+j;

  VectorIsoTriangle.push_back(&tableau[CurrentTriangle]);
}

} /// End of if (z_tmp < 460)

}
}

/// End of the condtruction of the vector

/// ++++++++++++++ Draw the vector of triangles ++++++++++++++

IsoTriangle * CurrentTrianglePt;
QPointArray * CurrentQPointArrayPt;
double        CurrentCosinusValue;
int TriangleType;
QPen gridcol(QColor(gridr,gridg,gridb), 1);
QPen red(QColor(255,0,0), axe_width),
     green(QColor(0, 255, 0), axe_width),
     blue(QColor(0, 0, 255), axe_width) ,
     CNDred(QColor(255,0,0), 1),
     WhiteBorder(QColor(255, 255, 255), 5);
QBrush redone(QColor(255, 0 ,0));
redone.setStyle(Qt::HorPattern);

QBrush CND(QColor(200, 0 ,0));
QBrush CNDG(QColor(200, 200 ,200));

QBrush greenone(QColor(0, 255, 0));
greenone.setStyle(Qt::HorPattern);

QBrush blueone(QColor(0, 0, 255));
blueone.setStyle(Qt::HorPattern);


nb_triangle = VectorIsoTriangle.size();
/*
if (gridtransparent == 1 ) g.setPen( Qt::NoPen );
else g.setPen( gridcol );
*/
if (gridtransparent == 1 ) gridcol = Qt::NoPen ;
g.setPen( gridcol );

 for(i=0; i< nb_triangle ; i++) {
CurrentTrianglePt    = VectorIsoTriangle.at(i);
CurrentQPointArrayPt = CurrentTrianglePt->pl;
CurrentCosinusValue  = CurrentTrianglePt->valeur_cos;
TriangleType         = CurrentTrianglePt->TypeCND;

switch (TriangleType){
/// First case: Normal triangles...
case 1 :
            if(IsoMesh != 1) {
CurrentCosinusValue > 0 ? g.setBrush(palette_front_face[(int)(CurrentCosinusValue*255)]) :
g.setBrush(palette_back_face[(int)(-CurrentCosinusValue*255)]);
g.drawPolygon(*CurrentQPointArrayPt);
                             }
            else {
g.drawPolyline(*CurrentQPointArrayPt);
g.drawLine ( CurrentQPointArrayPt->point(0), CurrentQPointArrayPt->point(2));
            }
        break;
/// Second Case : CND region draw
case 0 : if(CNDDraw == 1) {
if(CNDMesh == 1) {
CurrentCosinusValue > 0 ?
g.setBrush(palette_CND[(int)(CurrentCosinusValue*255)]) :
g.setBrush(palette_CND[(int)(-CurrentCosinusValue*255)]);
g.drawPolygon(*CurrentQPointArrayPt);
                  }
else {
            g.setPen( CNDred);
            g.drawPolyline(*CurrentQPointArrayPt);
            g.drawLine ( CurrentQPointArrayPt->point(0), CurrentQPointArrayPt->point(2));
            g.setPen( gridcol );
     }
}
break;

case 4 :
if(BorderDraw == 1)  {
            g.setPen( WhiteBorder );
            g.drawLine ( CurrentQPointArrayPt->point(0), CurrentQPointArrayPt->point(1));
            g.setPen( gridcol );
                     }
break;

case 10 :
g.setPen( red);
g.drawLine ( CurrentQPointArrayPt->point(0), CurrentQPointArrayPt->point(1));
//g.drawPolyline(*CurrentQPointArrayPt);
g.setPen( gridcol );
break;

case 11 :
g.setPen( green );
g.drawLine ( CurrentQPointArrayPt->point(0), CurrentQPointArrayPt->point(1));
//g.drawPolyline(*CurrentQPointArrayPt);
g.setPen( gridcol );
break;

case 12 :
g.setPen( blue );
g.drawLine ( CurrentQPointArrayPt->point(0), CurrentQPointArrayPt->point(1));
//g.drawPolyline(*CurrentQPointArrayPt);
g.setPen( gridcol );
break;

case 13 :
g.setPen( red );
g.setBrush(redone);
g.drawPolygon(*CurrentQPointArrayPt);
g.drawText((int)(2*AxeArrayProjectd[0][39*3  ] - AxeArrayProjectd[0][38*3  ]),
           (int)(2*AxeArrayProjectd[0][39*3+1] - AxeArrayProjectd[0][38*3+1]),
           "X");
g.setPen( gridcol );
break;
case 14 :
g.setPen( green );
g.setBrush(greenone);
g.drawPolygon(*CurrentQPointArrayPt);
g.drawText((int)(2*AxeArrayProjectd[1][39*3  ] - AxeArrayProjectd[1][38*3  ]),
           (int)(2*AxeArrayProjectd[1][39*3+1] - AxeArrayProjectd[1][38*3+1]),
           "Y");
g.setPen( gridcol );
break;

case 15:
g.setPen(blue );
g.setBrush(blueone);
g.drawPolygon(*CurrentQPointArrayPt);
g.drawText((int)(2*AxeArrayProjectd[2][39*3  ] - AxeArrayProjectd[2][38*3  ]),
           (int)(2*AxeArrayProjectd[2][39*3+1] - AxeArrayProjectd[2][38*3+1]),
           "Z");
g.setPen( gridcol );
break;

}
}

/*



if( DrawAxe_Ok != 1){
if(IsoMesh != 1 )
    for(i=0; i< nb_triangle ; i++) {
CurrentTrianglePt    = VectorIsoTriangle.at(i);
CurrentQPointArrayPt = CurrentTrianglePt->pl;
CurrentCosinusValue  = CurrentTrianglePt->valeur_cos;
TriangleType         = CurrentTrianglePt->TypeCND;
if((IsoConditionRequired !=1 ) || TriangleType == 1) {
if(CurrentCosinusValue > 0)
g.setBrush(palette_front_face[(int)(CurrentCosinusValue*255)]);
else g.setBrush(palette_back_face[-(int)(CurrentCosinusValue*255)]);
g.drawPolygon(*CurrentQPointArrayPt);
}
else {
if(CNDDraw == 1) {

if(TriangleType == 0)  {
CurrentCosinusValue > 0 ? g.setBrush(palette_CND[(int)(CurrentCosinusValue*255)]) :
                          g.setBrush(palette_CND[(int)(-CurrentCosinusValue*255)]);
//else g.setBrush(CNDG); /// Border (White)


            if(CNDMesh == 1)
            g.drawPolygon(*CurrentQPointArrayPt);
            else {
            g.setPen( CNDred);
            g.drawPolyline(*CurrentQPointArrayPt);
            g.drawLine ( CurrentQPointArrayPt->point(0), CurrentQPointArrayPt->point(2));
            g.setPen( gridcol );
            }
}
else if(BorderDraw == 1 && TriangleType == 4)  {
            g.setPen( WhiteBorder );
            g.drawLine ( CurrentQPointArrayPt->point(0), CurrentQPointArrayPt->point(1));
            g.setPen( gridcol );
}
}/// End of if(CNDDraw == 1)...
}


}
else
    for(i=0; i< nb_triangle ; i++) {
CurrentTrianglePt    = VectorIsoTriangle.at(i);
CurrentQPointArrayPt = CurrentTrianglePt->pl;
CurrentCosinusValue  = CurrentTrianglePt->valeur_cos;

g.drawPolyline(*CurrentQPointArrayPt);
g.drawLine ( CurrentQPointArrayPt->point(0), CurrentQPointArrayPt->point(2));

} /// End of if( DrawAxe_Ok != 1)...
}
/// We have to draw the 3D axes
else {


    for(i=0; i< nb_triangle ; i++) {
CurrentTrianglePt    = VectorIsoTriangle.at(i);
CurrentQPointArrayPt = CurrentTrianglePt->pl;
CurrentCosinusValue  = CurrentTrianglePt->valeur_cos;
     if ( CurrentCosinusValue == 0.000333777) {
g.setPen( red);
g.drawPolyline(*CurrentQPointArrayPt);
g.setPen( gridcol );

}
else if ( CurrentCosinusValue == 0.111333777) {
g.setPen( green );
g.drawPolyline(*CurrentQPointArrayPt);
g.setPen( gridcol );

}
else if ( CurrentCosinusValue == 0.222333777) {
g.setPen( blue );
g.drawPolyline(*CurrentQPointArrayPt);
g.setPen( gridcol );

}
else if ( CurrentCosinusValue == 0.0000000001) {
g.setPen( red );
g.setBrush(redone);
g.drawPolygon(*CurrentQPointArrayPt);
g.drawText((int)(2*AxeArrayProjectd[0][39*3  ] - AxeArrayProjectd[0][38*3  ]),
           (int)(2*AxeArrayProjectd[0][39*3+1] - AxeArrayProjectd[0][38*3+1]),
           "X");
g.setPen( gridcol );
}
else if ( CurrentCosinusValue == 0.0000000002) {
g.setPen( green );
g.setBrush(greenone);
g.drawPolygon(*CurrentQPointArrayPt);
g.drawText((int)(2*AxeArrayProjectd[1][39*3  ] - AxeArrayProjectd[1][38*3  ]),
           (int)(2*AxeArrayProjectd[1][39*3+1] - AxeArrayProjectd[1][38*3+1]),
           "Y");
g.setPen( gridcol );
}
else if ( CurrentCosinusValue == 0.0000000003) {
g.setPen(blue );
g.setBrush(blueone);
g.drawPolygon(*CurrentQPointArrayPt);
g.drawText((int)(2*AxeArrayProjectd[2][39*3  ] - AxeArrayProjectd[2][38*3  ]),
           (int)(2*AxeArrayProjectd[2][39*3+1] - AxeArrayProjectd[2][38*3+1]),
           "Z");
g.setPen( gridcol );
}




else {
if (gridtransparent == 1 ) g.setPen( Qt::NoPen );
else g.setPen( gridcol );

if(IsoMesh != 1 ){
if(CurrentCosinusValue > 0)
g.setBrush(palette_front_face[(int)(CurrentCosinusValue*255)]);
else g.setBrush(palette_back_face[-(int)(CurrentCosinusValue*255)]);
g.drawPolygon(*CurrentQPointArrayPt);
}
else  {
g.drawPolyline(*CurrentQPointArrayPt);
g.drawLine ( CurrentQPointArrayPt->point(0), CurrentQPointArrayPt->point(2));

} /// End of if( DrawAxe_Ok != 1)...




}
}













}
*/
/// End of the The Drawing of the vector


/// delete the vector
VectorIsoTriangle.clear();


/// Infos :

if( IsoInfos ==1 ){

g.setPen(QColor(250,0,0));
g.drawText(5,15,"           "+QString::number(nb_ligne)+" x "+QString::number(nb_colon)+" x "+QString::number(nb_depth));

g.setPen(QColor(0,250,0));
g.drawText(5,
           15,
           "Grid = ");


g.setPen(QColor(250,0,0));
g.drawText(5,30,"                 "+QString::number(nb_triangle));

g.setPen(QColor(0,250,0));
g.drawText(5,
           30,
           "Triangles = ");

g.setPen(QColor(250,0,0));
g.drawText(5,45,"                 "+QString::number(NbPointIsoMap));

g.setPen(QColor(0,250,0));
g.drawText(5,
           45,
           "Points = ");

g.setPen(QColor(250,0,0));
g.drawText(5,60,"                 "+ImplicitFunction);

g.setPen(QColor(0,250,0));
g.drawText(5,
           60,
            "F(x,y,z)   = ");

if(IsoConditionRequired == 1) {
g.setPen(QColor(250,0,0));
g.drawText(5,75,"                 "+IsoCondition);

g.setPen(QColor(0,250,0));
g.drawText(5,
           75,
            "CND      =  ");
}

}



}


