#include <time.h>
#include <stdio.h>

int main(void) 
{
    	tzset();

    	printf("Timezone : %ld\n", (long)timezone);
    	printf("Daylight : %d\n", daylight);
    	printf("TZname[0] : %s\n", tzname[0]);
    	printf("TZname[1] : %s\n", tzname[1]);

    	return 0;
}
