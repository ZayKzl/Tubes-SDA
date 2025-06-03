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

int hitungTotalItemDiList(PaperNode* head) {
    int count = 0;
    PaperNode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Tampilan MAJU dengan paginasi (NOMOR LOKAL 1-N PER HALAMAN)
int tampilkanListPaper(PaperNode* head, const char* list_name, int halaman_sekarang, int item_per_halaman) {
    if (head == NULL) {
        printf("   (List paper %s kosong)\n", list_name);
        return 0;
    }

    int total_item = hitungTotalItemDiList(head);
    if (total_item == 0) {
        printf("   (List paper %s kosong)\n", list_name);
        return 0;
    }

    int start_index_0based = (halaman_sekarang - 1) * item_per_halaman;
    
    if (start_index_0based >= total_item) {
        // Tidak ada item untuk halaman ini
        return total_item; 
    }

    PaperNode* current = head;
    int i_skip = 0; 
    while (current != NULL && i_skip < start_index_0based) {
        current = current->next;
        i_skip++;
    }

    int item_ditampilkan_di_halaman_ini = 0;
    int nomor_tampil_lokal = 1; // Nomor dimulai dari 1 untuk setiap halaman
    while (current != NULL && item_ditampilkan_di_halaman_ini < item_per_halaman) {
        printf("   %d.  Judul      : %s\n", nomor_tampil_lokal, current->data.judul);
        printf("       Tahun       : %d\n", current->data.tahun_terbit);
        printf("       Penulis     : %s\n", current->data.nama_penulis);
        printf("       InCitations : %d\n", current->data.jumlah_incitations);
        printf("      --------------------------------------------------\n");
        current = current->next;
        item_ditampilkan_di_halaman_ini++;
        nomor_tampil_lokal++;
    }
    
    if (item_ditampilkan_di_halaman_ini == 0 && halaman_sekarang > 0 && total_item > 0) {
         printf("   (Tidak ada item lagi di halaman %d untuk list %s)\n", halaman_sekarang, list_name);
    }


    return total_item;
}

// Tampilan MUNDUR dengan paginasi (NOMOR LOKAL 1-N PER HALAMAN)
int tampilkanListPaperReverse(PaperNode* tail, const char* list_name, int halaman_sekarang, int item_per_halaman) {
    if (tail == NULL) {
        printf("   (List paper %s kosong atau tail belum di-set)\n", list_name);
        return 0;
    }
    
    PaperNode* temp_head_untuk_hitung = tail;
    if (temp_head_untuk_hitung != NULL) { 
        while(temp_head_untuk_hitung->prev != NULL) {
            temp_head_untuk_hitung = temp_head_untuk_hitung->prev;
        }
    }
    int total_item = hitungTotalItemDiList(temp_head_untuk_hitung);

    if (total_item == 0) {
        printf("   (List paper %s kosong)\n", list_name);
        return 0;
    }

    int start_index_0based_dari_depan_untuk_referensi_halaman = (halaman_sekarang - 1) * item_per_halaman;
    if (start_index_0based_dari_depan_untuk_referensi_halaman >= total_item) {
        printf("   (Halaman %d tidak valid. Total item: %d)\n", halaman_sekarang, total_item);
        return total_item;
    }
    
    PaperNode* current = tail;
    int i_skip = 0; 
    // Dari tail, kita skip sejumlah (halaman_sekarang - 1) * item_per_halaman 
    // untuk mencapai item TERAKHIR dari halaman yang ingin ditampilkan (jika diurutkan maju)
    // atau item PERTAMA jika diurutkan mundur dari tail untuk halaman tersebut
    int items_to_skip_from_tail = (halaman_sekarang - 1) * item_per_halaman;
    
    current = tail;
    i_skip = 0;
    while(current != NULL && i_skip < items_to_skip_from_tail) {
        current = current->prev;
        i_skip++;
    }
    
    int item_ditampilkan_di_halaman_ini = 0;
    int nomor_tampil_lokal = 1; // Nomor dimulai dari 1 untuk setiap halaman
    
    while (current != NULL && item_ditampilkan_di_halaman_ini < item_per_halaman) {
        printf("   %d.  Judul       : %s\n", nomor_tampil_lokal, current->data.judul);
        printf("       Tahun       : %d\n", current->data.tahun_terbit);
        printf("       Penulis     : %s\n", current->data.nama_penulis);
        printf("       InCitations : %d\n", current->data.jumlah_incitations);
        printf("      --------------------------------------------------\n");
        current = current->prev;
        item_ditampilkan_di_halaman_ini++;
        nomor_tampil_lokal++;
    }
    
    if (item_ditampilkan_di_halaman_ini == 0 && halaman_sekarang > 0 && total_item > 0) {
         printf("   (Tidak ada item lagi di halaman %d untuk list %s)\n", halaman_sekarang, list_name);
    }

    return total_item;
}

// Fungsi pilihJurnalDariList dan pilihJurnalDariListReverse sekarang menerima nomor_pilihan_DI_HALAMAN
// dan parameter paginasi untuk menghitung node yang benar.
PaperNode* pilihJurnalDariList(PaperNode* head, int nomor_pilihan_global) {
    if (nomor_pilihan_global <= 0 || head == NULL) return NULL;
    PaperNode* current = head;
    int i_global = 1; 
    while (current != NULL) {
        if (i_global == nomor_pilihan_global) {
            return current;
        }
        current = current->next;
        i_global++;
    }
    return NULL; 
}

PaperNode* pilihJurnalDariListReverse(PaperNode* tail, int nomor_pilihan_global_dari_depan) {
    // nomor_pilihan_global_dari_depan adalah nomor urut jika dihitung dari head.
    // Kita akan traverse dari tail.
    if (nomor_pilihan_global_dari_depan <= 0 || tail == NULL) return NULL;
    
    PaperNode* temp_head = tail;
    if (temp_head != NULL) { 
        while(temp_head->prev != NULL) {
            temp_head = temp_head->prev;
        }
    }
    int total_item = hitungTotalItemDiList(temp_head);
    if (nomor_pilihan_global_dari_depan > total_item) return NULL;

    // Item ke-X dari depan adalah item ke-(Total - X + 1) dari belakang (jika penomoran dari belakang 1-based)
    int target_hitungan_dari_belakang = total_item - nomor_pilihan_global_dari_depan + 1;

    PaperNode* current = tail;
    int i_dari_belakang = 1;
    while (current != NULL) {
        if (i_dari_belakang == target_hitungan_dari_belakang) {
            return current;
        }
        current = current->prev;
        i_dari_belakang++;
    }
    return NULL;
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
    if (tail_ptr != NULL) { 
        *tail_ptr = NULL;
    }
}