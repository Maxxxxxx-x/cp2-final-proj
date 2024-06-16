#pragma once
#ifndef _ITEM_H
#define _ITEM_H

#include "../Script/read_yaml.h"

Item *createEmptyItem();
Item *createItem(char *name, char *description, int amount, char *image);

#endif