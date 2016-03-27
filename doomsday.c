#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define THURSDAY 0
#define FRIDAY   1
#define SATURDAY 2
#define SUNDAY   3
#define MONDAY   4
#define TUESDAY  5
#define WEDNESDAY 6
 
#define TRUE 1
#define FALSE 0

// A list of doomsday days for each month. We're going to use this to normalise
// each month before counting up to the specific day requested.
const int monthDoomsdays[] = {31,28,0,4,9,6,11,8,5,10,7,12};

// Function declaration
int dayOfWeek(int doomsday, int leapYear, int month, int day);

// Main method
// This runs a series of unit tests agains the dayOfWeek function to check that
// it works.
int main(int argc, char **argv)
{
    assert (dayOfWeek (THURSDAY,  FALSE,  4,  4) == THURSDAY);
    assert (dayOfWeek (FRIDAY,    FALSE,  6,  6) == FRIDAY);
    assert (dayOfWeek (MONDAY,    FALSE,  8,  8) == MONDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 10, 10) == WEDNESDAY);
    assert (dayOfWeek (FRIDAY,    FALSE, 12, 12) == FRIDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  9,  5) == THURSDAY);
    assert (dayOfWeek (FRIDAY,    FALSE,  5,  9) == FRIDAY);
    assert (dayOfWeek (SUNDAY,    FALSE,  7, 11) == SUNDAY);
    assert (dayOfWeek (TUESDAY,   FALSE, 11,  7) == TUESDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE,  3,  7) == WEDNESDAY);

    assert (dayOfWeek (THURSDAY,  FALSE,  4,  5) == FRIDAY);
    assert (dayOfWeek (SATURDAY,  FALSE,  6,  5) == FRIDAY);
    assert (dayOfWeek (MONDAY,    FALSE,  8,  9) == TUESDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 10,  9) == TUESDAY);
    assert (dayOfWeek (FRIDAY,    FALSE, 12, 20) == SATURDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  9,  9) == MONDAY);
    assert (dayOfWeek (FRIDAY,    FALSE,  5,  5) == MONDAY);
    assert (dayOfWeek (SUNDAY,    FALSE,  7,  7) == WEDNESDAY);
    assert (dayOfWeek (TUESDAY,   FALSE, 11, 11) == SATURDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  3, 30) == SATURDAY);

    assert (dayOfWeek (TUESDAY,   FALSE,  2,  28) == TUESDAY);
    assert (dayOfWeek (TUESDAY,   FALSE,  2,  27) == MONDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  1,  3)  == THURSDAY);

    printf ("all tests passed - You are awesome!\n");
    return EXIT_SUCCESS;
}

// Determines the day of the week (as a number between 0..6, starting with 
// Sunday) for specific date given a month, day and the year's doomsday (also
// 0..6 and representing a day of the week). The leapYear flag may be set to
// 1 if the year being considered is a leap year.
int dayOfWeek(int doomsday, int leapYear, int month, int day) {
    
    // There only three steps here, but they're logically dense. So for each
    // step I'll give you an explanation of what it does, a few random examples
    // and a worked example to help cement how each step fits together.
    //
    // The three steps, broadly speaking are:
    //     1. Get a point of reference for our chosen month
    //     2. Find out which day the first day of the month is
    //     3. Count upwards from the first day of the month to the date we're
    //        trying to resolve.
    //
    // Worked example
    // --------------
    // So for our worked example, pretend we're investigating October 9th 1986,
    // the birthday of of a close friend of Marcel and mine.
    // FYI, in 1986, the Doomsday was a Friday, thus:
    //     [doomsday] = 5
    //     [leapYear] = 0
    //     [month] = 10
    //     [day] = 9
    
    // Step 1: Find out on which day of the month our doomsday falls. This will
    // give us a point of reference within the month that we're investigating:
    int monthDoomsday = monthDoomsdays[month - 1];
    
    // Telling us:
    // 
    //     Day [monthDoomsday] of [month] is a [doomsday]
    //
    // E.g. Year 2001, where the doomsday day was Wednesday ([doomsday] = 3):
    //     Day       11        of   July  is a Wednesday
    //     Day        4        of   April is a Wednesday
    //     Day       10        of October is a Wednesday
    //
    // Worked example: (given that in 1986, [doomsday] = 5)
    // ---------------
    // 
    //     Day       10        of October is a Friday
    // 
    // Or alternatively:
    //    monthDoomsday = monthDoomsdays[10 - 1]; // monthDoomsday = 10
    //
    // N.B.: We're taking the [month - 1] element of our array because arrays
    // start at 0 and our counting of months starts at 1. So Jan=0, Feb=1 ...
    
    // TODO: This doesn't adjust for leap years, which only effects Jan/Feb. 
    // You'll have to add that bit of the algorithm in, once you understand
    // how it works for non leap years.
    if (leapYear == 1
        && (month == 1 || month == 2)) {
        // We might need to shift our numbers slightly IF the month is Jan/Feb.
    }
    
    // Step 2: now that we have a point of reference within the month for our
    // doomsday ([monthDoomsDay]), and the doomsday value for that day
    // ([doomsday]), let's use this to find out what day of the week our 1st day
    // of the month is:
    int monthStartDay = (doomsday - (monthDoomsday-1)) % 7;
    // By subtracting our month's reference doomsday from the year's
    // doomsday we'll know which which weekday the 1st of our month
    // falls on. For a set month, the starting day is:
    //     
    //     Start of [month] is the day ([doomsday] - ([monthDoomsday-1])) % 7
    //
    // N.B.: We're doing monthDoomsday-1 as we count day of week beginning 0
    // and day-date beginning 1.
    //
    // Eg. In year 2001, where the doomsday was a Wednesday ([doomsday] = 3):
    // 
    //     Start of   July  is the day (     3     -  (      11     -1 )) % 7
    //         = -7 % 7 = 0 (mod 7)
    //     Start of  April  is the day (     3     -  (       4     -1 )) % 7
    //         =  0 % 0 = 0 (mod 7)
    //     Start of October is the day (     3     -  (      10     -1 )) % 7
    //         = -6 % 7 = 1 (mod 7)
    //
    // Worked example (given that in 1986, [doomsday] = 5 and our month is Oct)
    // --------------
    //
    //     Start of October is the day (     5     -  (      10     -1 )) % 7
    //         = -4 % 7 = 3 (mod 7)
    // Or alternatively:
    // 
    //     monthStartDay = (3 - (10-1)) % 7; // monthStartDay = -4;
    //
    // N.B.: This may be a negative number as modulo of a negative number can be
    // negative also, but it doesn't change the arithmetic. It might help to
    // think of these as positives as they are actually equal. E.g:
    //     -3 % 7 = -3 = 4 (mod 7)
    //     -26 % 7 = -5 = 2 (mod 7)

    // Step 3: the final step is easy. If our month starts with day X, then we
    // add the day-date we're trying to figure out, and then simply remove whole
    // 7-day weeks until we have something between 0..6: 
    // 
    // Worked example: (for 9/10/1986, [doomsday] = 5, month = 10, day = 9)
    // ---------------
    // So our [monthStartDay], as we figured out above, is -4, which in mod 7
    // is equal to 3. The computer can still think of this as -4 (the arithmetic
    // still holds), but we're going to think of it as 3.
    //
    // ([monthStartDay] + ([day]-1)) % 7 = [dayOfWeek]
    //
    // (        3       + (  9  -1)) % 7 =      4
    // 
    // And just to show that the arithmatic still holds if our monthStartDay = -4:
    //
    // (       -4       + (  9  -1)) % 7 =      4
    return (monthStartDay + (day-1) ) % 7;
}