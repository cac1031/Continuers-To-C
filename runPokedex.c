// DO NOT MODIFY THIS FILE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "Pokedex.h"

#define MAX 100
#define BIN_BASE 2
#define PLACEHOLDER 0b0000000000000001
#define POKEMON_TYPES 15
#define INVALID_TYPE 0b1000000000000000

#define BORDER "\e[0;94m"
#define FILL "\e[0;93m"
#define FONT "\e[1;31m"
#define RESET "\e[0m"

static void showWelcomeMessage(void);
static bool getCommand(char *buf);
static char **tokenize(char *s, int *ntokens);
static void freeTokens(char **tokens);
static void showHelp(void);
static void showTypes(void);
static void showCmdHelp(void);

static void runPokedexAdd(Pokedex p, int argc, char *argv[]);
static bool checkGivenParams(int index, uint16_t type, double height, 
                             double weight);
static void runPokedexDelete(Pokedex p, int argc, char *argv[]);
static void runPokedexStats(Pokedex p, int argc, char *argv[]);
static void runPokedexView(Pokedex p, int argc, char *argv[]);
static void runPokedexRange(Pokedex p, int argc, char *argv[]);
static void runAddType(Pokedex p, int argc, char *argv[]);
static void runRemoveType(Pokedex p, int argc, char *argv[]);

static uint16_t typeNameToPosition(char *type);
static uint16_t typeBase16(int base, int exponent);

typedef struct command {
    char  *code;
    void (*fn)(Pokedex, int, char **);
    char  *argHint;
    char  *helpMsg;
} Command;

static Command COMMANDS[] = {
    {"a", runPokedexAdd,     "<index> <name> <type> <height> <weight>",
                             "add a new Pokémon"},
    {"d", runPokedexDelete,  "<index>",
                             "delete a Pokémon"},
    {"s", runPokedexStats,   "<index>",
                             "stats of a Pokémon"},
    {"v", runPokedexView,    "",
                             "show all the Pokémons in the Pokédex"},
    {"r", runPokedexRange,    "<start index> <end index>",
                             "show Pokémons in the Pokédex within a given index range"},
    {"+", runAddType,        "<index> <type>",
                             "add a type to a Pokémon"},
    {"-", runRemoveType,     "<index> <type>",
                             "remove a type from a Pokémon"},
    {"t", NULL,              "", "shows all the valid types a Pokémon has"},                        
    {"?", NULL,              "", "show this message"},
    {"q", NULL,              "", "quit"}
};

static const char *pokemonTypes[] = {
    "normal", "grass", "fire", "water", "bug", "fighting", "ground", "rock",
    "dragon", "ghost", "poison", "psychic", "electric", "flying", "ice"
};

static Command *currCommand = NULL;

int main (int argc, char *argv[]) {
    showWelcomeMessage();

    Pokedex p = PokedexNew();
    bool done = false;
    char cmd[MAX + 1] = {0};

    while (!done && getCommand(cmd)) {
        int ntokens = 0;
        char **tokens = tokenize(cmd, &ntokens);
        if (ntokens == 0) {
            free(tokens);
            continue;
        }
        char *cmdName = tokens[0];
        // Meta-commands
        if (strcmp(cmdName, "?") == 0) {
            showHelp();
        } else if (strcmp(cmdName, "q") == 0) {
            done = true;
        } else if (strcmp(cmdName, "t") == 0) {
            showTypes();
        // Actual commands
        } else {
            bool validCommand = false;

            int numCommands = sizeof(COMMANDS) / sizeof(Command);
            for (int i = 0; i < numCommands; i++) {
                if (strcmp(cmdName, COMMANDS[i].code) == 0) {
                    validCommand = true;
                    currCommand = &COMMANDS[i];
                    COMMANDS[i].fn(p, ntokens, tokens);
                }
            }

            if (!validCommand) {
                printf("Unknown command '%s'\n", cmdName);
            }
        }
        freeTokens(tokens);
    }
    PokedexClear(p);
    return 0;
}

// called in main
static void showWelcomeMessage(void) {
    printf("%s                               .;:**'\n", BORDER);
    printf("%s   .:XHHHHk.              db.  `.;;.     dH  MX\n", BORDER);
    printf("%s oMMMMMMMMMMM       ~MM  dMMP :MMMMMR   MMM  MR      ~MRMN\n", BORDER);
    printf("%s QMMMMMb  \"MMX       MMMMMMP !MX' :M~   MMM MMM  .oo. XMMM 'MMM\n", BORDER);
    printf("%s    `MMMM.  )M> :X!Hk. MMMM   XMM.o\"  .  MMMMMMM X?XMMM MMM>!MMP\n", FILL);
    printf("%s    'MMMb.dM! XM M'?M MMMMMX.`MMMMMMMM~ MM MMM XM `\" MX MMXXMM\n", FILL);
    printf("%s     ~MMMMM~ XMM. .XM XM`\"MMMb.~*?**~ .MMX M t MMbooMM XMMMMMP\n", FILL);
    printf("%s      ?MMM>  YMMMMMM! MM   `?MMRb.    `\"""   !L\"MMMMM XM IMMM\n", FILL);
    printf("%s       MMMX   \"MMMM\"  MM       ~k:           !Mh.\""" dMI IMMP\n", BORDER);
    printf("%s       'MMM                                              IMX\n", BORDER);
    printf(RESET);
    printf("=========================[ %sPokédex%s ]========================\n", "\e[1;37m", RESET);
    printf("%s         Hello there! Welcome to the World of Pokémon.        \n", FONT);
    printf("%s             Enter ? to see the list of commands.             %s\n", FONT, RESET);
    printf("============================================================\n");
}

// called by wrappers
static void showCmdHelp(void) {
    printf("Usage: %s %s\n", currCommand->code, currCommand->argHint);
}

// called when user inputs '?'
static void showHelp(void) {
    printf("Commands:\n");
    int numCommands = sizeof(COMMANDS) / sizeof(Command);
    for (int i = 0; i < numCommands; i++) {
        printf("%s%5s\t%s%-39s\t %s%s\n", FONT, COMMANDS[i].code, 
                                          FILL, COMMANDS[i].argHint,
                                          BORDER, COMMANDS[i].helpMsg);
    }
    printf(RESET);
    printf("\n");
}

// called when user inputs 't'
static void showTypes(void) {
    printf("Valid Types:\n");
    for (int i = 0; i < POKEMON_TYPES; i++) {
        printf("%s %s\n", typeColours[i], RESET);
    }
    printf("\n");
}

// called by main
static bool getCommand(char *buf) {
    printf("> ");
    if (fgets(buf, MAX, stdin) != NULL) {
        int len = strlen(buf);
        if (len > 0 && buf[len - 1] != '\n') {
            buf[len] = '\n';
            buf[len + 1] = '\0';
        }
        return true;
    } else {
        return false;
    }
}

// called by main
static char **tokenize(char *s, int *ntokens) {
    char *separators = " \t\r\n";
    *ntokens = 0;

    char **tokens = calloc((strlen(s) + 1), sizeof(*tokens));
    assert(tokens != NULL);

    while (*s != '\0') {
        s += strspn(s, separators);

        if (*s == '\0') {
            break;
        }

        size_t length = strcspn(s, separators);

        char *token = strndup(s, length);
        assert(token != NULL);
        s += length;

        tokens[*ntokens] = token;
        (*ntokens)++;
    }

    tokens[*ntokens] = NULL;

    tokens = realloc(tokens, (*ntokens + 1) * sizeof(*tokens));
    assert(tokens != NULL);

    return tokens;
}

// called by main
static void freeTokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
////////////////////////////////////////////////////////////////////////////////
static void runPokedexAdd(Pokedex p, int argc, char *argv[]) {
    if (argc != 6) {
        showCmdHelp();
        return;
    }
    int index = atoi(argv[1]);
    char *name = argv[2];
    uint16_t type = typeBase16(BIN_BASE, typeNameToPosition(argv[3]));
    double height = atof(argv[4]);
    double weight = atof(argv[5]);

    if (!checkGivenParams(index, type, height, weight)) {
        return;
    }

    if (PokedexAdd(p, index, name, type, height, weight)) {
        printf("%s was successfully added to the Pokedex!\n", name);
    }
}

static void runPokedexDelete(Pokedex p, int argc, char *argv[]) {
    if (argc != 2) {
        showCmdHelp();
        return;
    }

    int index = atoi(argv[1]);
    if (!checkGivenParams(index, PLACEHOLDER, PLACEHOLDER, PLACEHOLDER)) {
        return;
    }

    if (PokedexDelete(p, index)) {
        printf("Pokemon successfully deleted from Pokedex.\n");
    }
}

static void runPokedexStats(Pokedex p, int argc, char *argv[]) {
    if (argc != 2) {
        showCmdHelp();
        return;
    }

    int index = atoi(argv[1]);
    if (!checkGivenParams(index, PLACEHOLDER, PLACEHOLDER, PLACEHOLDER)) {
        return;
    }

    PokedexStats(p, index);
}
static void runPokedexView(Pokedex p, int argc, char *argv[]) {
    if (argc != 1) {
        showCmdHelp();
        return;
    }

    PokedexView(p);
}

static void runPokedexRange(Pokedex p, int argc, char *argv[]) {
    if (argc != 3) {
        showCmdHelp();
        return;
    }
    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    if (start <= 0 || end <= 0) {
        printf("start or end must be positive\n");
    } else if (start > end) {
        printf("start must be greater than or equal to end\n");
    } else {
        PokedexRange(p, start, end);
    }
}

static void runAddType(Pokedex p, int argc, char *argv[]) {
    if (argc != 3) {
        showCmdHelp();
        return;
    }
    int index = atoi(argv[1]);
    uint16_t type = typeBase16(BIN_BASE, typeNameToPosition(argv[2]));
    
    if (!checkGivenParams(index, type, PLACEHOLDER, PLACEHOLDER)) {
        return;
    }

    if (TypeAdd(p, index, type)) {
        printf("Type %s successfully added!\n", argv[2]);
    }
} 

static void runRemoveType(Pokedex p, int argc, char *argv[]) {
    if (argc != 3) {
        showCmdHelp();
        return;
    }

    int index = atoi(argv[1]);
    uint16_t type = typeBase16(BIN_BASE, typeNameToPosition(argv[2]));
    
    if (!checkGivenParams(index, type, PLACEHOLDER, PLACEHOLDER)) {
        return;
    }

    if (TypeRemove(p, index, type)) {
        printf("Type %s successfully removed!\n", argv[2]);
    }
}

////////////////////////////////////////////////////////////////////////////////
static bool checkGivenParams(int index, uint16_t type, double height, 
                             double weight) {
    if (index <= 0) {
        printf("Error: Pokemon index must be a positive number.\n");
        return false;
    } else if (type == INVALID_TYPE) {
        printf("Error: Invalid Pokemon type. Type 't' to view valid types.\n");
        return false;
    } else if (height <= 0 || weight <= 0) {
        printf("Error: Pokemon height and weight must be more than zero!\n");
        return false;
    } else {
        return true;
    }
}

static uint16_t typeNameToPosition(char *type) {
    uint16_t pokemonIndex = 0;
    for (int i = 0; i < POKEMON_TYPES; i++) {
        if (strcmp(type, pokemonTypes[i]) == 0) {
            return pokemonIndex; 
        }
        pokemonIndex++;
    }
    return INVALID_TYPE;
}

static uint16_t typeBase16(int base, int exponent) {
    if (exponent == INVALID_TYPE) {
        return INVALID_TYPE;
    }
    if (exponent == 0) {
        return 1;
    }
    return base * typeBase16(base, exponent - 1);
}
