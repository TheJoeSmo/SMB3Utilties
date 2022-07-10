/*
** Designation:  StriStr
**
** Call syntax:  char *stristr(char *String, char *Pattern)
**
** Description:  This function is an ANSI version of strstr() with
**               case insensitivity.
**
** Return item:  char *pointer if Pattern is found in String, else
**               pointer to 0
**
** Rev History:  16/07/97  Greg Thayer  Optimized
**               07/04/95  Bob Stout    ANSI-fy
**               02/03/94  Fred Cole    Original
**               09/01/03  Bob Stout    Bug fix (lines 40-41) per Fred Bulback
**
** Hereby donated to public domain.
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "stristr.h"

#define NUL '\0'

typedef unsigned int uint;

char *stristr(const char *String, const char *Pattern) {
    char *pptr, *sptr, *start;

    for (start = (char *) String; *start != NUL; start++) {
        /* find start of pattern in string */
        for (; ((*start != NUL) && (toupper(*start) != toupper(*Pattern))); start++)
            ;
        if (NUL == *start)
            return NULL;

        pptr = (char *) Pattern;
        sptr = (char *) start;

        while (toupper(*sptr) == toupper(*pptr)) {
            sptr++;
            pptr++;

            /* if end of pattern then pattern was found */

            if (NUL == *pptr)
                return (start);
        }
    }
    return NULL;
}
