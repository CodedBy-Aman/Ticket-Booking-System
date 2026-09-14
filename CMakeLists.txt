cmake_minimum_required(VERSION 3.10)
project(MovieTicketBooking)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# main.cpp is the executable integration unit.
# The other .cpp files document each required class separately because
# the assignment explicitly requires one class per file and no headers.
add_executable(movie_booking src/app/main.cpp)
