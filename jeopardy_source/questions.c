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
#include <strings.h>
#include "questions.h"

// Define the questions array here (to be used with extern in questions.h)
question questions[NUM_QUESTIONS];

// Define the categories that the players can select
char categories[NUM_CATEGORIES][MAX_LEN] = {
    "programming", 
    "algorithms", 
    "databases"
};

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
    for (int i = 0; i < NUM_QUESTIONS; i++) 
    {
        // Find the matching question
        if (strcmp(questions[i].category, category) == 0 && 
            questions[i].value == value) 
        {
            printf("\nQuestion: %s\n", questions[i].question);
            return;
        }
    }
    printf("Question not found!\n");
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) 
    {
        // Find the question
        if (strcmp(questions[i].category, category) == 0 && 
            questions[i].value == value) 
        {
            // Comparing answers
            if (strcasecmp(questions[i].answer, answer) == 0) 
            {
                //Correct answer
                return true;
            }
            //Incorrect answer
            return false;
        }
    }
    return false;
}

// Marks a question as answered
void mark_answered(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) 
    {
        if (strcmp(questions[i].category, category) == 0 && 
            questions[i].value == value) 
        {
            questions[i].answered = true;
            return;
        }
    }
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) 
    {
        // Find the question
        if (strcmp(questions[i].category, category) == 0 && 
            questions[i].value == value) 
        {
            //Flag question as answered
            return questions[i].answered;
        }
    }
    //Question not found
    return true;
}
