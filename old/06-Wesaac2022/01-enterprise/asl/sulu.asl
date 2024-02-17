+!config <-
	.port(ttyACM0).

+!fire <-
	!config;
	.print("Target acquired.");
	.print("Photon torpedo fired!");
	.act(buzzerOn);
	.wait(50);
	.act(buzzerOff);
	.act(buzzerOn);
	.wait(50);
	.act(buzzerOff).
	
	
