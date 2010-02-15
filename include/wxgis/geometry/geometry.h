/******************************************************************************
 * Project:  wxGIS (GIS Catalog)
 * Purpose:  geometry header.
 * Author:   Bishop (aka Barishnikov Dmitriy), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2009  Bishop
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

#pragma once

#include "wxgis/base.h"
#include "ogr_geometry.h"
#include "geos_c.h"
#include "geos/geom/prep/PreparedGeometry.h"
#include "geos/geom/prep/PreparedGeometryFactory.h"
#include "geos/geom/Geometry.h" 

#include <geos/export.h>

using geos::geom::Geometry;
using geos::geom::prep::PreparedGeometry;
using geos::geom::prep::PreparedGeometryFactory;
//using geos::geom::LineString;
//using geos::geom::Polygon;
//using geos::geom::CoordinateSequence;
//using geos::geom::GeometryFactory;

class wxGISGeometry
{
public:
    wxGISGeometry(void) : m_pGeosPrepGeom(NULL){};
    virtual ~wxGISGeometry(void)
    {
        PreparedGeometryFactory::destroy(m_pGeosPrepGeom);
    }
    virtual const Geometry* GetGEOSGeom(void)
    {
        if(m_pGeosPrepGeom)
        {
            const Geometry &wxGEOSGeom = m_pGeosPrepGeom->getGeometry();
            return &wxGEOSGeom;
        }
        else
            return NULL;
    }
protected:
    const PreparedGeometry* m_pGeosPrepGeom;
};

