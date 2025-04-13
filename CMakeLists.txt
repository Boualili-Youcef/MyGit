cmake_minimum_required(VERSION 3.10)
project(MyGit)

set(CMAKE_CXX_STANDARD 17)

# OpenSSL pour SHA1
find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(mygit 
    src/main.cpp 
    src/commands/init.cpp
    src/commands/HashObject.cpp
    src/objets/Blob.cpp
    src/objets/Utilities.cpp
)
target_link_libraries(mygit ${OPENSSL_LIBRARIES})
