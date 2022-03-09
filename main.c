#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include <stdbool.h>
# include <assert.h>

# define MAX_STRING_SIZE 100
# define MAX_N_WORDS_IN_STRING 100
# define MAX_WORD_SIZE 20


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




int main() {
    test_digitToStartTransform_oneWord();
    test_removeAdjacentEqualLetters();
    return 0;
}
