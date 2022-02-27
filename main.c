#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include <stdbool.h>

# define ASSERT_STRING(expected, got) assertString(expected,got, \
 __FILE__ , __FUNCTION__ , __LINE__ )


typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

size_t strlen_(const char *begin) {
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
    char *s[strlen_(beginSource)];
    char *destination = memcpy(&beginDestination, &s, endSource - beginSource);
    return destination;
}

char *copyIf(char *beginSource, const char *endSource,
             char *beginDestination, int (*f)(int)) {
    char *s[strlen_(beginSource)];
    char *s1[strlen_(beginDestination)];
    for (char i = *beginSource; i < *endSource; i++) {
        if (f) {
            s1[i] = s[i];
            beginDestination++;
        }
    }
    return beginDestination;
}

char *copyIfReverse(char *rbeginSource, const char *rendSource,
                    char *beginDestination, int (*f)(int)) {
    char *s[strlen_(rbeginSource)];
    char *s1[strlen_(beginDestination)];
    char j = *beginDestination;
    for (char i = *rendSource; i > *rbeginSource; i--) {
        if (f) {
            s1[j] = s[i];
            beginDestination++;
        }
        j++;
    }
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
    for (int i = 0; i < strlen_(0); i++) {
        for (int j = i + 1; j < strlen_(0); j++) {
            if (s[i] == s[j])
                RemoveValueAt(s, strlen_(0), j);
        }
    }
}

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word ->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}


bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word) {

}


int main() {
    printf("Hello, World!\n");
    return 0;
}
