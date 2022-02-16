/*
 * Tutorial 3 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
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
    // initialize each of the players in the array
    for (int i = 0; i < 4; i++) {
        printf("Please enter your name player %d: ",i+1);
        fgets(players[i].name, BUFFER_LEN, stdin); //get the user input
        players[i].score = 0; //initialize their score to 0
    }
    players[1].score = 10;
    players[2].score = 5;
    players[3].score = 3;
    players[0].score = 1;
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("%s", players[i].name);
    }
    
    show_results(players, NUM_PLAYERS);

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files
        
        // Execute the game until all questions are answered

        // Display the final results and exit
    }
    return EXIT_SUCCESS;
}


void show_results(player* players, int num_players) {
    int* scores = malloc(num_players * sizeof(*scores)); //defining array of size count
    if (!scores) { //error check for malloc
        printf("There was a problem with malloc.");
        exit(1);
    }


    for (int i = 0; i < num_players; i++) { //making a list of all the scores
        scores[i] = players[i].score;
    }

    
    for (int i = 1; i < num_players; i++) { //Reverse insertion sort to get proper order.
        int key = scores[i];
        int j = i - 1;

 
        while (j >= 0 && scores[j] < key) {
            scores[j + 1] = scores[j];
            j = j - 1;
        }
        scores[j + 1] = key;
    }
    for (int i = 0; i < num_players; i++) {
        printf("%d ", scores[i]);
        printf("\n");
    }
    int place = 1;
    for (int i = 0; i < num_players; i++) { //print results
        for (int j = 0; j < num_players; j++) {
            if (players[j].score == scores[i]) {
                printf("Place %d : %s Score: %d\n", place, players[j].name, players[j].score);
            }
            
        }
        place++;
    }


    free(scores); //free memory
}