!teach(kate).

+!teach(kate) <- 
	.print("This is how we dance.");
	.wait(2000);
	.send(kate, tellHow, "@d +!dance : true <- .print(\"I'm dancing with myself!\"); .wait(1000); !dance.");
	.wait(2000);
	.send(kate, untellHow, "@d").	

@d
+!dance : true <- 
	.print("I'm dancing with myself!");
	.wait(1000);
	!dance.
	
	