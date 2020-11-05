class led_control_pass //CLASE CONTROL LEDS PARA MODO PASSTROUGHT
{
  private:
  
  	int led_D2;    //variables LEDS
    int led_D1;
    int led_D0;
    int dips_S2;    //variables DIPSWITCHS
    int dips_S1;
    int dips_S0;
  
  public:
  
    void set_led_ports_1(int led2, int led1, int led0, int dips2, int dips1, int dips0)
    {
    	led_D2 = led2;
        led_D1 = led1;
       	led_D0 = led0;
        dips_S2 = dips2;
        dips_S1 = dips1;
        dips_S0 = dips0;
    }
    void config_leds_1()
    {
    	pinMode(led_D2, OUTPUT);	//asignacion de los pines como entrada o salida
        pinMode(led_D1, OUTPUT);
        pinMode(led_D0, OUTPUT);
        pinMode(dips_S2, INPUT);
        pinMode(dips_S1, INPUT);
        pinMode(dips_S0, INPUT);
    }
    void set_leds_1()
    {
        digitalWrite(led_D2, digitalRead(dips_S2));   //enciende los leds, segun lo que haya en los selectores s2, s1,s0
        digitalWrite(led_D1, digitalRead(dips_S1));
        digitalWrite(led_D0, digitalRead(dips_S0));
    }
};

class led_control_analog
{
  private:
  
  	int led_D2_1;   //variables LEDS
    int led_D1_1;
    int led_D0_1;
  
  public:
    void set_led_ports_2(int led2_1, int led1_1, int led0_1)
    {
    	led_D2_1 = led2_1;
        led_D1_1 = led1_1;
       	led_D0_1 = led0_1;
    }
    void config_leds_2()
    {
    	pinMode(led_D2_1, OUTPUT);	//asignacion de los pines como salida
        pinMode(led_D1_1, OUTPUT);
        pinMode(led_D0_1, OUTPUT);
    }
};

led_control_pass led_pass;                   //asigna el alias para cada una de las clases
led_control_analog led_analog;
    
int modo = 0;                             //modo de operacion del sistema:1. passthrough 2. Analogreference


void setup()
{
  pinMode(7, OUTPUT);                      //asigna los pines como entrada del selector S3 y salida el led D3
  pinMode(13, INPUT);
}

void loop()
{
  
  modo = digitalRead(13);                  //eligen que modo va a usar, si el 1 o el 2
  if (modo == HIGH)
  {
    digitalWrite(7, modo);                 //al pin 7 del led D3 muestra el valor de modo, es decir el selector S3
  	modo_pass();
  }
  else
  {
  	digitalWrite(7, modo);  
    modo_analog();
  }
}

void modo_pass()
{
    led_pass.set_led_ports_1(6, 5, 4, 12, 11, 10);   //en los leds D2, D1, D0, muestra lo de los selectores S2, S1, S0
    led_pass.config_leds_1();
    led_pass.set_leds_1();
}

void modo_analog()
{
    int select[3];
    int ref =538;         //valor referencia #carnet 2152/4 = 538
    int tol_max=0, tol_min=0; //variables para saber la tolerancia
    int adc=0;               //variable para compararlor de adc con la referencia
    
    led_analog.set_led_ports_2(6, 5, 4);
    led_analog.config_leds_2();
    
    select[0]=digitalRead(12);    //asigna a las variables lo que lee en el pin del dipswitch
    select[1]=digitalRead(11);
    select[2]=digitalRead(10);
  
    if(select[0]==LOW&select[1]==LOW&select[2]==LOW)      //evalua los casos para la tolerancia escogida en los S2, S1, S0
    {  	tol_max=538;                                      //porcentaje maximo 0% de tolerancia
        tol_min=538;                                      //porcentaje minimo 0% de tolerancia
    }
    if(select[0]==LOW&select[1]==LOW&select[2]==HIGH)
    {  	tol_max=543;                                     //porcentaje maximo 1% de tolerancia
        tol_min=533;                                     //porcentaje minimo 1% de tolerancia
    }
    if(select[0]==LOW&select[1]==HIGH&select[2]==LOW)
    {  	tol_max=548;                                     //porcentaje maximo 2% de tolerancia
        tol_min=528;                                     //porcentaje minimo 2% de tolerancia
    }
    if(select[0]==LOW&select[1]==HIGH&select[2]==HIGH)
    {  	tol_max=553;                                     //porcentaje maximo 3% de tolerancia
        tol_min=523;                                     //porcentaje minimo 3% de tolerancia
    }
    if(select[0]==HIGH&select[1]==LOW&select[2]==LOW)
    {  	tol_max=558;                                     //porcentaje maximo 4% de tolerancia
        tol_min=518;                                     //porcentaje minimo 4% de tolerancia
    }
    if(select[0]==HIGH&select[1]==LOW&select[2]==HIGH)
    {  	tol_max=563;                                     //porcentaje maximo 5% de tolerancia
        tol_min=513;                                     //porcentaje minimo 5% de tolerancia
    }
    if(select[0]==HIGH&select[1]==HIGH&select[2]==LOW)
    {  	tol_max=568;                                     //porcentaje maximo 6% de tolerancia
        tol_min=508;                                     //porcentaje minimo 6% de tolerancia
    }
    if(select[0]==HIGH&select[1]==HIGH&select[2]==HIGH)
    {  	tol_max=573;                                     //porcentaje maximo 7% de tolerancia
        tol_min=503;                                     //porcentaje minimo 7% de tolerancia
    }
    adc=analogRead(A0);       //asigna a variable auxiliar adc el valor de lectura en el pin A0 
    if(adc>tol_max)              //evalua si adc es mayor menor o esta dentro del rango de las tolerancias
    	digitalWrite(6, HIGH);   //si es mayor enciende D2
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
    if(adc>tol_min & adc<tol_max)  //si esta dentro de los valores de refencia enciende D1
    	digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(4, LOW);
    if(adc<tol_min)
    	digitalWrite(4, HIGH);     //si es menor enciende D0
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
}
    
