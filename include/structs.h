#ifndef STRUCTS_H
#define STRUCTS_H

// Konstanta untuk ukuran array char, bisa disesuaikan
#define MAX_ID_PAPER 50
#define MAX_FIELD_STUDY 100
#define MAX_JUDUL 255
#define MAX_SITASI_INFO 50 // Jika sitasi disimpan sebagai string info
#define MAX_PENULIS 150
#define MAX_ABSTRAK 2000

// --- Struktur Data untuk Informasi Jurnal ---
typedef struct {
    char id_paper[MAX_ID_PAPER];         // Field untuk ID paper
    char field_of_study[MAX_FIELD_STUDY];
    char judul[MAX_JUDUL];
    int tahun_terbit;
    char sitasi_info[MAX_SITASI_INFO];
    char nama_penulis[MAX_PENULIS];      // Field di C untuk menyimpan hasil dari key "penulis" di JSON
    char abstrak[MAX_ABSTRAK];
    int jumlah_incitations;
} JurnalData;

// --- Struktur Node untuk Linked List Paper ---
// Node ini akan menyimpan JurnalData dan pointer ke node berikutnya.
// Kita akan menggunakan ini untuk ketiga jenis linked list (urut tahun, incitations, abjad).
typedef struct PaperNode {
    JurnalData data;
    struct PaperNode* next;
    // Jika menggunakan Double Linked List (DLL), tambahkan:
    // struct PaperNode* prev; 
} PaperNode;

// --- Struktur Node untuk BST Field of Study ---
typedef struct BSTNodeField {
    char field_of_study[MAX_FIELD_STUDY];
    PaperNode* list_by_year_head;       // Pointer 1: Head list urut tahun
    PaperNode* list_by_incitations_head; // Pointer 2: Head list urut incitations
    PaperNode* list_by_title_head;      // Pointer 3: Head list urut abjad judul
    PaperNode* list_by_year_asc_head;   
    PaperNode* list_by_author_head;     // Pointer 4: Head list urut abjad penulis

    struct BSTNodeField* left_child;
    struct BSTNodeField* right_child;
} BSTNodeField;

#endif // STRUCTS_H