#include <yaml.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_yaml.h"

Character characters[3] = {
{1, "Mike", "A passionate basketball player.", "images/mike_sprite.png", 50, 50},
{1, "Jess", "A park enthusiast who loves nature.", "images/jess_sprite.png", 50, 50},
{1, "Tony", "A local artist who draws inspiration from the park.", "images/tony_sprite.png", 50, 50}
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
Actor actor[16] = {
{1, "left"},
{2, "left"},
{3, "right"},
{1, "left"},
{3, "right"},
{2, "left"},
{3, "right"},
{1, "left"},
{3, "right"},
{2, "left"},
{2, "left"},
{3, "right"},
{2, "left"},
{2, "left"},
{3, "right"},
{3, "right"}
};
Scene scenes[23] = {
{1, "Basketball Court", "You are at the basketball court, ready to shoot some hoops.", "images/basketball_court.png", {&options[0], &options[1]}, 2, NULL, 0, {NULL, NULL}, 0},
{2, "Playing Basketball", "You start playing basketball. Mike joins you.", "images/basketball_court.png", {&options[2], &options[3]}, 2, NULL, 0, {&actor[0], NULL}, 1},
{3, "Park", "The park is serene with a few people strolling around.", "images/park.png", {&options[4], &options[5]}, 2, NULL, 0, {&actor[1], &actor[2]}, 2},
{4, "Talking to Mike", "You start a conversation with Mike.", "images/basketball_court.png", {&options[6], &options[7]}, 2, &dialogues[0], 1, {&actor[3], NULL}, 1},
{5, "Playing Alone", "You keep playing alone. A mysterious figure approaches.", "images/basketball_court.png", {&options[8], &options[9]}, 2, &dialogues[1], 1, {&actor[4], NULL}, 1},
{6, "Talking to Jess", "You strike up a conversation with Jess.", "images/park.png", {&options[10], &options[11]}, 2, &dialogues[2], 1, {&actor[5], NULL}, 1},
{7, "Talking to Tony", "You start a conversation with Tony.", "images/park.png", {&options[12], &options[13]}, 2, &dialogues[3], 1, {&actor[6], NULL}, 1},
{8, "Game with Mike", "You have a fun game with Mike. You both feel closer.", "images/basketball_court.png", {&options[14], &options[15]}, 2, NULL, 0, {&actor[7], NULL}, 1},
{9, "Walking Away", "You walk away, feeling unsure about your decision.", "images/basketball_court.png", {&options[16], &options[17]}, 2, NULL, 0, {NULL, NULL}, 0},
{10, "Learning a Trick", "Tony teaches you a cool trick. You feel more skilled.", "images/basketball_court.png", {&options[18], &options[19]}, 2, NULL, 0, {&actor[8], NULL}, 1},
{11, "Peaceful Chat", "You and Jess enjoy a peaceful chat. You feel relaxed.", "images/park.png", {&options[20], &options[21]}, 2, NULL, 0, {&actor[9], NULL}, 1},
{12, "Different Interests", "You and Jess realize you have different interests.", "images/park.png", {&options[22], &options[23]}, 2, NULL, 0, {&actor[10], NULL}, 1},
{13, "Admiring Art", "You admire Tony's sketches. You feel inspired.", "images/park.png", {&options[24], &options[25]}, 2, NULL, 0, {&actor[11], NULL}, 1},
{14, "Later with Tony", "You decide to talk to Tony later.", "images/park.png", {&options[26], &options[27]}, 2, NULL, 0, {NULL, NULL}, 0},
{15, "Friendly Bond", "You feel a stronger bond with your new friends.", "images/basketball_court.png", {&options[28], NULL}, 1, NULL, 0, {NULL, NULL}, 0},
{16, "End of the Day", "You decide to end the day.", "images/sunset.png", {&options[29], NULL}, 1, NULL, 0, {NULL, NULL}, 0},
{17, "Deep Conversation", "You have a deep conversation with Jess.", "images/park.png", {&options[30], NULL}, 1, NULL, 0, {&actor[12], NULL}, 1},
{18, "Walking in the Park", "You enjoy a walk in the park, feeling refreshed.", "images/park_path.png", {&options[31], NULL}, 1, NULL, 0, {NULL, NULL}, 0},
{19, "Finding Common Ground", "You and Jess find something you both enjoy.", "images/park.png", {&options[32], NULL}, 1, NULL, 0, {&actor[13], NULL}, 1},
{20, "Artistic Compliment", "Tony appreciates your compliment and feels motivated.", "images/park.png", {&options[33], NULL}, 1, NULL, 0, {&actor[14], NULL}, 1},
{21, "Inspiration Talk", "Tony talks about his inspiration, and you feel inspired.", "images/park.png", {&options[34], NULL}, 1, NULL, 0, {&actor[15], NULL}, 1},
{22, "Day End", "The day ends with a sense of accomplishment.", "images/sunset.png", {&options[35], NULL}, 1, NULL, 0, {NULL, NULL}, 0},
{23, "Reflection", "You reflect on the day's events.", "images/sunset.png", {&options[36], NULL}, 1, NULL, 0, {NULL, NULL}, 0}
};
