#ifndef _lcthw_Hashmap_h
#define _lcthw_Hashmap_h

#include <stdint.h>
#include <lcthw/DArray.h>

#define DEFAULT_NUMBER_OF_BUCKETS 100

// 用于比较键的函数指针类型
typedef int (*Hashmap_compare)(void *a, void *b);

// 用于对键进行哈希的函数指针类型
typedef uint32_t (*Hashmap_hash)(void *key);

// 表示哈希表数据结构
typedef struct Hashmap
{
    DArray *buckets;			// 用于存储键-值对的桶数组
    Hashmap_compare compare;	// 用于比较键的函数指针
    Hashmap_hash hash;			// 用于对键进行哈希的函数指针
} Hashmap;

// 表示哈希表中的节点
typedef struct HashmapNode
{
    void *key;       // 指向键的指针
    void *data;      // 指向关联数据的指针
    uint32_t hash;   // 键的哈希值
} HashmapNode;

// 用于遍历哈希表的函数指针类型
typedef int (*Hashmap_traverse_cb)(HashmapNode *node);

// 创建具有给定比较和哈希函数的新哈希表
Hashmap *Hashmap_create(Hashmap_compare compare, Hashmap_hash hash);

// 销毁给定的哈希表并释放其内存
void Hashmap_destroy(Hashmap *map);

// 在哈希表中设置键-值对
int Hashmap_set(Hashmap *map, void *key, void *data);

// 从哈希表中检索与给定键关联的数据
void *Hashmap_get(Hashmap *map, void *key);

// 遍历哈希表并对每个节点应用给定的回调函数
int Hashmap_traverse(Hashmap *map, Hashmap_traverse_cb traverse_cb);

// 从哈希表中删除与给定键关联的键-值对
void *Hashmap_delete(Hashmap *map, void *key);

#endif
