// COMP CLUB SUMMER SCHOOL 2023 - BITWISE OPERATION EXERCISE
// In this exercise, we define Pokemons as 
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Constants for Pokemon Types
#define POKEMON_SIZE  16
#define NORMAL_TYPE   0x0001
#define GRASS_TYPE    0x0002
#define FIRE_TYPE     0x0004
#define WATER_TYPE    0x0008
#define BUG_TYPE      0x0010
#define FIGHTING_TYPE 0x0020
#define GROUND_TYPE   0x0040
#define ROCK_TYPE     0x0080
#define DRAGON_TYPE   0x0100
#define GHOST_TYPE    0x0200
#define POISON_TYPE   0x0400
#define PSYCHIC_TYPE  0x0800
#define ELECTRIC_TYPE 0x1000
#define FLYING_TYPE   0x2000
#define ICE_TYPE      0x4000

// Lookup Table for Pokemon Types
// There are 15 in Total
const char *pokemons[] = {
    "\e[1;48;5;144m normal ", "\e[1;48;5;76m grass ", "\e[1;48;5;208m fire ", 
    "\e[1;48;5;12m water ", "\e[1;48;5;112m bug ", "\e[1;48;5;196m fighting ", 
    "\e[1;48;5;180m ground ", "\e[1;48;5;94m rock ", "\e[1;48;5;57m dragon ", 
    "\e[1;48;5;55m ghost ", "\e[1;48;5;91m poison ", "\e[1;48;5;205m psychic ", 
    "\e[1;48;5;11m electric ", "\e[1;48;5;141m flying ", "\e[1;48;5;123m ice "
};

//////////////////////////// T O  I M P L E M E N T ////////////////////////////
void addType(uint16_t *pokemon, uint16_t type);
void removeType(uint16_t *pokemon, uint16_t type);
int countTypes(uint16_t pokemon);
bool isType(uint16_t pokemon, uint16_t type);

////////////////// T O  I M P L E M E N T : C H A L L E N G E //////////////////
int commonTypes(uint16_t pokemon1, uint16_t pokemon2);

//////////////////////////// I M P L E M E N T E D /////////////////////////////
///////// U S E  T H I S  T O  C H E C K  I M P L E M E N T A T I O N //////////
void showTypes(uint16_t pokemon);
void printBits(uint16_t value);

////////////////////////////////////////////////////////////////////////////////
int main (void) {
    uint16_t bulbasaur = POISON_TYPE;
    uint16_t jynx = ICE_TYPE | PSYCHIC_TYPE;
    /* Add your functions here after implemented */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////

/** TODO:
 * Add a type to a Pokemon using pointer dereferencing
 */
void addType(uint16_t *pokemon, uint16_t type) {

}

/** TODO:
 *  Remove a type to a Pokemon using pointer dereferencing
 */
void removeType(uint16_t *pokemon, uint16_t type) {
    
}

/** TODO:
 *  Count the number of types a Pokemon has
 */
int countTypes(uint16_t pokemon) {
    return 0;
}

/** TODO:
 *  Checks if a pokemon is of a certain type
 */
bool isType(uint16_t pokemon, uint16_t type) {
    return true;
}

/** TODO (CHALLENGE):
 *  Returns the number of common types between two pokemons
 */
int commonTypes(uint16_t pokemon1, uint16_t pokemon2) {
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// DONE:
// Displays the types a pokemon has with 🌈colours🌈 //
void showTypes(uint16_t pokemon) {
    int types[POKEMON_SIZE] = {0};
    int size = 0;
    for (int i = 0; i < POKEMON_SIZE - 1; i++) {
        uint16_t mask = 1u << i;
        if (pokemon & mask) {
            types[size++] = i;
        }
    }

    size == 0 ? printf("Pokemon has no types") : printf("The pokemon has types:\n");
    for (int i = size - 1; i >= 0; i--) {
        printf("%8s", pokemons[types[size - 1 - i]]);
    } printf("%s\n", "\e[0m");
}

// DONE:
// Debugging Function that prints which bits are turned on or off //
void printBits(uint16_t value) {
    for (int i = 0; i < POKEMON_SIZE; i++) {
        uint16_t mask = 1u << (POKEMON_SIZE - i - 1);
        if (i % 4 == 0) {
            printf(" ");
        }
        (value & mask) ? printf("1") : printf("0");
    }
    printf("\n");
}
