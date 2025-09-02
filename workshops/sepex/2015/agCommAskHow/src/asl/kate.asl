!talkTo.
!turn(on).

+!talkTo : true <- 
	.print("Please, Can you teach me how to turn on the lights?");
	.wait(5000);
	.send(bob, askHow, "+!turn(on)").

-!turn(on) <-
	.print("I don't know how to turn on the lights.");
	.wait(1000);
	!turn(on).
	
+kate(beautiful) <- 
	.print("Thank you.").	