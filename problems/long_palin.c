#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int expand(char *s, int len, int index, int *start, int *end)
{
    int st = index, stp = index;
    
    while(st > 0 && stp < len - 1)
    {
        if(s[st] == s[stp + 1])
        {
            stp++;
        }
        else if(s[st -1] == s[stp])
        {
            st--;
        }
        if(s[st -1] == s[stp + 1])
        {
            st--; stp++;
        }
        else
        {
            break;
        }
    }
    
    *start = st;
    *end = stp;
    return 0;
}


char* longestPalindrome(char* s)
{
    int len = strlen(s);
    int start = 0, end = 0;
    int m_start = 0, m_end = 0;
    int max = 0;
    int i = 0;
    char *result =NULL;

    for(i = 0; i < len; i++)
    {
        expand(s, len, i, &start, &end);
        if(max < (end - start + 1))
        {
            max  = end - start + 1;
            m_start = start;
            m_end = end;
        }
    }
    if(max)
    {
      result = calloc(max + 1, sizeof(char));
      for(i = 0; i < max; i++)
      {
          result[i] = s[m_start++];   
      }
    }     
    return result;
}


int main(int argc, char const *argv[])
{
    char test[6] = "hello";
    char *result = longestPalindrome(test);
    printf("result: %s\n", result);

	return 0;
}