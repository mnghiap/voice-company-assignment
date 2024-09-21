/*
Task: Given a text file, return the most n frequent words
NOTE: Since no explicit requirement is given, words are UNPROCESSED (keeping non alphabet characters like " : etc.)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD_SIZE 100 // Assuming no words with more than 100 chars
#define WORD_ARRAY_SIZE 30000 // Assuming there are at most 30000 unique words

// struct for words with their frequency
typedef struct word {
    char word[WORD_SIZE];
    int count;
} word;

typedef int int32_t;

// Function to compare frequency of words
// Need for qsort
int compareWords(const void *f1, const void *f2){
	word *a = (word *)f1;
	word *b = (word *)f2;
	return (b->count - a->count);
}

char **find_frequent_words(const char *path, int32_t n) {
    FILE *fp; // pointer to file stream
    char buffer[WORD_SIZE]; // temporary buffer for a word
    word wordArray[WORD_ARRAY_SIZE];
    int numUniqueWords = 0; // Number of unique words so far
    char **topNWords; // array to store top n words
    topNWords = malloc(n*sizeof(char*));

    // Open file
    fp = fopen(path, "rb");

    // scan word by word
    // copy current word to buffer
    while ( (fscanf(fp, "%s", buffer)) != EOF) {
        // Check if the word already in the array
        int wordIndex = -1; // If found in the array, store index here
        for (int i = 0; i < numUniqueWords; i++) {
            if (strcmp(wordArray[i].word, buffer) == 0) { // If found, increase word count
                wordIndex = i;
                wordArray[i].count += 1;
                break;
            }
        }
        // if not found, make a new entry, increase numUniqueWords
        if (wordIndex == -1) {
            strcpy(wordArray[numUniqueWords].word, buffer); // copy buffer to "last" entry of word array
            wordArray[numUniqueWords].count = 1;
            numUniqueWords += 1;
        }
    }

    // Sort words
    qsort(wordArray, numUniqueWords, sizeof(word), compareWords);

    // Copy results to topNWords
    for (int i = 0; i < n; i++) {
        topNWords[i] = malloc(WORD_SIZE*sizeof(char));
        strcpy(topNWords[i], wordArray[i].word);
    }

    // Close file
    fclose(fp);

    // Code snippet to load whole file to a string
    // fseek(fp, 0, SEEK_END);
    // long fsize = ftell(fp);
    // fseek(fp, 0, SEEK_SET);  /* same as rewind(f); */
    // char *fileString = malloc(fsize + 1);
    // fread(fileString, fsize, 1, fp);
    // printf("%lu", fsize);

    return topNWords;
}

int main() {
    int n = 10; // How many words do you want
    char** words = find_frequent_words("shakespeare.txt", n);
    for (int i = 0; i < n; i++){
        printf("%s\n", words[i]);
    }
    free(words);
    return 0;
}
