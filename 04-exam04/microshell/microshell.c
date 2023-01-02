#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int read_fd[2] = {0, 1};
int write_fd[2] = {0, 1};

void ft_putstr_fd(char *str, int fd) {
  while (*str) {
    write(fd, str, 1);
    str++;
  }
}

void wrap_close(int fd) {
  if (fd == 0 || fd == 1) {
    return;
  }
  close(fd);
}

void wrap_dup2(int fd1, int fd2) {
  dup2(fd1, fd2);
  wrap_close(fd1);
}

void update_pipe(int *read_fd, int *write_fd) {
  wrap_close(read_fd[0]);
  wrap_close(read_fd[1]);
  read_fd[0] = write_fd[0];
  read_fd[1] = write_fd[1];
  write_fd[0] = 0;
  write_fd[1] = 1;
}

void cd(char **argv, int i) {
  if (i != 2)
    ft_putstr_fd("error: cd: bad arguments\n", STDERR_FILENO);
  else {
    if (chdir(argv[1]) == -1) {
      ft_putstr_fd("error: cd: cannot change directory to ", STDERR_FILENO);
      ft_putstr_fd(argv[1], STDERR_FILENO);
      ft_putstr_fd("\n", STDERR_FILENO);
    }
  }
}

void exec_parallel(char **argv, int i, char **envp) {
  pid_t pid;

  pipe(write_fd);
  pid = fork();
  if (pid == 0) { // child process
    argv[i] = NULL;
    // close unused fd
    wrap_close(read_fd[1]);
    wrap_close(write_fd[0]);
    // change stdin and stdout
    wrap_dup2(read_fd[0], STDIN_FILENO);
    wrap_dup2(write_fd[1], STDOUT_FILENO);
    if (execve(argv[0], argv, envp) == -1) {
      ft_putstr_fd("error: cannot execute ", 2);
      ft_putstr_fd(argv[0], 2);
      ft_putstr_fd("\n", 2);
      exit(1);
    }
  } else {
    update_pipe(read_fd, write_fd);
    // waitpid(pid, NULL, 0); <--- We don't need waitpid!
  }
}

void exec(char **argv, int i, char **envp) {
  pid_t pid;

  // pipe(write_fd); <--- We don't need pipe!
  pid = fork();
  if (pid == 0) { // child process
    argv[i] = NULL;
    // close unused fd
    wrap_close(read_fd[1]);
    wrap_close(write_fd[0]);
    // change stdin and stdout
    wrap_dup2(read_fd[0], STDIN_FILENO);
    wrap_dup2(write_fd[1], STDOUT_FILENO);
    if (execve(argv[0], argv, envp) == -1) {
      ft_putstr_fd("error: cannot execute ", 2);
      ft_putstr_fd(argv[0], 2);
      ft_putstr_fd("\n", 2);
      exit(1);
    }
  } else {
    update_pipe(read_fd, write_fd);
    waitpid(pid, NULL, 0);
  }
}

int main(int argc, char **argv, char **envp) {
  int i;

  if (argc == 1)
    return 0;

  while (*argv) {
    argv++;
    i = 0;
    // stop at NULL || ";" || "|"
    while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
      i++;
    if (i == 0)
      continue;
    else if (!strcmp(argv[0], "cd"))
      cd(argv, i);
    else if (argv[i] && !strcmp(argv[i], "|"))
      exec_parallel(argv, i, envp);
    else
      exec(argv, i, envp);
    argv += i;
  }
}
