#ifndef CONFIG_H
#define CONFIG_H

#include <string.h>

// Data structure of the puzzle box
namespace configu{
  // Connection
  extern const char* ssid;
  extern const char* password;
  
  // I/O pins
  extern int LEDPWM1;
  extern int ledPin;
  extern int pinInput_1;
  
  // State machine
  extern int currentState;
  extern bool ledState;


  //JSON structure
  extern char* json_start;
  extern char* json_middle;
  extern char* json_coma;
  extern char* json_end;

  extern char* json_key_one;
  extern char* json_key_two;
  extern char* json_key_three;

    
  //State 2 - Labyrinthe
    // LED eclairent la bonne section du cube
    // L'app web load la page conséquente
      // L'app web fait comprendre que c est une epreuve de labyrinthe
    // Lorsque la bille rentre dans le trou final, cela conclus l etape

  //State 3 - APEX (Guess relief word)
    // LED eclairent la bonne section du cube
    // L'app web load la page conséquente
      // 4 choix avec un menu deroulant proposant des lettres
    extern char choice1[26];
    extern char choice2[26];
    extern char choice3[26];
    extern char choice4[26];

    extern char answer1;
    extern char answer2;
    extern char answer3;
    extern char answer4;
    
  //State 4 - Sequence d'activation


  //State 5 - Knock on time


  //State 6 - Release the gift
  
  
  }

#endif
