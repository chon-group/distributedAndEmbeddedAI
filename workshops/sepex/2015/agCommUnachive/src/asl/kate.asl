!talkTo.

+!talkTo : true <- 
	.print("Please, turn on the lights.");
	.send(bob, achieve, turn(on)).

+light(on) <-
	.wait(5000);
	.send(bob, unachieve, turn(on)). 
	
	