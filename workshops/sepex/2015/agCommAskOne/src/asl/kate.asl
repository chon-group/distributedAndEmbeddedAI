!talkTo.

+!talkTo : true <- 
	.print("What's your name?'");
	.send(bob, askOne, name(Name), Reply);
	+Reply.

+name(Name) : Name == bob <-
	 .print("Nice to meet you.").

