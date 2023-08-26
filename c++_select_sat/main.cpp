//  select sats
//  as of 24 aug 2023
//  Copyright © 2019 charles phillips. All rights reserved.
//  read in a TLE, all three lines, and fscanf the individual lines
// runs on Mike's computer, on the MacBook Pro, and on the Mac Mini
// this is a terminal application that asks for satellite numbers
// this finds a list of satellites and puts them into their own files

#include <iostream>
#include <stdio.h>
#include <string.h> // strtok, strcpy stuff not even used yet
#include <stdlib.h> // atoi, atof not used yet
#include <math.h>  // math functions
#include <string> // c++ string data type & operators
#include <sstream>
#include <vector>

using namespace std; // so I can just use cin / cout not std::cin / std::out

// define strings, each card starts as a string1

#define LINE_LEN 80
char name_card[LINE_LEN] = {0};  // imported first card of three, name (not needed)
char second_card[LINE_LEN] = {0}; // imported second line, card 1
char third_card[LINE_LEN] = {0}; // imported third line, card 2

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

void inputFile (FILE* spInput)  // read 3 lines from input file
{
    fgets(name_card, sizeof(name_card), spInput);  // get first line of TLE
    fgets(second_card, sizeof(second_card), spInput);  // get second line of TLE
    fgets(third_card, sizeof(third_card), spInput);  // get third line of TLE
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
    fprintf(spOutput, "%s", name_card);
    fprintf(spOutput, "%s", second_card);
    fprintf(spOutput, "%s", third_card);
    
    // end of print function
}
int main(void)
{
    // let's look at some satellites with low perigees

    cout << "Which Mac are you on:" << endl;
    cout << "\t 1: Charles Mini" << endl;
    cout << "\t 2: Charles MacBook" << endl;
    cout << "\t 3: Mike" << endl;
    cout << "\t 0: use current directory" << endl;
    int comp = -1;  // computer definition
    while(comp < 0 or comp > 3)
    {
        while (!(cin >> comp) or comp > 3 or comp < 0) {
            cin.clear();
            cin.ignore();
            cout << "Not a valid choice, try again: ";
        }  // error check to make sure the user chose a valid computer
    }
// needed to clear input buffer??
    cin.clear();
    cin.ignore();

    /*
     /Users/charlesphillips/Desktop/analyses/input_tles.txt
     
     */
    
    string datapath;
    switch (comp) {
        case 1: //Charles Mini
            datapath = "/Users/Charles/Desktop/analyses/highinclination/";
            break;
        case 2: //Charles MacBook
            datapath = "/Users/charlesphillips/Desktop/analyses/";
            break;
        case 3: //Mike's computer
            datapath = "/Users/mike/Dropbox/Projects/Charles/testdata/";
            break;
        default:
            datapath = ""; //just use current directory
    }
    cout << "Datapath set to: " << datapath << endl;

// Now get a list of satellite numbers to process
    cout << "Enter list of satellites to process: " << endl;
    std::string line;
    std::getline(std::cin, line);
    std::istringstream thisLine(line);
    std::istream_iterator<int> begin(thisLine), end;
    std::vector<int> satsToProcess(begin, end);

//    cout << "Sats to process:";
//    for (unsigned i = 0; i < satsToProcess.size(); i++){
//        cout << ' ' << satsToProcess[i];
//    }
//    cout << endl;

    // Open the input file
    FILE* spInput = fopen ((datapath+"tles.txt").c_str(),"r");
    
    //Now open an output file for each satellite to process
    //note: the file * will be NULL if file can't be opened
    std::vector<FILE *> spOutputFiles;
    std::string filename;
    for (unsigned i = 0; i < satsToProcess.size(); i++)
    {
        filename = datapath + "spOutput" + std::to_string(satsToProcess[i]) + ".txt";
        cout << "opening file: " + filename << endl;
        spOutputFiles.push_back(fopen(filename.c_str(), "a"));
        if(spOutputFiles[i] == NULL){
            cout << "File " << filename << " could not be opened." << endl;
        }
    }

    while (feof(spInput) == 0)
    {
        
        inputFile (spInput);  // go to function inputFile and read lines
        cardOne(name_card); // call function to scan name card
        cardTwo (second_card);  // call function to read second card, card #1
        cardThree (third_card);  // call function to read third card, card #2
//
        for (unsigned i = 0; i < satsToProcess.size(); i++)
        {
            if(satno1 == satsToProcess[i]){
                if(spOutputFiles[i] != NULL){
                    printParameters(spOutputFiles[i]);
                }
            }
        }
    } // end while reading input file
    
    fclose(spInput);  // close file we get input from
    // close all the output files
    for (unsigned i = 0; i < spOutputFiles.size(); i++)
    {
        fclose(spOutputFiles[i]);
    }
//    fclose(spOutput22519);
    
    return 0;
}
