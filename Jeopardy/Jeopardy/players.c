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
#include "players.h"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int num_players, char *name)
{
    return false;
}

// Go through the list of players and update the score for the 
// player given their name
void update_score(player *players, int num_players, char *name, int score)
{
  
    for(int i=0; i< num_players;i++) //iterate through all the players
    {
        if (players[i].name == name) { //if the player name entered matches a player name
            players[i].score += score; //then add the score to the players existing score
        }
    }
    
}