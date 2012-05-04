/******************************************************************************
 * Project:  wxGIS
 * Purpose:  FeatureLayer header.
 * Author:   Bishop (aka Baryshnikov Dmitriy), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2009,2011 Bishop
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

#include "wxgis/carto/carto.h"
#include "wxgis/datasource/featuredataset.h"

/** \class wxGISFeatureLayer featurelayer.h
    \brief The class represent vector datasource in map.
*/
class WXDLLIMPEXP_GIS_CRT wxGISFeatureLayer :
	public wxGISLayer
{
public:
	wxGISFeatureLayer(wxGISDatasetSPtr pwxGISDataset);
	virtual ~wxGISFeatureLayer(void);
//wxGISLayer
	virtual OGRSpatialReferenceSPtr GetSpatialReference(void);
	virtual void SetSpatialReference(OGRSpatialReferenceSPtr pSpatialReference);
	virtual bool Draw(wxGISEnumDrawPhase DrawPhase, wxGISDisplay *pDisplay, ITrackCancel *pTrackCancel = NULL);
	virtual OGREnvelope GetEnvelope(void);
	virtual bool IsValid(void);
	virtual bool IsCacheNeeded(void);
	virtual wxGISEnumDatasetType GetType(void){return enumGISFeatureDataset;};
//wxGISFeatureLayer
	virtual IFeatureRendererSPtr GetRenderer(void){return m_pFeatureRenderer;};
	virtual void SetRenderer(IFeatureRendererSPtr pFeatureRenderer){m_pFeatureRenderer = pFeatureRenderer;};
	virtual wxGISQuadTreeCursorSPtr Idetify(OGRGeometrySPtr pGeom); 
	virtual wxGISFeatureDatasetSPtr GetDataset(void){return m_pwxGISFeatureDataset;};
protected:
    virtual void LoadGeometry(void);
	virtual long GetPointsInGeometry(OGRGeometry* pGeom);
protected:
	wxGISFeatureDatasetSPtr m_pwxGISFeatureDataset;
    OGRSpatialReferenceSPtr m_pSpatialReference;

    OGREnvelope m_FullEnvelope;
	OGREnvelope m_PreviousEnvelope;

	wxGISQuadTreeSPtr m_pQuadTree;
	IFeatureRendererSPtr m_pFeatureRenderer;
};

DEFINE_SHARED_PTR(wxGISFeatureLayer);