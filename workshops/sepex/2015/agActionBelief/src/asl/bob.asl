hungry.
food(100).
stomach(0).

!eat.

+!eat: hungry & food(F) & stomach(S) <- 
	.print("Eating...");
	-+food(F-1);
	-+stomach(S+1);
	.print(F);
	!eat.

-!eat <- 
	.print("I ate a lot!").
	
+stomach(S): S > 60 <-
	.print("I'm Satisfied.");
	-hungry.	


