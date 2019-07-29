PROJECT(trunk)

<<<<<<< HEAD

=======
MESSAGE(STATUS "This is BINARY dir " ${TRUNK_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir" ${TRUNK_SOURCE_DIR})
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
add_compile_options(-std=c++11)
SET(CMAKE_CXX_COMPILER "/usr/bin/gcc-8") 
<<<<<<< HEAD
SET(SRC_LIST  wiser.c util.c encrypt.c token.c search.c postings.c  wikiload.c mongodatabase.c)
=======
SET(SRC_LIST myclient.c wiser.c util.c token.c search.c postings.c database.c wikiload.c)
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f

#判断编译器类型,如果是gcc编译器,则在编译选项中加入c++11支持

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wall -std=c99 -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -O3 -g  -I ./includec -I . ${CMAKE_CXX_FLAGS}")
    SET(CMAKE_BUILD_TYPE "Debug")  
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  

    message(STATUS "optional:-std=c99")   
endif(CMAKE_COMPILER_IS_GNUCXX)


<<<<<<< HEAD

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
=======
#ADD_EXECUTABLE(myclient ${SRC_LIST})

#TARGET_LINK_LIBRARIES(myclient m expat sqlite3)





#add_executable(searchengine searchengine.c ${SRC_LIST})
#target_link_libraries(searchengine m expat sqlite3 event pthread)

# Specify the minimum version you require.
find_package (libmongoc-1.0 1.7 REQUIRED)

message ("--   mongoc found version \"${MONGOC_VERSION}\"")
message ("--   mongoc include path \"${MONGOC_INCLUDE_DIRS}\"")
message ("--   mongoc libraries \"${MONGOC_LIBRARIES}\"")

# The "hello_mongoc.c" sample program is shared among four tests.
#add_executable (hello_mongoc  mongodatabase.c)
add_executable(mongotest testmongodatabase.c mongodatabase.c  ${SRC_LIST})

target_include_directories (mongotest PRIVATE "${MONGOC_INCLUDE_DIRS}")
target_link_libraries (mongotest PRIVATE  m cjson expat sqlite3  "${MONGOC_LIBRARIES}")
target_compile_definitions (mongotest PRIVATE "${MONGOC_DEFINITIONS}")
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f

# target_include_directories (hello_mongoc PRIVATE "${MONGOC_INCLUDE_DIRS}")
# target_link_libraries (hello_mongoc PRIVATE "${MONGOC_LIBRARIES}")
# target_compile_definitions (hello_mongoc PRIVATE "${MONGOC_DEFINITIONS}")