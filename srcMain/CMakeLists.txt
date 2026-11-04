# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
  
#Create a variable called linalg_SOURCES containing all .cpp files:


set(scanMain_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/scandemo.cpp
    PARENT_SCOPE
   )
