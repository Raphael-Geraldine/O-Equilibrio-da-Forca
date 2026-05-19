cmake_minimum_required(VERSION 3.10)
project(SFMLProject VERSION 1.0)

# set(CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Localização do diretório SFML (Apenas se o CMake não achar sozinho)
# set(SFML_DIR "C:/SFML_mingw64/SFML-2.6.2/lib/cmake/SFML")

# Encontrar os pacotes SFML necessários
find_package(SFML 2.6 COMPONENTS system window graphics audio network REQUIRED)
# find_package(Freetype REQUIRED)

# Adicionar headers da pasta include do meu projeto "include".
# include_directories(${CMAKE_SOURCE_DIR}/include)

# Para compilar recursivamente arquivos ".cpp" (pegar arquivos fontes).
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Criar o executável.
add_executable(SFMLProject ${SRC_FILES})

# Diretórios SFML "include"
# include_directories("C:/SFML_mingw64/SFML-2.6.2/include")

# "Linking libraries"
# link_libraries("C:/SFML_mingw64/SFML-2.6.2/lib")

# Link das libraries ao alvo
target_link_libraries(SFMLProject PRIVATE 
    sfml-graphics
    sfml-window
    sfml-audio
    sfml-network
    sfml-system
    # opegl32
    # winmm
    # gdi32
    # user32
    # freetype
)

# if(WIN32)
#   add_custom_command(TARGET SFMLProject POST_BUILD
#       COMMAND ${CMAKE_COMMAND} -E copy_if_different
#           -t "${CMAKE_CURRENT_BINARY_DIR}" # O "-t" força o CMake a tratar isso como pasta
#           "C:/msys64/ucrt64/bin/sfml-graphics-2.dll"
#           "C:/msys64/ucrt64/bin/sfml-window-2.dll"
#           "C:/msys64/ucrt64/bin/sfml-system-2.dll"
#           "C:/msys64/ucrt64/bin/sfml-audio-2.dll"
#           "C:/msys64/ucrt64/bin/sfml-network-2.dll"
#           "C:/msys64/ucrt64/bin/libgcc_s_ucrt-1.dll"
#           "C:/msys64/ucrt64/bin/libstdc++-6.dll"
#           "C:/msys64/ucrt64/bin/libwinpthread-1.dll"
#   )
# endif()