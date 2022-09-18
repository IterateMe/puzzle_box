#ifndef CONFIG_CPP
#define CONFIG_CPP

#include "config.h"

  const char* configu::ssid = "Adrienne";
  const char* configu::password = "NoOneIseGonnaBelieveThis";

// I/O pins
  int configu::LEDPWM1 = 12; //D6
  int configu::ledPin = 2;
  int configu::pinInput_1 = 14;
  
  // State machine
  int configu::currentState = 0;
  bool configu::ledState = false;

  //JSON structure
  char* configu::json_start  = "{\"";
  char* configu::json_middle = "\":\"";
  char* configu::json_coma   = "\",\"";
  char* configu::json_end    = "\"}";

  char* configu::json_key_one =  "one";
  char* configu::json_key_two =  "two";
  char* configu::json_key_three =  "three";

  //State 1 - Activation
    // Se connecter au serveur pour activer la machine (LED rouges vont clignoter lentement)

    // Mettre le cube "droit" pour allumer les LED vertes
    
  //State 2 - Labyrinthe
    // LED eclairent la bonne section du cube
    // L'app web load la page conséquente
      // L'app web fait comprendre que c est une epreuve de labyrinthe
    // Lorsque la bille rentre dans le trou final, cela conclus l etape

  //State 3 - APEX (Guess relief word)
    // LED eclairent la bonne section du cube
    // L'app web load la page conséquente
      // 4 choix avec un menu deroulant proposant des lettres
    char configu::choice1[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char configu::choice2[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char configu::choice3[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char configu::choice4[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    char configu::answer1 = 'a';
    char configu::answer2 = 'p';
    char configu::answer3 = 'e';
    char configu::answer4 = 'x';

  //State 4 - Sequence d'activation


  //State 5 - Knock on time


  //State 6 - Release the gift
  

#endif
