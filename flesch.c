// flesch.c - Student Implementation File
// Implement the Flesch Reading Ease algorithm
//
// DO NOT modify the function signatures

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "flesch.h"

int countSentences(const char* text) {
    // TODO: Implement this function
	int sentences = 0;
	const char* ptr = text;

	while (*ptr) {
		if (*ptr == '.' || *ptr == ':' || *ptr == ';' || 
            *ptr == '?' || *ptr == '!') {
            sentences++;
        }

		ptr++;
	}

    return sentences;
}

int countWords(const char* text) {
    // TODO: Implement this function
	int words = 0;
	bool inWord = false;
	const char* ptr = text;
	
	while (*ptr) {
		bool isDelimiter = isspace(*ptr) || (*ptr == '.' || *ptr == ':' || *ptr == ';' || *ptr == '?' *ptr == '!');

		if (!isDelimiter && !inWord) {
			inWord = true;
			words++;
		} else if (isDelimiter) {
			inWord = false;
		}

		ptr++;
	}

    return words;
}

int countSyllables(const char* text) {
    // TODO: Implement this function
	int syllables = 0;
	bool inVowelGroup = false;
	const char *ptr = text;  	
	
	while (*ptr) {
		char c = tolower(*ptr);
		bool isVowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
		
		if (isVowel && !inVowelGroup) {
			inVowelGroup = true;
			syllables++;	
		} else if (!isVowel) {
			inVowelGroup = false;
		}
	}

	return syllables;
}

double calculateFleschScore(TextStats stats) {
    // TODO: Implement this function
	if (stats.words == 0) {
        return 0.0;
    }

    double words = (double)stats.words;
    double sentences = (double)stats.sentences;
    double syllables = (double)stats.syllables;

    double score = 206.835 - (1.015 * (words / sentences)) - (84.6 * (syllables / words));

    return score;
}

TextStats analyzeText(const char* text) {
    TextStats stats;
    stats.sentences = countSentences(text);
    stats.words = countWords(text);
    stats.syllables = countSyllables(text);
    return stats;
}
