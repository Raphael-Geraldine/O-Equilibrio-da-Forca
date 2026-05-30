cmake_minimum_required(VERSION 3.10)
project(SFMLProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar os pacotes SFML necessários
find_package(SFML 2.6 COMPONENTS system window graphics audio network REQUIRED)

# 1. LISTA DE ARQUIVOS FONTE (.cpp)
# Guardamos todos os arquivos numa variável para o CMakeLists ficar organizado
set(SRC_FILES
    src/Ente.cpp
    src/Entidade.cpp
    src/Fase.cpp
    src/Gerenciador_Colisoes.cpp
    src/Gerenciador_Grafico.cpp
    src/Jogador.cpp
    src/main.cpp
    src/Menu.cpp
    src/Mustafar.cpp
    src/Obstaculo.cpp
    src/Personagem.cpp
    src/Plataforma.cpp
    src/Principal.cpp
)

# 2. CRIAR O EXECUTÁVEL 
add_executable(O_Equilibrio_da_Forca ${SRC_FILES})

# 3. DIRETÓRIO DE HEADERS 
target_include_directories(O_Equilibrio_da_Forca PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 4. LINK DAS LIBRARIES
target_link_libraries(O_Equilibrio_da_Forca PRIVATE 
    sfml-graphics
    sfml-window
    sfml-audio
    sfml-network
    sfml-system
)

# 5. COPIAR A PASTA ASSETS 
add_custom_command(TARGET O_Equilibrio_da_Forca POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "${CMAKE_CURRENT_BINARY_DIR}/assets"
    COMMENT "Espelhando a pasta assets para o diretorio de build..."
)