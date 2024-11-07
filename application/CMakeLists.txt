# folder names
set(APPLICATION_HEADERS_DIR "include") # .h files directory
set(APPLICATION_SRC_DIR "src") # .cpp files directory
set(APPLICATION_EXTERNALS_DIR "external") # external library files directory

# .h files
# Template : ${APPLICATION_HEADERS_DIR}/
set(APPLICATION_HEADERS 
	${APPLICATION_HEADERS_DIR}/error.hpp
	${APPLICATION_HEADERS_DIR}/lexer.hpp
	${APPLICATION_HEADERS_DIR}/parser.hpp
	${APPLICATION_HEADERS_DIR}/common.hpp
	${APPLICATION_HEADERS_DIR}/flag.hpp
)

# .cpp files
# Template : ${APPLICATION_SRC_DIR}/
set(APPLICATION_SRC 
	${APPLICATION_SRC_DIR}/error.cpp
	${APPLICATION_SRC_DIR}/lexer.cpp
	${APPLICATION_SRC_DIR}/parser.cpp
	${APPLICATION_SRC_DIR}/flag.cpp
)



add_executable(SkywardLangExecutable
	main.cpp
	${APPLICATION_HEADERS}
	${APPLICATION_SRC}
)

# Instead of typing the full path, just do #include "filename"
target_include_directories(SkywardLangExecutable PRIVATE ${APPLICATION_HEADERS_DIR} ${APPLICATION_EXTERNALS_DIR})