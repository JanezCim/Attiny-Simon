//                            attiny85
//                      reset -+---+- power
//    (MOTOR + stikalo 1) pb3 -+*  +- pb2 (LED 2)
//    (LED 4 + stikalo 2) pb4 -+   +- pb1 (PWM LED 3)
//                  ground    -+---+- pb0 (PWM LED1)




#define MEJA 180            //spodnja meja
#define ZMEJA 900             // zgornja meja
#define L3 2                       // mora da je 2 :D
#define L2 1
#define L1 0
#define S1 3
#define S2 2
int myArray [30];                               // kako dolga je kombinacija SIMONA
int krog = 0;
int pravkrog = 0;            //zaporedni tipka
int cakanje = 1000;  //kolko krogov nej bere tipke preden se ugasne 


void setup()
{
  Serial.begin(9600);
  pinMode (L3, OUTPUT);
  pinMode (L1, OUTPUT);
  pinMode (L2, OUTPUT);
  pinMode (S1, INPUT);
  //pinMode (S2, INPUT);
}
  



void loop ()
{
  for(int i=0; i<30; i++)
  {
    myArray[i]= random(1,4);
    Serial.print(myArray[i]);
  }
  Serial.println("");
  prikaz();
}


//////////////////////////////////////////////////prikaz lučk pred branjem tipk///////////////////////////////////////////////////////

void prikaz(){
  krog = krog + 1;
  for(int i = 0; i<krog; i++)                                       // če bo zajebavu da kaže 1 lučko na koncu premau spremen iz "krog" v "krog +1"
  {
    char c=0;
    if (myArray[i]==1) c=L1;
    if (myArray[i]==2) c=L2;
    if (myArray[i]==3) c=L3;
    
    analogWrite(c, 255);
    delay(200);
    analogWrite(c,0);
    delay(200);
    Serial.print(myArray[i]);
  }
  tipke();
  prikaz();
 }

//////////////////////////////////////////////////////////branje tipk in prižiganje lučk ob pritisku////////////////////////////////////////////////////
  
void tipke(){
  Serial.println ("tipke");
  for(int i=0; i<cakanje; i++)
  {
    if (analogRead(S1)>MEJA && analogRead(S1)<ZMEJA )
  {
    delay(20);
    if (analogRead(S2)>MEJA && analogRead(S2)<ZMEJA )
    {
      //analogWrite(L1, 0);
      analogWrite(L3, 255);
      while(analogRead (S2)>MEJA && analogRead(S2)<ZMEJA) delay(1);
      analogWrite(L3, 0);
      Serial.println("                      3");
      tretja();
      delay (100);
    }
    else {
      analogWrite(L1, 255);
      while(analogRead (S1)>MEJA && analogRead(S1)<ZMEJA) delay(1);
      analogWrite(L1, 0);
      Serial.println("                      1");
      prva();
    }
  }
  if (analogRead(S2)>MEJA && analogRead(S2)<ZMEJA)
  {
    delay(20);
    if (analogRead(S1)>MEJA && analogRead(S1)<ZMEJA)
    {
      analogWrite(L3, 255);
      while(analogRead (S1)>MEJA && analogRead(S1)<ZMEJA) delay(1);
      analogWrite(L3, 0);
      Serial.println("                      3_1");
      tretja();
      delay (100);
    }
    else {
      analogWrite(L2, 255);
      while(analogRead (S2)>MEJA && analogRead(S2)<ZMEJA) delay(1);
      analogWrite(L2, 0);
      Serial.println("                  2");
      druga();
    }
  }
}
                                                                                        //pejd spat!!!!!!!!!!!!!!!!!!!!!!!!!
}
///////////////////////////////////////////////////// preverjanje rešitev  ////////////////////////////////////////////////

void prva()
{
  if (myArray[pravkrog]== 1)
    {
     pravkrog = pravkrog+1;
     if (pravkrog >= krog)                                    // lahko zajebava " >= "             pri vseh spodaj moraš spremenit če popravlaš
      {
        prikaz();
        pravkrog=0;
      } 
     else {tipke();};
    }
  else 
    {
     pinMode (S1, OUTPUT);
     analogWrite(S1, 1024);
     delay (250);
     analogWrite(S1, 0);
     delay(250);
     analogWrite(S1, 1024);
     delay (250);
     analogWrite(S1, 0);
     delay (2000);
     pinMode (S1, INPUT);
     krog=0;
     pravkrog=0;
     loop();
    }
}

void druga()
{
  if (myArray[pravkrog]== 2)
    {
     pravkrog = pravkrog+1;
     if (pravkrog >= krog)                                    // lahko zajebava " >= "             pri vseh spodaj moraš spremenit če popravlaš
      {
        prikaz();
        pravkrog=0;
      } 
     else {tipke();};
    }
  else 
    {
     pinMode (S1, OUTPUT);
     analogWrite(S1, 1024);
     delay (250);
     analogWrite(S1, 0);
     delay(250);
     analogWrite(S1, 1024);
     delay (250);
     analogWrite(S1, 0);
     delay (2000);
     pinMode (S1, INPUT);
     krog=0;
     pravkrog=0;
     loop();
    }
}

void tretja()
{
  if (myArray[pravkrog]== 3)
    {
     Serial.println ("pravilno!");
     pravkrog = pravkrog+1;
     if (pravkrog >= krog)                                    // lahko zajebava " >= "             pri vseh spodaj moraš spremenit če popravlaš
      {
        prikaz();
        pravkrog=0;
      } 
     else {tipke();};
    }
  else 
    {
     pinMode (S1, OUTPUT);
     analogWrite(S1, 1024);
     delay (250);
     analogWrite(S1, 0);
     delay(250);
     analogWrite(S1, 1024);
     delay (250);
     analogWrite(S1, 0);
     delay (2000);
     pinMode (S1, INPUT);
     krog=0;
     pravkrog=0;
     loop();
    }
}

  

