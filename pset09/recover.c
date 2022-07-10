#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover image\n");
        return 1;
    }

    // Open input file
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    FILE *outfile = NULL;
    char outfilename[100];
    int file_count = 0;
    BYTE buf[512];
    while (fread(&buf, sizeof(buf), 1, infile)) {
    	if (buf[0] == u'\xFF' && buf[1] == u'\xD8' && buf[2] == u'\xFF'
    	    && ( (buf[3] & u'\xE0') == u'\xE0' ) ) {

    	    if (outfile != NULL) {
    	        fclose(outfile);
    	    }
    	    sprintf(outfilename, "%03i.jpg", file_count);
    	    file_count ++;
            // Open output file
            outfile = fopen(outfilename, "w");
            if (outfile == NULL)
            {
                fclose(infile);
                fprintf(stderr, "Could not create %s.\n", outfilename);
                return 1;
            }
        }
        if (outfile != NULL) {
            fwrite(buf, sizeof(buf), 1, outfile);
        }
    }
    return 0;
}
