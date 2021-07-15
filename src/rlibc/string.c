#include <common.h>
#include <stddef.h> // TODO: Create own stddef.h instead of using GNU's 

size_t strlen(char* str)
{
    size_t i;
    for (i = 0;str[i] != '\0';i++);
    return i; 
}

size_t strnlen(char* str, size_t size)
{
    size_t i;
    for (i = 0;i<=size && str[i] != '\0';i++);
    return i;
}

BOOL strncmp(char* str1, char* str2, size_t size)
{
    for (int i = 0;i <= size-1;i++)
    {
      if (str1[i] != str2[i]) return FALSE;
      else if ((str1[i] == '\0') || (str2[i] == '\0')) break;
    }
    return TRUE;
}

BOOL strcmp(char* str1, char* str2)
{
    if (strlen(str1) != strlen(str2)) return FALSE;
    return strncmp(str1, str2, strlen(str1));
}
      

