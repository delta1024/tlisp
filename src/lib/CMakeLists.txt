target_sources(${PROJECT_NAME}
	PRIVATE
	memory.c memory.h 
	errors.c errors.h
	state.c state.h
)
target_include_directories(${PROJECT_NAME}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)

if (BUILD_TESTING)
	add_subdirectory(tests)
endif()
