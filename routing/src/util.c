/*****************************************************************************
 *                                                                           *
 *                        <Routing - AStar Algorithm>                        *
 *             Copyright (C) <2018>   <Municoy, M., Salgado, D.>             *
 *                                                                           *
 *   Contact the authors at: mail@martimunicoy.com                           *
 *                           daniel.salgado@e-campus.uab.cat                 *
 *                                                                           *
 *   This program is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation, either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *****************************************************************************/

// Include Libraries
#include "routing.h"
#include "util.h"

/*
void RemoveNewLine(char* string)
{
    //Source: https://stackoverflow.com/questions/2693776/removing-trailing-new
    //                line-character-from-fgets-input/28462221
    size_t length;
    if( (length =strlen(string) ) >0)
        if(string[length-1] == '\n')
            string[length-1] ='\0';
}
*/

void CopyString(char *target, char *source)
{
    /*
    Source: https://www.w3schools.in/c-program/copy-string-using-pointers/
    */
    while(*source)
    {
        *target = *source;
        source++;
        target++;
    }
    *target = '\0';
}

bool EqualStrings(const char *s1, const char *s2)
{
    return strcmp(s1, s2) == 0;
}

bool StartsWith(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

char * SplitFields(char *str, char const *delims)
{
    /*
    Source: https://stackoverflow.com/questions/8705844/need-to-know-when-no-da
                    ta-appears-between-two-token-separators-using-strtok
    Source2: https://stackoverflow.com/questions/30294129/i-need-a-mix-of-strto
                     k-and-strtok-single/30295426#30295426
    */
    static char  *src = NULL;
    char  *p,  *ret = 0;

    if (str != NULL)
        src = str;

    if (src == NULL || *src == '\0')
        return NULL;

    ret = src;
    if ((p = strpbrk(src, delims)) != NULL)
    {
        *p  = 0;
        src = ++p;
    }
    else
        src += strlen(src);

    return ret;
}

bool ParseYesNo()
{
    printf("Yes[Y] or No[N]?\n");

    char ans[100];
    scanf("%s", ans);

    if (StartsWith(ans, "Yes") || StartsWith(ans, "yes"))
        return true;
    else if (StartsWith(ans, "No") || StartsWith(ans, "no"))
        return false;

    return ParseYesNo();
}

void ExitError(char * message, int num)
{
    fprintf(stderr, "Error %d: %s\n", num, message);
    exit(num);
}

FILE *OpenFile(const char file_dir[], char mode[], int i)
{
    FILE *f;

    f = fopen(file_dir, mode);

    if (f == NULL)
    {
        char *dir = Concat(SplitFields(strdup(file_dir), "."), ".cmap");
        if (access(dir, F_OK) != -1)
        {
            Decompress(file_dir);
            free(dir);
            return OpenFile(file_dir, mode, i);
        }
        else
        {
            free(dir);
            ExitError("when reading input file", i);
        }
    }

    return f;

}

const char *SingleArgumentParser(int argc, char *argv[])
{
    if (argc == 1)
        return NULL;

    else if (argc != 2)
        ExitError("when parsing program arguments", 45);

    return argv[1];
}

char *Concat(const char *s1, const char *s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);

    char *result = malloc(len1+len2+1);
    memcpy(result, s1, len1);
    memcpy(result+len1, s2, len2+1);

    return result;
}

void Compress(const char *bin_dir)
{
    printf("Compressing binary file...\n");

    char *command, *dir, *c1, *c2;

    // Run command to compress file
    command = Concat("gzip -f ", bin_dir);
    system(command);

    // Free memory
    free(command);

    // Run command to change file extension
    dir = Concat(SplitFields(strdup(bin_dir), "."), ".cmap");
    c1 = Concat(bin_dir, ".gz ");
    c2 = Concat("mv ", c1);
    command = Concat(c2, dir);
    system(command);

    // Free memory
    free(dir);
    free(c1);
    free(c2);
    free(command);

}

void Decompress(const char *bin_dir)
{
    printf("Decompressing binary file...\n");

    char *command, *dir, *c1, *c2;

    // Run command to change file extension
    dir = Concat(bin_dir, ".gz");
    c1 = Concat(SplitFields(strdup(bin_dir), "."), ".cmap ");
    c2 = Concat("mv ", c1);
    command = Concat(c2, dir);
    system(command);

    //Free memory
    free(dir);
    free(c1);
    free(c2);
    free(command);

    // Run command to decompress binary file
    command = Concat("gzip -d ", Concat(bin_dir, ".gz"));
    system(command);

    // Free memory
    free(command);
}