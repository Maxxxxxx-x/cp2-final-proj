#define MAX_CHARACTERS 100
#define MAX_SCENES 100
#define MAX_OPTIONS 10

typedef struct {
    int id;
    char name[51];
    char description[201];
    char sprite[101];
    int mood_happiness;
    int mood_friendship;
} Character;

typedef struct {
    char description[201];
    int next_scene;
} Option;

typedef struct {
    char speaker[51];
    char portrait[101];
    char text[201];
} Dialogue;

typedef struct {
    int id;
    char position[10];
} Actor;

typedef struct {
    int id;
    char name[51];
    char description[201];
    char background[101];
    Option* options[2];
    int optnum;
    Dialogue* dialogue;
    int has_dialogue;
    Actor* actor[2];
    int charnum;
} Scene;

void load_script(const char *filename, Character characters[], int *num_characters, Scene scenes[], int *num_scenes);
void parse_yaml(FILE *file, Character characters[], int *num_characters, Scene scenes[], int *num_scenes);
void print_script(Character characters[], int num_characters, Scene scenes[], int num_scenes);
