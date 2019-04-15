# cmake for word finder project

cmake_minimum_required(VERSION 3.5)

PROJECT(dict_word_finder)

# Scraping tool that harvests words out of the dictionary.
add_executable(word_scrape word_scrape.cpp)

# Builds the wordlib components
add_subdirectory(wordlib)

set(dictionary_file dictionary.txt)

# Copies the dictionary text file.
file(COPY "${dictionary_file}" DESTINATION ${PROJECT_BINARY_DIR})
