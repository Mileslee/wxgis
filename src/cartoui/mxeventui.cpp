/******************************************************************************
 * Project:  wxGIS
 * Purpose:  event UI classes special for MapView events.
 * Author:   Baryshnikov Dmitriy (aka Bishop), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2011,2013 Bishop
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#include "wxgis/cartoui/mxeventui.h"

IMPLEMENT_DYNAMIC_CLASS(wxMxMapViewUIEvent, wxEvent)

wxDEFINE_EVENT( wxMXMAP_ROTATED, wxMxMapViewUIEvent );
wxDEFINE_EVENT( wxMXMAP_DRAWING_START, wxMxMapViewUIEvent );
wxDEFINE_EVENT( wxMXMAP_DRAWING_STOP, wxMxMapViewUIEvent );

