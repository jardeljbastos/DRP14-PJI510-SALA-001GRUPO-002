// Definir os limiares de umidade, onde 0 Solo Muito molhado e 100 Solo muito Seco
const int MuitoUmido = 40; // Valor de umidade para solo muito molhado
const int SemiUmido = 50; // Recomendado entre 50 a 75
const int Seco = 75; // Solo seco

void setup() {
  // Inicializar a comunicação serial
  Serial.begin(9600);
  
  pinMode(A0, INPUT); // Sensor Umidade Solo
  pinMode(2, OUTPUT); // Relé
  pinMode(3, OUTPUT); // Buzzer
  pinMode(8, OUTPUT); // LED Vermelho
  pinMode(9, OUTPUT); // LED Amarelo
  pinMode(10, OUTPUT); // LED Verde

  digitalWrite(2, LOW); // Relé Bomba Desligada
  
}

void loop() {
  // Ler o valor de umidade do sensor
  int val = analogRead(A0);
  int umidade = map(val, 0, 1023, 0, 100);
  delay(50);

//add manual
  digitalWrite(2, LOW); //Força o relé a desligar
  Serial.println("Relé FORÇADO a DESLIGAR");
  delay(50);
  
  // Verificar o nível de umidade
  if (umidade <= MuitoUmido) {
    
    Serial.print(umidade);
    Serial.println("Muito molhado, bomba desligada, LED Vermelho e um Beep");
    
    digitalWrite(2, LOW); // Relé bomba
    digitalWrite(3, HIGH);
    delay(2000);
    digitalWrite(3, LOW); // Buzzer
   // LEDs    
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);    
   
  }   
  else if (umidade > Seco) {
    Serial.print(umidade);
    Serial.println(" Solo seco, Aciona a bomba por 5 segundos");

    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
   
    digitalWrite(2, HIGH); // Liga a bomba
    delay(4000);
    digitalWrite(2, LOW);
    delay(50);
    digitalWrite(8, LOW);
  }  
  else if (umidade < Seco && umidade >= SemiUmido) { // Melhor condição
    Serial.print(umidade);
    Serial.println(" Solo Bom! Bomba desligada, LED verde");
    
    digitalWrite(3, LOW); // Buzzer
    digitalWrite(8, LOW);    
    digitalWrite(9, LOW); 
    digitalWrite(10, HIGH); // LED Verde
    digitalWrite(2, LOW);
    delay(100);
  }
  else if (umidade < MuitoUmido) {
      Serial.print(umidade);
      Serial.println(" Liga o LED amarelo");
        
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH);  // LED Amarelo  
        digitalWrite(10, LOW);        
        digitalWrite(2, LOW);
        delay(50);
     for (int x = 0; x < 2; x++) { // 2 Beeps curtos, se você quiser, pode desativar essa função do beep,pode incomodar um pouco...
       digitalWrite(3, LOW);//HIGH);
       delay(500);
       digitalWrite(3, LOW);
       delay(500);
     }   
  }   
  else {
     Serial.print("Resultado: ");
     Serial.println(umidade);     
  }
  // Aguardar um intervalo antes da próxima leitura
  delay(1000);
}
