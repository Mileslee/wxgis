cmake_minimum_required (VERSION 2.6)
set(PROJECT_NAME wxgiscatalogui)

include(lib)
include(common)

set(LIB_HEADERS ${WXGIS_CURRENT_SOURCE_DIR}/include/wxgis/catalogui)
set(LIB_SOURCES ${WXGIS_CURRENT_SOURCE_DIR}/src/catalogui)

set(wxWidgets_EXCLUDE_COMMON_LIBRARIES ON)
find_package(wxWidgets COMPONENTS core base REQUIRED)
# wxWidgets include (this will do all the magic to configure everything)
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
endif(wxWidgets_FOUND)

if(WXGISGDAL_FOUND)
    include_directories(${WXGISGDAL_INCLUDE_DIR}/ogr/ogrsf_frmts)
endif(WXGISGDAL_FOUND) 

if(GDAL_FOUND)
    include_directories(${GDAL_INCLUDE_DIR}/ogr/ogrsf_frmts)
endif(GDAL_FOUND)

find_package(CAIRO REQUIRED)
if(CAIRO_FOUND)
    include_directories(${CAIRO_INCLUDE_DIR})
    add_definitions(-DHAVE_CAIRO)
endif(CAIRO_FOUND)

include_directories(${LIB_HEADERS})

set(PROJECT_HHEADERS ${PROJECT_HHEADERS}  
    ${LIB_HEADERS}/catalogcmd.h
    ${LIB_HEADERS}/catalogui.h
    ${LIB_HEADERS}/createnewcmd.h
    ${LIB_HEADERS}/gxapplication.h
    ${LIB_HEADERS}/gxarchfolderui.h
    ${LIB_HEADERS}/gxarchivefactoryui.h
    ${LIB_HEADERS}/gxcatalogui.h
    ${LIB_HEADERS}/gxcontdialog.h
    ${LIB_HEADERS}/gxcontentview.h
    ${LIB_HEADERS}/gxcsvfactoryui.h
    ${LIB_HEADERS}/gxdatasetui.h
    ${LIB_HEADERS}/gxdiscconnectionsui.h
    ${LIB_HEADERS}/gxdiscconnectionui.h
    ${LIB_HEADERS}/gxeventui.h
    ${LIB_HEADERS}/gxfilefactoryui.h
    ${LIB_HEADERS}/gxfileui.h
    ${LIB_HEADERS}/gxfolderfactoryui.h
    ${LIB_HEADERS}/gxfolderui.h
    ${LIB_HEADERS}/gxkmldatasetui.h
    ${LIB_HEADERS}/gxlocationcombobox.h
    ${LIB_HEADERS}/gxmapinfofactoryui.h
    ${LIB_HEADERS}/gxmapview.h
    ${LIB_HEADERS}/gxmlfactoryui.h
    ${LIB_HEADERS}/gxnoview.h
    ${LIB_HEADERS}/gxobjcmd.h
    ${LIB_HEADERS}/gxobjdialog.h
    ${LIB_HEADERS}/gxpending.h
    ${LIB_HEADERS}/gxprjfactoryui.h
    ${LIB_HEADERS}/gxpropertypages.h
    ${LIB_HEADERS}/gxrasterfactoryui.h
    ${LIB_HEADERS}/gxselection.h
    ${LIB_HEADERS}/gxshapefactoryui.h
    ${LIB_HEADERS}/gxspatreffolderui.h
    ${LIB_HEADERS}/gxtableview.h
    ${LIB_HEADERS}/gxtabview.h
    ${LIB_HEADERS}/gxtreeview.h
    ${LIB_HEADERS}/gxview.h
    ${LIB_HEADERS}/newmenu.h
    ${LIB_HEADERS}/rasterpropertypage.h
    ${LIB_HEADERS}/spatrefpropertypage.h
    ${LIB_HEADERS}/tablepropertypage.h
    ${LIB_HEADERS}/vectorpropertypage.h
    ${LIB_HEADERS}/viewscmd.h
)

if(POSTGRES_FOUND)
set(PROJECT_HHEADERS ${PROJECT_HHEADERS}
    ${LIB_HEADERS}/remoteconndlg.h
    ${LIB_HEADERS}/gxremoteconnui.h
    ${LIB_HEADERS}/gxpostgisdatasetui.h
    ${LIB_HEADERS}/gxdbconnectionsui.h
    ${LIB_HEADERS}/gxdbconnfactoryui.h
    )
endif(POSTGRES_FOUND)

set(PROJECT_CSOURCES ${PROJECT_CSOURCES}
    ${LIB_SOURCES}/catalogcmd.cpp
    ${LIB_SOURCES}/createnewcmd.cpp
    ${LIB_SOURCES}/gxapplication.cpp
    ${LIB_SOURCES}/gxarchfolderui.cpp
    ${LIB_SOURCES}/gxarchivefactoryui.cpp
    ${LIB_SOURCES}/gxcatalogui.cpp
    ${LIB_SOURCES}/gxcontdialog.cpp
    ${LIB_SOURCES}/gxcontentview.cpp
    ${LIB_SOURCES}/gxcsvfactoryui.cpp
    ${LIB_SOURCES}/gxdatasetui.cpp
    ${LIB_SOURCES}/gxdiscconnectionsui.cpp
    ${LIB_SOURCES}/gxdiscconnectionui.cpp
    ${LIB_SOURCES}/gxeventui.cpp
    ${LIB_SOURCES}/gxfilefactoryui.cpp
    ${LIB_SOURCES}/gxfileui.cpp
    ${LIB_SOURCES}/gxfolderfactoryui.cpp
    ${LIB_SOURCES}/gxfolderui.cpp
    ${LIB_SOURCES}/gxkmldatasetui.cpp
    ${LIB_SOURCES}/gxlocationcombobox.cpp
    ${LIB_SOURCES}/gxmapinfofactoryui.cpp
    ${LIB_SOURCES}/gxmapview.cpp
    ${LIB_SOURCES}/gxmlfactoryui.cpp
    ${LIB_SOURCES}/gxnoview.cpp
    ${LIB_SOURCES}/gxobgdialog.cpp
    ${LIB_SOURCES}/gxobjcmd.cpp
    ${LIB_SOURCES}/gxpending.cpp
    ${LIB_SOURCES}/gxprjfactoryui.cpp
    ${LIB_SOURCES}/gxpropertypages.cpp
    ${LIB_SOURCES}/gxrasterfactoryui.cpp
    ${LIB_SOURCES}/gxselection.cpp
    ${LIB_SOURCES}/gxshapefactoryui.cpp
    ${LIB_SOURCES}/gxspatreffolderui.cpp
    ${LIB_SOURCES}/gxtableview.cpp
    ${LIB_SOURCES}/gxtabview.cpp
    ${LIB_SOURCES}/gxtreeview.cpp
    ${LIB_SOURCES}/gxview.cpp
    ${LIB_SOURCES}/newmenu.cpp
    ${LIB_SOURCES}/rasterpropertypage.cpp
    ${LIB_SOURCES}/spatrefpropertypage.cpp
    ${LIB_SOURCES}/tablepropertypage.cpp
    ${LIB_SOURCES}/vectorpropertypage.cpp
    ${LIB_SOURCES}/viewscmd.cpp    
)

if(POSTGRES_FOUND)
set(PROJECT_CSOURCES ${PROJECT_CSOURCES}
    ${LIB_SOURCES}/gxdbconnectionsui.cpp
    ${LIB_SOURCES}/gxdbconnfactoryui.cpp
    ${LIB_SOURCES}/remoteconndlg.cpp
    ${LIB_SOURCES}/gxremoteconnui.cpp
    ${LIB_SOURCES}/gxpostgisdatasetui.cpp
    )
endif(POSTGRES_FOUND)
 
add_definitions(-DWXMAKINGDLL_GIS_CLU)
set( WXGISCATALOGUI_LIB_NAME ${LIB_NAME} PARENT_SCOPE )

add_library(${LIB_NAME} SHARED ${PROJECT_HHEADERS} ${PROJECT_CSOURCES})

if(wxWidgets_FOUND)
   target_link_libraries(${LIB_NAME} ${wxWidgets_LIBRARIES})
endif(wxWidgets_FOUND)

if(WXGISGDAL_FOUND)
    target_link_libraries(${LIB_NAME} ${WXGISGDAL_LIBRARIES})
endif(WXGISGDAL_FOUND) 

if(GDAL_FOUND)
    target_link_libraries(${LIB_NAME} ${GDAL_LIBRARIES})
endif(GDAL_FOUND) 

if(CAIRO_FOUND)
    target_link_libraries(${LIB_NAME} ${CAIRO_LIBRARIES})
endif(CAIRO_FOUND)

target_link_libraries(${LIB_NAME} ${WXGISCORE_LIB_NAME} ${WXGISFRAMEWORK_LIB_NAME} ${WXGISDATASOURCE_LIB_NAME} ${WXGISCATALOG_LIB_NAME} ${WXGISCARTO_LIB_NAME})

include(installlib)