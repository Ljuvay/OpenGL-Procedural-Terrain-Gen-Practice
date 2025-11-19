#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

const float chunkWidth = 256.0f;

const float renderDistance = 1024.0f;

const int CAMSPEEDSETTING = 25;

static int SCR_WIDTH = 800;
static int SCR_HEIGHT = 600;

extern float deltaTime;
extern float lastFrame;

/*
* ----- NOISE TYPE -----
* Options:
* PERLIN
* SIMPLEX
*/
const std::string NOISETYPE = "PERLIN";

#endif
