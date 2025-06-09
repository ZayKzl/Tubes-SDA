#include "../include/stack_search_history.h"

// Inisialisasi stack kosong
void initSearchHistoryStack(SearchHistoryStack *s) {
    s->top = NULL;
}

// Mengecek apakah stack kosong
int isSearchHistoryStackEmpty(SearchHistoryStack *s) {
    return (s->top == NULL);
}

// Menambahkan query ke stack
void pushSearchHistory(SearchHistoryStack *s, const char *query) {
    // Hindari menambahkan query kosong atau hanya spasi
    if (query == NULL || strlen(query) == 0 || strspn(query, " \t\n\r") == strlen(query)) {
        return;
    }

    // Alokasi memori untuk node baru
    SearchHistoryNode *newNode = (SearchHistoryNode *)malloc(sizeof(SearchHistoryNode));
    if (newNode == NULL) {
        perror("Memory allocation failed for search history node");
        return;
    }
    // Salin query ke node baru
    strncpy(newNode->query, query, MAX_QUERY_LENGTH - 1);
    newNode->query[MAX_QUERY_LENGTH - 1] = '\0'; // Memastikan null-terminated

    // Tambahkan node baru ke bagian atas stack
    newNode->next = s->top;
    s->top = newNode;
    // printf("Query '%s' ditambahkan ke riwayat pencarian.\n", query); // Opsional: Untuk debugging
}

// Menampilkan seluruh riwayat pencarian
void displaySearchHistory(SearchHistoryStack *s) {
    if (isSearchHistoryStackEmpty(s)) {
        printf("\n--- Riwayat Pencarian ---\n");
        printf("Riwayat pencarian kosong.\n");
        printf("-------------------------\n");
        return;
    }

    printf("\n--- Riwayat Pencarian (Terbaru ke Terlama) ---\n");
    SearchHistoryNode *current = s->top;
    int i = 1;
    while (current != NULL) {
        printf("%d. %s\n", i++, current->query);
        current = current->next;
    }
    printf("---------------------------------------------\n");
}

// Mengosongkan seluruh riwayat pencarian dan membebaskan memori
void clearSearchHistory(SearchHistoryStack *s) {
    SearchHistoryNode *current = s->top;
    SearchHistoryNode *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    s->top = NULL;
    // printf("Riwayat pencarian telah dikosongkan.\n"); // Opsional: Untuk debugging
}