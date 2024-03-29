/******************************************************************************
 * Project:  wxGIS (GIS Catalog)
 * Purpose:  wxGxDiscConnectionsUI class.
 * Author:   Baryshnikov Dmitriy (aka Bishop), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2010-2013 Bishop
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
#include "wxgis/catalogui/gxdiscconnectionsui.h"
#include "wxgis/catalogui/gxdiscconnectionui.h"
#include "wxgis/catalogui/gxcatalogui.h"
#include "wxgis/core/format.h"

#include "../../art/folder_conns_16.xpm"
#include "../../art/folder_conns_48.xpm"
#include "../../art/folder_conn_16.xpm"
#include "../../art/folder_conn_48.xpm"

#include "wx/volume.h"
#include "wx/msgdlg.h"
#include "wx/dir.h"

IMPLEMENT_DYNAMIC_CLASS(wxGxDiscConnectionsUI, wxGxDiscConnections)

wxGxDiscConnectionsUI::wxGxDiscConnectionsUI(void) : wxGxDiscConnections(), wxGxAutoRenamer()
{
}

wxGxDiscConnectionsUI::~wxGxDiscConnectionsUI(void)
{
}

wxIcon wxGxDiscConnectionsUI::GetLargeImage(void)
{
    if(!m_Conns48.IsOk())
        m_Conns48 = wxIcon(folder_conns_48_xpm);
	return m_Conns48;
}

wxIcon wxGxDiscConnectionsUI::GetSmallImage(void)
{
    if(!m_Conns16.IsOk())
        m_Conns16 = wxIcon(folder_conns_16_xpm);
	return m_Conns16;
}

wxGxObject *wxGxDiscConnectionsUI::CreateChildGxObject(const wxXmlNode* pNode)
{
    if(!m_Conn16.IsOk())
        m_Conn16 = wxIcon(folder_conn_16_xpm);
    if(!m_Conn48.IsOk())
        m_Conn48 = wxIcon(folder_conn_48_xpm);
    if(!m_ConnDsbld16.IsOk())
    {
        wxImage Img(folder_conn_16_xpm);
        m_ConnDsbld16.CopyFromBitmap(Img.ConvertToGreyscale());
    }
    if(!m_ConnDsbld48.IsOk())
    {
        wxImage Img(folder_conn_48_xpm);
        m_ConnDsbld48.CopyFromBitmap(Img.ConvertToGreyscale());
    }

    wxString soName = pNode->GetAttribute(wxT("name"), NONAME);
    wxString sPath = pNode->GetAttribute(wxT("path"), NONAME);
    CPLString soPath(sPath.mb_str(wxConvUTF8));
    int nXmlId = GetDecimalValue(pNode, wxT("id"), wxNOT_FOUND);
    return new wxGxDiscConnectionUI(this, m_sXmlStoragePath, nXmlId, soName, soPath, m_Conn16, m_Conn48, m_ConnDsbld16, m_ConnDsbld48);
}
/*
void wxGxDiscConnectionsUI::EmptyChildren(void)
{
    m_aConnections.clear();
	for(size_t i = 0; i < m_Children.size(); ++i)
	{
        wxGxDiscConnectionUI* pwxGxDiscConnection = dynamic_cast<wxGxDiscConnectionUI*>(m_Children[i]);
        if(pwxGxDiscConnection)
        {
            CONN_DATA data = {pwxGxDiscConnection->GetName(), pwxGxDiscConnection->GetInternalName()};
            m_aConnections.push_back(data);
        }
		m_Children[i]->Detach();
		wxDELETE(m_Children[i]);
	}
	m_Children.clear();
	m_bIsChildrenLoaded = false;
}

void wxGxDiscConnectionsUI::LoadChildren(void)
{
	if(m_bIsChildrenLoaded)
		return;	

    for(size_t i = 0; i < m_aConnections.size(); ++i)
    {
        wxGxDiscConnectionUI* pwxGxDiscConnection = new wxGxDiscConnectionUI(m_aConnections[i].sPath, m_aConnections[i].sName, m_Conn16, m_Conn48, m_ConnDsbld16, m_ConnDsbld48);
        IGxObject* pGxObject = static_cast<IGxObject*>(pwxGxDiscConnection);
        if(AddChild(pGxObject))
            wxLogMessage(_("wxGxDiscConnections: Add folder connection [%s]"), m_aConnections[i].sName.c_str());
    }

	m_bIsChildrenLoaded = true;
}

IGxObject* wxGxDiscConnectionsUI::ConnectFolder(wxString sPath)
{
    IGxObject* pReturnObj(NULL);

    for(size_t i = 0; i < m_Children.size(); ++i)
    {
        wxGxDiscConnectionUI* pConn = dynamic_cast<wxGxDiscConnectionUI*>(m_Children[i]);
        if(pConn)
        {
            wxString sConnPath(pConn->GetInternalName(), wxConvUTF8);
            if(sConnPath.CmpNoCase(sPath) == 0)
                return dynamic_cast<IGxObject*>(pConn);
        }
    }

    if(wxDir::Exists(sPath)) 	//check if path is valid
	{
	    wxGxDiscConnectionUI* pwxGxDiscConnection = new wxGxDiscConnectionUI(CPLString(sPath.mb_str(wxConvUTF8)), sPath, m_Conn16, m_Conn48, m_ConnDsbld16, m_ConnDsbld48);
        IGxObject* pGxObject = static_cast<IGxObject*>(pwxGxDiscConnection);
        if(AddChild(pGxObject))
        {
		    m_pCatalog->ObjectAdded(pGxObject->GetID());
            StoreConnections();
            return pGxObject;
        }
        else
		    pReturnObj = this;
    }
    else
    {
		pReturnObj = this;
    }
	return pReturnObj;
}
*/