# Project info
cmake_minimum_required(VERSION 3.22.1)
project(ENVLoader)

# Options
option(ENVLoader_Static "Build static library" ON)
option(ENVLoader_Shared "Build shared library" ON)
option(ENVLoader_Test "Build test executable" OFF)

# Target Names
set(ENVLoader_C_Static "${PROJECT_NAME}-s")
set(ENVLoader_C_Shared "${PROJECT_NAME}")
set(ENVLoader_C_Test "Test-${PROJECT_NAME}")

# File locations
set(ENVLoader_C_Include_Dir "${PROJECT_SOURCE_DIR}/include")
file(GLOB ENVLoader_C_Src_Files CONFIGURE_DEPENDS
  src/*.c
)
file(GLOB ENVLoader_C_Include_Files CONFIGURE_DEPENDS
  include/*.h
)
file(GLOB ENVLoader_C_Test_Files CONFIGURE_DEPENDS
  src/*.c
  test/*.c
)

# IF Options
if (ENVLoader_Static)
  add_library(${ENVLoader_C_Static} STATIC ${ENVLoader_C_Src_Files})
  target_include_directories(${ENVLoader_C_Static} PRIVATE ${ENVLoader_C_Include_Dir})
  set_target_properties(${ENVLoader_C_Static} PROPERTIES PUBLIC_HEADER ${ENVLoader_C_Include_Files})
  install(
    TARGETS ${ENVLoader_C_Static} 
    LIBRARY DESTINATION bin 
    PUBLIC_HEADER DESTINATION include
  )
endif()

if(ENVLoader_Shared)
  add_library(${ENVLoader_C_Shared} SHARED ${ENVLoader_C_Src_Files})
  target_include_directories(${ENVLoader_C_Shared} PRIVATE ${ENVLoader_C_Include_Dir})
  set_target_properties(${ENVLoader_C_Shared} PROPERTIES PUBLIC_HEADER ${ENVLoader_C_Include_Files})
  install(
    TARGETS ${ENVLoader_C_Shared}
    LIBRARY DESTINATION bin
    PUBLIC_HEADER DESTINATION include
  )
endif()

if(ENVLoader_Test)
  enable_testing()
  add_executable(${ENVLoader_C_Test} ${ENVLoader_C_Test_Files})
  target_include_directories(${ENVLoader_C_Test} PRIVATE ${ENVLoader_C_Include_Dir})
  configure_file(test/.test.env "${CMAKE_BINARY_DIR}/.test.env" COPYONLY)
  add_test(NAME ${ENVLoader_C_Test} COMMAND ${ENVLoader_C_Test})
endif()