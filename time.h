#include <time.h>
#define LEN 150

int timeStamp(){
        char buf[LEN];
        time_t curtime;
        struct tm *loc_time;
        curtime = time (NULL);
        loc_time = localtime (&curtime);
        strftime (buf, LEN, "%b %d 2018", loc_time);
        fputs (buf, stdout);
        strftime (buf, LEN, "\nTime   : %I:%M %p", loc_time);
        fputs (buf, stdout);
        return 0;
}
