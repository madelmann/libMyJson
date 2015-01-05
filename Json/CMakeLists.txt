INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Parser.cpp
	Token.cpp
	Tokenizer.cpp
#	Utils.cpp
	Value.cpp
	Writer.cpp
)

SET(HEADERS
	Exceptions.h
	Json.h
	Parser.h
	Token.h
	Tokenizer.h
	Types.h
	Utils.h
	Value.h
	Writer.h
)

SET(DEPENDENCIES
)

build_static_lib(Json "")
