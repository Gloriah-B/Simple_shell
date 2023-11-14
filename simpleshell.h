#ifndef __simpleshell_H__
#define __simpleshell_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void display_prompt(void);
void execute_command(char *command);
int main(void);

#endif
