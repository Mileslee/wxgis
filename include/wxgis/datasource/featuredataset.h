/******************************************************************************
 * Project:  wxGIS
 * Purpose:  FeatureDataset class.
 * Author:   Baryshnikov Dmitriy (aka Bishop), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2009-2013 Bishop
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

#include "wxgis/datasource/table.h"
#include "wxgis/datasource/gdalinh.h"
#include "wxgis/datasource/quadtree.h"

/** \class wxGISFeatureDataset featuredataset.h
    \brief The GIS FeatureDataset class.

    This class stores vector geographic data.
*/

class WXDLLIMPEXP_GIS_DS wxGISFeatureDataset :
	public wxGISTable
{
    DECLARE_CLASS(wxGISFeatureDataset)
    friend class wxGISQuadTree;
public:
	wxGISFeatureDataset(const CPLString &sPath, int nSubType, OGRLayer* poLayer = NULL, OGRDataSource* poDS = NULL);
	virtual ~wxGISFeatureDataset(void);
//wxGISTable
    virtual const wxGISSpatialReference GetSpatialReference(void);
    virtual void Close(void);
	virtual bool Open(int iLayer = 0, int bUpdate = 0, bool bCache = true, ITrackCancel* const pTrackCancel = NULL);
    virtual wxGISDataset* GetSubset(size_t nIndex);	
    virtual wxGISDataset* GetSubset(const wxString & sSubsetName); 
    virtual bool IsCached(void) const; 
	virtual bool IsCaching(void) const;    
	virtual void Cache(ITrackCancel* const pTrackCancel = NULL);
    virtual void StopCaching(void);
//wxGISFeatureDataset
	virtual OGREnvelope GetEnvelope(void);
    virtual OGRwkbGeometryType GetGeometryType(void) const;
    virtual wxFeatureCursor Search(const wxGISSpatialFilter &SpaFilter, bool bOnlyFirst = false);
 	virtual wxGISQuadTreeCursor SearchGeometry(const CPLRectObj* pAoi = 0);
    /*
    virtual OGRErr SetFilter(wxGISQueryFilter* pQFilter);
	virtual wxFeatureCursorSPtr Search(wxGISQueryFilter* pQFilter, bool bOnlyFirst = false);

//	//virtual void SetSpatialFilter(double dfMinX, double dfMinY, double dfMaxX, double dfMaxY);
//	//virtual wxGISFeatureSet* GetFeatureSet(IQueryFilter* pQFilter = NULL, ITrackCancel* pTrackCancel = NULL);
	//virtual wxGISGeometrySet* GetGeometrySet(wxGISQueryFilter* pQFilter = NULL, ITrackCancel* pTrackCancel = NULL);
    //virtual wxGISGeometrySet* GetGeometries(void);
    */
	//wxGISTable
    virtual char **GetFileList();
    virtual void SetCached(bool bCached = true){m_bIsCached = bCached;};
protected:
    virtual void SetInternalValues(void);
    /*
    virtual void LoadGeometry(ITrackCancel* pTrackCancel = NULL);
    //virtual void UnloadGeometry(void);
    */
protected:	
    OGREnvelope m_stExtent;
    OGRwkbGeometryType m_eGeomType;
	wxGISQuadTree* m_pQuadTree;
    /*
	


    //wxGISGeometrySet *m_pGeometrySet;
//    wxArrayString m_FeatureStringData;

private:
*/
};

