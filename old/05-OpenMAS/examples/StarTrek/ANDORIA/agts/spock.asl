/* Initial beliefs and rules */

/* Initial goals */
!start.

/* Plans */
+abroad(no)[source(X)]<- 
	.print("Computer, Lieutenant Commander Spock, First Officer").
	
+abroad(yes)[source(X)] <-
	.print("Waiting for transport...").

+!start <-
	.abolish(abroad(_));
	.wait(2000);
	.send(kirk,askOne,abroad(Status),Reply); 
	+Reply;
	!start.