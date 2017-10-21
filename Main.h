#ifndef MAIN_H
#define MAIN_H 0

#include <random>
#include <vector>
#include <memory>

typedef std::vector<float> vecf;

#include "Utils.h"

#define WINDOW_WIDTH      1024
#define WINDOW_HEIGHT      768

#define WINDOW_HWIDTH  (WINDOW_WIDTH / 2.0)
#define WINDOW_HHEIGHT (WINDOW_HEIGHT / 2.0)

#define MAX_BESUCHER        36

#define MS_PER_TICK         25

#define IMMUNITY            20

#define REFLECTION_ANGLE   100

#define CONE_ANGLE       25.0f
#define MEGAPHONE_RANGE 200.0f
#define VELOCITY          5.0f

#define ROTATION_PER_TICK   10

#endif /* MAIN_H */
