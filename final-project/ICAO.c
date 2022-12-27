#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
//Check if correct number of arguments were provided
if (argc != 2) {
printf("Please provide airport ICAO identifier as argument.\n");
return 1;
}

//Store airport identifier in a variable
char* airport_icao = argv[1];

//URL for retrieving METAR data for the given airport
char url[100];
sprintf(url, "https://tgftp.nws.noaa.gov/data/observations/metar/stations/%s.TXT", airport_icao);

//Retrieve METAR data using the URL
FILE* fp = fopen(url, "r");
if (fp == NULL) {
printf("Unable to retrieve METAR data for %s\n", airport_icao);
return 1;
}

//Read and print the METAR data
char line[256];
while (fgets(line, sizeof(line), fp)) {
printf("%s", line);
}

//Close the file
fclose(fp);
return 0;
}