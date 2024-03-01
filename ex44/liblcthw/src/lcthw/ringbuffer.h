#ifndef _lcthw_RingBuffer_h
#define _lcthw_RingBuffer_h

#include <lcthw/bstrlib.h>

// 定义环形缓冲区的结构体
typedef struct
{
    char *buffer;  // 缓冲区指针
    int length;    // 缓冲区长度
    int start;     // 缓冲区中的起始位置
    int end;       // 缓冲区中的结束位置
} RingBuffer;

// 创建一个指定长度的环形缓冲区
RingBuffer *RingBuffer_create(int length);

// 销毁环形缓冲区
void RingBuffer_destroy(RingBuffer *buffer);

// 从环形缓冲区中读取数据到目标数组中
int RingBuffer_read(RingBuffer *buffer, char *target, int amount);

// 向环形缓冲区中写入数据
int RingBuffer_write(RingBuffer *buffer, char *data, int length);

// 检查环形缓冲区是否为空
int RingBuffer_empty(RingBuffer *buffer);

// 检查环形缓冲区是否已满
int RingBuffer_full(RingBuffer *buffer);

// 获取环形缓冲区中可用的数据量
int RingBuffer_available_data(RingBuffer *buffer);

// 获取环形缓冲区中可用的空间大小
int RingBuffer_available_space(RingBuffer *buffer);

// 从环形缓冲区中读取指定长度的数据到bstring中
bstring RingBuffer_gets(RingBuffer *buffer, int amount);

// 获取环形缓冲区中可用的数据量
#define RingBuffer_available_data(B) (((B)->end + 1) % (B)->length - (B)->start - 1)

// 获取环形缓冲区中可用的空间大小
#define RingBuffer_available_space(B) ((B)->length - (B)->end - 1)

// 检查环形缓冲区是否已满
#define RingBuffer_full(B) (RingBuffer_available_data((B)) - (B)->length == 0)

// 检查环形缓冲区是否为空
#define RingBuffer_empty(B) (RingBuffer_available_data((B)) == 0)

// 向环形缓冲区中写入bstring数据
#define RingBuffer_puts(B, D) RingBuffer_write((B), bdata((D)), blength((D)))

// 获取环形缓冲区中所有可用的数据到bstring中
#define RingBuffer_get_all(B) RingBuffer_gets((B), RingBuffer_available_data((B)))

// 获取环形缓冲区中的起始位置指针
#define RingBuffer_starts_at(B) ((B)->buffer + (B)->start)

// 获取环形缓冲区中的结束位置指针
#define RingBuffer_ends_at(B) ((B)->buffer + (B)->end)

// 移动环形缓冲区的读取位置
#define RingBuffer_commit_read(B, A) ((B)->start = ((B)->start + (A)) % (B)->length)

// 移动环形缓冲区的写入位置
#define RingBuffer_commit_write(B, A) ((B)->end = ((B)->end + (A)) % (B)->length)

#endif
