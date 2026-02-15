/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U: Operating Systems
 *
 * Copyright (C) 2026, <GROUP NUMBER>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    printf("Welcome to Jeopardy!\n");
    for (int i = 0; i < NUM_PLAYERS; i++) 
    {
        printf("Please enter the name for Player %d: ", i + 1);
        scanf("%s", players[i].name);
        players[i].score = 0; // initialize each of the players in the array with 0
    }

    // Clear the buffer after scanf so fgets works inside the loop
    getchar(); 

    // Requirement 3: Print out each of the question categories and dollar values
    printf("\n--- The Game is Starting! ---\n");
    display_categories();

    // Requirement 1: Command line prompt for all interactions
    printf("\nJeopardy> ");

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL) {
    buffer[strcspn(buffer, "\n")] = 0;
    // Skip if input is empty
    if (strlen(buffer) == 0) {
        printf("Skipping turn.\n");
        continue;
    }
    // Quit command
    if (strcmp(buffer, "quit") == 0) {
        printf("\nEnding game. Thanks for playing!\n");
        break;
    }
    // Check for correct format
    char player_name[256];
    char category[256];
    int value;
    // Try to parse the input
    if (sscanf(buffer, "%s %s %d", player_name, category, &value) != 3) {
        printf("Invalid format! Use: PlayerName Category Value\n");
        continue;
    }
    // Check if player exists
    if (!player_exists(players, NUM_PLAYERS, player_name)) {
        printf("Player '%s' not found! Valid players: ", player_name);
        for (int i = 0; i < NUM_PLAYERS; i++) {
            printf("%s%s", players[i].name, (i < NUM_PLAYERS - 1) ? ", " : "\n");
        }
        continue;
    }
    // Check if question already answered
    if (already_answered(category, value)) {
        printf("That question has already been answered! Please choose another question.\n");
        continue;
    }
    // Display the question
    printf("\n%s selected %s for $%d\n", player_name, category, value);
    display_question(category, value);
    // Get player's answer
    printf("\nYour answer (format: 'what is ...' or 'who is ...'): ");
    char answer_buffer[BUFFER_LEN];
    if (fgets(answer_buffer, BUFFER_LEN, stdin) == NULL) {
        break;  // End of input
    }
    answer_buffer[strcspn(answer_buffer, "\n")] = 0;
    // Tokenize the answer to extract the actual answer part
    char *tokens[10];  // Array to hold tokenized parts
    tokenize(answer_buffer, tokens);
    // Validate the answer
    if (valid_answer(category, value, tokens[0])) {
        printf("\n Correct! %s earns $%d\n", player_name, value);
        update_score(players, NUM_PLAYERS, player_name, value);
        
    // Mark question as answered
    mark_answered(category, value);
        
    } else {
        printf("\n Incorrect! The correct answer was: ");
        //Display answer
        printf("\n");
    }
    // Show updated scores
    printf("\nCurrent Scores:\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("  %s: $%d\n", players[i].name, players[i].score);
    }    
    // Check if all questions have been answered
    bool game_over = true;
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered) {
            game_over = false;
            break;
        }
    }
    if (game_over) {
        printf("\n All questions have been answered!\n");
        break;
    }
    // Display remaining categories
    printf("\n");
    display_categories();
    
    printf("\nJeopardy> ");
    }
    printf("\nGame Over!\n");
    show_results(players, NUM_PLAYERS);
    
    return EXIT_SUCCESS;
}
