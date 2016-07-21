cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Library sources
list(APPEND LIB_SOURCES
   "${CMAKE_CURRENT_LIST_DIR}/lib/product.cc"
   "${CMAKE_CURRENT_LIST_DIR}/lib/grocery_list.cc"
)
add_library(GroceryList STATIC ${LIB_SOURCES})

# Console application
option(BUILD_CONSOLE_APP "Build the console application" ON)
if(BUILD_CONSOLE_APP)
   list(APPEND CONSOLE_BIN_SOURCES
      "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
   )
   add_executable(sgl ${CONSOLE_BIN_SOURCES})
   target_link_libraries(sgl GroceryList)

   file(COPY "${CMAKE_SOURCE_DIR}/products/products.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
endif()
