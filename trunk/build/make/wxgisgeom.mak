g++ -Wall  -g -D__UNIX__ -D__WXGTK__ -DWXUSINGDLL -D_USRDLL -DWXMAKINGDLL_GIS_GEOM  -g -I/usr/lib/wx/include/gtk2-unicode-release-2.8 -I/usr/include/wx-2.8 -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -D__WXGTK__ -pthread      -I../../include -I/home/bishop/projects/gdal-1.7.2/ogr/ogrsf_frmts -I/home/bishop/projects/gdal-1.7.2/ogr -I/home/bishop/projects/gdal-1.7.2/port -I/home/bishop/projects/gdal-1.7.2/gcore -I/home/bishop/projects/gdal-1.7.2/alg  -c /home/bishop/projects/wxGIS/src/geometry/algorithm.cpp -o ../obj/src/geometry/algorithm.o