/* Initial beliefs and rules */
//inside.

/* Initial goals */
!start.

/* Plans */

+!start : true <-
	.print("Computer, Commander Montgomery Scott, Chief Engineering Office");
	.connectCN("skynet.chon.group",3273,"07ba9e4a-d539-4a0e-8c14-4ac336476858").

+beam_us_up_scotty[source(X)] <-
    .print("Transporter ready for ",X);
	.sendOut(X,tell,energizing);
    -beam_us_up_scotty[source(X)].
   

