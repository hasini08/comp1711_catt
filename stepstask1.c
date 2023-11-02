#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

// Define any additional variables here

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Outputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);

    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {
        strcpy(date, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }

    // Free the duplicated string
    free(inputCopy);
}

int main() {
    // Define array to store FITNESS_DATA records
    FITNESS_DATA records[1000];  

    // Open the input file
    FILE *file = fopen("FitnessData_2023.csv", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open the file.\n");
        return 1;
    }

    // Read data and store it in an array
    char line[80];  // Assume a maximum line length of 80 characters
    int numRecords = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char date[11], time[6], stepsStr[20];

        // Tokenize the line to extract the  date, time, and steps
        tokeniseRecord(line, ",", date, time, stepsStr);

        // Convert steps to an integer
        int steps = atoi(stepsStr);

        // Store the data in tan array
        if (numRecords < 1000) {
            strcpy(records[numRecords].date, date);
            strcpy(records[numRecords].time, time);
            records[numRecords].steps = steps;
            numRecords++;
        }
    }

    fclose(file);

    // Output number of records
    printf("Number of records in the file: %d\n", numRecords);

    // Output first three rows
    for (int i = 0; i < 3 && i < numRecords; i++) {
        printf("%s/%s/%d\n", records[i].date, records[i].time, records[i].steps);
    }

    return 0;
}
