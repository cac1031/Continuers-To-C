#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include "Pokedex.h"

#define POKEMON_SIZE 16

// DO NOT MODIFY: Struct definition for a Pokemon
struct pokemon {
    int index;
    char *name;
    uint16_t type;
    double height;
    double weight;
    Pokemon next;
};

// DO NOT MODIFY: Root struct definition for a Pokedex
struct pokedex {
    Pokemon first;
    Pokemon last;
    int size;
};

// DO NOT MODIFY: Array to store Pokemon types with colours (don't worry about this)
const char *typeColours[] = {
    "\e[1;48;5;144m normal", "\e[1;48;5;76m grass", "\e[1;48;5;208m fire", 
    "\e[1;48;5;12m water", "\e[1;48;5;112m bug", "\e[1;48;5;196m fighting", 
    "\e[1;48;5;180m ground", "\e[1;48;5;94m rock", "\e[1;48;5;57m dragon", 
    "\e[1;48;5;55m ghost", "\e[1;48;5;91m poison", "\e[1;48;5;205m psychic", 
    "\e[1;48;5;11m electric", "\e[1;48;5;141m flying", "\e[1;48;5;123m ice"
};

////////////////////////////////////////////////////////////////////////////////
// Helper functions you can use
// If you want to add more functions, add their declaration here
// Make sure to prefix them with static!
static Pokemon PokemonNew(int index, char *name, uint16_t type, double height,
                          double weight);
static void PokemonClear(Pokemon o);
static void PokemonInfo(Pokemon o);
static bool PokedexIsEmpty(Pokedex p);
static Pokemon PokedexFind(Pokedex p, int i);
static int TypeCount(Pokemon o);
static void TypeShow(Pokemon o);
static bool isType(Pokemon o, uint16_t type);
static void colourReset(void);
////////////////////////////////////////////////////////////////////////////////

// TODO: Create a New Pokedex //
Pokedex PokedexNew(void) {
    return NULL;
}

// TODO: Add Pokemon into Pokedex //
bool PokedexAdd(Pokedex p, int index, char *name, uint16_t type, double height,
                double weight) {                
    return true;
}

// TODO: Remove Pokemon from Pokedex //
bool PokedexDelete(Pokedex p, int index) {
    return true;
}

// TODO: Find specific Pokemon from Pokedex based on index //
bool PokedexStats(Pokedex p, int index) {
    return true;
}

// TODO: Show all Pokemons in Pokedex //
void PokedexView(Pokedex p) {
    return;
}

// TODO: Show Pokemon within a certain range in Pokedex //
void PokedexRange(Pokedex p, int start, int end) {
    return;
}

// TODO: Clear Pokedex //
void PokedexClear(Pokedex p) {
    return;
}

// TODO: Add a Type to a Pokemon //
bool TypeAdd(Pokedex p, int index, uint16_t type) {
    return true;
}

// TODO: Remove a Type from a Pokemon //
bool TypeRemove(Pokedex p, int index, uint16_t type) {
    return true;
}

//////////////////////// H E L P E R  F U N C T I O N S ////////////////////////
/**
 * Creates a new Pokemon instance
 */
static Pokemon PokemonNew(int index, char *name, uint16_t type, double height,
                          double weight) {
    Pokemon o = malloc(sizeof(*o));
    if (o == NULL) {
        fprintf(stderr, "Coudn't add Pokemon\n");
        exit(EXIT_FAILURE);
    }
    o->index = index;
    o->name = malloc(sizeof(char) * (strlen(name) + 1));
    if (o->name == NULL) {
        fprintf(stderr, "Coudn't allocate memory\n");
        exit(EXIT_FAILURE);
    }
    strcpy(o->name, name);
    o->type = type;
    o->height = height;
    o->weight = weight;
    o->next = NULL;
    return o;
}

/**
 * Frees all associated memory with a Pokemon
 */
static void PokemonClear(Pokemon o) {
    free(o->name);
    free(o);
}

/**
 * Finds a Pokemon based on its index
 * Returns NULL if Pokemon does not exist
 */ 
static Pokemon PokedexFind(Pokedex p, int i) {
    if (PokedexIsEmpty(p)) {
        return NULL;
    } else if (p->first->index == i) {
        return p->first;
    } else if (p->last->index == i) {
        return p->last;
    } else {
        for (Pokemon curr = p->first; curr != NULL && curr->index <= i; 
             curr = curr->next) {
            if (curr->index == i) {
                return curr;
            }
        }
    }
    return NULL;
}

/*
 * Displays info about a Pokemon similar to that of in Pokedex Entry
 * excluding the picture obviously
 */
static void PokemonInfo(Pokemon o) {
    printf("\n========[ No. %03d ]========\n", o->index);
    printf("NAME: %s\n", o->name);
    printf("TYPE: ");
    TypeShow(o);
    printf("HT  : %.2lfm\n", o->height);
    printf("WT  : %.2lfkg\n", o->weight);
    printf("Currently has %d ", TypeCount(o));
    printf("%s\n", (TypeCount(o) == 1) ? "type" : "types");
    printf("===========================\n");
}

/**
 * Checks if Pokedex is Empty
 */
static bool PokedexIsEmpty(Pokedex p) {
    return p->first == NULL;
}

/**
 * Counts the number of types a Pokemon has
 */
static int TypeCount(Pokemon o) {
    int numTypes = 0;
    for (int i = 0; i < POKEMON_SIZE; i++) {
        uint16_t mask = 1u << i;
        if (o->type & mask) {
            numTypes++;
        }
    }
    return numTypes;
}

/**
 * Displays the types a Pokemon has in words
 */
static void TypeShow(Pokemon o) {
    int types[POKEMON_SIZE] = {0};
    int size = 0;
    for (int i = 1; i < POKEMON_SIZE; i++) {
        uint16_t mask = 1u << (POKEMON_SIZE - i - 1);
        if (isType(o, mask)) {
            types[size++] = POKEMON_SIZE - i - 1;
        }
    }

    for (int i = size - 1; i >= 0; i--) {
        printf("%8s ", typeColours[types[i]]);
    }
    colourReset();
    printf("\n");
}

/**
 * Checks if a Pokemon has a certain type
 */
static bool isType(Pokemon o, uint16_t type) {
    return (o->type & type);
}

/**
 * Resets to default colour
 * Do not worry about this function
 */
static void colourReset(void) {
    printf("\e[0m");
}
