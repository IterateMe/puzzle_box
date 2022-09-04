// model
#ifndef MODEL_H
#define MODEL_H

// Data structure of the puzzle box
namespace model{
  // Connection
  extern const char* ssid = "Adrienne";
  extern const char* password = "thisAintGood!alicelamalice";
  
  // I/O pins
  int LEDPWM1 = D0;
  const int ledPin = 2;
  const int pinInput_1 = 14;
  
  // State machine
  int currentState = 0;
  bool ledState = 0;

  //GLOBAL
  bool isOnGoodSide = false;

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


  //State 4 - Sequence d'activation


  //State 5 - Knock on time


  //State 6 - Release the gift
  
  
  }

#endif
