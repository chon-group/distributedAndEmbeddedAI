listOfNumbers([1,2,3,4,5,6,7,8,9,0]).

!choosingNUmbersInAList(3).

+!choosingNUmbersInAList(Round): listOfNumbers(List) & Round > 0 <- 
    .random(List,N);
    !choosed(Round,N).

+!choosed(Round,N): numberChoosed(N) <- 
    !choosingNUmbersInAList(Round).
+!choosed(Round,N): not numberChoosed(N) <- 
    .print("This is a choosed number of the list: ", N);
    +numberChoosed(N);
    !choosingNUmbersInAList(Round-1).

-!choosingNUmbersInAList(Round).