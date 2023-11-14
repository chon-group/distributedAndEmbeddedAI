// Agente A
/* Initial beliefs and rules */
abroad(yes).
/* Initial goals */
!start.

/* Plans */
+!start: abroad(no) <-
	.wait(5000);
  	.print("Computer, Lieutenant Commander Spock, First Officer");
	.print("Spock está na nave");
	!play.
	
+!start: abroad(yes) <-
	.print("Spock Aguardando transporte  - abroad(yes)");
	.wait(5000);
	-abroad(yes);
	.send(kirk, askOne, abroad(Status), Reply);
	+Reply;
	!start.

+!play <-
	.print("estou na nave e usando o arduino");
	.port(ttyACM0);
	.print("ligando led");
	.act(ledOn);
	.print("desligando led");
	.act(ledOff);
	!play.   

