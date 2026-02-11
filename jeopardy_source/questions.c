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
#include "questions.h"

// Define the questions array here (to be used with extern in questions.h)
question questions[NUM_QUESTIONS];

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    int values[4] = {200, 400, 600, 800};
    int q_count = 0;

    for (int i = 0; i < NUM_CATEGORIES; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            // Set the category and value
            strcpy(questions[q_count].category, categories[i]);
            questions[q_count].value = values[j];
            questions[q_count].answered = false;

            // Placeholders for questions/answers (Requirements 4-6)
            strcpy(questions[q_count].question, "Sample Question");
            strcpy(questions[q_count].answer, "Sample Answer");
            
            q_count++;
        }
    }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    printf("\nAvailable Questions:\n");
    for (int i = 0; i < NUM_QUESTIONS; i++) 
    {
        if (!questions[i].answered) 
        {
            printf("Category: %-15s | Value: $%d\n", 
                   questions[i].category, questions[i].value);
        }
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    return false;
}