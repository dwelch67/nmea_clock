
extern void show_clock ( void );


//unsigned int dollars;

//static
unsigned int nmea_timezone;
static unsigned int nmea_state;
static unsigned int nmea_off;
static unsigned char nmea_string[16];
//static
unsigned char nmea_time[8];
//static
int nmea_init ( void )
{
    nmea_state=0;
    nmea_off=0;
    nmea_timezone=0;
}
//static
int do_nmea ( unsigned char newchar )
{
    unsigned int rb;
    unsigned int rc;

//$GPRMC,054033.00,V,
    switch(nmea_state)
    {
        case 0:
        {
            if(newchar=='$') nmea_state++;
            else nmea_state=0;
            break;
        }
        case 1:
        {
            //dollars++;
            if(newchar=='G') nmea_state++;
            else nmea_state=0;
            break;
        }
        case 2:
        {
            if(newchar=='P') nmea_state++;
            else nmea_state=0;
            break;
        }
        case 3:
        {
            if(newchar=='R') nmea_state++;
            else nmea_state=0;
            break;
        }
        case 4:
        {
            if(newchar=='M') nmea_state++;
            else nmea_state=0;
            break;
        }
        case 5:
        {
            if(newchar=='C') nmea_state++;
            else nmea_state=0;
            break;
        }
        case 6:
        {
            nmea_off=0;
            if(newchar==',') nmea_state++;
            else nmea_state=0;
            break;
        }
        case 7:
        {
            if(newchar==',')
            {
                nmea_state++;
            }
            else
            {
                if(nmea_off<16)
                {
                    nmea_string[nmea_off++]=newchar;
                }
            }
            break;
        }
        case 8:
        {
            nmea_state=0;
            //-------------
            if(newchar!='A')
            {
                nmea_state=0;
                return(1);
            }
            //-------------
            //hhmmss
            if(nmea_off<6)
            {
                nmea_state=0;
                return(1);
            }
            //validate that the string is just numbers?

            //adjust for timezone
            //assume AM/PM format not 24 hour.
            rb=nmea_string[0]&0xF; //tens of hours
            rc=nmea_string[1]&0xF; //ones of hours
            //1010
            rb=/*rb*10*/(rb<<3)+(rb<<1); //times 10
            rb+=rc;
            if(rb<nmea_timezone) rb+=12;
            rb-=nmea_timezone;
            while(rb>12) rb-=12;
            if(rb==0) rb=12;
            //rb is between 1 and 12
            if(rb>9)
            {
                nmea_string[0]='1';
                rb-=10;
            }
            else
            {
                nmea_string[0]='0';
            }
            nmea_string[1]=0x30+rb;
            nmea_time[0]=nmea_string[0];
            nmea_time[1]=nmea_string[1];
            nmea_time[2]=nmea_string[2];
            nmea_time[3]=nmea_string[3];
            nmea_time[4]=nmea_string[4];
            nmea_time[5]=nmea_string[5];
            nmea_time[6]=0;
            show_clock();
            nmea_state=0;
            break;
        }
    }
    return(0);
}


