//  select sats 10 aug 2021
//  this is the C code compiled with C++
//  Copyright © 2019 charles phillips. All rights reserved.
//  read in a TLE, all three lines, and fscanf the individual lines
// generally to just collect a file for a particular satellite though parameters are read
// runs on Mike's computer, on the MacBook Pro, and on the Mac Mini

#include <iostream>
#include <stdio.h>
#include <string.h> // strtok, strcpy stuff not even used yet
#include <stdlib.h> // atoi, atof not used yet
#include <math.h>  // math functions

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
   // printf("name card: %s \n", name_card);
  //  printf("second card: %s \n", second_card);
  //  printf("third card: %s \n", third_card);
    
     //let's try printing from inside the print function
    fprintf(spOutput, "%s", name_card);
    fprintf(spOutput, "%s", second_card);
    fprintf(spOutput, "%s", third_card);
    // end of print function
}
int main(void)
{
    
    FILE* spInputTLE;  // a file of all the TLEs
       
    FILE* spOutput = nullptr; // output points to file to write calculate results to

    printf("Which Computer??\n");
        
        char answer = 'd';  // define answer and give it a default value of d
        // sort by what?

        while (answer != 'q')
        {
            printf(" a) MacBook Pro\n");
            printf(" b) Mac Mini\n");
            printf(" c) Mike's System\n");
            printf(" q) Never Mind, Quit\n\n");

        scanf(" %c", &answer);
        
        switch (answer)
        {
            case 'a':

        spInputTLE = fopen("/Users/charlesphillips/Desktop/analyses/input_tle.txt", "r");
        spOutput = fopen("/Users/charlesphillips/Desktop/analyses/selected_satellite.txt", "w");
                       
                break;
            case 'b':

        spInputTLE = fopen("/Users/Charles/Desktop/analyses/input_tle.txt", "r");
        spOutput = fopen("/Users/Charles/Desktop/analyses/selected_satellite.txt", "w");
                        
                break;
                
                case 'c':
                        
        spInputTLE = fopen("/Users/mike/Dropbox/Projects/Charles/input_tle.txt", "r");
        spOutput = fopen("/Users/mike/Dropbox/Projects/Charles/selected_satellite.txt", "w");
                             
                break;
                
            case 'q':  // initialize spInputTLE and spOutput to stop compiler nagging
                spInputTLE = fopen("/Users/mike/Dropbox/Projects/Charles/input_tle.txt", "r");
                spOutput = fopen("/Users/mike/Dropbox/Projects/Charles/no_output.txt", "w");
                break;
            default:// initialize spInputTLE and spOutput to stop compiler nagging
                spInputTLE = fopen("/Users/mike/Dropbox/Projects/Charles/input_tle.txt", "r");
                spOutput = fopen("/Users/mike/Dropbox/Projects/Charles/no_output.txt", "w");
                break;
        }  // end of switch

    while (feof(spInputTLE) == 0)
    {
        
        inputFile (spInputTLE);  // go to function inputFile and read lines
        
        //  printf("\ncards input, for test print three cards\n\n");
        
        cardOne(name_card); // call function to scan name card
        cardTwo (second_card);  // call function to read second card, card #1
        cardThree (third_card);  // call function to read third card, card #2
//
        if (satno1 == 29249)
        {
            printParameters (spOutput);  //creates file with just 29249
        }
   /*     else if (satno1 == 90115)
        {
            printParameters (spOutput90115);  //creates file
        }
        else if (satno1 == 90122)
        {
            printParameters(spOutput90122);
        }
        else if (satno1 == 90103)
        {
            printParameters (spOutput90103);  //creates file
        }
        else if (satno1 == 90097)
        {
            printParameters(spOutput90097);
        }
        else
    
        {
            printParameters(stdout); //debug just print to terminal
            printf("\n");  // if you output to screen add a CR
        }
     */
    } // end while reading input file
    
 //  fclose(spOutput);  // close file we put output into
    fclose(spInputTLE);  // close file we get input from
    
    fclose(spOutput);
        
    return 0;
}  // end main, sends to functions to read cards, parse parameters (duh)

}
