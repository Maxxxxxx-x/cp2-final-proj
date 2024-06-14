#include <stdbool.h>
#include <unistd.h>

#include "utils.h"

bool fileExists(char *path) {
    return (access(path, F_OK) == 0);
}
