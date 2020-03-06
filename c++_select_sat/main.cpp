//  select sats
//  this is the C code compiled with C++
//  as of 29 feb 2020
//  Copyright © 2019 charles phillips. All rights reserved.
//  read in a TLE, all three lines, and fscanf the individual lines
// runs on Mike's computer, on the MacBook Pro, and on the Mac Mini

#include <iostream>
#include <stdio.h>
#include <string.h> // strtok, strcpy stuff not even used yet
#include <stdlib.h> // atoi, atof not used yet
#include <math.h>  // math functions

// uncomment on of the two following depending on who's directory structure in use
  #define CHARLES_Mini
//  #define CHARLES_MacBook
// #define MIKE

// set up constants needed
#define MU  398600.4418  // gravitational parameter
#define min_per_day  1440  // minutes per day
#define sec_per_day  86400   //seconds per day
#define PI        3.141592653589
#define Two_Pi  6.283185307  // 2 times Pi (for use in finding semi-major axis)

// define strings, each card starts as a string
char name_card[80] = {0};  // imported first card of three, name (not needed)
char second_card[80] = {0}; // imported second line, card 1
char third_card[80] = {0}; // imported third line, card 2
char LINE_LEN = 80;  // define line length as 80 char  is this a good definition? =80

// define variables, no structure here!!
int card1;
int satno1;
char sat_name[12] = "\0\0\0\0\0\0\0\0\0\0\0"; // name assigned, fill with \0
char int_des;  // char is ok? want to discard blanks
float epoch; // not yet scanned
char card2;  // same as card1
int satno2; // same as satno1
float inclination;
float mean_anomaly;
float big_eccentricity; // format has implied decimal point
float eccentricity;  // divide to get actual value
float arg_perigee; // argument of perigee
float raan;  // Right Ascension of Ascending Node
float mean_motion; // revs per day
float apogee = 0.0; // initial value
float perigee = 0.0; // initial value
float intermediate_one = 0.0;
// (mean motion x2 xpi/sec per day) not squared, inverted
float intermediate_two = 0.0; // intermediate_one, squared
float intermediate_three = 0.0; // intermediate two, cube root
float semi_major = 0.0; // semi-major axis cube root of: mu * intermediate three squared
// set variables as float - intermediate_one, _two, _three
// they were defined as long integers!
void inputFile (FILE* input);   // read from file

void printParameters (FILE* output);  // print to display, file

// define functions
char cardOne (char* name_card);
// parse name card to try to get rid of char return
char cardTwo (char* second_card);  // parse card #1
char cardThree (char* third_card);  // parse card #2

void inputFile (FILE* spInput)  // read from input file, this works (duh)
{
    fgets(name_card, LINE_LEN, spInput);  // get first line of TLE
    fgets(second_card, LINE_LEN, spInput);  // get first line of TLE, outside of the while
    fgets(third_card, LINE_LEN, spInput);  // outside of the while loop
    // how do these statements know to go to sequential lines?
} // end of inputFile

char cardOne (char* name_card)  // this reads name card!!
// scans to get name without CR - this darn version still has that CR
{
    sscanf (name_card,"%12c", sat_name); // scan card #1, sat_name is a pointer
    //  printf("\n");  // blank line
    return 0;
}

char cardTwo (char* second_card)
// this reads second card!! no need to print this
{
    sscanf (second_card, "%d %6dU %6c %f", &card1, &satno1, &int_des, &epoch); // scan card #1

    return 0;
}

char cardThree (char* third_card)  // this reads third card!!
{
    sscanf (third_card, "%s %6d  %f %f %f %f %f %f", &card2, &satno2, &inclination, &raan, &big_eccentricity, &arg_perigee, &mean_anomaly,
            &mean_motion); // scan card #2
  
    return 0;  // passed parameters out??
}

void printParameters (FILE* spOutput)   // move all print statements here???
{
    // the next three lines print everything - just to demo printing to two files
    printf("name card: %s \n", name_card);
    printf("second card: %s \n", second_card);
    printf("third card: %s \n", third_card);
    
     //let's try printing from inside the print function
    fprintf(spOutput, "%s", name_card);
    fprintf(spOutput, "%s", second_card);
    fprintf(spOutput, "%s", third_card);
    
//    if (satno1 == 90107)
//        //  printf("do we get here??");
//    {   fprintf(spOutput90107, "%10s", name_card);  // nothing shows up in sats.txt
//        fprintf(spOutput90107, "%s", second_card);
//        fprintf(spOutput90107, "%s", third_card);
//    }
//    else
//
//        if (satno1 == 90115)
//            //  printf("do we get here??");
//        {
//            fprintf(spOutput90115, "%10s", name_card);
//            fprintf(spOutput90115, "%s", second_card);
//            fprintf(spOutput90115, "%s", third_card);
//        }
//        else
//        {}
    
    // end of print function
}
int main(void)
{
    
    FILE* spInput; // input points to file to read from
    
   // FILE* spOutput; // output points to file to write to
    FILE* spOutput90115;  // a file just for TLEs for selected sats
    FILE* spOutput90107;  // a file just for TLEs for selected sa
    //    FILE* spOutput4418;  // a file just for TLEs for 4418
    
    // these next two lines are specific to the laptop - change for other computers.
// based on #define line at top of file - open files using either:
//      Charles directory structure (#define CHARLES_Mini)
//      or Mike's directory structure (#define MIKE)
    
#ifdef CHARLES_MacBook
    spInput = fopen("/Users/Admin/Documents/sequential_TLEs/4_mar_2020.txt", "r");  // read data from folder where the code is - now taken from
    // this took a while - now the program outputs to two files!
    //  spOutput = fopen("/Users/Charles/Documents/satellites_analyzed/sorted/sats_out.txt", "a");
    // put output in folder "sorted"
    spOutput90107 = fopen("/Users/Admin/Documents/satellites_analyzed/90107.txt", "a");  // put output in folder "sorted"
    
    spOutput90115 = fopen("/Users/Admin/Documents/satellites_analyzed/90115.txt", "a");
#endif

#ifdef CHARLES_Mini
    spInput = fopen("/Users/Charles/Documents/satellites_to_analyze/sequential_elements/8_dec_2019.txt", "r");  // read data from folder where the code is - now taken from
    // this took a while - now the program outputs to two files!
  //  spOutput = fopen("/Users/Charles/Documents/satellites_analyzed/sorted/sats_out.txt", "a");
    // put output in folder "sorted"
    spOutput90107 = fopen("/Users/Charles/Documents/satellites_analyzed/sorted/90107.txt", "a");  // put output in folder "sorted"
    
    spOutput90115 = fopen("/Users/Charles/Documents/satellites_analyzed/sorted/90115.txt", "a");
#endif
    
#ifdef MIKE
    spInput = fopen("/Users/mike/Dropbox/Projects/Charles/tle_cards.txt", "r");  // read data from folder where the code is - now taken from
    spOutput90107 = fopen("/Users/mike/Dropbox/Projects/Charles/90107.txt", "a");  // put output in folder "sorted"
    spOutput90115 = fopen("/Users/mike/Dropbox/Projects/Charles/90115.txt", "a");
#endif

    // this line would build an output file for sats which would be empty :-(
    
    //    spInput = fopen("~/tle_cards.txt", "r");  // read data from right place
    
    //    spOutput = fopen("~/tle_output.txt", "w");  // put satellite in right place
    while (feof(spInput) == 0)
    {
        
        inputFile (spInput);  // go to function inputFile and read lines
        
        //  printf("\ncards input, for test print three cards\n\n");
        
        cardOne(name_card); // call function to scan name card
        cardTwo (second_card);  // call function to read second card, card #1
        cardThree (third_card);  // call function to read third card, card #2
//
        if (satno1 == 90107)
        {
            printParameters (spOutput90107);  //just prints cards for now
        }
        else if (satno1 == 90115)
        {
            printParameters (spOutput90115);  //just prints cards for now
        }
        else
        {
            printParameters(stdout); //didn't match either so just print to terminal
        }

    } // end while reading input file
    
 //  fclose(spOutput);  // close file we put output into
    fclose(spInput);  // close file we get input from
    fclose(spOutput90115);
    fclose(spOutput90107);
    
    return 0;
}  // end main, sends to functions to read cards, parse parameters (duh)


