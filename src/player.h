#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H

#include "inventory.h"

typedef struct {
    char *name;
    Inventory *inventory;
} Player;

#endif