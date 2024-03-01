#include "DataDecoder.h"

using namespace std;

data decode(char *input)
{
    data inputData;

    char delim = ' ';
    char *delimPtr = &delim;

    char *token = strtok(input, delimPtr); // This will be the type of data. e.g.: DATE, TIME, GPS, RADEC

    inputData.type = token;

    token = strtok(NULL, delimPtr); // The next part of the data.

    if (inputData.type == "DATE")
    {
        *delimPtr = '.';
    }
    else if (inputData.type == "TIME")
    {
        *delimPtr = ':';
    }
    else if (inputData.type == "GPS" || inputData.type == "RADEC")
    {
        *delimPtr = ',';
    }

    token = strtok(token, delimPtr); // Start extracting actual data values.

    inputData.value1 = atof(token);
    token = strtok(NULL, delimPtr);
    inputData.value2 = atof(token);
    token = strtok(NULL, delimPtr);
    inputData.value3 = atof(token);

    return inputData;
}