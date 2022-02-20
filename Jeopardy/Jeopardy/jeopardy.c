/*
 * Tutorial 3 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <Banujan Sutheswaran, Cyrus Lee, Yehchan Park>
 * All rights reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS

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
char* tokenize(char *input);

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
        players[i].name[strlen(players[i].name) - 1] = '\0';
        players[i].score = 0; //initialize their score to 0
    }
    
    
  

    // Perform an infinite loop getting command input from users until game ends
    while (true)
    {
        // Call functions from the questions and players source files
        int roundCounter = 0;

        while (roundCounter < 12) {
                //declare category and value variable 
                
                int currentPlayer = roundCounter % 4;

                printf("%s's Turn\n", players[currentPlayer].name);
                display_categories();
                char categoryValueinput[2][BUFFER_LEN];
            do {
                
              
                
                do{//ask the user to choose the category and value
                    int i = 0;
                    char* pch;
                    printf("Choose a category (as a number) and value: ");
                    fgets(buffer, BUFFER_LEN, stdin);
                    pch = strtok(buffer, " "); //spliting user input into 2 tokens
                    while (pch != NULL) { //looping until done. all tokens acquired
                        strcpy(categoryValueinput[i], pch); //copying token into array
                        i++; //increasing counter to make sure only two inputs are inputted
                        pch = strtok(NULL, " "); //moving to the next token
                    }
                    if(i==2){
                        if (valid_CategoryAnswer(atoi(categoryValueinput[0]), atoi(categoryValueinput[1]))) {
                            break;
                        }
                    }

                    printf("Please enter the category and value in the correct format. (EG. 1 100)\n");
                } while (true);
                switch (atoi(categoryValueinput[0])) {
                case 1: strcpy(categoryValueinput[0], "CSGO"); break;
                case 2: strcpy(categoryValueinput[0], "Valorant"); break;
                case 3: strcpy(categoryValueinput[0], "Apex"); break;
                }
                
                if (already_answered(categoryValueinput[0], atoi(categoryValueinput[1]))) {
                    printf("The question you selected has already been answered. Please select another question!\n");
                }
            } while (already_answered(categoryValueinput[0], atoi(categoryValueinput[1])));
            
            

            display_question(categoryValueinput[0], atoi(categoryValueinput[1]));
            
            char* answer;
            int result;
            do {
                printf("Please enter your answer : ");
                fgets(buffer, sizeof buffer, stdin);

                answer = tokenize(buffer);

                result = strcmp(answer, "invalid");
                if(result == 0){
                    printf("Please use the proper formating starting with \"what is \" or \"who is \"");
                }

            } while (result == 0);

            answer[strlen(answer) - 1] = '\0';
            //ask for answer
            //string tok

            if(valid_answer(categoryValueinput[0], atoi(categoryValueinput[1]), answer)){//Correct answer
                printf("Thats the right answer!\n");
                players[currentPlayer].score += atoi(categoryValueinput[1]);
			}
            else{
                //incorrect answer
                printf("That was the wrong answer!!!\n");
                players[currentPlayer].score -= atoi(categoryValueinput[1]);
                display_answer(categoryValueinput[0], atoi(categoryValueinput[1]));
                //Print out correct answer
            }
            //Questions are set to asnwered in the valid answer
            

            // Execute the game until all questions are answered

            
            roundCounter++;
        }
        // Display the final results and exit
        show_results(players, NUM_PLAYERS);
        break;
    }
    return EXIT_SUCCESS;
}


void show_results(player* players, int num_players) {
    int* scores = malloc(num_players * sizeof(*scores)); //defining array of size count
    int printed[] = { 0, 0, 0, 0 };
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
    
    int place = 1;
    int count = 0;
    for (int i = 0; i < num_players; i++) { //print results
        for (int j = 0; j < num_players; j++) {
            if (count==4){
                break;
            }
            if (players[j].score == scores[i]) {
                if (printed[j] == 0) {
                    printf("Place %d : %s Score: %d\n", place, players[j].name, players[j].score);
                    printed[j] = 1;
                    count++;
                }
            }
            
        }
        place++;
        if (count==4){
                break;
            }
    }


    free(scores); //free memory
}

char* tokenize(char *input){
    
    char* pch;
    char array[3][100];
    int i = 0;

    pch = strtok(input, " ,"); //spliting user input into 3 tokens
    while (pch != NULL) { //looping until done. all tokens acquired
        strcpy(array[i],pch); //copying token into array

        i++; //increasing counter to make sure only two inputs are inputted
        pch = strtok(NULL, " ,"); //moving to the next token
    }

    if (strcmp(array[0], "who") != 0 && strcmp(array[0], "what") != 0) {
        return "invalid";
    }

    if (strcmp(array[1], "is") != 0) {
        return "invalid";
    }

    strcpy(input,array[2]);
    return input;
}
