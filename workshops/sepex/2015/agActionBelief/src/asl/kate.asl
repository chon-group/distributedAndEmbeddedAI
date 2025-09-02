hungry.
food(100).
stomach(0).

!eat.

+!eat: hungry & food(F) & stomach(S) & S<=50 <- 
	.print("Eating...");
	-+food(F-1);
	-+stomach(S+1);
	.print(F);
	!eat.
	
+!eat: stomach(S) & S>50 <-
	.print("I'm Satisfied.");
	-hungry.	


