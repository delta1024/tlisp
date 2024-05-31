function(create_test name)
	add_executable(${name} ${name}.c)
	target_link_libraries(${name} PRIVATE tlisp unity)
	target_include_directories(${name} PRIVATE
		$<TARGET_PROPERTY:tlisp,INCLUDE_DIRECTORIES>
	)
	add_test(${name} ${name})
endfunction()
create_test(errStream)
create_test(errAdd)
