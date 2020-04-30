float Qrad(float Tc)
{
   // s="""
   // at square meter, radiative heat transfer Watt/m2
   // """
   float Stefan_Boltzmann_coeff=5.67;
   float TempK=Tc+273.15;
   float Watt_per_m2 = Stefan_Boltzmann_coeff*pow(TempK/100.0,4);
   return Watt_per_m2;
}

float Stephan(float Tc) {
   float dia=2.54E-2;
   float ring=3.14*dia;
   float L=2E-1; // #m to cm, lengthg of the pipe
   float area=L*ring;
//   print("area of radiation_cooling(m2)=",f'{area:.4f}')
   float S=area*Qrad(Tc);
//   print("Watt of radiation",f'{S:.4f}')
   return S;
}

float Heat_Capasity_RodBody()
   {
   float Volume_in_cm=20*4;
   float Veff=0.1*Volume_in_cm;
   float Weight_in_gram=1.5*Veff;
   float Effective_Cp=4.2*Weight_in_gram;
//   print("Heat_Capasity_RodBody",f'{rouCp_eff:.4f}')
   return Effective_Cp;
   }


String incomingByte; // for incoming serial data
int dec;

unsigned int hexToDec(String hexString) {
  
  unsigned int decValue = 0;
  int nextInt;
  
  for (int i = 0; i < hexString.length(); i++) {
    
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);
    
    decValue = (decValue * 16) + nextInt;
  }
  
  return decValue;
}

  float dt=10;
  float Troom_c=20;
  float K1=1;
  float K2=1E-2;
  float Tc=Troom_c;
  float Heat_Capasity=Heat_Capasity_RodBody();
  float Q=Heat_Capasity*(Troom_c+273.0);

void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
  }

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    dec = hexToDec(incomingByte);

    float Win=dec;
    for(int i =1; i<=50; i++)
    {
      float Wout=K1*Stephan(Tc)+K2*(Tc-Troom_c);
      Q +=(Win - Wout)*dt;
      Tc=Q/Heat_Capasity-273.0;
    }
  //print(Tc)
   Serial.println(Tc);
   // say what you got:
    //analogWrite(9,dec);
  }
}
