# unpretty
Simple C program to "unpretty" JSON that has been "*pretty printed*".

Input is read from STDIN and output is written to STDOUT.

## Building on Mac or Linux
gcc -o unpretty unpretty.c

## Usage

cat myinput.json | unpretty > myoutput.json

