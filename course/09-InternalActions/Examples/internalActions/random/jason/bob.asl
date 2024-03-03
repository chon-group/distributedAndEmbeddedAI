//!sortingRandomNumber(3).

+!sortingRandomNumber(Round): Round>0 <- 
    .random(N); 
    .print("This is a RANDOM number: ", N);
    !sortingRandomNumber(Round-1).

-!sortingRandomNumber(Round).
