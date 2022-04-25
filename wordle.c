#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *known; // List of 5 letters. Not knowns have "."
static char possible[27]; // List of N letters.

static void
printPossibility(int *letters) {
    for (int i = 0, used = 0; i < 5; i++) {
        if (known[i] != '.') {
            printf("%c", known[i]);
        }
        else {
            int letter = letters[used++];
            printf("%c", possible[letter]);
        }
    }
    printf("\n");
}

static void
swap(int *v, int i, int j) {
    int	t;
    t = v[i];
    v[i] = v[j];
    v[j] = t;
}

// Recursive function to generate permutations.
static void
perm(int *v, int n, int i) {
    // This function generates the permutations of the array
    // from element i to element n-1.

    // If we are at the end of the array, we have one permutation
    // we can use (here we print it; you could as easily hand the
    // array off to some other function that uses it for something.
    if (i == n) {
        printPossibility(v);
        //for (int j=0; j<n; j++) printf("%d ", v[j]);
		//printf ("\n");
    }
    else {
        // Recursively explore the permutations starting
        // at index i going through index n-1.
        for (int j = i; j < n; j++) {
            // Try the array with i and j switched.
            swap(v, i, j);

            perm(v, n, i+1);

            // Swap them back the way they were.
            swap(v, i, j);
        }
    }
}

int
main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("usage: %s KNOWN MISPLACED WRONG\n", argv[0]);
        return 1;
    }

    printf("slant\n");
    printf("price\n");
    printf("dough\n");
    printf("balmy\n");

    printf("warning: no duplicate letters in here\n");

    known = argv[1];
    char *misplaced = argv[2];
    char *wrong = argv[3];

    int required = 0;
    for (int letter = 'a', i = 0; letter <= 'z'; letter++) {
        //char *k = strchr(known ,letter);
        //char *w = strchr(wrong ,letter);
        //printf("letter %c %ld %ld\n", letter, k ? k - known : -1, w ? w - wrong : -1);
        if (!strchr(known, letter) && !strchr(wrong, letter)) {
            possible[i] = letter;
            if (strchr(misplaced, letter)) {
                required |= 1 << i;
            }
            i++;
        }
    }
    //printf("required=%d\n", required);

    int nKnown = 0;
    for (int i = 0; i < 5; i++) {
        nKnown += known[i] != '.';
    }

    int k = 5 - nKnown;
    int n = 26 - nKnown - strlen(wrong);
    possible[n] = 0;
    //printf("possible = %s\n", possible);

    //printf("k=%d, misplaced=%zu, wrong=%zu\n", k, strlen(misplaced), strlen(wrong));
    //printf("n=%d\n", n);

    // i goes through all n-bit numbers.
    for (int i = 0; i < (1 << n); i++) {
        int c = __builtin_popcountl(i);
        if ((i & required) == required && c == k) {
            // By again going through all the bits indices, 
            // printing only the ones with 1-bits.
            int set[5];
            for (int bit = 0, j = 0; bit < 32; bit++) {
                if (i & (1 << bit)) {
                    set[j++] = bit;
                }
            }
            printf("\n");
            printf("PERMUTATIONS ON ");
            for (int j = 0; j < k; j++) {
                printf("%c ", possible[set[j]]);
            }
            printf("\n");
            perm(set, k, 0);
        }
    }
    return 0;
}
