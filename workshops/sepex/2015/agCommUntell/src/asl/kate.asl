!talkTo.

+!talkTo : true <- 
	.print("Hi Bob, I'm Beautiful!");
	.send(bob, tell, kate(beautiful)).

+~kate(beautiful) [source(bob)] <-
	.print("Sorry.");
	.send(bob, untell, kate(beautiful)[source(kate)]).


 