+!turn(on) <- 
	.print("Lights On.");
	.wait(500);
	.send(kate, tell, light(on));
	!turn(on).