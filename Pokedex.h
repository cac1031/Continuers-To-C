// DO NOT MODIFY THIS FILE
// Header File for Pokedex.c

#ifndef POKEDEX_H
#define POKEDEX_H

#include <stdint.h>
typedef struct pokemon *Pokemon;
typedef struct pokedex *Pokedex;
extern const char *typeColours[];

// Creates a new Pokedex instance
Pokedex PokedexNew(void);

// Insert a Pokemon into Pokedex in ascending order of index
bool PokedexAdd(Pokedex p, int index, char *name, uint16_t type, double height,
                double weight);

// Delete a Pokemon from the Pokedex
bool PokedexDelete(Pokedex p, int index);

// Finds a specific Pokemon and displays detailed info about it
bool PokedexStats(Pokedex p, int index);

// Shows all Pokemons discovered in the Pokedex
void PokedexView(Pokedex p);

// Adds a type to a Pokemon
bool TypeAdd(Pokedex p, int index, uint16_t type);

// Removes a type to a Pokemon
bool TypeRemove(Pokedex p, int index, uint16_t type);

// Clears all memory of the Pokedex
void PokedexClear(Pokedex p);

// CHALLENGE: Shows all Pokemon discovered within a certain range of the Pokedex
void PokedexRange(Pokedex p, int start, int end);
 
#endif
