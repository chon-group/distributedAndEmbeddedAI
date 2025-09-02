!bark.

+!bark : dog(unknow) <- 
	.print("Au Au Au!").

-!bark <-
	.print("sniff sniff!");
	!sniff.

+!sniff <-
	.print("Is it bob?");
	?dog(X);
	.print(X).	
 	
+?dog(X) <-
	X = bob; 
	+dog(X).
		
		
