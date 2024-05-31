add_executable(errStream errStream.c)
target_link_libraries(errStream PRIVATE unity tlisp)
target_include_directories(errStream PRIVATE
	$<TARGET_PROPERTY:tlisp,INCLUDE_DIRECTORIES>
)
add_test(errStream errStream)
