#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include "../definition.h"

SDL_Texture* graphic_case_fond(bric bk, SDL_Renderer *r);
void graphic_plateau(bric **carte, int TC, SDL_Renderer *r);

#endif // GRAPHIC_H_INCLUDED