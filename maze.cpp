#ifndef MAZE_CPP
#define MAZE_CPP

#include "maze.h"

String maze::startPayload = "START THE MAZE !";

void maze::startMaze(){
  String payload = (String)configu::json_start + (String)configu::json_key_one + (String)configu::json_middle + (String)startPayload + (String)configu::json_end;
  //String payload = "{\"one\":\"test\"}";
  network::ws->textAll(payload);
    
}

#endif
