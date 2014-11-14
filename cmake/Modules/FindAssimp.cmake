#
# Try to find Assimp library and include path.
# Once done this will define
#
# ASSIMP_FOUND
# ASSIMP_INCLUDE_PATH
# ASSIMP_LIBRARY

FIND_PATH(ASSIMP_INCLUDE_PATH assimp/
	${PROJECT_SOURCE_DIR}/lib/assimp/include/
)

FIND_LIBRARY(ASSIMP_LIBRARY
	NAMES
		libassimp.a # OS X
		assimp      # Windows
	PATHS
		${PROJECT_SOURCE_DIR}/lib/assimp/osx/
		${PROJECT_SOURCE_DIR}/lib/assimp/windows/
)

SET(ASSIMP_FOUND "NO")
IF (ASSIMP_INCLUDE_PATH AND ASSIMP_LIBRARY)
	SET(ASSIMP_INCLUDE_PATH ${ASSIMP_INCLUDE_PATH})
	SET(ASSIMP_LIBRARY ${ASSIMP_LIBRARY})
	SET(ASSIMP_FOUND "YES")
ENDIF (ASSIMP_INCLUDE_PATH AND ASSIMP_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ASSIMP DEFAULT_MSG ASSIMP_LIBRARY ASSIMP_INCLUDE_PATH)