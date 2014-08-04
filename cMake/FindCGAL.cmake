# http://code.google.com/p/pixelstruct/source/browse/trunk/cmake/FindCGAL.cmake?r=29
#
# - Find CGAL
# adapted from
#   <http://pgrouting.postlbs.org/browser/trunk/cmake/FindCGAL.cmake?rev=53>
# Find the CGAL includes and client library
# This module defines
#  CGAL_DEFINITIONS: compiler flags for compiling with CGAL
#  CGAL_INCLUDE_DIR: where to find CGAL.h
#  CGAL_LIBRARIES: the libraries needed to use CGAL
#  CGAL_FOUND: if false, do not try to use CGAL

SET(CGAL_DEFINITIONS -frounding-math)

IF(CGAL_INCLUDE_DIR AND CGAL_LIBRARIES)
    SET(CGAL_FOUND TRUE)
ELSE(CGAL_INCLUDE_DIR AND CGAL_LIBRARIES)
    FIND_PATH(CGAL_INCLUDE_DIR basic.h
        /usr/include/CGAL
        /usr/local/include/CGAL
        $ENV{ProgramFiles}/CGAL/*/include/CGAL
        $ENV{SystemDrive}/CGAL/*/include/CGAL
    )
    SET(LIB_SEARCH_PATHS_CGAL 
        /usr/lib
        /usr/local/lib
        /usr/lib/CGAL
        /usr/lib64
        /usr/local/lib64
        /usr/lib64/CGAL
        $ENV{ProgramFiles}/CGAL/*/lib/ms
        $ENV{SystemDrive}/CGAL/*/lib/ms)
        
    FIND_LIBRARY(CGAL_LIBRARIES NAMES CGAL 
        PATHS
        ${LIB_SEARCH_PATHS_CGAL}
    )
    
    FIND_LIBRARY(CGAL_LIBRARIES_Core NAMES CGAL_Core 
        PATHS
        ${LIB_SEARCH_PATHS_CGAL}
    )
    
    FIND_LIBRARY(CGAL_LIBRARIES_Image NAMES CGAL_ImageIO 
        PATHS
        ${LIB_SEARCH_PATHS_CGAL}
    )
    
    SET(CGAL_LIBRARIES ${CGAL_LIBRARIES} ${CGAL_LIBRARIES_Core} ${CGAL_LIBRARIES_Image})
    IF(CGAL_INCLUDE_DIR AND CGAL_LIBRARIES AND CGAL_LIBRARIES_Core AND CGAL_LIBRARIES_Image)
        SET(CGAL_FOUND TRUE)
        MESSAGE(STATUS "Found CGAL: ${CGAL_INCLUDE_DIR}, ${CGAL_LIBRARIES}")
    ELSE(CGAL_INCLUDE_DIR AND CGAL_LIBRARIES AND CGAL_LIBRARIES_Core AND CGAL_LIBRARIES_Image)
        SET(CGAL_FOUND FALSE)
        MESSAGE(STATUS "CGAL not found.")
    ENDIF(CGAL_INCLUDE_DIR AND CGAL_LIBRARIES AND CGAL_LIBRARIES_Core AND CGAL_LIBRARIES_Image)
    
    MARK_AS_ADVANCED(CGAL_INCLUDE_DIR CGAL_LIBRARIES)
ENDIF(CGAL_INCLUDE_DIR AND CGAL_LIBRARIES)
