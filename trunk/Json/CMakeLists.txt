INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	AtomicValue.cpp
	Parser.cpp
	Reader.cpp
	Token.cpp
	Tokenizer.cpp
	Utils.cpp
	Value.cpp
	Writer.cpp
)

SET(HEADERS
	Array.h
	AtomicValue.h
	Exceptions.h
	Json.h
	Object.h
	Parser.h
	Reader.h
	Token.h
	Tokenizer.h
	Utils.h
	Value.h
	Writer.h
)

SET(DEPENDENCIES
)

add_include(Json)

build_static_lib(Json "")

