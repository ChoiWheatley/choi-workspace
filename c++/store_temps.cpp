/*
 * << PPPUC++ Chapter10 Exercise2 >>
 * Write a program that creates a file of data in the form of the temperature Reading type defined in §10.5. 
 * For testing, fill the file with at least 50 “temperature readings.” 
 * Call this program store_temps.cpp and the file it creates raw_temps.txt.
 * 
 * << PPPUC++ Chapter10 Exercise4 >> add suffix 'c' and 'f' 
 * Modify the store_temps.cpp program from exercise 2 to include a temperature suffix c for Celsius 
 * or f for Fahrenheit temperatures. 
 * Then modify the temp_stats.cpp program to test each temperature, 
 * converting the Celsius readings to Fahrenheit before putting them into the vector.
 */ 

#include "std_lib_facilities.h"


struct Reading {
    int hour;
    double temperature;
    char format;
};
constexpr char Celsius = 'c';
constexpr char Fahrenheit = 'f';

double random_double(int dec, double min, double max);

int main() {
    ofstream of{"raw_temps.txt"};
    if (!of) error("something wrong opening the file");
    srand(time(NULL));
    for (int i = 0; i < 50; i++) {
        int hr = (int)random_double(0, 0, 23);
        double temp = random_double(3, -30, 100);
        char fmt = (rand()%2 == 0 ? Celsius : Fahrenheit);
        of << hr << '\t' << fmt << temp << '\n';
    }
    of << '\b';
    return 0;
}
double random_double(int dec, double min, double max) {
    return (
        (double)((long int)rand() %
                     (long int)((max - min + 1) * pow(10, dec)) /
                     pow(10, dec) +
                 min));
}