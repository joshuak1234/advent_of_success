#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define IN_LEN 255
#define binarySize 12


struct binarySignal {
    int oneCount;
    int zeroCount;
};

int calculate_power(FILE *binaryInput) {

    char *binaryLine;
    char line[IN_LEN] = {0};
    int gamma = 0;
    int epsilon = 0;
    char gammaBin[binarySize];
    struct binarySignal binarySignals[binarySize] = {0};

    while (fgets(line, IN_LEN, binaryInput)) {
        for (int i = 0; i <= binarySize-1; i++) {
            if (strtol(line, &binaryLine, 2) & (1 << (i))) {
                binarySignals[i].oneCount++;
            }
            else {
                binarySignals[i].zeroCount++;
            }
        }
    }
    for (int i = binarySize-1; i >= 0; i--) {
        printf("Postion %d Values for ones: %d and zeroes: %d\n", i, binarySignals[i].oneCount, binarySignals[i].zeroCount);
    }
    
    for (int i = binarySize-1; i >= 0; i--) {
        if (binarySignals[i].oneCount > binarySignals[i].zeroCount) {
            gamma += ((pow(2,i)) * 1);
            epsilon += (pow(2,i)) * 0;
        }
        if (binarySignals[i].oneCount < binarySignals[i].zeroCount) {
            gamma += (pow(2,i)) * 0;
            epsilon += (pow(2,i)) * 1;
        }
    }
    printf("Values for gamma: %d and epsilon: %d\n", gamma, epsilon);
    return gamma * epsilon;
}

int main (int argc, char **argv) {

    if (argc < 2) {
        printf("Please provide a text file with the binary inputs\n");
        return -1;
    }

    char *filePath = (char *) malloc(255*sizeof(char));
    FILE *binaryInput;

    filePath = argv[1];
    binaryInput = fopen(filePath, "r");
    printf("Power draw is: %d\n", calculate_power(binaryInput));
}