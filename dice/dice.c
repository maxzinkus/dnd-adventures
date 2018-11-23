#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* can probably do an ifdef for windows here... */
#define RAND_SRC "/dev/urandom"

#define FORMAT "%ud%u%c%u\n"
#define MAX_LINE 32
#define PROMPT "> "

static FILE *urandom = NULL;
static char input[MAX_LINE];

typedef enum {
   D4 = 4,
   D6 = 6,
   D8 = 8,
   D10 = 10,
   D20 = 20,
   PERCENTILE = 100
} Die;

/* random byte < threshold
 * so that random byte % threshold is uniform 
 */
#define D6_THRESHOLD 252
#define D10_THRESHOLD 250
#define D20_THRESHOLD 240
#define PERC_THRESHOLD 200

#ifdef TEST_MODE
#define TEST_LEN 1000000
void histogram(unsigned int num, Die faces, char op, unsigned int mod);
#endif

unsigned int roll(unsigned int num, Die faces, char op, unsigned int mod) {
   unsigned int result = 0;
   unsigned char r;
   unsigned char thresh;
   size_t in;
   switch (faces) {
      case D6:
         thresh = D6_THRESHOLD;
         break;
      case D10:
         thresh = D10_THRESHOLD;
         break;
      case D20:
         thresh = D20_THRESHOLD;
         break;
      case PERCENTILE:
         thresh = PERC_THRESHOLD;
         break;
      default:
         thresh = 0;
         break;
   }
   while (num--) {
      do {
         in = fread(&r, sizeof(unsigned char), 1, urandom);
         if (in != 1) {
            abort();
         }
         if (thresh > 0 && r >= thresh) {
            in = 0;
         }
      } while (in < 1);
      r = (r % faces) + 1;
      result += r;
   } 
   if (op == '+') {
      result += mod;
   }
   else if (op == '-') {
      result -= mod;
   }
   return result;
}

int main(int argc, char **argv) {
#ifdef TEST_MODE
   printf("Test mode enabled, iterations = %u\n", TEST_LEN);
#endif
   urandom = fopen(RAND_SRC, "rb");
   if (!urandom) {
      perror("fopen");
      return 1;
   }
   if (printf("%s", PROMPT) < 0) {
      perror("printf");
      return 1;
   }
   if (fflush(stdout) == EOF) {
      perror("fflush");
      return 1;
   }
   bool prev = true;
   unsigned int num = 1;
   Die faces = D20;
   char op = '+';
   unsigned int mod = 0;
   int s_res;
   while (fgets(input, MAX_LINE, stdin)) {
      s_res = sscanf(input, FORMAT, &num, &faces, &op, &mod);
      switch (s_res) {
         case EOF:
            if (ferror(stdin)) {
               perror("sscanf");
               return 1;
            }
            else if (prev) { /* newline */
               printf(FORMAT, num, faces, op, mod);
               printf("%u\n", roll(num, faces, op, mod));
            }
            break;
         case 4: /* all inputs */
            if (!(op == '+' || op == '-')) {
               prev = false;
               break;
            }
            /* fallthrough */
         case 3: /* input w/o modifier */
            if (!(op == '+' || op == '-')) {
               op = '+';
               mod = 0;
            }
            switch (faces) {
               case D4:
               case D6:
               case D8:
               case D10:
               case D20:
               case PERCENTILE:
                  prev = true;
#ifdef TEST_MODE
                  histogram(num, faces, op, mod);
#else
                  printf("%u\n", roll(num, faces, op, mod));
#endif
                  break;
               /* if default, fall all the way down to the outer default */
            }
         default:
            prev = false;
            break;
      }
      printf("%s", PROMPT);
      fflush(stdout);
   }
   return 0;
}

#ifdef TEST_MODE
void histogram(unsigned int num, Die faces, char op, unsigned int mod) {
   unsigned int *results;
   results = calloc((num*faces)+1, sizeof(unsigned int));
   if (!results) {
      perror("calloc");
      return;
   }
   for (unsigned int i = 0; i < TEST_LEN; i++) {
      if (op == '-') {
         results[roll(num, faces, op, mod)+mod] += 1;
      }
      else {
         results[roll(num, faces, op, mod)-mod] += 1;
      }
   }
   for (unsigned int i = 1; i <= num*faces; i++) {
      if (op == '-') {
         printf("%10u:%6f |", i-mod, ((float)results[i])/TEST_LEN);
      }
      else {
         printf("%10u:%6f |", i+mod, ((float)results[i])/TEST_LEN);
      }
      for (unsigned int j = 0;
           j < (unsigned int)((((float)results[i])/TEST_LEN)*100.0f); j++) {
         printf("*");
      }
      printf("\n");
   }
}
#endif