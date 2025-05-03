cmake_minimum_required(VERSION 3.10)
project(GerenciadorMedico VERSION 1.0)

# Define o padrão para C (C11) e habilita warnings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# Adiciona o diretório 'src' ao caminho de includes
include_directories(src)

# Lista todos os arquivos fonte
file(GLOB SOURCES "src/*.c")

# Cria o executável principal
add_executable(gerenciador-medico ${SOURCES})

# Opcional: Configuração para Windows (se necessário)
if(WIN32)
    # Ajustes específicos para Windows (ex: caminhos de arquivos)
endif()
