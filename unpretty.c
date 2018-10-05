/* =======================================================================================
 * Written by Scott Stokes, Copyright (c) 2018
 * 
 * Notice 
 * ------
 * This program is written as a sample of how to "unpretty" JSON objects passed to it via 
 * STDIN.  There are no warranties or guarantees of ANY kind made about this code.  
 * 
 * This was written rather quickly and is not intended to be efficient, optimized C code. 
 * 
 * After being compiled, if you want to "unpretty" the file sample.json and save the output
 * to a file named output.json, you would likely invoke this program like this:
 *   
 *   cat sample.json | ./unpretty > output.json
 *
 *======================================================================================== */
#include <stdio.h>

int main(void){
    int countOpen = 0;
    int inString = 0;
    int lastChar = 'x';

    while (1) {
        int ch = fgetc(stdin);
        if(ch == EOF) break;

        if (ch == '\n') 
        {
            lastChar = ch;
            continue;
        }

        if (ch == '"') {
            if (inString == 0)
                inString = 1;
            else
                inString = 0;
            fputc(ch,stdout);
            lastChar = ch;
            continue;
        }

        if (ch == '{') {
            countOpen++; 
            fputc(ch,stdout);
            lastChar = ch;
            continue;
        }

        if (ch == '}')
        {
            countOpen--;
            fputc(ch,stdout);
            /*
             * If we're not in an open JSON Object, write a newline
             */
            if (countOpen == 0)
            {
                fputc('\n',stdout);
            }
            lastChar = ch;
            continue;
        }

        /*
         * If I'm NOT inside a string and both ch and lastChar are spaces, skip writing
         */

        if (inString > 0)
        {
            fputc(ch,stdout);
            lastChar = ch;
            continue;
        }
        /*
         * Get rid of duplicate spaces if we're not inside of a string
         */
        if ((ch == ' ') && (lastChar == ' '))
            continue;
        /*
         * Don't add any white space before the object either
         */
        if ((countOpen == 0) && (ch == ' '))
            continue;
        
        /*
         * Otherwise write the character
         */
        fputc(ch,stdout);
        lastChar = ch;
    }
    fflush(stdout);
    return 0;
}