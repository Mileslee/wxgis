/******************************************************************************
 * Project:  wxGIS (GIS Toolbox)
 * Purpose:  geoprocessingui header.
 * Author:   Bishop (aka Barishnikov Dmitriy), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2009-2010  Bishop
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

#include "wxgis/catalogui/catalogui.h"
#include "wxgis/geoprocessing/geoprocessing.h"

#define SASHCTRLID	1012
#define TOOLVIEWCTRLID	1015
#define TASKSVIEWCTRLID	1016

/** \class IToolManagerUI
 *  \brief A base class (virtual) for config and run tool from UI.
 */

class IToolManagerUI
{
public:
    virtual ~IToolManagerUI(void){};    
/** \fn IGPToolSPtr GetGPTool(wxString sToolName)
     *  \brief Return tool by name.
     *  \param sToolName Tool name
     *  \return IGPTool pointer or NULL.
     */		
	virtual IGPToolSPtr GetGPTool(wxString sToolName) = 0;
/** \fn void OnExecuteTool(wxWindow* pParentWnd, IGPTool* pTool, IGPCallBack* pCallBack, bool bSync)
     *  \brief Execute passed preconfig tool
     *  \param pParentWnd The Parent wxWindow created dialogs
     *  \param pTool The preconfigured tool to execute
     *  \param pCallBack The callback executed on tool execution ends
     *  \param bSync If bSync parameter is true, shows Execution dialog, and interface blocked. If bSync parameter is false, created GxTask Object and inserted to wxGxToolExecuteView.
     */		
	virtual void OnExecuteTool(wxWindow* pParentWnd, IGPToolSPtr pTool, IGPCallBack* pCallBack, bool bSync) = 0;
/** \fn bool OnPrepareTool(wxWindow* pParentWnd, IGPToolSPtr pTool, IGPCallBack* pCallBack, bool bSync)
     *  \brief Execute passed preconfig tool
     *  \param pParentWnd The Parent wxWindow created dialogs
     *  \param pTool The tool to configure
     *  \param pCallBack The callback executed on tool execution ends
     *  \param bSync If bSync parameter is true, shows Execution dialog, and interface blocked. If bSync parameter is false, created GxTask Object and inserted to wxGxToolExecuteView.
     */		
	virtual bool OnPrepareTool(wxWindow* pParentWnd, IGPToolSPtr pTool, IGPCallBack* pCallBack, bool bSync) = 0;
};


