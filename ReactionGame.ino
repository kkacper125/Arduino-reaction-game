
byte SW_P1 = 10;	// Player one button
byte SW_P2 = 11;	// Player two button
byte LED_P1 = 0;	// Player one led
byte LED_P2 = 1;	// Player two led
byte Reset = 12;	// Reset button (Starts the game again)

byte Flag = 0;

unsigned long Diff_T;
unsigned long Start_T = millis(); 
unsigned long Time = random(3000, 10000);

unsigned long B_Diff_T;
unsigned long B_Start_T = millis();
byte B_Time = 250;


void setup(){
   pinMode(0-7, OUTPUT);
   pinMode(10-13, INPUT);
}


void loop(){	// Main loop
 
	if (digitalRead(Reset) == HIGH){	// Resets variables and restarts starts the game
		Time = random(3000, 10000);
		Start_T = millis();
		PORTD = B0;
		Flag = 1;
	}
	
   switch (Flag){	
    case 1:
		Play();		// Function where lights blink and the winner is choosen
		break;

	case 2:
		P1_Win();	
		break;

	case 3:
		P2_Win();
		break;
	}
}


void Play(){	// The function with the main game and game states
	
	Diff_T = millis() - Start_T;

	if (Diff_T < Time){
		LedsBlink();
	}
	
	if (Diff_T == Time){
		PORTD = B0;
	}

	if (Diff_T > Time){
		React();
	}


}


void LedsBlink(){	// The leds blink one each time 

	B_Diff_T = millis() - B_Start_T;

	if (B_Diff_T < B_Time){
		digitalWrite(LED_P1, HIGH);
		digitalWrite(LED_P2, LOW);


        // If one person presses button to early, the other person wins
		if (digitalRead(SW_P1) == HIGH){	
			Flag = 3;
		}

		if (digitalRead(SW_P2) == HIGH){
			Flag = 2;
		}
	}

	if (B_Diff_T > B_Time && B_Diff_T  < B_Time*2){
        digitalWrite(LED_P1, LOW);
        digitalWrite(LED_P2, HIGH);

        // If one person presses button to early, the other person wins
		if (digitalRead(SW_P1) == HIGH){
			Flag = 3;
		}

		if (digitalRead(SW_P2) == HIGH){
			Flag = 2;
		}
	}

	if (B_Diff_T > B_Time *2){
		B_Start_T = millis();
	}

}


void React(){	// The first person that presses the button wins
	
	if (digitalRead(SW_P1) == HIGH){
		Flag = 2;
	}
	
	if (digitalRead(SW_P2) == HIGH){
		Flag = 3;
	}

}


void P1_Win(){		// Player one won
	digitalWrite(LED_P1, HIGH);
	digitalWrite(LED_P2, LOW);
}



void P2_Win(){		// Player two won
	digitalWrite(LED_P2, HIGH);
	digitalWrite(LED_P1, LOW);
}





