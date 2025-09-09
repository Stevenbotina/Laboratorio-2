int const LED_VERDE = 11;
int const LED_AMARILLO = 12;
int const LED_ROJO = 13;
int const BOTON = 10;

bool modoIntermitencia = false;
unsigned long ultimoCambio = 0;
const unsigned long intervalo = 500;
bool estadoLeds = false;

bool intermitRojo = false;
bool intermitAmarillo = false;
bool intermitVerde = false;

int contadorPulsaciones = 0;
unsigned long tiempoUltimaPulsacion = 0;
const unsigned long tiempoAntirrebote = 300;

void setup() {
  Serial.begin(9600);
  mostrarMenu();
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BOTON, INPUT_PULLUP);
}

void loop() {
  if (Serial.available() > 0) {
    char opcion = Serial.read();
    if (opcion == '9') {
      Serial.println("Opcion 9: Intermitencia INFINITA activada.");
      modoIntermitencia = true;
      intermitRojo = true;
      intermitAmarillo = true;
      intermitVerde = true;
    } else {
      ejecutarOpcion(opcion);
    }
  }

 if (digitalRead(BOTON) == LOW) { // presionado
    if (millis() - tiempoUltimaPulsacion > tiempoAntirrebote) {
      contadorPulsaciones++;
      if (contadorPulsaciones > 6) contadorPulsaciones = 1;
      ejecutarBoton(contadorPulsaciones);
      tiempoUltimaPulsacion = millis();
    }
  }
  
  if (modoIntermitencia) {
    if (millis() - ultimoCambio >= intervalo) {
      ultimoCambio = millis();
      estadoLeds = !estadoLeds;
      if (intermitRojo) digitalWrite(LED_ROJO, estadoLeds);
      if (intermitAmarillo) digitalWrite(LED_AMARILLO, estadoLeds);
      if (intermitVerde) digitalWrite(LED_VERDE, estadoLeds);
    }
  }
}

void ejecutarOpcion(char opcion) {
  switch (opcion) {
    case '0':
      Serial.println("Opcion 0: Alternar LED ROJO");
      digitalWrite(LED_ROJO, !digitalRead(LED_ROJO));
      intermitRojo = false;
    break;
    case '1':
      Serial.println("Opcion 1: Encender LED ROJO (fijo)");
      digitalWrite(LED_ROJO, HIGH);
      intermitRojo = false;
      break;
    case '2':
      Serial.println("Opcion 2: Apagar LED ROJO");
      digitalWrite(LED_ROJO, LOW);
      intermitRojo = false;
      break;
    case '3':
      Serial.println("Opcion 3: Encender LED AMARILLO (fijo)");
      digitalWrite(LED_AMARILLO, HIGH);
      intermitAmarillo = false;
      break;
    case '4':
      Serial.println("Opcion 4: Apagar LED AMARILLO");
      digitalWrite(LED_AMARILLO, LOW);
      intermitAmarillo = false;
      break;
    case '5':
      Serial.println("Opcion 5: Encender LED VERDE (fijo)");
      digitalWrite(LED_VERDE, HIGH);
      intermitVerde = false;
      break;
    case '6':
      Serial.println("Opcion 6: Apagar LED VERDE");
      digitalWrite(LED_VERDE, LOW);
      intermitVerde = false;
      break;
    case '7':
      Serial.println("Opcion 7: Encender TODOS (fijos)");
      digitalWrite(LED_ROJO, HIGH);
      digitalWrite(LED_AMARILLO, HIGH);
      digitalWrite(LED_VERDE, HIGH);
      intermitRojo = false;
      intermitAmarillo = false;
      intermitVerde = false;
      break;
    case '8':
      Serial.println("Opcion 8: Apagar TODOS");
      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_VERDE, LOW);
      intermitRojo = false;
      intermitAmarillo = false;
      intermitVerde = false;
      break;
    case 'm':
      mostrarMenu();
      break;
    default:
      Serial.println("Opcion invalida, presione 'm' para ver el menu");
      break;
  }
}

void ejecutarBoton(int contador) {
  switch (contador) {
    case 1: // LED rojo
      Serial.println("Botón 1: Encender ROJO");
      apagarTodos();
      digitalWrite(LED_ROJO, HIGH);
      break;

    case 2: // LED verde
      Serial.println("Botón 2: Encender VERDE");
      apagarTodos();
      digitalWrite(LED_VERDE, HIGH);
      break;

    case 3: // LED amarillo
      Serial.println("Botón 3: Encender AMARILLO");
      apagarTodos();
      digitalWrite(LED_AMARILLO, HIGH);
      break;

    case 4: // Apagar todos
      Serial.println("Botón 4: Apagar TODOS");
      apagarTodos();
      break;

    case 5: // Encender todos
      Serial.println("Botón 5: Encender TODOS");
      digitalWrite(LED_ROJO, HIGH);
      digitalWrite(LED_AMARILLO, HIGH);
      digitalWrite(LED_VERDE, HIGH);
      break;

    case 6: // Regresa al ciclo
      Serial.println("Botón 6: Volver a ROJO");
      apagarTodos();
      digitalWrite(LED_ROJO, HIGH);
      contadorPulsaciones = 1; // reinicia ciclo
      break;
  }
}


void apagarTodos() {
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_VERDE, LOW);
}

void mostrarMenu() {
  Serial.println("Seleccione una opcion:");
  Serial.println("1 - Encender LED ROJO");
  Serial.println("2 - Apagar LED ROJO");
  Serial.println("3 - Encender LED AMARILLO");
  Serial.println("4 - Apagar LED AMARILLO");
  Serial.println("5 - Encender LED VERDE");
  Serial.println("6 - Apagar LED VERDE");
  Serial.println("7 - Encender TODOS");
  Serial.println("8 - Apagar TODOS");
  Serial.println("9 - Intermitencia INFINITA");
  Serial.println("0 - turn on/off led rojo");
  Serial.println("m - Mostrar Menu");
}