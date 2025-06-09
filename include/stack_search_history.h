#ifndef STACK_SEARCH_HISTORY_H
#define STACK_SEARCH_HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUERY_LENGTH 50 // Sesuaikan panjang maksimal query jika perlu

// Struktur untuk node stack
typedef struct SearchHistoryNode {
    char query[MAX_QUERY_LENGTH];
    struct SearchHistoryNode *next;
} SearchHistoryNode;

// Struktur untuk stack riwayat pencarian
typedef struct SearchHistoryStack {
    SearchHistoryNode *top;
} SearchHistoryStack;

// Deklarasi fungsi-fungsi stack
void initSearchHistoryStack(SearchHistoryStack *s);
int isSearchHistoryStackEmpty(SearchHistoryStack *s);
void pushSearchHistory(SearchHistoryStack *s, const char *query);
void displaySearchHistory(SearchHistoryStack *s);
void clearSearchHistory(SearchHistoryStack *s); // Fungsi opsional untuk mengosongkan riwayat

#endif // STACK_SEARCH_HISTORY_H