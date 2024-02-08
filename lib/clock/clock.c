#define CURRENT_YEAR        2024                            // Change this each year!
 
unsigned char second;
unsigned char minute;
unsigned char hour;
unsigned char day;
unsigned char month;
unsigned uint32_t year;

typedef struct {
    uint8_t seconds;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint32_t;
} datetime_t;

datetime_t time;

uint32_t clock_getupdate() {
      outb(0x70, 0x0A);
      return (inb(0x71) & 0x80);
}
 
unsigned char clock_getregister(uint32_t reg) {
      outb(0x70, reg);
      return inb(0x71);
}
 
void read_rtc() {
    unsigned char century;
    unsigned char last_second;
    unsigned char last_minute;
    unsigned char last_hour;
    unsigned char last_day;
    unsigned char last_month;
    unsigned char last_year;
    unsigned char last_century;
    unsigned char registerB;
    
    while (clock_getupdate());
    time->second = clock_getregister(0x00);
    time->minute = clock_getregister(0x02);
    time->hour = clock_getregister(0x04);
    time->day = clock_getregister(0x07);
    time->month = clock_getregister(0x08);
    time->year = clock_getregister(0x09);
    if(0x00 != 0) {
          century = clock_getregister(0x00);
    }

    do {
          last_second = time->second;
          last_minute = time->minute;
          last_hour = time->hour;
          last_day = time->day;
          last_month = time->month;
          last_year = time->year;
          last_century = century;

          while (clock_getupdate());           // Make sure an update isn't in progress
          time->second = clock_getregister(0x00);
          time->minute = clock_getregister(0x02);
          time->hour = clock_getregister(0x04);
          time->day = clock_getregister(0x07);
          time->month = clock_getregister(0x08);
          time->year = clock_getregister(0x09);
          if(0x00 != 0) {
                century = clock_getregister(0x00);
          }
    } while( (last_second != time->second) || (last_minute != time->minute) || (last_hour != time->hour) ||
             (last_day != time->day) || (last_month != time->month) || (last_year != time->year) ||
             (last_century != century) );

    registerB = clock_getregister(0x0B);
 
    if (!(registerB & 0x04)) {
          time->second = (time->second & 0x0F) + ((time->second / 16) * 10);
          time->minute = (time->minute & 0x0F) + ((time->minute / 16) * 10);
          time->hour = ( (time->hour & 0x0F) + (((time->hour & 0x70) / 16) * 10) ) | (time->hour & 0x80);
          time->day = (time->day & 0x0F) + ((time->day / 16) * 10);
          time->month = (time->month & 0x0F) + ((time->month / 16) * 10);
          time->year = (time->year & 0x0F) + ((time->year / 16) * 10);
          if(0x00 != 0) {
                century = (century & 0x0F) + ((century / 16) * 10);
          }
    }
    // Convert 12 hour clock to 24 hour clock if necessary
    if (!(registerB & 0x02) && (time->hour & 0x80)) {
          time->hour = ((time->hour & 0x7F) + 12) % 24;
    }
    // Calculate the full (4-digit) year
    if(0x00 != 0) {
          time->year += century * 100;
    } else {
          time->year += (CURRENT_YEAR / 100) * 100;
          if(time->year < CURRENT_YEAR) time->year += 100;
    }
}