#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 4; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            return 1;
        }
        if (pid == 0) {
            switch (i) {
                case 0:
                    execlp("ls", "ls", NULL);
                    break;
                case 1:
                    execlp("pwd", "pwd", NULL);
                    break;
                case 2:
                    execlp("whoami", "whoami", NULL);
                    break;
                case 3:
                    execlp("date", "date", NULL);
                    break;
                default:
                    break;
            }
            perror("exec failed");
            return 1;
        }
    }
    
    for (int i = 0; i < 4; ++i) {
        if (wait(NULL) == -1) {
            perror("wait failed");
        }
    }

}