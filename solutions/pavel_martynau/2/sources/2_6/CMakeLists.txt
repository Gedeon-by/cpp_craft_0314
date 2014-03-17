find_package( Boost 1.41 ${SEARCH_PARAMETERS} COMPONENTS
	system date_time
)

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries Boost )