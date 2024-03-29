//-----------------------------------------------------------------------------
// TmxMapTile.h
//
// Copyright (c) 2010-2014, Tamir Atias
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL TAMIR ATIAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Tamir Atias
//-----------------------------------------------------------------------------
#pragma once

#include <math.h>
#include <iostream>
#include <vector>

using std::vector;

namespace Tmx 
{
    //-------------------------------------------------------------------------
    // Flags that may be in the first two bits of the gid.
    //-------------------------------------------------------------------------
    const unsigned FlippedHorizontallyFlag = 0x80000000;
    const unsigned FlippedVerticallyFlag   = 0x40000000;
    const unsigned FlippedDiagonallyFlag   = 0x20000000;

    //-------------------------------------------------------------------------
    // Struct to store information about a specific tile in the map layer.
    //-------------------------------------------------------------------------
    struct MapTile 
    {
        // Default constructor.
        MapTile()
            : tilesetId(0)
            , id(0)
            , flippedHorizontally(false)
            , flippedVertically(false)
            , flippedDiagonally(false)
        {
		}

        // Will take a gid and read the attributes from the first
        // two bits of it.
        MapTile(unsigned _gid, int _tilesetFirstGid, unsigned _tilesetId)
            : tilesetId(_tilesetId)
            , id(_gid & ~(FlippedHorizontallyFlag | FlippedVerticallyFlag | FlippedDiagonallyFlag))
            , flippedHorizontally((_gid & FlippedHorizontallyFlag) != 0)
            , flippedVertically((_gid & FlippedVerticallyFlag) != 0)
            , flippedDiagonally((_gid & FlippedDiagonallyFlag) != 0)
        {
            gid = id;
            id -= _tilesetFirstGid;
        }

		// ANECOZ HACK
		void setTexCoords(unsigned& imWidth, unsigned& imHeight, unsigned& tileWidth, unsigned& tileHeight) {			
			unsigned tilesPerRow = imWidth / tileWidth;
			int topY = floor(id / tilesPerRow);
			int leftX = id - tilesPerRow * topY;
			topY = (int)((float)imHeight / (float)tileHeight) - topY;
			texCoords.push_back((float)leftX * (float)tileHeight / (float)imWidth);
			texCoords.push_back((float)topY * (float)tileHeight / (float)imHeight);
			texCoords.push_back((float)leftX * (float)tileHeight / (float)imWidth);
			texCoords.push_back((float)(topY - 1) * (float)tileHeight / (float)imHeight);
			texCoords.push_back((leftX + 1) * (float)tileHeight / (float)imWidth);
			texCoords.push_back((float)topY * (float)tileHeight / (float)imHeight);
			texCoords.push_back((float)(leftX + 1) * (float)tileHeight / (float)imWidth);
			texCoords.push_back((float)(topY - 1) * (float)tileHeight / (float)imHeight);
		}

		// ANECOZ HACK
		vector<float> texCoords;

        // Tileset id.
        int tilesetId;		

        // Id.
        unsigned id;

        // Gid.
        unsigned gid;

        // True when the tile should be drawn flipped horizontally.
        bool flippedHorizontally;

        // True when the tile should be drawn flipped vertically.
        bool flippedVertically;

        // True when the tile should be drawn flipped diagonally.
        bool flippedDiagonally;
    };
}
