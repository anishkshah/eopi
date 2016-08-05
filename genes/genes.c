#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int get_specific_char(char c, char *input, int total_size)
{   
    int count = 0;
    int size = total_size;
    while(size) {
        if(*input == c) count++;
        *input++;
        size --;
    }
    return count; 
}

/* need to finish coding it up*/

int main() {

    int a_num = 0;
    int c_num = 0;
    int g_num = 0;
    int t_num = 0;

    char *buffer = NULL;
    int read;
    unsigned int len;
    read = getline(&buffer, &len, stdin);
    if (-1 != read)
        puts(buffer);
    else
        printf("No line read...\n");

    printf("read %d\n", read);
    a_num = get_specific_char('A', buffer, read);
    c_num = get_specific_char('C', buffer, read);
    g_num = get_specific_char('G', buffer, read);
    t_num = get_specific_char('T', buffer, read);
    
    printf("a_num %d, c_num %d g_num %d t_num %d \n", a_num, c_num, g_num, t_num);
    
    if(a_num)
    
    free(buffer);
    return 0;
}
