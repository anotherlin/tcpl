#include <stdio.h>

/* Same as exercise 5-8 but using pointers instead. */

static char daytab[2][13] = {

	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },

};

int day_of_year (int year, int month, int day)

{
	int	i, leap;
	char	*tab = (char *) daytab;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
        if (month < 1 || month > 12 
	|| day < 1 || day > *(tab + 13 * leap + month))

                return -1;

	for (i = 1; i < month; i++)

		day += *(tab + 13 * leap + i);

	return day;
}

int month_day (int year, int yearday, int *pmonth, int *pday)

{
	int	i, leap;
	char	*tab = (char *) daytab;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
        if (yearday < 1 || (!leap && yearday > 365) || (leap && yearday > 366))

                return -1;

	for (i = 1; yearday > *(tab + 13 * leap + i); i++)

		yearday -= *(tab + 13 * leap + i);

	*pmonth = i;
	*pday = yearday;
	
	return 0;
}

int main ()

{
        int     month, day;

        printf("day_of_year(2007, 2, 29) = %d\n", day_of_year(2007, 2, 29));
        printf("day_of_year(2007, 2, 28) = %d\n", day_of_year(2007, 2, 28));

        printf("month_day(2007, 366, &month, &day) = %d\n",
                month_day(2007, 366, &month, &day));
        printf("month_day(2007, 365, &month, &day) = %d, ",
                month_day(2007, 365, &month, &day));
        printf("month = %d, day = %d\n", month, day);

        return 0;
}
