#
# Try to find GLFW library and include path.
# Once done this will define
#
# GLFW_FOUND
# GLFW_INCLUDE_PATH
# GLFW_LIBRARY

FIND_PATH(GLFW_INCLUDE_PATH GLFW/glfw3.h
	${PROJECT_SOURCE_DIR}/lib/glfw/include/
)

FIND_LIBRARY(GLFW_LIBRARY
	NAMES
		libglfw3.a # OS X
		glfw3.lib  # Windows
	PATHS
		${PROJECT_SOURCE_DIR}/lib/glfw/osx/
		${PROJECT_SOURCE_DIR}/lib/glfw/windows/
)

SET(GLFW_FOUND "NO")
IF (GLFW_INCLUDE_PATH AND GLFW_LIBRARY)
	SET(GLFW_INCLUDE_PATH ${GLFW_INCLUDE_PATH})
	SET(GLFW_LIBRARY ${GLFW_LIBRARY})
	SET(GLFW_FOUND "YES")
ENDIF (GLFW_INCLUDE_PATH AND GLFW_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_LIBRARY GLFW_INCLUDE_PATH)
