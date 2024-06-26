
void recibirMensajes()
{

  while (BT.available()){
    
    char mensaje = BT.read();
    Serial.println(mensaje);
    if (mensaje == 'N')
    {
      estado = ADELANTE;
    }
    if (mensaje == 'W')
    {
      estado = IZQUIERDA;
    }
    if (mensaje == 'E')
    {
      estado = DERECHA;
    }
    if (mensaje == 'S')
    {
      estado = ATRAS;
    }
    if (mensaje == 'P')
    {
      estado = FRENAR;
    }
    if (mensaje == 'L')
    {
      estado = SG;
    }
    if (mensaje == 'J')
    {
      estado = DD;
    }
    if (mensaje == 'K')
    {
      estado = DI;
    }

  }
}
