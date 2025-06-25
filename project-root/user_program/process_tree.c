#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define NUM_CHILDREN 3
#define MEMORY_SIZE 1024 * 1024 // 1 MB

// Function to print memory map
void print_memory_map(pid_t pid, int indent) {
    char filename[100];
    FILE *fp;
    char line[256];

    sprintf(filename, "/proc/%d/maps", pid);
    fp = fopen(filename, "r");
    if (!fp) {
        perror("Unable to open memory map");
        return;
    }

    printf("|- Process ID: %d\n", pid);

    int count = 0;
    while (fgets(line, sizeof(line), fp) && count < 5) {
        printf("    |- %s", line);
        count++;
    }

    fclose(fp);
}

// Function to create child processes recursively
void create_child_processes(int depth, int max_depth) {
    if (depth >= max_depth) return;

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Allocate memory in child
            void *child_memory = malloc(MEMORY_SIZE);
            if (!child_memory) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            memset(child_memory, 'B', MEMORY_SIZE);

            // Print memory map of the child
            print_memory_map(getpid(), depth + 1);

            sleep(2);

            free(child_memory);
            exit(0);
        }
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }
}

void print_process_tree(pid_t root_pid) {
    char cmd[256];
    printf("\nProcess Tree:\n");
    sprintf(cmd, "pstree -p %d", root_pid);
    system(cmd);
}

int main() {
    pid_t pid = getpid();

    printf("Starting parent process with PID: %d\n", pid);

    // Load kernel module
    system("sudo insmod ../kernel_module/birthday_module.ko");
    printf("Kernel module loaded\n");

    print_process_tree(pid);
    print_memory_map(pid, 0);

    create_child_processes(0, 2);

    // Unload kernel module
    system("sudo rmmod birthday_module");
    printf("Kernel module unloaded\n");

    return 0;
}

