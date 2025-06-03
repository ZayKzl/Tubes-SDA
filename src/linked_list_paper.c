#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // Untuk strcasecmp (umumnya di sistem POSIX)
#include "../include/linked_list_paper.h"

PaperNode* buatPaperNode(JurnalData data_jurnal) {
    PaperNode* node_baru = (PaperNode*)malloc(sizeof(PaperNode));
    if (node_baru == NULL) {
        perror("Gagal alokasi memori untuk PaperNode baru");
        return NULL;
    }
    node_baru->data = data_jurnal;
    node_baru->next = NULL;
    node_baru->prev = NULL;
    return node_baru;
}

// Menyisipkan paper ke DLL yang diurutkan berdasarkan TAHUN (MENAIK: terlama dulu)
// Ini adalah fungsi Anda 'sisipkanPaperUrutTahunDLL' yang sudah bekerja, mungkin hanya ganti nama.
void sisipkanDLLUrutTahunAsc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal) {
    PaperNode* node_baru = buatPaperNode(data_jurnal);
    if (node_baru == NULL) return;

    if (*head_ptr == NULL) { // List kosong
        *head_ptr = node_baru;
        *tail_ptr = node_baru;
        return;
    }

    if (data_jurnal.tahun_terbit < (*head_ptr)->data.tahun_terbit) { // Sisip di awal
        node_baru->next = *head_ptr;
        (*head_ptr)->prev = node_baru;
        *head_ptr = node_baru;
        return;
    }

    PaperNode* current = *head_ptr;
    while (current->next != NULL && current->next->data.tahun_terbit <= data_jurnal.tahun_terbit) {
        current = current->next;
    }

    node_baru->next = current->next;
    node_baru->prev = current;
    if (current->next != NULL) {
        current->next->prev = node_baru;
    } else {
        *tail_ptr = node_baru; // Update tail jika sisip di akhir
    }
    current->next = node_baru;
}

// Menyisipkan paper ke DLL yang diurutkan berdasarkan JUMLAH INCITATIONS (MENURUN: terbanyak dulu)
void sisipkanDLLUrutIncitationsDesc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal) {
    PaperNode* node_baru = buatPaperNode(data_jurnal);
    if (node_baru == NULL) return;

    if (*head_ptr == NULL) { // List kosong
        *head_ptr = node_baru;
        *tail_ptr = node_baru;
        return;
    }

    if (data_jurnal.jumlah_incitations > (*head_ptr)->data.jumlah_incitations) { // Sisip di awal (lebih besar)
        node_baru->next = *head_ptr;
        (*head_ptr)->prev = node_baru;
        *head_ptr = node_baru;
        return;
    }

    PaperNode* current = *head_ptr;
    while (current->next != NULL && current->next->data.jumlah_incitations >= data_jurnal.jumlah_incitations) {
        current = current->next;
    }

    node_baru->next = current->next;
    node_baru->prev = current;
    if (current->next != NULL) {
        current->next->prev = node_baru;
    } else {
        *tail_ptr = node_baru; // Update tail jika sisip di akhir
    }
    current->next = node_baru;
}

// Menyisipkan paper ke DLL yang diurutkan berdasarkan JUDUL (abjad A-Z, case-insensitive)
void sisipkanDLLUrutJudulAsc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal) {
    PaperNode* node_baru = buatPaperNode(data_jurnal);
    if (node_baru == NULL) return;

    if (*head_ptr == NULL) { // List kosong
        *head_ptr = node_baru;
        *tail_ptr = node_baru;
        return;
    }
    
    if (strcasecmp(data_jurnal.judul, (*head_ptr)->data.judul) < 0) { // Sisip di awal (lebih kecil secara abjad)
        node_baru->next = *head_ptr;
        (*head_ptr)->prev = node_baru;
        *head_ptr = node_baru;
        return;
    }

    PaperNode* current = *head_ptr;
    while (current->next != NULL && strcasecmp(data_jurnal.judul, current->next->data.judul) >= 0) {
        current = current->next;
    }

    node_baru->next = current->next;
    node_baru->prev = current;
    if (current->next != NULL) {
        current->next->prev = node_baru;
    } else {
        *tail_ptr = node_baru; // Update tail jika sisip di akhir
    }
    current->next = node_baru;
}


void tampilkanListPaper(PaperNode* head, const char* list_name) {
    if (head == NULL) {
        printf("   (List paper %s kosong)\n", list_name);
        return;
    }
    printf("--- Menampilkan List: %s (Maju) ---\n", list_name);
    PaperNode* current = head;
    int i = 1;
    while (current != NULL) {
        printf("   %d. Judul    : %s\n", i, current->data.judul);
        printf("      Tahun    : %d\n", current->data.tahun_terbit);
        printf("      Penulis  : %s\n", current->data.nama_penulis);
        printf("      InCitations: %d\n", current->data.jumlah_incitations);
        printf("      --------------------------------------------------\n");
        current = current->next;
        i++;
    }
}

void tampilkanListPaperReverse(PaperNode* tail, const char* list_name) {
    if (tail == NULL) {
        printf("   (List paper %s kosong atau tail belum di-set)\n", list_name);
        return;
    }
    printf("--- Menampilkan List: %s (Mundur) ---\n", list_name);
    PaperNode* current = tail;
    int i = 1;
    while (current != NULL) {
        printf("   %d. Judul    : %s\n", i, current->data.judul);
        printf("      Tahun    : %d\n", current->data.tahun_terbit);
        printf("      Penulis  : %s\n", current->data.nama_penulis);
        printf("      InCitations: %d\n", current->data.jumlah_incitations);
        printf("      --------------------------------------------------\n");
        current = current->prev;
        i++;
    }
}

void hapusListPaper(PaperNode** head_ptr, PaperNode** tail_ptr) {
    PaperNode* current = *head_ptr;
    PaperNode* next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *head_ptr = NULL;
    *tail_ptr = NULL; // Juga reset tail
}