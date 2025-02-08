cmake_minimum_required(VERSION 3.14)
project(binary_tree_tests)

set(CMAKE_CXX_STANDARD 17)

# Dodaj GoogleTest jako zależność
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)

# Pobierz i dodaj GoogleTest do projektu
FetchContent_MakeAvailable(googletest)

enable_testing()

# Dodaj katalog z nagłówkami do ścieżki kompilacji
include_directories(${CMAKE_SOURCE_DIR}/src/binary_tree)

# Dodaj plik wykonywalny dla testów
add_executable(nr3_test src/binary_tree/test/nr3_test.cc)

# Linkuj GoogleTest
target_link_libraries(nr3_test PRIVATE gtest gtest_main)

# Dodaj test
add_test(NAME nr3_test COMMAND nr3_test)