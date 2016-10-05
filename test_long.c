
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char test_data[]=
"$GPRMC,235946.084,V,,,,,,,310109,,,N*44";


int main ( void )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    rb=0;
    rc=0;
    for(ra=0;test_data[ra];ra++)
    {
        printf("%c 0x%02X ",test_data[ra],test_data[ra]);
        if(test_data[ra]=='$')
        {
            printf("\n");
            rc++;
            continue;
        }
        if(test_data[ra]=='*')
        {
            printf("\n");
            rc++;
            continue;
        }
        if(rc==1)
        {
            rb^=test_data[ra];
            rb&=0xFF;
            printf(": 0x%02X",rb);
        }
        printf("\n");
    }
    return(0);
}

