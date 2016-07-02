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

#ifndef TITANIC_STAR_VIEW_H
#define TITANIC_STAR_VIEW_H

#include "titanic/support/simple_file.h"
#include "titanic/support/video_surface.h"
#include "titanic/star_control/star_control_sub12.h"
#include "titanic/star_control/star_control_sub13.h"
#include "titanic/star_control/surface_fader.h"

namespace Titanic {

class CStarControl;
class CStarControlSub1;

class CStarView {
private:
	CStarControl *_owner;
	CStarControlSub1 *_sub1;
	CVideoSurface *_videoSurface;
	CStarControlSub12 _sub12;
	int _field118;
	CStarControlSub13 _sub13;
	CSurfaceFader _fader;
	CVideoSurface *_videoSurface2;
	int _field210;
	CGameObject *_homePhotoMask;
	int _field218;
	int _field21C;
public:
	CStarView();

	/**
	 * Load the data for the class from file
	 */
	void load(SimpleFile *file, int param);

	/**
	 * Save the data for the class to file
	 */
	void save(SimpleFile *file, int indent);

	/**
	 * Sets references used by the view
	 */
	void setup(CScreenManager *screenManager, CStarControlSub1 *sub1, CStarControl *starControl);

	void reset();

	/**
	 * Allows the item to draw itself
	 */
	void draw(CScreenManager *screenManager);
};

} // End of namespace Titanic

#endif /* TITANIC_STAR_RENDERER_H */
