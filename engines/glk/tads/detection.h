/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef GLK_TADS_DETECTION
#define GLK_TADS_DETECTION

#include "common/fs.h"
#include "engines/game.h"

namespace Glk {
namespace TADS {

/**
 * Meta engine for TADS interpreter
 */
class TADSMetaEngine {
public:
	/**
	 * Get a list of supported games
	 */
	static void getSupportedGames(PlainGameList &games);

	/**
	 * Returns a game description for the given game Id, if it's supported
	 */
	static PlainGameDescriptor findGame(const char *gameId);

	/**
	 * Detect supported games
	 */
	static bool detectGames(const Common::FSList &fslist, DetectedGames &gameList);
};

} // End of namespace TADS
} // End of namespace Glk

#endif
