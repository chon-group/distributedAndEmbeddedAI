hungry.
stomach(0).

!eat.

+!eat: hungry & food(F) & stomach(S) & S<=49 & F>0 <- 
	.print("Eating...");
	.print(F);
	eat;
	-+stomach(S+1);
	.wait(500);
	!eat.
	
+!eat: stomach(S) & S>49 <-
	.print("I'm Satisfied.");
	-hungry.	

+!eat: food(F) & F=0 <-
	.print("I'm sad! There is no more food.").	

-!eat <-
	!eat.