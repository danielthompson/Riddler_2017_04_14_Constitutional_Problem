#include <iostream>
#include <array>
#include <time.h>

/**
 * Imagine that U.S. Supreme Court nominees are only confirmed if the same party
 * holds the presidency and the Senate. What is the expected number of vacancies
 * on the bench in the long run?
 *
 * You can assume the following:
 *
 * 1. You start with an empty, nine-person bench.
 * 2. There are two parties, and each has a 50 percent chance of winning the
 *    presidency and a 50 percent chance of winning the Senate in each election.
 * 3. The outcomes of Senate elections and presidential elections are independent.
 * 4. The length of time for which a justice serves is uniformly distributed between
 *    zero and 40 years.
 *
 * @return
 */

const int minTermLength = 0;
const int maxTermLength = 40;

const int benchSize = 9;
const int years = 1000000;

const int presidentTermLength = 2;
const int senateTermLength = 2;

const int numParties = 2;

int getJusticeLength() {
   return minTermLength + (rand() % (maxTermLength + 1));
}

int getElection() {
   return rand() % numParties;
}

int main() {

   // seed the RNG
   srand((unsigned int) time(NULL));

   // initialize to 0
   std::array<int, benchSize> bench = { };

   int presidency = 0;
   int senate = 0;

   int totalEmptySeats = 0;

   for (int year = 0; year < years; year++) {

      // age the justices
      for (int seat = 0; seat < benchSize; seat++)
      {
         bench[seat] = bench[seat] - 1;
      }

      // run the elections
      if (year % senateTermLength == 0)
         senate = getElection();

      if (year % presidentTermLength == 0)
         presidency = getElection();

      if (senate == presidency) {
         // appoint justices to any empty seats
         for (int seat = 0; seat < benchSize; seat++)
         {
            while (bench[seat] <= 0) {
               bench[seat] = getJusticeLength();
            }
         }
      };

      // count empty seats

      int emptySeats = 0;

      for (int seat = 0; seat < benchSize; seat++)
      {
         if (bench[seat] <= 0) {
            emptySeats++;
         }
      }

      totalEmptySeats += emptySeats;

      //std::cout << "Year " << year << ": " << emptySeats << std::endl;
   }

   double average = (double)totalEmptySeats / (double)years;

   std::cout << "Longterm, " << average << " total empty seats per year" << std::endl;

   return 0;
}