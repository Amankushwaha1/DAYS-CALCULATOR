#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Date 
{ 
	int d, m, y; 
}; 

// To store number of days in all months from January to Dec. 
const int monthDays[12] = {31, 28, 31, 30, 31, 30, 
						31, 31, 30, 31, 30, 31}; 

// Print current date and time in C
int main(void)
{
	// variables to store date and time components
	int hours, minutes, seconds, day, month, year;
	int Lday,Lmonth,Lyear;
	scanf("%d%d%d",&Lday,&Lmonth,&Lyear);

	// time_t is arithmetic time type
	time_t now;
	
	// Obtain current time
	// time() returns the current time of the system as a time_t value
	time(&now);

	// Convert to local time format and print to stdout
	printf("Today is : %s", ctime(&now));

	// localtime converts a time_t value to calendar time and 
	// returns a pointer to a tm structure with its members 
	// filled with the corresponding values
	struct tm *local = localtime(&now);

    hours = local->tm_hour;      	// get hours since midnight (0-23)
    minutes = local->tm_min;     	// get minutes passed after the hour (0-59)
    seconds = local->tm_sec;     	// get seconds passed after minute (0-59)

    day = local->tm_mday;        	// get day of month (1 to 31)
    month = local->tm_mon + 1;   	// get month of year (0 to 11)
    year = local->tm_year + 1900;	// get year since 1900

	// print local time
	if (hours < 12)	// before midday
		printf("Time is : %02d:%02d:%02d am\n", hours, minutes, seconds);

	else	// after midday
		printf("Time is : %02d:%02d:%02d pm\n", hours - 12, minutes, seconds);

	// print current date
	printf("Date is : %02d/%02d/%d\n", day, month, year);
	printf("\n");printf("\n");

	printf("ALWAYS GIVE DATE IN INTEGERS AND AS DAY MONTH YEAR\n");
	printf("\n");
	struct Date dt1 = {day,month,year}; 
	struct Date dt2 = {Lday,Lmonth,Lyear}; 

	int diff=getDifference(dt1, dt2); 
	printf("\nDAYS REMAINING = %d",diff);
	return 0;
}




// This function counts number of leap years before the 
// given date 
int countLeapYears(struct Date d) 
{ 
	int years = d.y; 

	// Check if the current year needs to be considered 
	// for the count of leap years or not 
	if (d.m <= 2) 
		years--; 

	// An year is a leap year if it is a multiple of 4, 
	// multiple of 400 and not a multiple of 100. 
	return years / 4 - years / 100 + years / 400; 
} 

// This function returns number of days between two given 
// dates 
int getDifference(struct Date dt1, struct Date dt2) 
{ 
	// COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1' 

	// initialize count using years and day 
	long int n1 = dt1.y*365 + dt1.d; 

	// Add days for months in given date 
	for (int i=0; i<dt1.m - 1; i++) 
		n1 += monthDays[i]; 

	// Since every leap year is of 366 days, 
	// Add a day for every leap year 
	n1 += countLeapYears(dt1); 

	// SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2' 

	long int n2 = dt2.y*365 + dt2.d; 
	for (int i=0; i<dt2.m - 1; i++) 
		n2 += monthDays[i]; 
	n2 += countLeapYears(dt2); 

	// return difference between two counts 
	return (n2 - n1); 
} 
