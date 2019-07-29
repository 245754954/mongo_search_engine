PROJECT(trunk)



CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
add_compile_options(-std=c++11)
SET(CMAKE_CXX_COMPILER "/usr/bin/gcc-8") 
SET(SRC_LIST  wiser.c util.c encrypt.c token.c search.c postings.c  wikiload.c mongodatabase.c)

#判断编译器类型,如果是gcc编译器,则在编译选项中加入c++11支持

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wall -std=c99 -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -O3 -g  -I ./includec -I . ${CMAKE_CXX_FLAGS}")
    SET(CMAKE_BUILD_TYPE "Debug")  
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  

    message(STATUS "optional:-std=c99")   
endif(CMAKE_COMPILER_IS_GNUCXX)



find_package (libmongoc-1.0 1.7 REQUIRED)
# ADD_EXECUTABLE(wiser ${SRC_LIST})

# TARGET_LINK_LIBRARIES(wiser m cjson expat  "${MONGOC_LIBRARIES}")
# target_include_directories (wiser PRIVATE "${MONGOC_INCLUDE_DIRS}")
# target_compile_definitions (wiser PRIVATE "${MONGOC_DEFINITIONS}")




# add_executable(searchengine searchengine.c util.c encrypt.c token.c search.c postings.c  wikiload.c mongodatabase.c myclient.c)
# target_link_libraries(searchengine m expat cjson sqlite3 event pthread "${MONGOC_LIBRARIES}")
# target_include_directories (searchengine PRIVATE "${MONGOC_INCLUDE_DIRS}")
# target_compile_definitions (searchengine PRIVATE "${MONGOC_DEFINITIONS}")






# # The "hello_mongoc.c" sample program is shared among four tests.
#add_executable (hello_mongoc  mongodatabase.c)
add_executable(mysqltest testmongodatabase.c mysqldatabase.c   wiser.c  ${SRC_LIST})


target_link_libraries (mysqltest PRIVATE  m cjson mysqlclient expat "${MONGOC_DEFINITIONS}"  )
target_include_directories (mysqltest PRIVATE "${MONGOC_INCLUDE_DIRS}")
target_compile_definitions (mysqltest PRIVATE "${MONGOC_DEFINITIONS}")

# target_include_directories (hello_mongoc PRIVATE "${MONGOC_INCLUDE_DIRS}")
# target_link_libraries (hello_mongoc PRIVATE "${MONGOC_LIBRARIES}")
# target_compile_definitions (hello_mongoc PRIVATE "${MONGOC_DEFINITIONS}")