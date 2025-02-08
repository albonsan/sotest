#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 512

static void *loaded_library = NULL;

void unload_library() {
    if (loaded_library) {
        dlclose(loaded_library);
        loaded_library = NULL;
    }
}

bool load_library(const char *lib_name) {       
    unload_library();
    
    char library[MAX_LINE_LENGTH];
    getcwd(library, sizeof(library));
    strcat(library, "/");
    strncat(library, lib_name, strlen(lib_name));

    loaded_library = dlopen(library, RTLD_LAZY);
    if (!loaded_library) {
        fprintf(stderr, "Error: Loading library, %s.\n", dlerror());
        return false;
    }
    
    printf("%s library loaded successfully.\n", lib_name);
    return true;
}

bool call_function_lib(const char *func_name) {
    if (!loaded_library) {
        fprintf(stderr, "Error: The library is not loaded.\n");
        return false;
    }
    
    void (*func)() = (void (*)())dlsym(loaded_library, func_name);
    if (!func) {
        fprintf(stderr, "Error: The <%s> function is not found.\n", func_name);
        return false;
    }
    
    func();
    printf("%s executed successfully.\n", func_name);
    return true;
}

bool process_command(char *line) {
    bool command_status = true;
    
    line[strcspn(line, "\r")] = '\0';
    line[strcspn(line, "\n")] = '\0';
    
    if (strncmp(line, "use ", 4) == 0) {
        command_status = load_library(line + 4);
    } else if (strncmp(line, "call ", 5) == 0) {
        command_status = call_function_lib(line + 5);
    } 
    else if (line[0] == '#' || line[0] == ';' || line[0] == '\r' || line[0] == '\n') {
        ;
    } else if (*line != '\0') {
        fprintf(stderr, "Warning: Syntaxis error in line -> %s\n", line);
    }       
    
    return command_status;
}

void run_script_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Script file <%s> not found.\n", filename);
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (!process_command(line)) {
            break;
        }
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        run_script_file(argv[1]);
    } else {
        printf("Write commands\n  use <so_name>: Load the library.\n  call <func_name>: Library function call.\n  exit: To finish.\n");
        
        char command[MAX_LINE_LENGTH];
        while (1) {
            printf("> ");
            if (!fgets(command, sizeof(command), stdin)) break;
            if (strcmp(command, "exit\n") == 0) break;
            process_command(command);
        }
    }
    unload_library();
    
    return 0;
}
