#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include <stdbool.h>
# include <assert.h>

# define MAX_STRING_SIZE 100
# define MAX_N_WORDS_IN_STRING 100
# define MAX_WORD_SIZE 20


char *getEndOfString(char *str) {
    while (*str)
        str++;

    return str;
}

int getDigit(char x) {
    return (x > '0') && (x < '9');
}

char _stringBuffer[MAX_STRING_SIZE + 1];


typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

size_t strlen_(char *begin) {
    char *end = begin;
    while (*end != '\0') {
        end++;
    }
    return end - begin;
}


void RemoveValueAt(char *a, int n, int index) {
    n--; // уменьшаем р
    for (int i = index; i < n; i++) {
        a[i] = a[i + 1];
    }
}


char *find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch) {
        begin++;
    }

    return begin;
}


char *findNonSpace(char *begin) {
    while (*begin != '\0') {
        if (isspace(*begin) == 0)
            return begin;
        begin++;
    }
    return begin;
}


char *findSpace(char *begin) {
    while (*begin != '\0') {
        if (isspace(*begin) == 1)
            return begin;
        begin++;
    }
    return begin;
}


char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (*rbegin != *rend) {
        if (isspace(*rbegin) == 0)
            return rbegin;
        rbegin--;
    }
    return rbegin;
}


char *findSpaceReverse(char *rbegin, const char *rend) {
    while (*rbegin != *rend) {
        if (isspace(*rbegin) == 1)
            return rbegin;
        rbegin--;
    }
    return rbegin;
}


int strcmp(const char *lhs, const char *rhs) {
    while (*lhs && (*lhs == *rhs)) {
        lhs++;
        rhs++;
    }
    return *(const unsigned char *) lhs - *(const unsigned char *) rhs;
}


char *copy(const char *beginSource, const char *endSource,
           char *beginDestination) {
    while (beginSource != endSource) {
        memcpy(beginDestination, beginSource, sizeof(char));
        beginDestination++;
        beginSource++;
    }
    return beginDestination;

}

char *copyIf(const char *beginSource, const char *endSource,
             char *beginDestination, int (*f)(int)) {
    while (beginSource != endSource)
        if (f(*beginSource)) {
            memcpy(beginDestination, beginSource, sizeof(char));
            beginDestination++;
            beginSource++;
        } else
            beginSource++;
    return beginDestination;
}

char *copyIfReverse(const char *rbeginSource, const char *rendSource,
                    char *beginDestination, int (*f)(int)) {
    while (rbeginSource != rendSource)
        if (f(*rbeginSource)) {
            memcpy(beginDestination, rbeginSource, sizeof(char));
            beginDestination++;
            rbeginSource--;
        } else
            rbeginSource--;

    return beginDestination;
}


void removeNonLetters(char *s) {
    char *endSource = strlen_(0);
    char *destination = copyIf(s, endSource, s, isspace);
    *destination = '\0';
}


void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp(expected, got) > 0 || strcmp(expected, got) < 0) {
        fprintf(stderr, " File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, " Expected : \"%s \"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}


void removeAdjacentEqualLetters(char *s) {
    char *endBuffer = copy(s, s + strlen_(s), _stringBuffer);
    char *beginBuffer = _stringBuffer;
    while (beginBuffer < endBuffer) {
        if (*beginBuffer == *(beginBuffer + 1)) {
            while (*beginBuffer == *(beginBuffer + 1)) {
                beginBuffer++;
            }
        } else {
            *s++ = *beginBuffer;
            beginBuffer++;
        }
    }
    *s = '\0';
}


int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}


void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,

                                      word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}


bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word) {
    word->begin = findNonSpaceReverse(rbegin, rend);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpaceReverse(rbegin, rend);

}

void outPutArray(char *s) {
    for (int i = 0; i < MAX_STRING_SIZE; i++) {
        printf("%c", s[i]);
    }
}

void replaceDigitsWithSpaces(char *str) {
    char *endBuffer = copy(str, str + strlen_(str), _stringBuffer);
    char *beginBuffer = _stringBuffer;
    while (beginBuffer < endBuffer) {
        if (isdigit(*beginBuffer)) {
            int nSpaces = *beginBuffer - '0';
            for (int i = 0; i < nSpaces; i++)
                *str++ = ' ';
        } else
            *(str++) = *beginBuffer;
        beginBuffer++;
    }
    *str = '\0';
}

void test_digitToStartTransform_oneWord() {
    char s[] = "Hi123";
    replaceDigitsWithSpaces(s);
    char s1[] = "Hi      ";
    assert(strcmp(s, s1) == 0);
}

void test_removeAdjacentEqualLetters() {
    char s[] = "Hiii123";
    removeAdjacentEqualLetters(s);
    char s1[] = "Hi123";
    assert(strcmp(s, s1) == 0);
}

int WordsEqual(WordDescriptor w1,
               WordDescriptor w2) {
    return strcmp(w1.begin, w2.begin) == 0;
}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};

    char *readPtr;
    char *recPtr;
    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }
    WordDescriptor currentWord;
    while (getWord(readPtr, &currentWord)) {
        if (WordsEqual(word1, currentWord)) {
            recPtr = copy(word2.begin, word2.end, recPtr);
        } else
            recPtr = copy(currentWord.begin, currentWord.end, recPtr);
        *recPtr++ = ' ';
        readPtr = currentWord.end;
    }

    recPtr -= (recPtr != source);
    *recPtr = '\0';
}


void getMergeString(char *s1, char *s2, char *res) {
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2;
    while ((isW1Found = getWord(beginSearch1, &word1)),
            (isW2Found = getWord(beginSearch2, &word2)),
            isW1Found || isW2Found) {
        if (isW1Found) {
            res = copy(word1.begin, word1.end, res);
            *res++ = ' ';
            beginSearch1 = word1.end;
        }
        if (isW2Found) {
            res = copy(word2.begin, word2.end, res);
            *res++ = ' ';
            beginSearch2 = word2.end;
        }
    }
    *res = '\0';
}



void reverseString(char *str) {
    if (*str == '\0')
        return;
    char *endBuffer = copy(str, getEndOfString(str), _stringBuffer);
    WordDescriptor word;
    while (getWordReverse(endBuffer - 1, _stringBuffer - 1, &word)) {
        str = copy(word.begin,word.end,str);
        *(str++) = ' ';
        endBuffer = word.begin;
    }
    *(--str) = '\0';
}

void lexicographicallyOrderedWords() {


}

int main() {
    char s[] = "Hi123";
    char s1[] = "Hi123";
    size_t w1Size = strlen_(s);
    size_t w2Size = strlen_(s1);
    WordDescriptor word1 = {s, s + w1Size};
    WordDescriptor word2 = {s1, s1 + w2Size};
    int result = WordsEqual(word1, word2);
    printf("%d", result);
    return 0;
}
