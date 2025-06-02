#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list_paper.h" // Berisi deklarasi fungsi dan include "structs.h"

// --- Fungsi untuk Membuat Node Paper Baru ---
PaperNode* buatPaperNode(JurnalData data_jurnal) {
    PaperNode* node_baru = (PaperNode*)malloc(sizeof(PaperNode));
    if (node_baru == NULL) {
        perror("Gagal alokasi memori untuk PaperNode baru");
        return NULL;
    }
    node_baru->data = data_jurnal; // Salin data jurnal
    node_baru->next = NULL;
    // Jika menggunakan DLL, inisialisasi: node_baru->prev = NULL;
    return node_baru;
}

// --- Implementasi Fungsi Sisip Terurut ---

// Menyisipkan paper ke list yang diurutkan berdasarkan TAHUN (menurun: terbaru dulu)
PaperNode* sisipkanPaperUrutTahun(PaperNode* head, JurnalData data_jurnal) {
    PaperNode* node_baru = buatPaperNode(data_jurnal);
    if (node_baru == NULL) {
        return head; // Gagal membuat node, kembalikan head asli
    }

    // Kasus 1: List kosong atau node baru harus jadi head (tahun lebih baru)
    if (head == NULL || node_baru->data.tahun_terbit > head->data.tahun_terbit) {
        node_baru->next = head;
        // Jika DLL: if (head != NULL) head->prev = node_baru;
        return node_baru; // Head baru adalah node_baru
    }

    // Kasus 2: Cari posisi yang tepat untuk menyisipkan
    PaperNode* current = head;
    while (current->next != NULL && current->next->data.tahun_terbit >= node_baru->data.tahun_terbit) {
        current = current->next;
    }

    node_baru->next = current->next;
    // Jika DLL:
    // if (current->next != NULL) {
    //     current->next->prev = node_baru;
    // }
    current->next = node_baru;
    // node_baru->prev = current;
    
    return head;
}

// Menyisipkan paper ke list yang diurutkan berdasarkan JUMLAH INCITATIONS (menurun: terbanyak dulu)
PaperNode* sisipkanPaperUrutIncitations(PaperNode* head, JurnalData data_jurnal) {
    PaperNode* node_baru = buatPaperNode(data_jurnal);
    if (node_baru == NULL) {
        return head;
    }

    if (head == NULL || node_baru->data.jumlah_incitations > head->data.jumlah_incitations) {
        node_baru->next = head;
        return node_baru;
    }

    PaperNode* current = head;
    while (current->next != NULL && current->next->data.jumlah_incitations >= node_baru->data.jumlah_incitations) {
        current = current->next;
    }
    node_baru->next = current->next;
    current->next = node_baru;
    return head;
}

// Menyisipkan paper ke list yang diurutkan berdasarkan JUDUL (abjad A-Z, case-insensitive)
PaperNode* sisipkanPaperUrutJudul(PaperNode* head, JurnalData data_jurnal) {
    PaperNode* node_baru = buatPaperNode(data_jurnal);
    if (node_baru == NULL) {
        return head;
    }

    // Menggunakan strcasecmp untuk perbandingan case-insensitive (butuh _GNU_SOURCE di beberapa sistem atau string.h POSIX)
    // Alternatif: konversi kedua string ke huruf kecil/besar dulu sebelum strcmp.
    // Untuk portabilitas lebih, kita bisa buat fungsi lower_strcmp sendiri.
    // Di sini kita asumsikan strcasecmp tersedia atau diganti dengan strcmp jika case-sensitive cukup.
    // #include <strings.h> // untuk strcasecmp di beberapa sistem
    
    if (head == NULL || strcasecmp(node_baru->data.judul, head->data.judul) < 0) {
        node_baru->next = head;
        return node_baru;
    }

    PaperNode* current = head;
    while (current->next != NULL && strcasecmp(node_baru->data.judul, current->next->data.judul) >= 0) {
        current = current->next;
    }
    node_baru->next = current->next;
    current->next = node_baru;
    return head;
}

// --- Fungsi untuk Menampilkan Isi Linked List Paper ---
void tampilkanListPaper(PaperNode* head) {
    if (head == NULL) {
        printf("   (List paper kosong)\n");
        return;
    }
    PaperNode* current = head;
    int i = 1;
    while (current != NULL) {
        printf("   %d. Judul    : %s\n", i, current->data.judul);
        printf("      Tahun    : %d\n", current->data.tahun_terbit);
        printf("      Penulis  : %s\n", current->data.nama_penulis);
        printf("      InCitations: %d\n", current->data.jumlah_incitations);
        // Tampilkan field lain jika perlu
        printf("      --------------------------------------------------\n");
        current = current->next;
        i++;
    }
}

// --- Fungsi untuk Menghapus (Dealokasi Memori) Linked List Paper ---
void hapusListPaper(PaperNode* head) {
    PaperNode* current = head;
    PaperNode* next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

PaperNode* sisipkanPaperUrutTahunAsc(PaperNode* head, JurnalData data_jurnal) {
    PaperNode* node_baru = buatPaperNode(data_jurnal);
    if (node_baru == NULL) {
        return head; // Gagal membuat node, kembalikan head asli
    }

    // Kasus 1: List kosong atau node baru harus jadi head (tahun lebih LAMA atau SAMA)
    // Jika tahun sama, node baru bisa diletakkan di depan untuk urutan stabil,
    // atau di belakang tergantung preferensi (di sini kita letakkan di depan jika lebih kecil).
    if (head == NULL || node_baru->data.tahun_terbit < head->data.tahun_terbit) {
        node_baru->next = head;
        // Jika DLL: if (head != NULL) head->prev = node_baru;
        return node_baru; // Head baru adalah node_baru
    }
    // Jika tahun sama dengan head, dan Anda ingin yang baru masuk setelahnya (atau sebaliknya)
    // Anda bisa tambahkan kondisi: else if (node_baru->data.tahun_terbit == head->data.tahun_terbit) { ... }
    // Untuk kesederhanaan, jika tahun sama, kita akan letakkan setelahnya sesuai loop di bawah.

    // Kasus 2: Cari posisi yang tepat untuk menyisipkan
    PaperNode* current = head;
    // Kita mencari posisi di mana node berikutnya memiliki tahun yang LEBIH BESAR ATAU SAMA
    // sehingga node baru (yang lebih kecil atau sama) disisipkan SEBELUM node tersebut.
    while (current->next != NULL && current->next->data.tahun_terbit <= node_baru->data.tahun_terbit) {
        current = current->next;
    }

    node_baru->next = current->next;
    // Jika DLL:
    // if (current->next != NULL) {
    //     current->next->prev = node_baru;
    // }
    current->next = node_baru;
    // node_baru->prev = current;
    
    return head;
}