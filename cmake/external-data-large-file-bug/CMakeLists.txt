cmake_minimum_required ( VERSION 2.8.12 )

project ( ExternalDataTest )

################################################################################
# Setup External Data
################################################################################
include ( ExternalData )

if ( NOT DATA_STORE_DIR )
  # Select a default in the home directory
  set ( DATA_STORE_DIR_DEFAULT "$ENV{HOME}/ExternalData")
endif ()

# Provide users with an option to select a local object store,
# starting with the above-selected default.
set ( DATA_STORE_DIR "${DATA_STORE_DIR_DEFAULT}" CACHE PATH
  "Local directory holding ExternalData objects in the layout %(algo)/%(hash)."
)
mark_as_advanced ( DATA_STORE_DIR )

# Tell ExternalData module about selected object stores.
list(APPEND ExternalData_OBJECT_STORES
  # Store selected by Mantid-specific configuration above.
  ${DATA_STORE_DIR}
)

# Default binary root to build directory
set ( ExternalData_BINARY_ROOT ${CMAKE_BINARY_DIR}/ExternalData CACHE STRING
     "A directory holding the links (copies on windows) to the real content files." )

# Templates
set ( ExternalData_URL_TEMPLATES "" CACHE STRING
      "Additional URL templates for the ExternalData CMake script to look for testing data. E.g.
       file:///var/bigharddrive/%(algo)/%(hash)"
)
mark_as_advanced ( ExternalData_URL_TEMPLATES )
list ( APPEND ExternalData_URL_TEMPLATES
  "http://198.74.56.37/ftp/external-data/%(algo)/%(hash)"
)

################################################################################
# Target
################################################################################
ExternalData_Expand_Arguments ( TestData
  link_location
  DATA{Testing/Data/LargeFile.nxs}
)
ExternalData_Add_Target ( TestData )
