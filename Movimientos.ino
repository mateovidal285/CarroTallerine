void frenarMotores()
{
  Serial.println("Frenar");

  digitalWrite(PIN_DD, LOW);
  digitalWrite(PIN_DI, LOW);

  digitalWrite(PIN_ID, LOW);
  digitalWrite(PIN_II, LOW);
}

void moverAtras()
{
  Serial.println("Atras");

  digitalWrite(PIN_DD, LOW);
  digitalWrite(PIN_DI, HIGH);

  digitalWrite(PIN_ID, LOW);
  digitalWrite(PIN_II, HIGH);
}

void moverAdelante()
{
  Serial.println("Adelante");

  digitalWrite(PIN_DD, HIGH);
  digitalWrite(PIN_DI, LOW);

  digitalWrite(PIN_ID, HIGH);
  digitalWrite(PIN_II, LOW);
}

void girarIzquierda()
{
  Serial.println("Izquierda");

  digitalWrite(PIN_DD, LOW);
  digitalWrite(PIN_DI, LOW);

  digitalWrite(PIN_ID, HIGH);
  digitalWrite(PIN_II, LOW);
}

void girarDerecha()
{
  Serial.println("Derecha");

  digitalWrite(PIN_DD, HIGH);
  digitalWrite(PIN_DI, LOW);

  digitalWrite(PIN_ID, LOW);
  digitalWrite(PIN_II, LOW);
}

void DiagonalDerAdelante(byte pin, byte vel)
{
  Serial.println("Diagonal Derecha Adelante");

  digitalWrite(PIN_DD, HIGH);
  digitalWrite(PIN_DI, LOW);

  digitalWrite(PIN_ID, HIGH);
  digitalWrite(PIN_II, LOW);

  analogWrite(pin, vel - 40);
}

void DiagonalIzqAdelante(byte pin, byte vel)
{
  Serial.println("Diagonal Izquierda Adelante");
  
  digitalWrite(PIN_DD, HIGH);
  digitalWrite(PIN_DI, LOW);

  digitalWrite(PIN_ID, HIGH);
  digitalWrite(PIN_II, LOW);

  analogWrite(pin, vel - 40);
}


void seguirLinea(byte derecho, byte izquierdo)
{
  Serial.println("Siguiendo Linea");

  byte lecturaInfD = digitalRead(derecho);
  byte lecturaInfI = digitalRead(izquierdo);

  if (lecturaInfI == LOW && lecturaInfD == LOW) {
   
    moverAdelante();

  } else if (lecturaInfI == HIGH && lecturaInfD == LOW) {

    girarIzquierda();

    
  } else if (lecturaInfI == LOW && lecturaInfD == HIGH) {

    girarDerecha();

  } if (lecturaInfI == HIGH && lecturaInfD == HIGH) {

    frenarMotores();

  }

}
