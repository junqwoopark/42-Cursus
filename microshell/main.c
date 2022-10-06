#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void ft_close(int fd) {
  if (fd == 0 || fd == 1) {
    return;
  }
  close(fd);
}

void ft_dup2(int fd1, int fd2) {
  dup2(fd1, fd2);
  ft_close(fd1);
}

void close_unused_fd(int *read_fd, int *write_fd) {
  ft_close(read_fd[1]);
  ft_close(write_fd[0]);
}

void update_pipe(int *read_fd, int *write_fd) {
  ft_close(read_fd[0]);
  ft_close(read_fd[1]);
  read_fd[0] = write_fd[0];
  read_fd[1] = write_fd[1];
  write_fd[0] = 0;
  write_fd[1] = 1;
}

char **get_argv_list(int argc, char **argv) {
  char **argv_list = malloc(sizeof(char *) * argc);
  for (int i = 0; i < argc; i++) {
    argv_list[i] = 0;
  }
  for (int i = 0; i + 1 < argc; i++) {
    argv_list[i] = strdup(argv[i + 1]);
  }
  return (argv_list);
}

int main(int argc, char **argv, char **envp) {
  int read_fd[2] = {0, 1};
  int write_fd[2] = {0, 1};

  if (argc == 1) {
    return (0);
  }

  char **argv_list = get_argv_list(argc, argv);

  for (int i = 0; i + 1 < argc; i++) {
    int is_pipe = 0;
    char **start = argv_list + i;
    while (argv_list[i] && strcmp(argv_list[i], "|") &&
           strcmp(argv_list[i], ";"))
      i++;

    if (argv_list[i] && strcmp(argv_list[i], "|") == 0) {
      is_pipe = 1;
      pipe(write_fd);
    }
    if (argv_list[i] &&
        (strcmp(argv_list[i], "|") == 0 || strcmp(argv_list[i], ";") == 0)) {
      free(argv_list[i]);
      argv_list[i] = 0;
    }

    pid_t pid = fork();
    if (pid == 0) { // 자식 프로세스
      close_unused_fd(read_fd, write_fd);
      ft_dup2(write_fd[1], STDOUT_FILENO);
      ft_dup2(read_fd[0], STDIN_FILENO);

      if (execve(start[0], start, envp) == -1)
        write(2, "error: cannot execute executable_that_failed\n",
              strlen("error: cannot execute executable_that_failed\n"));
      exit(0);
    } else { // 부모 프로세스
      update_pipe(read_fd, write_fd);
      if (!is_pipe) {
        while (waitpid(-1, 0, 0) != -1)
          ;
      }
    }
  }
}
