#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 26 // Length of Alphabet

// Trie structure
struct Trie {
    char letter, // Current Branch's Letter
    occurrences; // Number of Occurrences where Node was last letter
    struct Trie *branch[ALPHABET]; // Trie Branches
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
    if (pTrie == NULL) return; // Check for NULL
    struct Trie *current = pTrie; // Pointer to current Node starting at pTrie
    while (strlen(word)) { // Repeat until end of Word
        if (!(current->branch[word[0] - 'a'])) {
            current->branch[word[0] - 'a'] = calloc(1, sizeof(struct Trie)); // Allocate branch
            current->branch[word[0] - 'a']->letter = word[0]; // Set new branch's letter
        }
        current = current->branch[word[0] - 'a']; // Increment Branch
        word++; // Increment Character in Word
    }
    current->occurrences++; // Increment Occurrences if end of Word
}

// computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    struct Trie *current = pTrie; // Pointer to current node starting at pTrie
    while (strlen(word)) { // Repeat until end of Word
        current = current->branch[word[0] - 'a']; // Increment Node
        if (current) word++; // Increment Character in Word if current Node exists
        else return 0; // Current Node does not exist
    }
    return current->occurrences; // Return occurrences of current Node
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie) { // Check if Trie exists
        for (int i = 0; i < ALPHABET; ++i) { // Loop through all Branches
            if (pTrie->branch[i]) // Check if Branch exists
                pTrie->branch[i] = deallocateTrie(pTrie->branch[i]); // Deallocate and set Branch to NULL
        }
        free(pTrie); // Deallocate current branch
    }
    return NULL; // Returns NULL always
}

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *out = calloc(1, sizeof(struct Trie)); // Allocate Node
    out->letter = '\n'; // Set Trie root Node to NEWLINE
    return out; // Return Node
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
    FILE *input = fopen(filename, "r"); // Open Input File for Reading
    int length; // Length of Input File
    fscanf(input, "%d", &length); // Read Length of Input File from first line
    for (int i = 0; i < length; ++i) { // Read remainder of Input File
        char *word = calloc(256, 1); // Allocate 256-character word to all NULL terminator characters
        fscanf(input, "%255s", word); // Read Word from Input File
        pInWords[i] = word; // Save to index of Input Words
    }
    return length; // Return number of inputs
}

// GLOBAL VARIABLES
char *dictionary; // File path of input dictionary

int main(int nArgs, char **args) {
    switch (nArgs) { // Determine Operating Schema for I/O (Input/Output Mode)
        case 2: // 2 Arguments: Working Directory, Input File Path (Input Mode)
            dictionary = args[1]; // Set Dictionary to custom input
            break; // Prevent further execution
        case 1: // 1 Argument: Working Directory (Default Mode)
            dictionary = "dictionary.txt"; // Set Dictionary to default input
            break; // Prevent further execution
        default: // Not Expected
            exit(1); // Exit with Error Code 1
    }

    char *inWords[256];

    //read the number of the words in the dictionary
    int numWords = readDictionary(dictionary, inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i]);
    }
    // parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL) printf("There is an error in this program\n");
    for (int i = 0; i < numWords; ++i) free(inWords[i]); // Free Input Words List
    return 0;
}