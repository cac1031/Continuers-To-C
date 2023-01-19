////////////////////////////////////////////////////////////////////////////////

// Simple Pokedex
// What will I need to do?

// 1) I have decided I want to start a Pokedex
// I want the Pokedex to be able to:
// 2) Add a Pokemon to the end of my list (providing it the name and index)
// 3) Print the Pokemons we have in our Pokedex
// 4) Delete a Pokemon based on it's index
// 5) Destroy the entire Pokedex

////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

////////////////////////////////////////////////////////////////////////////////

// TODO: Define my structs to represent a Pokemon node which has a name & index
// TODO: typedef the pointer to my struct


// TODO: Define my root struct which points to the head of the list
// TODO: typedef the pointer to my root struct
// Root structure - starting my Pokedex, which will have Pokemons


////////////////////////////////////////////////////////////////////////////////

// Function Declarations
Pokedex PokedexSetup();
void PokedexAppend(Pokedex p, char *name, int index);
void PokedexPrint(Pokedex p);
void PokedexRemove(Pokedex p, int index);
void PokedexDestroy(Pokedex p);

////////////////////////////////////////////////////////////////////////////////

int main (void) {
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

/** TODO: 
 *  Setup the Pokedex
 *  Returns an empty Pokedex
 */
Pokedex PokedexSetup() {
    return NULL;
}

/** TODO:
 *  Appends a Pokemon to our Pokedex 
 */
void PokedexAppend(Pokedex p, char *name, int index) {
    // Empty List

    // Non-Empty List
}

/** TODO: 
 *  Prints all the pokemons we have in the Pokedex
 */
void PokedexPrint(Pokedex p) {

}

/** TODO:
 *  Removes a Pokemon with index index
 *  from our Pokedex
 */
void PokedexRemove(Pokedex p, int index) {
    // Empty List, nothing to be deleted

    // One node list, but relevant node does not exist

    // Delete at the head

    // Delete at the middle/tail

}

/** TODO:
 *  Destroys all memory associated with the Pokedex
 */
void PokedexDestroy(Pokedex p) {

}
