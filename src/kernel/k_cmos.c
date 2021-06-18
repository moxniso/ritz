#include <kernel/kcore.h>
#include <common.h>

int rk_date(void)
{
     rk_writeport(0x70, 0x08);
     char month = rk_readport(0x71);

     rk_writeport(0x70, 0x07);
     char day = rk_readport(0x71);

     rk_writeport(0x70, 0x09);
     char year = rk_readport(0x71);

     int date = (0 | month | day | year);
     return date;
}

time_strs rk_datestrs(void)
{
     time_strs ts;

     rk_writeport(0x70, 0x08);
     switch(rk_readport(0x71)) {
         case 1:
            ts.month = "January";
            break;
         case 2:
            ts.month = "February";
            break;
         case 3:
            ts.month = "March";
            break;
         case 4:
            ts.month = "April";
            break;
         case 5:
            ts.month = "May";
            break;
         case 6:
            ts.month = "June";
            break;
         case 7:
            ts.month = "July";
            break;
         case 8:
            ts.month = "August";
            break;
         case 9:
            ts.month = "September";
            break;
         case 10:
            ts.month = "October";
            break;
         case 11:
            ts.month = "November";
            break;
         case 12:
            ts.month = "December";
            break;
         default:
            ts.month = "???";
            break;
     }

     rk_writeport(0x70, 0x07);
     char day_of_month = (rk_readport(0x71) - 13);

     if (day_of_month < 10) {
         ts.day_first_digit = '0';
         ts.day_second_digit = (day_of_month + '0');
      }
      else {
         ts.day_first_digit = (((day_of_month - (day_of_month % 10)) / 10) + '0');
         ts.day_second_digit = ((day_of_month % 10) + '0');
      }

      // TODO: add year decoding

     return ts;
}
