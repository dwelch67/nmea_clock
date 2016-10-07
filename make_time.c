
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//"$GPRMC,235946.084,V,,,,,,,,,,N*44";

char xstring[128];

unsigned int hh,mm,ss;

FILE *fp;

void checksum_out ( void )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    rb=0;
    for(ra=1;xstring[ra];ra++)
    {
        rb^=xstring[ra];
    }
    rb&=0xFF;
    fprintf(fp,"%s*%02X\n",xstring,rb);
}
void one_second ( void )
{
    ss++;
    if(ss>59) { ss=0; mm++; }
    if(mm>59) { mm=0; hh++; }
    if(hh>23) hh=0;
}
int main ( void )
{
    unsigned int ra;

    fp=fopen("test.dat","wt");
    if(fp==NULL)
    {
        printf("Error creating file\n");
        return(1);
    }

    hh=16;
    mm=17;
    ss=18;


    for(ra=0;ra<50000;ra++)
    {
        sprintf(xstring,"$GPRMC,%02u%02u%02u,V,,,,,,,,,,N",hh,mm,ss);
        checksum_out();
        one_second();
    }
    for(ra=0;ra<30000;ra++)
    {
        sprintf(xstring,"$GPRMC,%02u%02u%02u.00,V,,,,,,,,,,N",hh,mm,ss);
        checksum_out();
        one_second();
    }
    for(ra=0;ra<30000;ra++)
    {
        sprintf(xstring,"$GPRMC,%02u%02u%02u.000,V,,,,,,,,,,N",hh,mm,ss);
        checksum_out();
        one_second();
    }
    for(ra=0;ra<50000;ra++)
    {
        sprintf(xstring,"$GPRMC,%02u%02u%02u,A,,,,,,,,,,A",hh,mm,ss);
        checksum_out();
        one_second();
    }
    for(ra=0;ra<30000;ra++)
    {
        sprintf(xstring,"$GPRMC,%02u%02u%02u.00,A,,,,,,,,,,A",hh,mm,ss);
        checksum_out();
        one_second();
    }
    for(ra=0;ra<30000;ra++)
    {
        sprintf(xstring,"$GPRMC,%02u%02u%02u.000,A,,,,,,,,,,A",hh,mm,ss);
        checksum_out();
        one_second();
    }

    fclose(fp);
}




