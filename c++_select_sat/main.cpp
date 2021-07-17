//  select sats
//  this is the C code compiled with C++
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
 // #define CHARLES_MacBook
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

// for "GUI" version
#define satellite_number 80  // this is the satellite that a run is for

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

void inputFile (FILE* spInputTLE)  // read from input file, this works (duh)
{
    fgets(name_card, LINE_LEN, spInputTLE);  // get first line of TLE
    fgets(second_card, LINE_LEN, spInputTLE);  // get first line of TLE, outside of the while
    fgets(third_card, LINE_LEN, spInputTLE);  // outside of the while loop
    // how do these statements know to go to sequential lines?
} // end of inputFile

char cardOne (char* name_card)  // this reads name card!!
// scans to get name without CR - this darn version still has that CR
{
    sscanf (name_card,"%12c", sat_name); // scan card #1, sat_name is a pointer

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
void printParameters (FILE* spOutput42491)   // move all print statements here???
{
    // the next three lines print everything - just to demo printing to two files
   // printf("name card: %s \n", name_card);
  //  printf("second card: %s \n", second_card);
  //  printf("third card: %s \n", third_card);
    
     //let's try printing from inside the print function
    fprintf(spOutput42491, "%s", name_card);
    fprintf(spOutput42491, "%s", second_card);
    fprintf(spOutput42491, "%s\n\n", third_card);
    
} // end of print function

int main(void)
{
    FILE* spInputTLE; // input points to file to read from, file consists of TLEs
    
   // FILE* spOutput; // output points to file to write to
    FILE* spOutput11720;  // for 11720
    /*
     
    FILE* spOutput38770; // for 38770
    FILE* spOutput38773;  // for 38778
    FILE* spOutput40964;  // for 40964
    FILE* spOutput40978; // for 40978
    FILE* spOutput40981; // duh
    */
    
    // these next lines are specific to the laptop - change for other computers.
    // based on #define line at top of file - open files using either:
    // MacBook Pro directory (#define MacBook_Pro2015)
    // Mac Mini directory structure (#define CHARLES_Mini)
    // Mike's directory structure (#define MIKE)
    
#ifdef CHARLES_MacBook
    spInputTLE = fopen("/Users/Admin/Documents/alltle.txt", "r");  // read data from folder where the code is - now taken from
    // this took a while - now the program outputs to two files!
    //  spOutput = fopen("/Users/Charles/Documents/satellites_analyzed/sorted/sats_out.txt", "a");
    // put output in folder "sorted"
    
    spOutput42491 = fopen("/Users/Admin/Documents/satellites_analyzed/42491.txt","a");
    
    /*
     spOutput38770 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/38770.txt", "a");
    spOutput38773 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/38773.txt", "a");
    spOutput40964 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/40964.txt", "a");
    spOutput40978 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/40978.txt", "a") ;
    spOutput40981 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/40981.txt", "a") ;
    */
    
#endif
#ifdef CHARLES_Mini
    spInputTLE = fopen("/Users/Charles/Documents/satellites_to_analyze/sequential_elementsets/2021/all_tles.txt", "r");
    // read data from folder for satellites to analyze
  //  spOutput = fopen("/Users/Charles/Documents/satellites_analyzed/sorted/sats_out.txt", "a");
    // put output in folder "sorted"
     spOutput11720 = fopen("/Users/Charles/Documents/satellites_to_analyze/low_perigee/11720/11720_output.txt","a");
    /*
     /Users/Charles/Documents/

      spOutput38770 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/38770.txt", "a");
      spOutput38773 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/38773.txt", "a");
      spOutput40964 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/40964.txt", "a");
      spOutput40978 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/40978.txt", "a") ;
      spOutput40981 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/40981.txt", "a") ;
    */
    
#endif
    
#ifdef MIKE
    spInputTLE = fopen("/Users/mike/Dropbox/Projects/Charles/tle_cards.txt", "r");  // read data from folder where the code is - now taken from
    
     spOutput38758 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/38758.txt","a");
      spOutput38770 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/38770.txt", "a");
      spOutput38773 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/38773.txt", "a");
      spOutput40964 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/40964.txt", "a");
      spOutput40978 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/40978.txt", "a") ;
      spOutput40981 = fopen("/Users/Admin/Documents/satellites_analyzed/noss/40981.txt", "a") ;
#endif

    while (feof(spInputTLE) == 0)
    {
        
        inputFile (spInputTLE);  // go to function inputFile and read lines
        
        //  printf("\ncards input, for test print three cards\n\n");
        
        cardOne(name_card); // call function to scan name card
        cardTwo (second_card);  // call function to read second card, card #1
        cardThree (third_card);  // call function to read third card, card #2
//
        if (satno1 == 11720)
        {
            printParameters (spOutput11720);  //creates file with just 11720
        }
        /*
        else if (satno1 == 38770)
         // 38770 or other satellite numbers???
        {
            printParameters (spOutput38770);  //creates file
        }
        else if (satno1 == 38773)
        {
            printParameters(spOutput38773);
        }
        else if (satno1 == 40964)
        {
            printParameters (spOutput40964);  //creates file
        }
        else if (satno1 == 40978)
        {
            printParameters(spOutput40978);
        }
        else if (satno1 == 40981)
        {
                   printParameters(spOutput40981);
        }
         */
        
        else
        {
            printParameters(stdout); //didn't match either so just print to terminal
        }

    } // end while reading input file
    
 //  fclose(spOutput);  // close file we put output into
    fclose(spInputTLE);  // close file we get input from
    
    fclose(spOutput11720);
    
    /*
    fclose(spOutput38770);
    fclose(spOutput38773);
    fclose(spOutput40964);
    fclose(spOutput40978);
    fclose(spOutput40981);
*/
    
    return 0;
}  // end main, sends to functions to read cards, parse parameters (duh)
