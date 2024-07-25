cmake_minimum_required(VERSION 3.5)

project(so_long_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Test definitions ###
##
configure_file(CMakeLists.txt.in
	googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
	${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
##

set(PARENT_DIR ${PROJECT_SOURCE_DIR}/..)
set(PARENT_DIR ${PROJECT_SOURCE_DIR}/..)
set(LIBFT_DIR ${PARENT_DIR}/libs/libft)
set(MLX_DIR ${PARENT_DIR}/libs/MLX42)
set(MLX_BUILD_DIR ${MLX_DIR}/build)

include_directories(
	"${PARENT_DIR}/include"
	"${LIBFT_DIR}"
	"${MLX_DIR}/include"
)

file(GLOB sources "${PARENT_DIR}/src/*.c")
list(REMOVE_ITEM sources "${PARENT_DIR}/src/main.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/main.cpp")

# Build libft
add_custom_target(libft
	COMMAND make -C ${LIBFT_DIR} -j4
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Build MLX42
add_custom_target(mlx42
	COMMAND cd ${MLX_DIR} && cmake -B build && make -C build -j4
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

function(add_leak_test test_name executable)
	if(APPLE)
		add_test(NAME ${test_name}_leaks
			COMMAND leaks -atExit -- $<TARGET_FILE:${executable}>)
	elseif(UNIX)
		find_program(VALGRIND "valgrind")
		if(VALGRIND)
			add_test(NAME ${test_name}_leaks
					COMMAND ${VALGRIND} --leak-check=full --error-exitcode=1 $<TARGET_FILE:${executable}>)
		endif()
	endif()
	set_tests_properties(${test_name}_leaks PROPERTIES DEPENDS ${test_name})
endfunction()

foreach(file ${tests})
	set(name)
	get_filename_component(name ${file} NAME_WE)
	add_executable("${name}_tests"
		${sources}
		${file}
		"${PROJECT_SOURCE_DIR}/main.cpp")
	add_dependencies(${name}_tests libft mlx42)
	target_link_libraries(
		"${name}_tests" gtest_main
  		${LIBFT_DIR}/libft.a
		${MLX_BUILD_DIR}/libmlx42.a
		glfw
	)
	add_test(NAME ${name} COMMAND "${name}_tests")
	add_leak_test(${name} "${name}_tests")
endforeach()
