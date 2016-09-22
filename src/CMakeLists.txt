cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Library sources
list(APPEND LIB_SOURCES
   "${CMAKE_CURRENT_LIST_DIR}/lib/product.cc"
   "${CMAKE_CURRENT_LIST_DIR}/lib/grocery_list.cc"
)
add_library(GroceryList ${LIB_SOURCES})
target_include_directories(GroceryList PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../include")

install(TARGETS GroceryList DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/sgl DESTINATION include)

# Console application
option(BUILD_CONSOLE_APP "Build the console application" ON)
if(BUILD_CONSOLE_APP)
   list(APPEND CONSOLE_BIN_SOURCES
      "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
   )
   add_executable(sgl ${CONSOLE_BIN_SOURCES})
   target_link_libraries(sgl GroceryList)

   set(products_file "${CMAKE_CURRENT_LIST_DIR}/../products/products.txt")
   file(COPY ${products_file} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")

   install(TARGETS sgl DESTINATION bin)
   install(FILES ${products_file} DESTINATION bin)
endif()
