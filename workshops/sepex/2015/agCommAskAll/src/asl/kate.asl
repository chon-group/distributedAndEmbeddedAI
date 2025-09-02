!goToBeach.

+!goToBeach <-
	!!analyze;
	!talkTo.
	
+!talkTo : true <- 
	.print("What is the weather forecast?'");
	.wait(2000);
	.send(bob, askAll, weather(Name)).

/* 	
+!analyze : not weather(clean) & not weather(sunny) <-
	.print("I will not go to the beach.").
*/
 	
+!analyze : weather(clean) & weather(sunny) <-
	.print("Lets go to the beach.").

-!analyze <-
	.print("I do not have weather information yet.");
	.wait(1000);
	!analyze.
