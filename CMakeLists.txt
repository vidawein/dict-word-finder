# cmake for word finder project

cmake_minimum_required(VERSION 3.5)

PROJECT(dict_word_finder)

# Scraping tool that harvests words out of the dictionary.
add_executable(word_scrape word_scrape.cpp)

# Builds the wordlib components
add_subdirectory(wordlib)

add_executable(word_finder word_finder.cpp)
target_include_directories(word_finder PUBLIC ${PROJECT_SOURCE_DIR}/wordlib)
target_link_libraries(word_finder PUBLIC wordtool)

set(dictionary_file dictionary.txt)

# Copies the dictionary text file.
file(COPY "${dictionary_file}" DESTINATION ${PROJECT_BINARY_DIR})
