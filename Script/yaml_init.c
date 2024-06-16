#include <yaml.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_yaml.h"

Character characters[3] = {
{"1", "Mike", "A passionate basketball player.", "images/mike_sprite.png", 50, 50, "images/mike.png"},
{"2", "Jess", "A park enthusiast who loves nature.", "images/jess_sprite.png", 50, 50, "images/jeff.png"},
{"3", "Tony", "A local artist who draws inspiration from the park.", "images/tony_sprite.png", 50, 50, "images/tony.png"}
};
Option options[37] = {
{"Play basketball", 2},
{"Go to the park", 3},
{"Talk to Mike", 4},
{"Keep playing", 5},
{"Talk to Jess", 6},
{"Talk to Tony", 7},
{"Sure, let's play!", 8},
{"Not now.", 9},
{"Learn the trick", 10},
{"Not interested", 9},
{"I love it too.", 11},
{"I prefer the court.", 12},
{"Sure!", 13},
{"Maybe later.", 14},
{"Chat after the game", 15},
{"Say goodbye", 16},
{"Go to the park", 3},
{"Leave the area", 16},
{"Thank Tony", 15},
{"Practice the trick", 5},
{"Continue talking", 17},
{"Go for a walk", 18},
{"Say goodbye", 16},
{"Try to find common ground", 19},
{"Compliment Tony", 20},
{"Ask about his inspiration", 21},
{"Talk to Jess", 6},
{"Walk around the park", 18},
{"End the day", 22},
{"Reflect on the day", 23},
{"Share your thoughts", 24},
{"Return to the court", 1},
{"Explore together", 18},
{"Talk more about art", 21},
{"Thank Tony", 15},
{"Reflect", 23},
{"Start over", 1}
};
Dialogue dialogues[4] = {
{"Mike", "images/mike.png", "Hey! Want to team up for a game?"},//4
{"Tony", "images/tony.png", "You have some good moves. Want to learn a trick?"},//5
{"Jess", "images/jess.png", "Hi! I love the tranquility here. How about you?"},//6
{"Tony", "images/tony.png", "Hey! I'm sketching the scenery. Want to see?"}//7
};
CharacterPosition characterPosition[16] = {
{&characters[0], LEFT},
{&characters[1], LEFT},
{&characters[2], RIGHT},
{&characters[0], LEFT},
{&characters[2], RIGHT},
{&characters[1], LEFT},
{&characters[2], RIGHT},
{&characters[0], LEFT},
{&characters[2], RIGHT},
{&characters[1], LEFT},
{&characters[1], LEFT},
{&characters[2], RIGHT},
{&characters[1], LEFT},
{&characters[1], LEFT},
{&characters[2], RIGHT},
{&characters[2], RIGHT}
};

Scene scenes[23] = {
{1, "Basketball Court", "You are at the basketball court, ready to shoot some hoops.", "images/basketball_court.png",  NULL, 0, {&options[0], &options[1]}, 2, NULL, NULL, {NULL, NULL}, 0},
{2, "Playing Basketball", "You start playing basketball. Mike joins you.", "images/basketball_court.png",  NULL, 0, {&options[2], &options[3]}, 2, NULL, NULL, {&characterPosition[0], NULL}, 1},
{3, "Park", "The park is serene with a few people strolling around.", "images/park.png",  NULL, 0, {&options[4], &options[5]}, 2, NULL, NULL, {&characterPosition[1], &characterPosition[2]}, 2},
{4, "Talking to Mike", "You start a conversation with Mike.", "images/basketball_court.png",  NULL, 0, {&options[6], &options[7]}, 2, &characters[0], "Hey! Want to team up for a game?", {&characterPosition[3], NULL}, 1},
{5, "Playing Alone", "You keep playing alone. A mysterious figure approaches.", "images/basketball_court.png",  NULL, 0, {&options[8], &options[9]}, 2, &characters[2], "You have some good moves. Want to learn a trick?", {&characterPosition[4], NULL}, 1},
{6, "Talking to Jess", "You strike up a conversation with Jess.", "images/park.png",  NULL, 0, {&options[10], &options[11]}, 2, &characters[1], "Hi! I love the tranquility here. How about you?", {&characterPosition[5], NULL}, 1},
{7, "Talking to Tony", "You start a conversation with Tony.", "images/park.png",  NULL, 0, {&options[12], &options[13]}, 2, &characters[2], "Hey! I'm sketching the scenery. Want to see?", {&characterPosition[6], NULL}, 1},
{8, "Game with Mike", "You have a fun game with Mike. You both feel closer.", "images/basketball_court.png",  NULL, 0, {&options[14], &options[15]}, 2, NULL, NULL, {&characterPosition[7], NULL}, 1},
{9, "Walking Away", "You walk away, feeling unsure about your decision.", "images/basketball_court.png",  NULL, 0, {&options[16], &options[17]}, 2, NULL,  NULL, {NULL, NULL}, 0},
{10, "Learning a Trick", "Tony teaches you a cool trick. You feel more skilled.", "images/basketball_court.png",  NULL, 0, {&options[18], &options[19]}, 2, NULL, NULL, {&characterPosition[8], NULL}, 1},
{11, "Peaceful Chat", "You and Jess enjoy a peaceful chat. You feel relaxed.", "images/park.png",  NULL, 0, {&options[20], &options[21]}, 2, NULL, NULL, {&characterPosition[9], NULL}, 1},
{12, "Different Interests", "You and Jess realize you have different interests.", "images/park.png",  NULL, 0, {&options[22], &options[23]}, 2, NULL, NULL, {&characterPosition[10], NULL}, 1},
{13, "Admiring Art", "You admire Tony's sketches. You feel inspired.", "images/park.png",  NULL, 0, {&options[24], &options[25]}, 2, NULL, NULL, {&characterPosition[11], NULL}, 1},
{14, "Later with Tony", "You decide to talk to Tony later.", "images/park.png",  NULL, 0, {&options[26], &options[27]}, 2, NULL,  NULL, {NULL, NULL}, 0},
{15, "Friendly Bond", "You feel a stronger bond with your new friends.", "images/basketball_court.png",  NULL, 0, {&options[28], NULL}, 1, NULL,  NULL, {NULL, NULL}, 0},
{16, "End of the Day", "You decide to end the day.", "images/sunset.png",  NULL, 0, {&options[29], NULL}, 1, NULL,  NULL, {NULL, NULL}, 0},
{17, "Deep Conversation", "You have a deep conversation with Jess.", "images/park.png",  NULL, 0, {&options[30], NULL}, 1, NULL, NULL, {&characterPosition[12], NULL}, 1},
{18, "Walking in the Park", "You enjoy a walk in the park, feeling refreshed.", "images/park_path.png",  NULL, 0, {&options[31], NULL}, 1, NULL,  NULL, {NULL, NULL}, 0},
{19, "Finding Common Ground", "You and Jess find something you both enjoy.", "images/park.png",  NULL, 0, {&options[32], NULL}, 1, NULL, NULL, {&characterPosition[13], NULL}, 1},
{20, "Artistic Compliment", "Tony appreciates your compliment and feels motivated.", "images/park.png",  NULL, 0, {&options[33], NULL}, 1, NULL, NULL, {&characterPosition[14], NULL}, 1},
{21, "Inspiration Talk", "Tony talks about his inspiration, and you feel inspired.", "images/park.png",  NULL, 0, {&options[34], NULL}, 1, NULL, NULL, {&characterPosition[15], NULL}, 1},
{22, "Day End", "The day ends with a sense of accomplishment.", "images/sunset.png",  NULL, 0, {&options[35], NULL}, 1, NULL,  NULL, {NULL, NULL}, 0},
{23, "Reflection", "You reflect on the day's events.", "images/sunset.png",  NULL, 0, {&options[36], NULL}, 1, NULL,  NULL, {NULL, NULL}, 0}
};