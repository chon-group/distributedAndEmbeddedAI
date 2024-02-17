/* Crenças Iniciais */
//https://www.uuidgenerator.net/
myUUID("07ba9e4a-d539-4a0e-8c14-4ac336476858").
skyNet("skynet.chon.group",5500).				//public SkynetServer

/* Initial goals */
!start.

/* Plans */
+!start : true <-
	?myUUID(ID);
	?skyNet(Server,Port);
	.connectCN(Server,Port,ID);
	.print("Computer, Commander Montgomery Scott, Chief Engineering Office").

+beam_us_up_scotty[source(X)] <-
    .print("Transporter ready for ",X);
	.sendOut(X,tell,energizing);
    -beam_us_up_scotty[source(X)];
	!!greeting.

+!greeting <-
	.wait(2500);
	.print("Welcome to Enterprise...");
	.broadcast(tell,abroad(no));
	!greeting.