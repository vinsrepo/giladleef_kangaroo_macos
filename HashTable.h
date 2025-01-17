#ifndef HASHTABLEH
#define HASHTABLEH

#include <string>
#include <vector>
#include "SECPK1/Point.h"

#define HASH_SIZE_BIT 18
#define HASH_SIZE (1<<HASH_SIZE_BIT)
#define HASH_MASK (HASH_SIZE-1)

#define ADD_OK        0
#define ADD_DUPLICATE 1
#define ADD_COLLISION 2

union int256_s {
        uint8_t  i8[32];
        uint16_t i16[16];
        uint32_t i32[8];
        uint64_t i64[4];
};

typedef union int256_s int256_t;

#define safe_free(x) if(x) {free(x);x=NULL;}

typedef struct {

  int256_t  x;    // Position of kangaroo (256bit LSB)
  int256_t  d;    // Travelled distance (b255=sign b254=kangaroo type, b253..b0 distance

} ENTRY;

typedef struct {

  uint32_t   nbItem;
  uint32_t   maxItem;
  ENTRY    **items;

} HASH_ENTRY;

class HashTable {

public:

  HashTable();
  int Add(Int *x,Int *d,uint32_t type);
  int Add(uint64_t h,int256_t *x,int256_t *d);
  int Add(uint64_t h,ENTRY *e);
  uint64_t GetNbItem();
  void Reset();
  std::string GetSizeInfo();
  void PrintInfo();
  void SaveTable(FILE *f);
  void SaveTable(FILE* f,uint32_t from,uint32_t to,bool printPoint=true);
  void LoadTable(FILE *f);
  void LoadTable(FILE* f,uint32_t from,uint32_t to);
  void ReAllocate(uint64_t h,uint32_t add);
  void SeekNbItem(FILE* f,bool restorePos = false);
  void SeekNbItem(FILE* f,uint32_t from,uint32_t to);

  HASH_ENTRY    E[HASH_SIZE];
  // Collision info
  Int      kDist;
  uint32_t kType;

  static void Convert(Int *x,Int *d,uint32_t type,uint64_t *h,int256_t *X,int256_t *D);
  static int MergeH(uint32_t h,FILE* f1,FILE* f2,FILE* fd,uint32_t *nbDP,uint32_t* duplicate,
                    Int* d1,uint32_t* k1,Int* d2,uint32_t* k2);
  static void CalcDistAndType(int256_t d,Int* kDist,uint32_t* kType);

private:

  ENTRY *CreateEntry(int256_t *x,int256_t *d);
  static int compare(int256_t *i1,int256_t *i2);
  std::string GetStr(int256_t *i);

};

#endif // HASHTABLEH