/******************************************************************************
 * Project:  wxGIS (GIS Catalog)
 * Purpose:  Transformation Threads header.
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

#include "wxgis/carto/transformthreads.h"

wxGISFeatureTransformThread::wxGISFeatureTransformThread(wxGISFeatureDataset* pwxGISFeatureDataset, OGRCoordinateTransformation *poCT, bool bTransform, wxGISGeometry* pRgn1, wxGISGeometry* pRgn2, wxCriticalSection* pCritSect, OGREnvelope* pFullEnv, wxGISFeatureSet* pOGRFeatureArray, size_t &nCounter, wxGISProgressor* pProgressor, ITrackCancel* pTrackCancel) : wxThread(wxTHREAD_JOINABLE), m_nCounter(nCounter)
{
    m_pwxGISFeatureDataset = pwxGISFeatureDataset;
    m_poCT = poCT;
    m_pTrackCancel = pTrackCancel;
    m_bTransform = bTransform;
    m_pRgn1 = pRgn1;
    m_pRgn2 = pRgn2;
    m_pCritSect = pCritSect;
    m_pFullEnv = pFullEnv;
    m_pOGRFeatureArray = pOGRFeatureArray;
    //m_nCounter = nCounter;
    m_pProgressor = pProgressor;
}

void *wxGISFeatureTransformThread::Entry()
{
    
    size_t nStep = m_pwxGISFeatureDataset->GetSize() < 20 ? 1 : m_pwxGISFeatureDataset->GetSize() / 20;

    OGREnvelope *pRgnEnv1(NULL), *pRgnEnv2(NULL);

    if(m_pRgn1)
    {
        pRgnEnv1 = m_pRgn1->GetEnvelope();
    }
    if(m_pRgn2)
    {
        pRgnEnv2 = m_pRgn2->GetEnvelope();
    }

 	OGRFeature* poFeature;
    while((poFeature = m_pwxGISFeatureDataset->Next()) != NULL)	
    {
        if(m_pTrackCancel && !m_pTrackCancel->Continue())
            return NULL;

        OGRGeometry* pFeatureGeom = poFeature->GetGeometryRef();
        wxGISGeometry* pwxGISGeom = dynamic_cast<wxGISGeometry*>(pFeatureGeom);

        if(!pwxGISGeom)
            continue;

        if(m_bTransform)
        {
            if(m_pRgn1 == NULL && m_pRgn2 == NULL)
            {
                if(pwxGISGeom->Transform( m_poCT ) != OGRERR_NONE)
                {
                    OGRFeature::DestroyFeature(poFeature);
                    continue;
                }
            }
            else
            {
                ////speed fix needed fo diff types of geom
                wxGISGeometry* pGeom = CheckRgnAndTransform1(pwxGISGeom, m_pRgn1, m_pRgn2, pRgnEnv1, pRgnEnv2, m_poCT);
                if(pGeom)
                    poFeature->SetGeometryDirectly(dynamic_cast<OGRGeometry*>(pGeom));

                //OGRGeometry* pGeom1 = CheckRgnAndTransform(pFeatureGeom, m_pRgn1, pRgnEnv1, m_poCT);
                //OGRGeometry* pGeom2 = CheckRgnAndTransform(pFeatureGeom, m_pRgn2, pRgnEnv2, m_poCT);
                //if(pGeom1 && !pGeom2)
                //    poFeature->SetGeometryDirectly(pGeom1); 
                //else if(pGeom2 && !pGeom1)
                //    poFeature->SetGeometryDirectly(pGeom2); 
                //else if(pGeom1 && pGeom2)
                //{
                //    OGRGeometryCollection* pGeometryCollection = new OGRGeometryCollection();
                //    pGeometryCollection->addGeometryDirectly(pGeom1);
                //    pGeometryCollection->addGeometryDirectly(pGeom2);
                //    poFeature->SetGeometryDirectly(pGeometryCollection); 
                //}
                else
                {
                    OGRFeature::DestroyFeature(poFeature);
                    continue;
                }
            }
        }

        OGREnvelope* pEnv;
        pFeatureGeom = poFeature->GetGeometryRef();
        pwxGISGeom = dynamic_cast<wxGISGeometry*>(pFeatureGeom);
        if(pwxGISGeom)
            pEnv = pwxGISGeom->GetEnvelope();
        else
            poFeature->GetGeometryRef()->getEnvelope(pEnv);
        m_pCritSect->Enter();

        m_pFullEnv->Merge(*pEnv);
	    m_pOGRFeatureArray->AddFeature(poFeature);

        m_nCounter++;
        if(m_pProgressor && m_nCounter % nStep == 0)
            m_pProgressor->SetValue(m_nCounter);

        m_pCritSect->Leave();
    }
    
	return NULL;
}
void wxGISFeatureTransformThread::OnExit()
{
}

OGRGeometry* wxGISFeatureTransformThread::CheckRgnAndTransform(OGRGeometry* pFeatureGeom, OGRPolygon* pRgn, OGREnvelope* pRgnEnv, OGRCoordinateTransformation *poCT)
{
    if(!pFeatureGeom)
        return NULL;
    if(!pRgn)
        return NULL;
    if(!pRgnEnv)
        return NULL;    
    if(!poCT)
        return NULL;

    OGREnvelope FeatureEnv;
    pFeatureGeom->getEnvelope(&FeatureEnv);
    if(!FeatureEnv.Intersects(*pRgnEnv))
        return NULL;

    OGRGeometry* pGeom;
    if(pRgnEnv->Contains(FeatureEnv) )
        pGeom = pFeatureGeom->clone();
    else if(pFeatureGeom->Within(pRgn))
        pGeom = pFeatureGeom->clone();
    else
        pGeom = pFeatureGeom->Intersection(pRgn);//speed!Intersection

    if(!pGeom)
        return NULL;

    if(pGeom->getSpatialReference() == NULL)
        pGeom->assignSpatialReference(pFeatureGeom->getSpatialReference());

    if(pGeom->transform( poCT ) != OGRERR_NONE)
    {
        wxDELETE(pGeom);
        return NULL;
    }  
    return pGeom;
}


wxGISGeometry* wxGISFeatureTransformThread::CheckRgnAndTransform1(wxGISGeometry* pwxGISGeom, wxGISGeometry* pRgn1, wxGISGeometry* pRgn2, OGREnvelope* pRgnEnv1, OGREnvelope* pRgnEnv2, OGRCoordinateTransformation *poCT)
{
    if(!pwxGISGeom)
        return NULL;
    if(!poCT)
        return NULL;

    OGREnvelope* pFeatureEnv = pwxGISGeom->GetEnvelope();

    if(pRgnEnv1 && !pFeatureEnv->Intersects(*pRgnEnv1))
        return NULL;
    if(pRgnEnv2 && !pFeatureEnv->Intersects(*pRgnEnv2))
        return NULL;

    wxGISGeometry* pGeom(NULL);

    if(pRgnEnv1 && pRgnEnv1->Contains(*pFeatureEnv) )
    {
        pGeom = pwxGISGeom->Clone();
        goto PROCEED;
    }
    if(pRgnEnv2 && pRgnEnv2->Contains(*pFeatureEnv) )
    {
        pGeom = pwxGISGeom->Clone();
        goto PROCEED;
    }

    if(pRgn1 && pwxGISGeom->Within(pRgn1))
    {
        pGeom = pwxGISGeom->Clone();
        goto PROCEED;
    }
    if(pRgn2 && pwxGISGeom->Within(pRgn2))
    {
        pGeom = pwxGISGeom->Clone();
        goto PROCEED;
    }

    //wxGISGeometry* pGeom1 = Intersection(pFeatureGeom, pRgn1, pRgnEnv1);
    //wxGISGeometry* pGeom2 = Intersection(pFeatureGeom, pRgn2, pRgnEnv2);
    wxGISGeometry* pGeom1(NULL);
    if(pRgn1)
        pGeom1 = pwxGISGeom->Intersection(pRgn1);//speed!Intersection
    wxGISGeometry* pGeom2(NULL);
    if(pRgn2) 
        pGeom2 = pwxGISGeom->Intersection(pRgn2);//speed!Intersection


    if(pGeom1 && !pGeom2)
        pGeom = pGeom1; 
    else if(pGeom2 && !pGeom1)
        pGeom = pGeom2;
    else if(pGeom1 && pGeom2)
    {
        //OGRGeometryCollection* pGeometryCollection = new OGRGeometryCollection();
        //pGeometryCollection->addGeometryDirectly(pGeom1);
        //pGeometryCollection->addGeometryDirectly(pGeom2);
        //pGeom = pGeometryCollection; 
    }

PROCEED:
    if(!pGeom)
        return NULL;

    if(pGeom->GetSpatialReference() == NULL)
        pGeom->SetSpatialReference(pwxGISGeom->GetSpatialReference());

    if(pGeom->Transform( poCT ) != OGRERR_NONE)
    {
        wxDELETE(pGeom);
        return NULL;
    }  
    return pGeom;
}

OGRGeometry* wxGISFeatureTransformThread::Intersection(OGRGeometry* pFeatureGeom, OGRGeometry* pRgn, OGREnvelope* pRgnEnv)
{
    if(!pFeatureGeom || !pRgn || !pRgnEnv)
        return NULL;

    OGREnvelope FeatureEnv;
    pFeatureGeom->getEnvelope(&FeatureEnv);

    OGRwkbGeometryType gType = wkbFlatten(pFeatureGeom->getGeometryType());
    switch(gType)
    {
    case wkbPoint:
        if(pRgnEnv && pRgnEnv->Contains(FeatureEnv) )
            return pFeatureGeom->clone();
        if(pRgn && pFeatureGeom->Within(pRgn))
            return pFeatureGeom->clone();
        break;
    case wkbLineString:
        if(pRgnEnv && pRgnEnv->Contains(FeatureEnv) )
            return pFeatureGeom->clone();
        if(pRgn && pFeatureGeom->Within(pRgn))
            return pFeatureGeom->clone();
        return pFeatureGeom->Intersection(pRgn);
        break;
    case wkbPolygon:
        if(pRgnEnv && pRgnEnv->Contains(FeatureEnv) )
            return pFeatureGeom->clone();
        if(pRgn && pFeatureGeom->Within(pRgn))
            return pFeatureGeom->clone();
        return pFeatureGeom->Intersection(pRgn);
        break;
    case wkbLinearRing:
        if(pRgnEnv && pRgnEnv->Contains(FeatureEnv) )
            return pFeatureGeom->clone();
        if(pRgn && pFeatureGeom->Within(pRgn))
            return pFeatureGeom->clone();
        return pFeatureGeom->Intersection(pRgn);
        break;
    case wkbMultiPoint:
    case wkbMultiLineString:
    case wkbMultiPolygon:
    case wkbGeometryCollection:
        {
        	OGRGeometryCollection* pOGRGeometryCollection = (OGRGeometryCollection*)pFeatureGeom;
            OGRGeometryCollection* pNewOGRGeometryCollection = new OGRGeometryCollection();
            for(size_t i = 0; i < pOGRGeometryCollection->getNumGeometries(); i++)
            {
                OGRGeometry* pGeom = (OGRGeometry*)pOGRGeometryCollection->getGeometryRef(i);
                pGeom->assignSpatialReference(pFeatureGeom->getSpatialReference());
                OGRGeometry* pNewGeom = Intersection(pGeom, pRgn, pRgnEnv);
                if(pNewGeom)
                    pNewOGRGeometryCollection->addGeometryDirectly(pNewGeom);
            }
            if(pNewOGRGeometryCollection->getNumGeometries() == 0)
            {
                wxDELETE(pNewOGRGeometryCollection);
                return NULL;
            }
            else
                return pNewOGRGeometryCollection;
        }
        break;
    case wkbUnknown:
    case wkbNone:
        break;
    }
    return NULL;
}
