  int minutenvorne =  floor(minuten / 10); //floor rundet die Zahlen ab
     switch(minutenvorne){
    case 0:
     leds2.setBrightness(0, 0x55);
	 leds2.setBrightness(5, 0x55);
	 leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(3, 0x55);
	 leds2.setBrightness(2, 0x55);
	 leds2.setBrightness(7, 0x55);
    break;
    case 1:
     leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(3, 0x55);
    break;
    case 2:     
	 leds2.setBrightness(5, 0x55);
	 leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(1, 0x55);
	 leds2.setBrightness(2, 0x55);
	 leds2.setBrightness(7, 0x55);
    break;
    case 3:
     leds2.setBrightness(1, 0x55);
	 leds2.setBrightness(5, 0x55);
	 leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(3, 0x55);
	 leds2.setBrightness(2, 0x55);
	break;
    case 4:
     leds2.setBrightness(0, 0x55);
	 leds2.setBrightness(1, 0x55);
	 leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(3, 0x55);
	break;
    case 5:
     leds2.setBrightness(0, 0x55);
	 leds2.setBrightness(5, 0x55);
	 leds2.setBrightness(1, 0x55);
	 leds2.setBrightness(3, 0x55);
	 leds2.setBrightness(2, 0x55);
    break;
	}
      
    int moduloMinuten = minuten % 10; // Modulo Beispiel: 23 % 10 = 3 
      switch(moduloMinuten){
   case 0:
     leds2.setBrightness(0, 0x55);
	 leds2.setBrightness(5, 0x55);
	 leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(3, 0x55);
	 leds2.setBrightness(2, 0x55);
	 leds2.setBrightness(7, 0x55);
    break;
    case 1:
     leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(3, 0x55);
    break;
    case 2:     
	 leds2.setBrightness(5, 0x55);
	 leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(1, 0x55);
	 leds2.setBrightness(2, 0x55);
	 leds2.setBrightness(7, 0x55);
    break;
    case 3:
     leds2.setBrightness(1, 0x55);
	 leds2.setBrightness(5, 0x55);
	 leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(3, 0x55);
	 leds2.setBrightness(2, 0x55);
	break;
    case 4:
     leds2.setBrightness(0, 0x55);
	 leds2.setBrightness(1, 0x55);
	 leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(3, 0x55);
	break;
    case 5:
     leds2.setBrightness(0, 0x55);
	 leds2.setBrightness(5, 0x55);
	 leds2.setBrightness(1, 0x55);
	 leds2.setBrightness(3, 0x55);
	 leds2.setBrightness(2, 0x55);
    break;
	 case 6:
     leds2.setBrightness(0, 0x55);
	 leds2.setBrightness(5, 0x55);
	 leds2.setBrightness(1, 0x55);
	 leds2.setBrightness(3, 0x55);
	 leds2.setBrightness(2, 0x55);
	 leds2.setBrightness(7, 0x55);
    break;
    case 7:
     leds2.setBrightness(5, 0x55);
	 leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(3, 0x55);
    break;
    case 8:
     leds2.setBrightness(0, 0x55);
	 leds2.setBrightness(1, 0x55);
	 leds2.setBrightness(5, 0x55);
	 leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(3, 0x55);
	 leds2.setBrightness(2, 0x55);
	 leds2.setBrightness(7, 0x55);
    break;

    case 9:
     leds2.setBrightness(0, 0x55);
	 leds2.setBrightness(5, 0x55);
	 leds2.setBrightness(6, 0x55);
	 leds2.setBrightness(3, 0x55);
	 leds2.setBrightness(2, 0x55);
	 leds2.setBrightness(1, 0x55);
    break;
    
    }
	
	
	