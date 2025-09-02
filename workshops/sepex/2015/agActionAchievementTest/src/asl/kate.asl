!bark.

+!bark <-
	.print("sniff!");
	!!sniff;
	.print("sniff!").
	
+!sniff <-
	.print("Is it bob?");
	?dog(X);
	.print(X).	
 	
+?dog(X) <-
	X = bob; 
	+dog(X);
	.print("I found X").
	
		
		
