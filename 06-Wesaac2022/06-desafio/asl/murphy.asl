scott("07ba9e4a-d539-4a0e-8c14-4ac336476858").
!start.

+!start <-
	.print("I'm Murphy.");
	.connectCN("skynet.chon.group",3273,"229195d9-555f-42a2-bc10-f63552870564");
	!move.

+!move: scott(UUID) <-
	.send(robocop, tell, moved);
	.moveOut(UUID, mutualism, robocop).
