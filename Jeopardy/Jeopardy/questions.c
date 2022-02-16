/*
 * Tutorial 3 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <Banujan Sutheswaran, Cyrus Lee, Yehchan Park>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    question csgoq1 = { "CSGO","Cost of an AWP","4750",100,false};
    question csgoq2 = { "CSGO","A s1mple graffiti map.","Cache",200,false };
    question csgoq3 = { "CSG","Most successful organization in terms of majors. ","Astralis",300,false };
    question csgoq4 = { "CSGO","Team that ended the 87-0 NIP win streak.","VP",400,false };

    question valorantq1 = { "Valorant","Amount of seconds that a Jett smoke lasts.","4.5",100,false };
    question valorantq2 = { "Valorant","Amount of time for a Killjoy ultimate to detonate.","7",200,false };
    question valorantq3 = { "Valorant","Cost of Operator in beta.","4500",300,false };
    question valorantq4 = { "Valorant","Headhunter shots in Spike Rush.","4",400,false };

    question apexq1 = { "Apex","The first character to obtain an heirloom.","Wraith",100,false };
    question apexq2 = { "Apex","The gun that deals the most damage in Apex Legends.","Kraber",200,false };
    question apexq3 = { "Apex","Character that is Homosexual.","Gibraltar",300,false };
    question apexq4 = { "Apex","Character in possession of Fuse's severed arm.","Maggie",400,false };

    //sort the questions by their dollar value rather than their category
    questions[0] = csgoq1;
    questions[1] = valorantq1;
    questions[2] = apexq1;
    questions[3] = csgoq2;
    questions[4] = valorantq2;
    questions[5] = apexq2;
    questions[6] = csgoq3;
    questions[7] = valorantq3;
    questions[8] = apexq3;
    questions[9] = csgoq4;
    questions[10] = valorantq4;
    questions[11] = apexq4;

}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    printf("   %s   |", categories[0]);
    printf(" %s |", categories[1]);
    printf("   %s   ", categories[2]);
    printf("\n");
    printf("--------------------------------");
    printf("\n");
    for (int i = 0; i < 12; i++) {
        if (questions[i].answered == false) {
            printf("   $%-3d   ", questions[i].value);
        }
        else {
            printf("          ");
        }
        if ((i + 1) % 3 != 0) {
            printf("|");
        }
        else {
            printf("\n");
        }
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    //find the question by iterating through the corresponding category and dollar value
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            printf("%s\n", questions[i].question);
        }
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    //find the question and check if the answer is the correct answer
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value && strcmp(questions[i].answer, answer) == 0) {
            questions[i].answered = true;
            return true;
        }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value && questions[i].answered == true) {
            return true;
        }
    }
    return false;
}

