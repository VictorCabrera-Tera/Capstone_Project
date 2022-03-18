typedef char s8;
typedef unsigned char u8;


typedef short s16;
typedef unsigned short u16;

typedef int s32;
typedef unsigned int u32;


typedef long long s64;
typedef unsigned long long u64;

#define global_variable static
#define internal static


inline int 
clamp(int min, int max, int value) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}