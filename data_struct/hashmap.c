#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHMAP_SIZE 100

struct entry {
    char *key;
    char *value;
    struct entry *next;
}

struct hash_map {
    int size;
    struct entry **table;
}

/* Given key get a hashmap for it */
int get_hash(char *key, struct hash_map *hash_map)
{
    int hash = 0;
    long magic= 3456789734;
    long temp_hash = 0;
 
    temp_hash = magic * strlen(key);
    temp_hash = temp_hash % hash_map->size;
    hash = temp_hash;
    return hash;
}

struct hash_map *init_hashmap(int size)
{
    struct hash_map *hash_map = NULL;

    hash_map = calloc(1, sizeof(struct hash_map))    
    if(hash_map == NULL) {
        goto error;
    }

    hash_map->table = calloc(size, sizeof(struct entry));
    if(hash_map->table == NULL) {
        free(hash_map);
        goto error;
    }

error:
    return hash_map;
}

void entries_dump(struct entry *entry)
{
    struct entry *iter = entry;
    while(iter) {
        printf("Key: %s Value:%s \n", entry->key, entry->value);
        iter = iter->next; 
    }
    return;
}

void hashmap_dump(struct hash_map *hash_map)
{
    struct entry *next = NULL;
    int iter = 0;
    if(hash_map == NULL) return;

    for(iter = 0; iter < hash_map->size ; iter++) {
        if(hash_map->table[iter] != NULL) {
	    entries_dump(hash_map->table[iter]); 
        }
    }
    return;
}

struct entry* new_entry(char *key, char *value)
{
    struct entry *new = NULL;

    new = calloc(1, sizeof(struct entry));
    if(new == NULL) {
        goto error;
    }

    new->key = strdup(key);
    new->value =strdup(value);
    
    if((new->key == NULL) || (new->value == NULL)) {
        goto error;
    }

goto cleanup:
    return new;

error:
    if(new && new->key) free(new->key);
    if(new && new->value) free(new->value);
    if(new) free(new);
    goto cleanup;
}

void delete_entry(struct entry *entry)
{
    if(entry) {
        if(entry->key)free(entry->key);
        if(entry->value)free(entry->value);
        free(entry);
    }
    return;
}

/* The entry is updated to the requested entry if found and prev */
int entry_exist(struct entry *entry, struct entry *prev, char *key, char *value)
{
    int valid_entry = 0;
    struct entry *temp = entry;

    while(temp) {
        if((strcmp(key, temp->key) == 0) && (strcmp(value, temp->value) == 0)){
             valid_entry = 1;
             break;
        }
        prev = temp;
        temp = temp->next;
    }
    entry = temp;
    return valid_entry;
}

int hashmap_insert(char *key, char *value, struct hash_map *hash_map)
{
    struct entry *entry = NULL;
    struct entry *new = NULL;
    int ret = 0;
    int hash = 0;

    hash = get_hash(key);

    entry = hash_map->table[hash];
    if(entry_exist(entry, key, value)) {
        return EEXIST;
    }

    while(entry) {
        entry = entry->next;
    }

    entry =  new_entry(key, value);
    if(entry == NULL) {
        return ENOMEM;
    }

    return 0;
}

int hashmap_delete(char *key, char *value, struct hash_map *hash_map)
{
    struct entry *entry = NULL;
    struct entry *prev = NULL;
    int ret = 0;
    int hash = 0;

    hash = get_hash(key);
    entry = hash_map->table[hash];
    if(entry_exist(entry ,prev ,key, value)) {
	prev->next = entry->next;
        delete_entry(entry);
    } else {
        ret = EINVAL
    }

    return ret;
}

/* Return number fo entries for the same key diff value */
int hashmap_search(char *value, char *key)
{
     struct entry *entry = NULL;
     int count = 0;

     entry = 

    return count;
}
