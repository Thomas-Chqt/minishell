# ---------------------------------------------------
# CMakeLists.txt
#
# Author: Thomas Choquet <semoir.dense-0h@icloud.com>
# Date: 2024/08/11 19:56:15
# ---------------------------------------------------

cmake_minimum_required(VERSION 3.16)

set(MSH_READLINE_DIR "" CACHE PATH "Directory where the readline library is installed")

project(minishell)
enable_language(C)
add_executable(minishell)
file(GLOB_RECURSE MSH_SOURCES "sources/*.c" "includes/*.h" "Libft/*.c" "Libft/*.h")
target_sources(minishell PRIVATE ${MSH_SOURCES})
target_include_directories(minishell PRIVATE "includes" "Libft/includes")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/realine_check.c
   "char *readline(const char *prompt);
    int rl_on_new_line(void);
    void rl_replace_line(const char *text, int clear_undo);
    void rl_redisplay(void);
    int main()
    {
        char* line = readline(\"\");
        rl_on_new_line();
        rl_replace_line(\"\", 1);
        rl_redisplay();
    }"
)
function(readline_check validator_result_var lib_path)
    try_compile(COMPILE_SUCCESS ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/realine_check.c LINK_LIBRARIES ${lib_path})
    set(${validator_result_var} ${COMPILE_SUCCESS} PARENT_SCOPE)
endfunction()
find_library(MSH_READLINE_PATH readline HINTS "${MSH_READLINE_DIR}" ENV "LD_LIBRARY_PATH" VALIDATOR readline_check DOC "Path to the readline library" REQUIRED)

target_link_libraries(minishell ${MSH_READLINE_PATH})