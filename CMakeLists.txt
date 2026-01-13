cmake_minimum_required(VERSION 3.20)

# Nome del progetto
project(SimplePhysics VERSION 1.0 LANGUAGES CXX)

# Impostiamo C++ 20 (Standard moderno)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- INIZIO INTEGRAZIONE LIBRERIA ---
# FetchContent è un modulo di CMake che permette di scaricare cose da internet
include(FetchContent)

message(STATUS "Sto preparando il download di SFML... attendere...")

FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.6.1  # Usiamo questa versione specifica stabile
)

# Questo scarica i sorgenti di SFML e li prepara per essere compilati insieme al tuo codice
FetchContent_MakeAvailable(sfml)
# --- FINE INTEGRAZIONE LIBRERIA ---

# Creiamo il nostro eseguibile prendendo il file main.cpp
add_executable(physics_engine src/main.cpp)

# LINKING: Questa è la parte cruciale.
# Diciamo al compilatore: "Quando crei physics_engine, attaccaci dentro i pezzi di SFML"
# sfml-graphics: per disegnare
# sfml-window: per gestire la finestra
# sfml-system: per orologi e vettori
target_link_libraries(physics_engine PRIVATE sfml-graphics sfml-window sfml-system)

# Copia automatica delle DLL (per Windows)
# Senza questo, l'eseguibile crasherebbe perché non trova i file .dll di SFML
add_custom_command(TARGET physics_engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:sfml-graphics>
    $<TARGET_FILE:sfml-window>
    $<TARGET_FILE:sfml-system>
    $<TARGET_FILE_DIR:physics_engine>
)