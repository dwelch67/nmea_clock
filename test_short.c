
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int nmea_init ( void );
extern int do_nmea ( unsigned char );
extern unsigned int nmea_timezone;
extern unsigned char nmea_time[8];

unsigned char last_time[8];

unsigned char data[4096];
unsigned char last_time[8];

void show_clock ( void )
{
    unsigned int ra;
    printf("[%s]",(char *)nmea_time);
    ra=0;
    if(last_time[0]!=nmea_time[0]) ra++;
    if(last_time[1]!=nmea_time[1]) ra++;
    if(last_time[2]!=nmea_time[2]) ra++;
    if(last_time[3]!=nmea_time[3]) ra++;
    if(ra)
    {
        last_time[0]=nmea_time[0];
        last_time[1]=nmea_time[1];
        last_time[2]=nmea_time[2];
        last_time[3]=nmea_time[3];
        last_time[4]=0;
        printf(" %s",(char *)last_time);
        //update an HH:MM clock here
    }
    printf("\n");
}
int main ( int argc, char *argv[] )
{
    unsigned int ra;
    unsigned int rb;
    FILE *fp;

    if(argc<2)
    {
        printf("nmea text file not specified\n");
        return(1);
    }
    fp=fopen(argv[1],"rb");
    if(fp==NULL)
    {
        printf("Error opening file [%s]\n",argv[1]);
        return(1);
    }
    nmea_init();
    nmea_timezone=4; //EDT
    last_time[0]=8;
    last_time[1]=8;
    last_time[2]=8;
    last_time[3]=8;
    while(1)
    {
        rb=fread(data,1,sizeof(data),fp);
        if(rb==0) break;
        for(ra=0;ra<rb;ra++)
        {
            do_nmea(data[ra]);
        }
    }
    fclose(fp);
}
