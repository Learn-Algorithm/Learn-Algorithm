# algorithm

project(rex)

# project setting
set(TEST true)
set(CMAKE_BUILD_TYPE "Debug")
set(SRC_DIR "src/")
set(TST_DIR "test/")
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)
if(UNIX)
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -ggdb")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -s -DNDEBUG")
elseif(WIN32)
	add_definitions("-D_CRT_SECURE_NO_DEPRECATE")
endif(UNIX)
include_directories("src")
#######################################################
set(REX_LIST 
	${SRC_DIR}/hashtable.c
	${SRC_DIR}/ds.c
	${TST_DIR}/hashtable.c
)
add_executable(rex ${REX_LIST})

set(
	GEN_LIST
	../createFile.cpp
)
add_executable(gen ${GEN_LIST})

############
add_custom_target(generatefile ALL
	DEPENDS gen
	COMMAND gen
	COMMENT "Generating inputfile.txt, it will take some time, please wait..."
)





