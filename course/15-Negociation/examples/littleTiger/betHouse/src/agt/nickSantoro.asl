// Agent nickSantoro in project betHouse
iotGateway("skynet.chon.group",5500).
betHouseIotAddress("07ba9e4a-d539-4a0e-8c14-4ac336476999").
blockChain("http://testchain.chon.group:9984/").
vellusToken("d7bd13c107b432246713a0a95018c91dfd699406422877d7219ecffcccf4a9d2").
value(0,"🍎").
value(1,"🍈").
value(2,"🎸").
value(3,"🔥").
value(4,"🍒").
value(5,"🎂").
value(6,"🍋").
value(7,"7️").
listOfNumbers([0,1,2,3,4,5,6,7]).


!connectIoTGateway.
//!sort.

+!saldo: 
 myWallet(P,Q) & 
 blockChain(B) & 
 vellusToken(T)<-
	.velluscinum.tokenBalance(B,P,Q,T,balance);
	.wait(balance(T,U));
	.print("Premio máximo = ",U," Vellus");
.


+?myWallet(P,Q) <-
	.velluscinum.loadWallet(myWallet);
	.wait(myWallet(P,Q));
	!saldo;
.
+!connectIoTGateway <-
	.policy(input,migration,all,drop);
    .policy(input,communication,all,drop);
    .guidance(input,communication,"*",achieve,accept);
	?iotGateway(Server,Port);
	?betHouseIotAddress(UUID);
    .connectCN(Server,Port,UUID);
	// .connectCN(Server,Port,_);
	// .connectCN(Server,Port);
.

+!isOnline(ACK)[source(S)]: not rodando <-
	.print("GoAhead ", S);
	.sendOut(S,tell,isOnline(ACK)).

+!infoWalletAddress[source(S)] <-
	?myWallet(PrivateKey,PublicKey);
	.print("Informing to ",S," that the betHouseWallet address is:",PublicKey);
    .sendOut(S,tell,betHouseWallet(PublicKey)).

+!apostar(Valor,TransactionID,Carteira)[source(Source)] <-
	+rodando;
	?blockChain(S);
	?vellusToken(Token);
	?myWallet(P,Q);
	.velluscinum.stampTransaction(S,P,Q,TransactionID,all(amount(Valor),asset(Token),ownerBefore(Carteira)));
	!sort(TransactionID,Valor,Carteira,Source);
.

-!apostar(Valor,TransactionID,Carteira)[source(Source)] <-
	.print("Erro na verificação");
	-rodando.

+!sort(TransactionID,Valor,Carteira,UUID) <-
	.print("Sorting for... ",TransactionID);
	?choosed(N1);
	?choosed(N2);
	?choosed(N3);
	!info(TransactionID,Valor,Carteira,UUID,numbers(N1,N2,N3)).
	
+!info(TransactionID,Valor,Carteira,UUID,numbers(N1,N2,N3)): N1==N2 & N1==N3 <- 
	!show(N1,N2,N3); 
	.print("You WIN!!!! Wallet:",Carteira," até: ",Valor*100);
	!saldo;
	!pagar(Carteira,Valor*100);
	.sendOut(UUID,tell,result(TransactionID,win));
	-rodando.

+!info(TransactionID,Valor,Carteira,UUID,numbers(N1,N2,N3)) <- !show(N1,N2,N3); 
	.print("You LOSE!!!! Wallet:",Carteira); 
	!saldo; 
	.sendOut(UUID,tell,result(TransactionID,lose));
	-rodando.

+!show(N1,N2,N3) <-
	?value(N1,F1);
	?value(N2,F2);
	?value(N3,F3);
	.print(F1," ",F2," ",F3).

+?choosed(N): listOfNumbers(List)<-  .random(List,N).

+!pagar(Carteira,Valor):vellusToken(Token) & balance(Token,U) & Valor <= U <-
	!transferir(Carteira,Valor,Token).

+!pagar(Carteira,Valor):vellusToken(Token) & balance(Token,U) & Valor > U <-
	!transferir(Carteira,U,Token).

+!transferir(Carteira,Units,Token) <-
	?blockChain(S);
	?myWallet(P,Q);
	.velluscinum.transferToken(S,P,Q,Token,Carteira,Units);
.