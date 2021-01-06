#include "std_lib_facilities.h"


struct Reading {
    int hour;
    double temperature;
};

double random_double(int dec, double min, double max);

int main() {
    ofstream of{"raw_temps.txt"};
    if (!of) error("something wrong opening the file");
    srand(time(NULL));
    for (int i = 0; i < 50; i++) {
        int hr = (int)random_double(0, 0, 23);
        double temp = random_double(3, -30, 100);
        of << hr << '\t' << temp << '\n';
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