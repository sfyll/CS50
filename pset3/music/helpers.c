// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>
#include "helpers.h"
#include <stdio.h>


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator = fraction[0] - '0';
    int denominator = fraction[2] - '0';

    return 8 * numerator / denominator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    double frequency = 0.0;
    int semitonechange = 0;
    int accidentalsoffset = 0;
    int octaveoffset = 0;
    int noteoffset = 0;
    switch (note[0])
    {
        case 'A':
            noteoffset = 0;
            break;
        case 'B':
            noteoffset = +2;
            break;
        case 'C':
            noteoffset = -9;
            break;
        case 'D':
            noteoffset = -7;
            break;
        case 'E':
            noteoffset = -5;
            break;
        case 'F':
            noteoffset = -4;
            break;
        case 'G':
            noteoffset = -2;
            break;
    }
    if(note[1] == 'b')
        {
            accidentalsoffset = -1;
            octaveoffset = note[2] -'0' - 4;
        }
    else if(note[1] == '#')
        {
            accidentalsoffset = +1;
            octaveoffset = note[2] - '0' - 4;
        }
    else
        {
            octaveoffset = note[1] - '0' - 4;
        }
    semitonechange = 12*octaveoffset + noteoffset + accidentalsoffset;
    frequency = 440 * pow(2.0, semitonechange/12.0);
    int final = round(frequency);
    //float test = pow(2.0, semitonechange/12.0);
    //printf("%f // ", test);
    //printf("%d", noteoffset);
    //printf("%d", accidentalsoffset);
    //printf("%d", octaveoffset);
    //printf("%d", frequency);
    //printf("%d", semitonechange);
    return final;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if(s[0] == '\0')
    {
       return true;
    }
    return false;
}
