#include "Random.h"

random_device dev;
default_random_engine dre{dev()};