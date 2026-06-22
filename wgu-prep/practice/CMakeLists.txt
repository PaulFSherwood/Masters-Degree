cmake_minimum_required(VERSION 3.20)

project(practice LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to Release unless overridden
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()


# -----------------------------
# Explicit executables
# -----------------------------
add_executable(O1       O1/main.cpp)
add_executable(O2n      O2n/main.cpp)
add_executable(OLogN    OLogN/main.cpp)
add_executable(On2      On2/main.cpp)
add_executable(OnLogN   OnLogN/main.cpp)
add_executable(OnSquare OnSquare/main.cpp)
add_executable(OofN     OofN/main.cpp)

# Collect only the targets that exist
set(BUILT_TARGETS "")
foreach(tgt IN ITEMS O1 Olog On OnLog arrays)
  if(TARGET ${tgt})
    list(APPEND BUILT_TARGETS ${tgt})
  endif()
endforeach()

# Apply common warnings/properties to built targets only
foreach(tgt IN LISTS BUILT_TARGETS)
  if(MSVC)
    target_compile_options(${tgt} PRIVATE /W4 /permissive-)
  else()
    target_compile_options(${tgt} PRIVATE -Wall -Wextra -Wpedantic)
  endif()
  set_target_properties(${tgt} PROPERTIES POSITION_INDEPENDENT_CODE ON)
endforeach()

# Optional: link Qt/SDL only if both the target and package exist
# (uncomment if/when you need them)
# find_package(Qt6 QUIET COMPONENTS Widgets)
# if(TARGET Olog AND TARGET Qt6::Widgets)
#   target_link_libraries(Olog PRIVATE Qt6::Widgets)
# endif()
#
# find_package(SDL3 QUIET)
# if(TARGET arrays AND TARGET SDL3::SDL3)
#   target_link_libraries(arrays PRIVATE SDL3::SDL3)
# endif()

# Install only the built targets
if(BUILT_TARGETS)
  install(TARGETS ${BUILT_TARGETS} RUNTIME DESTINATION bin)
endif()

