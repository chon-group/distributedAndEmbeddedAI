!teach(kate).

+!teach(kate) <- 
	.print("This is how we do it.");
	.send(kate, tellHow, "+!turn(on) <- .print(\"Lights On.\").");
	.wait(3000);
	.send(kate, achieve, turn(on)).

+!turn(on) <- 
	.print("Lights On.").
	
	