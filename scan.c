/**
 *	Projekt geforked von https://github.com/bjoekeldude/fscanf
 *	Projekt geforked von https://github.com/NP199/fscanf
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char const* const VERSIONSNR = "0.1.3";

int const DB_SIZE = 20;

struct person
{
    char name[20];
    char geburtstag[15];
    char sterbe_tag[15];
    char geburtsort[20];
    char ehepartner[30];
    char geschwister[30];
};
typedef struct person person_t;

void readcsv(char const* const datei)
{
    FILE* filepointer = NULL;
    int   zaehler     = 0;

    filepointer = fopen(datei, "r");
    if(NULL == filepointer)
    {
        fprintf(stderr, "Couldnt open file '%s'\n", datei);
        exit(2);
    }
    person_t database[DB_SIZE];
    printf("\nName:		Geburtstag:		Sterbe Tag:		Geburtsort:		Ehepartner:		Geschwister:\n");
    while(fscanf(filepointer,
                 "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],",
                 database[zaehler].name,
                 database[zaehler].geburtstag,
                 database[zaehler].sterbe_tag,
		 database[zaehler].geburtsort,
		 database[zaehler].ehepartner,
		 database[zaehler].geschwister)
          != EOF)
    {    
        printf("\n%s		%s		%s		%s			%s		%s\n",
                 database[zaehler].name,
                 database[zaehler].geburtstag,
                 database[zaehler].sterbe_tag,
                 database[zaehler].geburtsort,
                 database[zaehler].ehepartner,
                 database[zaehler].geschwister);
        zaehler++;
        if(zaehler == DB_SIZE)
        {
            fprintf(stderr, "Datenbank voll! \n");
            break;
        }
    }
    // check if file closed correctly
    if(fclose(filepointer) == EOF)
    {
        fprintf(stderr, "Fehler beim schließen der Datei! \n");
        exit(2);
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "No option recognized. Wrong Usage. Please try -h\n");
    }

    while(true)
    {
        int option = getopt(argc, argv, "hvf:");
        switch(option)
        {
        case 'h':
            printf("Bitte -f nutzen um einen File-Path anzugeben\n");
            exit(0);

        case 'v':
            printf("Version %s\n", VERSIONSNR);
            exit(0);

        case 'f':
            readcsv(optarg);
            break;

        case '?':
            fprintf(stderr, "Please try -h\n");
            exit(1);

        case -1:
            exit(0);
        }
    }

    return 0;
}
