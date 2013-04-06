#ifndef SHELL_H
#define SHELL_H

char * rmSpaces( char * );
char * getLoc( int, char * );
void execute_piping(char ** );
void execute_r_in(char ** );
void execute_r_out(char ** );
void execute( char ** );
char ** package( char * ); 
int prompt();

#endif
