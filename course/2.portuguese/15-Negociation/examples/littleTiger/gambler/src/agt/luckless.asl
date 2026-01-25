iotGateway("skynet.chon.group",5500).
betHouseIotAddress("07ba9e4a-d539-4a0e-8c14-4ac336476999").
blockChain("http://testchain.chon.group:9984/").
vellusToken("d7bd13c107b432246713a0a95018c91dfd699406422877d7219ecffcccf4a9d2").

!jogar(50000,1).

+!conectar: not hermes::contextNetConfiguration(_,_,_,_,"true",_) <-
	?iotGateway(Server,Port);
    .connectCN(Server,Port,"11ba9e4a-d539-4a0e-8c14-4ac336476999");
.

+!conectar: hermes::contextNetConfiguration(_,_,_,_,"true",_).

+!ping <-
	!conectar;
	?betHouseIotAddress(BetMAS);
	.abolish(isOnline(_)[source(_)]);
	.random(ACK);
	.sendOut(BetMAS,achieve,isOnline(ACK));
	.wait(isOnline(ACK),5000);
	.print("Liberado para jogar!!!");
.

-!ping <-
	.disconnectCN;
	.random(R); .wait(5000*R);
	!ping.


+?getBetHouseWallet(Address): 
 betHouseWallet(Address)[source(Source)] &
 betHouseIotAddress(UUID) & 
 .substring(UUID,Source).

+?getBetHouseWallet(Address): 
 betHouseIotAddress(UUID) <-
	.print("Perguntando sobre a betHouseWallet para: ",UUID);
	.sendOut(UUID,achieve,infoWalletAddress);
	.random(R); .wait(10000*R);
	?getBetHouseWallet(Address);
.

+?saldo(Units): 
 myWallet(P,Q) & 
 blockChain(S) & 
 vellusToken(Coin)<-
	.abolish(balance(_,_));
	.velluscinum.tokenBalance(S,P,Q,Coin,balance);
	.wait(balance(Coin,Units));
	.print("Exists ",Units," of ",Coin," in my wallet!");
.

+?saldo(Units): not myWallet(P,Q) <-
	.velluscinum.loadWallet(myWallet);
	.wait(myWallet(PrivateKey,PublicKey));
	?saldo(Units);
.

+!jogar(Apostas,Valor): balance(Coin,Units) <-
	!apostar(Apostas,Valor).

+!jogar(Apostas,Valor): not balance(Coin,Units) <-
	?saldo(Units);
	!jogar(Apostas,Valor).

+!apostar(Apostas,Valor): 
 vellusToken(T) & Apostas > 0 &
 balance(T,U) & Valor <= U <-
	!ping;
	?getBetHouseWallet(BetMASWallet);
 	?myWallet(P,Q);
 	?blockChain(S);
 	.velluscinum.transferToken(S,P,Q,T,BetMASWallet,Valor,comprovante);
	-+balance(T,U-Valor);
	?betHouseIotAddress(BetMAS);
 	.wait(comprovante(TransactionID));
	.sendOut(BetMAS,achieve,apostar(Valor,TransactionID,Q));
	.print("Aposta Nr",Apostas," Valor ",Valor," tokens: ",S,"api/v1/transactions/",TransactionID);
	!aguardar(TransactionID,Apostas,Valor)
.

+!aguardar(TransactionID,ApostaNr,Valor) <-
	.wait(result(TransactionID,Result),30000);
	!jogar(ApostaNr-1,Valor);
.

-!aguardar(TransactionID,ApostaNr,Valor) <-
	!jogar(ApostaNr-1,Valor);
.

+!apostar(Apostas,Valor): Apostas <= 0 <-
	.abolish(balance(_,_));
	.print("Fim das apostas!!!!");
.

+!apostar(Apostas,Valor): 
 vellusToken(T) &
 balance(T,U) & Valor > U <-
	?myWallet(P,Q);
	.print("Sem saldo suficiente na carteira: ",Q);
	.print("---> use the Vellus Faucet to get some tokens at: https://testchain.chon.group/");
.

+result(TransactionID,Result): Result==lose<-
	.print("Aposta Id=",TransactionID," Resultado... ",Result).

+result(TransactionID,Result): Result==win <-
	.print("Aposta Id=",TransactionID," WIN!!!!... ");
	.abolish(balance(_,_));
	.drop_desire(jogar(_,_));
	?saldo(Units);
.