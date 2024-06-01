set(TEST_LIST 
	errStream.c
	errAdd.c
)
create_test_sourcelist(TestSources 
	libTests.c 
	${TEST_LIST}
	EXTRA_INCLUDE test_common.h
)

add_executable(LibTests ${TestSources} test_common.c)
target_link_libraries(LibTests PRIVATE tlisp)
target_include_directories(LibTests PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	$<TARGET_PROPERTY:tlisp,INCLUDE_DIRECTORIES>
)

foreach(tPath ${TEST_LIST})
	get_filename_component(test ${tPath} NAME_WE)
	add_test(NAME ${test}
		COMMAND LibTests ${test})
	set_tests_properties(
		${test}
		PROPERTIES
		PASS_REGULAR_EXPRESSION "PASS"
		FAIL_REGULAR_EXPRESSION "FAIL"
	)
endforeach()

