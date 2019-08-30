# Tries to find gr-osmosdr.
#
# Usage of this module as follows:
#
# find_package(GrOsmoSDR)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
# GrOsmoSDR_ROOT_DIR Set this variable to the root installation of
# gr-osmosdr if the module has problems finding
# the proper installation path.
#
# Variables defined by this module:
#
# GROSMOSDR_FOUND System has gr-osmosdr libs/headers
# GROSMOSDR_LIBRARIES The gr-osmosdr libraries (gnuradio-osmosdr)
# GROSMOSDR_INCLUDE_DIR The location of gr-osmosdr headers

pkg_check_modules (GROSMOSDR_PKG gnuradio-osmosdr)

FIND_PATH(GROSMOSDR_INCLUDE_DIR
     NAMES osmosdr/source_c.h
           osmosdr/api.h
     HINTS ${GROSMOSDR_PKG_INCLUDE_DIRS}
     PATHS /usr/local/include
           /usr/include
)


find_library(GROSMOSDR_LIBRARIES
  NAMES gnuradio-osmosdr
  HINTS ${GROSMOSDR_PKG_LIBRARY_DIRS}
  PATHS /usr/local/lib
        /usr/lib
  )


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  GrOsmoSDR
  DEFAULT_MSG
  GROSMOSDR_LIBRARIES
  GROSMOSDR_INCLUDE_DIR
)


mark_as_advanced(
  GROSMOSDR_LIBRARIES
  GROSMOSDR_INCLUDE_DIR
)

message(STATUS "Pkg: ${LIBDSD_PKG}, ${LIBDSD_PKG_INCLUDE_DIRS}, ${LIBDSD_PKG_LIBRARY_DIRS}")
message(STATUS "Vars: ${GROSMOSDR_INCLUDE_DIR}, ${GROSMOSDR_LIBRARIES}")
