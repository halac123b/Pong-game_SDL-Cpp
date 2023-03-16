#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Screen size
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Initialize SDL
int initSDL(int width, int height, int argc, char *args[]);

static SDL_Window *g_window;
static SDL_Renderer *g_screen;

static SDL_Surface *screen;
static SDL_Surface *title;
static SDL_Surface *scoreMap;
static SDL_Surface *endScreen;

#endif