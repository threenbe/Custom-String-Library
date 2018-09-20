/*
 * Replace this comment with the standard EE312 file header!
 */

#include <assert.h>
#include <string.h>
/*#include "MemHeap.h"*/ /*Removed: Michael Bartling: 06/21/2016*/
#include <stdlib.h>
#include "String.h"

/* use these two macros and the function functions if you want -- not required */
#define SIGNATURE (~0xdeadbeef)

/** STRING(s)
 * Helper macro for accessing ut String object (if applicable)
 * [INPUT] pointer to cstring
 * [OUTPUT] pointer to UT String object (if applicable)
 */
#define STRING(s) ((String*)(s - 3*sizeof(uint32_t)))

/* this simple function can be useful when you implement stage 4
 * you are not required to use the function, and you can implement stage 4 without it */
int32_t isOurs(char* s) {
    /*if (!isHeapVar(s)) { return 0; }*//*Removed: Michael Bartling: 06/21/2016*/
    if (STRING(s)->check == SIGNATURE) { return 1; }
    else { return 0; }
}

/************************************utstrdup**************************************************
 * allocate a utstring on the heap, initialize the string correctly by copying
 * the characters from 'src' and return a pointer to the first character of actual string data 
 * meta-data is filled in as follows: check gets ~0xdeadbeef, capacity and length both get length
 * of the input string
 * [INPUT] pointer to string
 * [OUTPUT] pointer to duplicated utstring
 */
char* utstrdup(const char* src) {
    uint32_t i, len=0;
    for(i=0;src[i] != 0;i++){//find length of 'src'
        len++;
    }

    //allocate enough for struct+string length+zero at the end
    String* utsrc = (String*) malloc(sizeof(String)+len+1);

    for(i=0;src[i] != 0;i++){//duplicate string
        utsrc->data[i] = src[i];
    }
    utsrc->data[i] = 0;//add null char at end
    utsrc->length = len;
    utsrc->capacity = len;
    utsrc->check = SIGNATURE;

    return (char*)(utsrc->data);
}

/*************************************utstrlen**************************************************
 * Find the length of this string by accessing the meta-data
 * and return that length
 * [INPUT] pointer to utstring
 * [OUTPUT] length of said utstring
 */
uint32_t utstrlen(const char* utstr) {
    uint32_t* lenpt = (uint32_t*) utstr;
    assert(*(lenpt-3) == SIGNATURE);//check if input is a utstring

    return *(lenpt-1);
}

/**************************************utstrcat**************************************************
 * append the characters from suffix to the string s. Do not allocate any additional storage, and
 * only append as many characters as will actually fit in s. Update the length meta-data for utstring s
 * and then return s 
 * [INPUTS] pointer to utstring, pointer to suffix string (of any type)
 * [OUTPUTS] the first string (for no real reason), might as well be nothing
 */
char* utstrcat(char* s, const char* suffix) {
    uint32_t* spt = (uint32_t*) s;
    assert(*(spt-3) == SIGNATURE);
    uint32_t cap = *(spt-2);
    uint32_t len = *(spt-1);//length prior to appending chars
    cap -= len;//remaining capacity to append characters from suffix
    uint32_t newlen = len;
    uint32_t i;

    //appends chars in suffix to s and records new length
    for(i=0;suffix[i] != 0 && i < cap ;i++){
        s[i+len] = suffix[i];
        newlen++;
    }
    s[i+len] = 0;//null char termination
    *(spt-1) = newlen;

    return s;
}

/**************************************utstrcpy**************************************************
 * overwrite the characters in dst with the characters from src. Do not overflow the capacity of dst
 * For example, if src has five characters and dst has capacity for 10, then copy all five characters
 * However, if src has ten characters and dst only has capacity for 8, then copy only the first 8
 * characters. Do not allocate any additional storage, do not change capacity. Update the length
 * meta-data for dst and then return dst 
 * [INPUTS] a utstring (dst) and a source string from which characters are copied (src)
 * [OUTPUTS] the utstring that was overwritten (useless output)
 */
char* utstrcpy(char* dst, const char* src) {
    uint32_t* dstpt = (uint32_t*) dst;
    assert(*(dstpt-3) == SIGNATURE);
    uint32_t cap = *(dstpt-2);
    uint32_t len = 0;
    uint32_t i;

    //copies src to dst and records new length
    for(i=0;i < cap && src[i] != 0;i++){
        dst[i] = src[i];
        len++;
    }
    dst[i] = 0;
    *(dstpt-1) = len;

    return dst;
}

/**************************************utstrfree**************************************************
 * locate the start of the chunk and call free to dispose of the chunk, note that the start of
 * the chunk will be 12 bytes before *self
 * [INPUTS] pointer to utstring chunk on heap that is to be freed
 * [OUTPUTS] none
 */
void utstrfree(char* self) {
    uint32_t* selfpt = (uint32_t*) self;
    assert(*(selfpt-3) == SIGNATURE);
    free(selfpt-3);
}

/***************************************utstrrealloc**************************************************
 * ensure that s has capacity at least as large as 'new_capacity'
 * if s already has capacity equal to or larger than new_capacity, then return s
 * if s has less capacity than new_capacity, then allocate new storage with sufficient space to store
 * new_capacity characters (plus a terminating zero), copy the current characters from s into this
 * new storage. Update the meta-data to correctly describe new new utstring you've created, deallocate s
 * and then return a pointer to the first character in the newly allocated storage 
 * [INPUT] utstring pointer and new capacity of said utstring
 * [OUTPUT] pointer to newly allocated string space if reallocation occurred, otherwise original pointer
 */
char* utstrrealloc(char* s, uint32_t new_capacity) {
    uint32_t* cappt = (uint32_t*) s;
    assert(*(cappt-3) == SIGNATURE);
    cappt -= 2;

    //check if capacity needs to be enlarged or not
    if(*cappt >= new_capacity){
        return s;
    }
    else{
        String* uts = (String*) malloc(sizeof(String)+new_capacity+1);
        uts->check = SIGNATURE;
        uts->capacity = new_capacity;
        uts->length = *(cappt+1);//length is right after capacity in String struct
        uint32_t i;
        for(i=0; s[i] != 0; i++){//copies old string into new
            uts->data[i] = s[i];
        }
        uts->data[i] = 0;
        free(cappt-1);
        return (char*)(uts->data);
    }
}



