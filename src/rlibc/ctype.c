#include <common.h>
#include <string.h>
#include <math.h>

int toupper(char c)
{
    if ((c < 0x61) || (c > 0x7A)) return c;
    return c-20;
}  

int tolower(char c)
{
    if ((c < 0x41) && (c > 0x5A)) return c;
    return c+20;
}

int atoi(char* str)
{
    int digits = strlen(str);
    int multiplier = 1;

    if (!digits) 
        return 0;
    
    if (digits >= 2) 
        multiplier = pow(10, (digits-1));  
    else 
        return (str[0] - '0');      
    
    int converted[digits];
    for (int i=0;i < digits;i++) {
        converted[i] = (str[i] - '0'); 
        converted[i] *= multiplier;
        multiplier /= 10;
    }
            
    int final = 0;
    for (int i=0;i < digits;i++) 
        final += converted[i];    
    
    return final;
}
            
        
                