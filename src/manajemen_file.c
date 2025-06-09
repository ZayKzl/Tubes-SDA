#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // For strcasecmp
#include "../include/manajemen_file.h"   // Deklarasi fungsi dan include "structs.h"
#include "../include/bst_field_study.h"  // Untuk memanggil bangunBSTSeimbang dan tambahkanJurnalKeBST
#include "../cJSON/cJSON.h"            // Library untuk parsing JSON

// Struktur untuk menyimpan semua jurnal yang dibaca sementara
typedef struct {
    JurnalData* data_array;
    int count;
    int capacity;
} JurnalDataCollection;

// Helper untuk menambahkan JurnalData ke koleksi
void addJurnalToCollection(JurnalDataCollection* collection, JurnalData data) {
    if (collection->count == collection->capacity) {
        collection->capacity = (collection->capacity == 0) ? 100 : collection->capacity * 2;
        JurnalData* new_array = realloc(collection->data_array, collection->capacity * sizeof(JurnalData));
        if (new_array == NULL) {
            perror("Gagal alokasi ulang memori untuk JurnalDataCollection");
            exit(EXIT_FAILURE); // Keluar jika alokasi gagal
        }
        collection->data_array = new_array;
    }
    collection->data_array[collection->count++] = data;
}

// Fungsi perbandingan untuk qsort (case-insensitive)
int compareStringsIgnoreCase(const void *a, const void *b) {
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    return strcasecmp(s1, s2);
}

// --- Fungsi untuk Memuat Data Jurnal dari File JSON (DIUBAH) ---
int muatDataDariMasterFile(const char* nama_file_json, BSTNodeField** root_bst_ptr) {
    char* json_string_buffer = NULL;
    FILE* file_json = NULL;
    long file_length = 0;
    size_t read_length = 0;
    cJSON* json_root = NULL;
    int berhasil = 0; // 0 untuk gagal, 1 untuk berhasil

    file_json = fopen(nama_file_json, "rb");
    if (file_json == NULL) {
        perror("Gagal membuka master file JSON");
        *root_bst_ptr = NULL;
        return 0;
    }

    fseek(file_json, 0, SEEK_END);
    file_length = ftell(file_json);
    if (file_length <= 0) {
        fprintf(stderr, "File JSON kosong atau error saat membaca ukuran file.\n");
        fclose(file_json);
        *root_bst_ptr = NULL;
        return 0;
    }
    fseek(file_json, 0, SEEK_SET);

    json_string_buffer = (char*)malloc(file_length + 1);
    if (json_string_buffer == NULL) {
        perror("Gagal alokasi memori untuk buffer JSON");
        fclose(file_json);
        *root_bst_ptr = NULL;
        return 0;
    }

    read_length = fread(json_string_buffer, 1, file_length, file_json);
    fclose(file_json);

    if (read_length != (size_t)file_length) {
        perror("Gagal membaca seluruh isi file JSON");
        free(json_string_buffer);
        *root_bst_ptr = NULL;
        return 0;
    }
    json_string_buffer[file_length] = '\0';

    json_root = cJSON_Parse(json_string_buffer);
    if (json_root == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error parsing JSON sebelum: %s\n", error_ptr);
        } else {
            fprintf(stderr, "Error parsing JSON: Struktur JSON tidak valid atau memori habis.\n");
        }
        free(json_string_buffer);
        *root_bst_ptr = NULL;
        return 0;
    }

    if (!cJSON_IsArray(json_root)) {
        fprintf(stderr, "Error: Root JSON bukan sebuah array.\n");
        cJSON_Delete(json_root);
        free(json_string_buffer);
        *root_bst_ptr = NULL;
        return 0;
    }

    JurnalDataCollection all_journals = { .data_array = NULL, .count = 0, .capacity = 0 };
    cJSON* jurnal_json_obj = NULL;

    // FASE 1: Membaca semua data jurnal ke koleksi sementara
    cJSON_ArrayForEach(jurnal_json_obj, json_root) {
        if (!cJSON_IsObject(jurnal_json_obj)) {
            fprintf(stderr, "Peringatan: Item dalam array JSON bukan objek, dilewati.\n");
            continue;
        }
        
        JurnalData temp_jurnal = {0}; 
        cJSON* item_json_current;

        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "id_paper");
        if (cJSON_IsString(item_json_current) && (item_json_current->valuestring != NULL)) {
            strncpy(temp_jurnal.id_paper, item_json_current->valuestring, MAX_ID_PAPER - 1);
            temp_jurnal.id_paper[MAX_ID_PAPER - 1] = '\0'; 
        }

        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "judul");
        if (cJSON_IsString(item_json_current) && (item_json_current->valuestring != NULL)) {
            strncpy(temp_jurnal.judul, item_json_current->valuestring, MAX_JUDUL - 1);
            temp_jurnal.judul[MAX_JUDUL - 1] = '\0';
        }
        
        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "tahun_terbit");
        if (cJSON_IsNumber(item_json_current)) {
            temp_jurnal.tahun_terbit = item_json_current->valueint;
        }

        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "abstrak");
        if (cJSON_IsString(item_json_current) && (item_json_current->valuestring != NULL)) {
            strncpy(temp_jurnal.abstrak, item_json_current->valuestring, MAX_ABSTRAK - 1);
            temp_jurnal.abstrak[MAX_ABSTRAK - 1] = '\0';
        }

        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "penulis");
        if (cJSON_IsString(item_json_current) && (item_json_current->valuestring != NULL)) {
            strncpy(temp_jurnal.nama_penulis, item_json_current->valuestring, MAX_PENULIS - 1);
            temp_jurnal.nama_penulis[MAX_PENULIS - 1] = '\0';
        }
        
        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "jumlah_incitations");
        if (cJSON_IsNumber(item_json_current)) {
            temp_jurnal.jumlah_incitations = item_json_current->valueint;
        }
        
        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "field_of_study");
        if (cJSON_IsString(item_json_current) && (item_json_current->valuestring != NULL)) {
            strncpy(temp_jurnal.field_of_study, item_json_current->valuestring, MAX_FIELD_STUDY - 1);
            temp_jurnal.field_of_study[MAX_FIELD_STUDY - 1] = '\0';
        }
        
        addJurnalToCollection(&all_journals, temp_jurnal);
    }
    
    cJSON_Delete(json_root); // JSON parse tree sudah tidak diperlukan
    free(json_string_buffer); // Buffer JSON juga sudah tidak diperlukan

    // FASE 2: Ekstraksi field_of_study unik dan pengurutan
    char** unique_field_strings = NULL;
    int current_unique_count = 0;
    int max_unique_capacity = 0; 

    if (all_journals.count > 0) {
        max_unique_capacity = all_journals.count; // Maksimum jumlah unik adalah jumlah total jurnal
        unique_field_strings = (char**)malloc(max_unique_capacity * sizeof(char*));
        if (unique_field_strings == NULL) {
            perror("Gagal alokasi memori untuk array string unik");
            free(all_journals.data_array);
            *root_bst_ptr = NULL;
            return 0;
        }

        // Untuk efisiensi, gunakan strategi: alokasikan semua string lalu urutkan, lalu salin uniknya
        char** temp_all_field_pointers = (char**)malloc(all_journals.count * sizeof(char*));
        if (temp_all_field_pointers == NULL) {
             perror("Gagal alokasi memori untuk temporary field pointers");
             free(all_journals.data_array);
             free(unique_field_strings);
             *root_bst_ptr = NULL;
             return 0;
        }
        for (int i = 0; i < all_journals.count; i++) {
            temp_all_field_pointers[i] = strdup(all_journals.data_array[i].field_of_study);
            if (temp_all_field_pointers[i] == NULL) { /* handle error */ }
        }

        qsort(temp_all_field_pointers, all_journals.count, sizeof(char*), compareStringsIgnoreCase);

        // Salin string unik (dan membebaskan duplikat)
        if (all_journals.count > 0) {
            unique_field_strings[current_unique_count++] = temp_all_field_pointers[0]; // Ambil yang pertama
            for (int i = 1; i < all_journals.count; i++) {
                if (strcasecmp(temp_all_field_pointers[i], unique_field_strings[current_unique_count - 1]) != 0) {
                    unique_field_strings[current_unique_count++] = temp_all_field_pointers[i]; // Salin pointer ke yang unik
                } else {
                    free(temp_all_field_pointers[i]); // Bebaskan duplikat
                }
            }
        }
        free(temp_all_field_pointers); // Array pointer itu sendiri
    }
    
    // FASE 3: Membangun BST seimbang
    *root_bst_ptr = bangunBSTSeimbang(unique_field_strings, 0, current_unique_count - 1);
    if (*root_bst_ptr == NULL) {
        fprintf(stderr, "Error: Gagal membangun BST seimbang. Mungkin ada masalah alokasi memori.\n");
        // Pastikan semua memori dibebaskan
        for (int i = 0; i < current_unique_count; i++) {
            free(unique_field_strings[i]);
        }
        free(unique_field_strings);
        free(all_journals.data_array);
        return 0;
    }

    // FASE 4: Mengisi DLL pada node BST yang sudah terbentuk
    for (int i = 0; i < all_journals.count; i++) {
        // tambahkanJurnalKeBST sekarang akan mencari node yang sudah ada dan menambahkan ke DLL-nya.
        tambahkanJurnalKeBST(root_bst_ptr, all_journals.data_array[i]);
    }

    printf("Berhasil memuat %d data jurnal dari file JSON '%s' dan membangun BST seimbang.\n", all_journals.count, nama_file_json);
    berhasil = 1;

    // Bersihkan memori dari string unik (yang tidak menjadi bagian dari tree)
    for (int i = 0; i < current_unique_count; i++) {
        free(unique_field_strings[i]);
    }
    free(unique_field_strings);
    free(all_journals.data_array); // Bebaskan array koleksi jurnal

    return berhasil;
}