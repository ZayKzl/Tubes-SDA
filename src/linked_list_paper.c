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

int hitungTotalItemDiList(PaperNode* head) {
    int count = 0;
    PaperNode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Tampilan MAJU dengan paginasi
int tampilkanListPaper(PaperNode* head, const char* list_name, int halaman_sekarang, int item_per_halaman, int* nomor_urut_awal_di_halaman_ptr) {
    if (nomor_urut_awal_di_halaman_ptr != NULL) {
        *nomor_urut_awal_di_halaman_ptr = 0; // Default jika list kosong atau halaman tidak valid
    }
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
        // printf("   (Halaman %d tidak valid untuk list %s. Total item: %d)\n", halaman_sekarang, list_name, total_item);
        // Tidak perlu print error di sini, biarkan pemanggil yang handle jika total_item_di_halaman_ini 0
        if (nomor_urut_awal_di_halaman_ptr != NULL) {
             *nomor_urut_awal_di_halaman_ptr = (total_item > 0 && start_index_0based == 0) ? 1 : 0;
        }
        return total_item;
    }

    if (nomor_urut_awal_di_halaman_ptr != NULL) {
        *nomor_urut_awal_di_halaman_ptr = start_index_0based + 1;
    }

    PaperNode* current = head;
    int i_skip = 0; 
    int nomor_tampil_relatif_di_halaman = 1; 

    while (current != NULL && i_skip < start_index_0based) {
        current = current->next;
        i_skip++;
    }

    int item_ditampilkan_di_halaman_ini = 0;
    while (current != NULL && item_ditampilkan_di_halaman_ini < item_per_halaman) {
        // Menampilkan nomor urut GLOBAL di sisi kiri
        printf("   %d. Judul    : %s\n", (start_index_0based + nomor_tampil_relatif_di_halaman), current->data.judul);
        printf("      Tahun    : %d\n", current->data.tahun_terbit);
        printf("      Penulis  : %s\n", current->data.nama_penulis);
        printf("      InCitations: %d\n", current->data.jumlah_incitations);
        printf("      --------------------------------------------------\n");
        current = current->next;
        item_ditampilkan_di_halaman_ini++;
        nomor_tampil_relatif_di_halaman++;
    }
    
    if (item_ditampilkan_di_halaman_ini == 0 && start_index_0based < total_item) {
         // Ini bisa terjadi jika halaman yang diminta valid tapi tidak ada item lagi (misal halaman terakhir sebagian)
         // Atau jika memang tidak ada item sama sekali
    }
    return total_item;
}

// Tampilan MUNDUR dengan paginasi
int tampilkanListPaperReverse(PaperNode* tail, const char* list_name, int halaman_sekarang, int item_per_halaman, int* nomor_urut_awal_di_halaman_ptr) {
    if (nomor_urut_awal_di_halaman_ptr != NULL) {
        *nomor_urut_awal_di_halaman_ptr = 0;
    }
    if (tail == NULL) {
        printf("   (List paper %s kosong atau tail belum di-set)\n", list_name);
        return 0;
    }
    
    PaperNode* temp_head = tail; // Cari head untuk menghitung total item
    if (temp_head != NULL) {
        while(temp_head->prev != NULL) {
            temp_head = temp_head->prev;
        }
    }
    int total_item = hitungTotalItemDiList(temp_head);

    if (total_item == 0) {
        printf("   (List paper %s kosong)\n", list_name);
        return 0;
    }

    // Item dihitung dari depan (0 hingga total_item-1) untuk konsistensi penomoran global
    int start_index_0based_dari_depan = (halaman_sekarang - 1) * item_per_halaman;

    if (start_index_0based_dari_depan >= total_item) {
        // printf("   (Halaman %d tidak valid. Total item: %d)\n", halaman_sekarang, total_item);
        if (nomor_urut_awal_di_halaman_ptr != NULL) {
            *nomor_urut_awal_di_halaman_ptr = (total_item > 0 && start_index_0based_dari_depan == 0) ? 1 : 0;
        }
        return total_item;
    }
    
    if (nomor_urut_awal_di_halaman_ptr != NULL) {
        *nomor_urut_awal_di_halaman_ptr = start_index_0based_dari_depan + 1;
    }

    PaperNode* current = tail;
    int i_skip = 0; 
    // Dari tail, kita skip sejumlah (halaman_sekarang - 1) * item_per_halaman untuk mencapai
    // item TERAKHIR dari halaman yang ingin ditampilkan (jika dihitung dari belakang).
    int items_to_skip_from_tail_to_reach_last_of_page = (halaman_sekarang - 1) * item_per_halaman;
    
    current = tail;
    i_skip = 0;
    while(current != NULL && i_skip < items_to_skip_from_tail_to_reach_last_of_page) {
        current = current->prev;
        i_skip++;
    }
    
    int item_ditampilkan_di_halaman_ini = 0;
    // Nomor global dihitung mundur dari (total_item - items_to_skip_from_tail_to_reach_last_of_page)
    int nomor_global_saat_ini = total_item - items_to_skip_from_tail_to_reach_last_of_page;

    while (current != NULL && item_ditampilkan_di_halaman_ini < item_per_halaman) {
        printf("   %d. Judul    : %s\n", nomor_global_saat_ini, current->data.judul);
        printf("      Tahun    : %d\n", current->data.tahun_terbit);
        printf("      Penulis  : %s\n", current->data.nama_penulis);
        printf("      InCitations: %d\n", current->data.jumlah_incitations);
        // ... (print field lain) ...
        printf("      --------------------------------------------------\n");
        current = current->prev;
        item_ditampilkan_di_halaman_ini++;
        nomor_global_saat_ini--;
    }
    return total_item;
}

// Fungsi pilihJurnalDariList dan pilihJurnalDariListReverse sekarang diimplementasikan di sini
// dan menerima nomor_pilihan_di_halaman
PaperNode* pilihJurnalDariList(PaperNode* head, int nomor_pilihan_di_halaman, int halaman_sekarang, int item_per_halaman) {
    if (nomor_pilihan_di_halaman <= 0 || head == NULL || halaman_sekarang <= 0 || item_per_halaman <= 0) {
        return NULL;
    }
    // Hitung nomor urut global absolut dari item yang dipilih
    int nomor_pilihan_global = ((halaman_sekarang - 1) * item_per_halaman) + nomor_pilihan_di_halaman;

    PaperNode* current = head;
    int i_global = 1; // Indeks global 1-based
    while (current != NULL) {
        if (i_global == nomor_pilihan_global) {
            return current;
        }
        current = current->next;
        i_global++;
    }
    return NULL; 
}

PaperNode* pilihJurnalDariListReverse(PaperNode* tail, int nomor_pilihan_di_halaman, int halaman_sekarang, int item_per_halaman) {
    if (nomor_pilihan_di_halaman <= 0 || tail == NULL || halaman_sekarang <= 0 || item_per_halaman <= 0) {
        return NULL;
    }
    // Hitung nomor urut global absolut dari item yang dipilih (dihitung dari DEPAN/HEAD)
    int nomor_pilihan_global_dari_depan = ((halaman_sekarang - 1) * item_per_halaman) + nomor_pilihan_di_halaman;

    PaperNode* temp_head = tail; // Cari head untuk menghitung total item
    if (temp_head != NULL) {
        while(temp_head->prev != NULL) {
            temp_head = temp_head->prev;
        }
    }
    int total_item = hitungTotalItemDiList(temp_head);
    if (nomor_pilihan_global_dari_depan > total_item || nomor_pilihan_global_dari_depan <= 0) return NULL;

    // Item ke-X dari depan adalah item ke-(Total - X + 1) dari belakang (jika penomoran dari belakang juga 1-based)
    // Atau, kita bisa langsung iterasi dari tail dan hitung sampai nomor global yang sesuai dari belakang.
    // Nomor global yang ditampilkan di layar saat reverse adalah (total_item - i_skip_from_tail), dst.
    // Jadi, jika pengguna memilih nomor global X, kita cari saja dari tail.

    PaperNode* current = tail;
    int i_hitung_mundur_global = total_item; // Nomor global item terakhir (tail)
    while (current != NULL) {
        if (i_hitung_mundur_global == nomor_pilihan_global_dari_depan) {
            return current;
        }
        current = current->prev;
        i_hitung_mundur_global--;
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
    *tail_ptr = NULL; // Juga reset tail
}