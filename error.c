#include <stdio.h>
#include "error.h"

void error(char *e) {
    fprintf(stderr, "%s\n", e);
}
