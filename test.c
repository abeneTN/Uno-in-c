#include <stdio.h>
#include <string.h>
#include <time.h>
 
int main () {	 
    char var[10]="Rouge";
    printf("%d",memcmp("Rouge", var, 5));
}