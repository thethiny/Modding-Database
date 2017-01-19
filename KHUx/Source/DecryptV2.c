#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "zlib.h"
#include <sys/stat.h>

#define BGADMagic 0x44414742
#define BGADSize sizeof(struct BGAD)
#define BGADMaxNameLength 0x100
#define BGADMaxDataSize 0x1000000

#define false 0
#define true 1

#define CatchError(condition) if (condition) { return false; }
#define Read(ptr, size) CatchError(fread(ptr, size, 1, file) != 1)
/*Quick notes to any khux hacker out there.
 * misc.png contains one file, "/" which is the filelist for the big mp4-like
 * file. Since the name is not usable I called it @noname(@ is a standard to say
 * the name isn't the real one).
 * Also some names are really long and since those libs are still using windows
 * PATH_MAX limit(256 char) if the soft goes to crash you should just try in a
 * shorter path to the exe(ie C:\TEST\ would do it I guess)
 * No such issue reported on linux */
int khux_random(int seed) {
    return 0x19660D * seed + 0x3C6EF35F;
}

void khux_decrypt(int* data, int length, int key) {
    int count = (length + 3) >> 2, i;
    for (i=0; i<count; i++) {
        key = khux_random(key);
        data[i] ^= key;
    }
}

struct BGAD {
    int magic;
    short key_type;
    short unk;
    short header_size;
    short name_length;
    short data_type;
    short is_compressed;
    int data_size;
    int decompressed_size;
};

struct BGADInfo {
    struct BGAD header;
    void* name;
    void* data;
    void* decompressed;
};

typedef struct BGADInfo BGADInfo;

void BGADInfoInit(BGADInfo* info) {
    info->name = malloc(BGADMaxNameLength);
    info->data = malloc(BGADMaxDataSize);
    info->decompressed = malloc(BGADMaxDataSize);
}

void BGADDecryptName(BGADInfo* info) {
    khux_decrypt(info->name, info->header.name_length, info->header.data_size);

    ((char*)info->name)[info->header.name_length] = 0;
}

void BGADDecryptData(BGADInfo* info) {
    khux_decrypt(info->data, info->header.data_size, info->header.name_length);

    if (info->header.is_compressed) {
        unsigned long int size = info->header.decompressed_size;
        uncompress(info->decompressed, &size, info->data, info->header.data_size);
    }
}

int ReadBGAD(FILE* file, BGADInfo* info) {
    Read(&info->header, BGADSize)

    CatchError(info->header.magic != BGADMagic)
    CatchError(info->header.name_length > BGADMaxNameLength)

    Read(info->name, info->header.name_length)
    BGADDecryptName(info);

    CatchError(info->header.data_size > BGADMaxDataSize)
    CatchError(info->header.decompressed_size > BGADMaxDataSize)

    Read(info->data, info->header.data_size)
    BGADDecryptData(info);
    return true;
}

void WriteBGAD(FILE* file, BGADInfo* info) {
    void* ptr = info->header.is_compressed
        ? info->decompressed
        : info->data;

    int size  = info->header.is_compressed
        ? info->header.decompressed_size
        : info->header.data_size;

    fwrite(ptr, size, 1, file);
}

void CreateDirectories(char** base, char* directories) {
    char* directory = strtok(directories, "/");
    char* next_directory;
#ifdef _WIN32
    mkdir(*base);
#else
    mkdir(*base, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
    while (directory != NULL) {
        next_directory = strtok(NULL, "/");

        strncat(*base, "/", 1);
        strncat(*base, directory, strlen(directory));

        if (next_directory != NULL) {
#ifdef _WIN32
             mkdir(*base);
#else
             mkdir(*base, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

        }

        directory = next_directory;
    }
}

int main(int argc, const char * argv[]) {
    if(argc<3)//Can't you make smthg clean at least?
    {
        printf("Usage: khuxdecrypt file folder_out\n");
        return 0;
    }
    setbuf(stdout, NULL);
    int ctr = 1;

    char* in_path = (char*)argv[1];
    char* out_path = (char*)argv[2];
    unsigned long out_path_len = strlen(out_path);
    int index = 1;
    FILE* file = fopen(in_path, "rb");/* If you try to make portable code then
                                         please do open files in binary mode*/
    BGADInfo* info = malloc(sizeof(BGADInfo));
    BGADInfoInit(info);
    char* write_path = malloc(0x100);

    while (ReadBGAD(file, info)) {
        printf("Name: %s\n", info->name);
        //This is a quick and dirty fix, don't wait for something miraculous
        if(strcmp((char *)info->name, "/")==0)/* / is an invalid char for a
                                               * filename on all oses */
        {
            char *noname = malloc(0x100);/*Write path is limited at 0x100
                                           so will follow the exemple*/
            memset(noname, 0, 0x100);
            strcat(noname, "@noname");
            char indexfile[32];
            sprintf(indexfile, "%d", index);
            strcat(noname, indexfile);
            strcat(noname, ".bin");
            index++;
            info->name = noname;
        }
        ///The code for renaming files goes here
            char *newname = malloc(0x100);
            memset(newname, 0, 0x100);
            strcat(newname, "File_");
            char ctrfile[32];
            sprintf(ctrfile, "%d", ctr);
            strcat(newname, ctrfile);
            strcat(newname, ".out");
            ctr++;
            info->name = newname;

        memset(write_path, 0, 0x100);
        strncat(write_path, out_path, out_path_len);

        CreateDirectories(&write_path, info->name);
        FILE* out_file = fopen(write_path, "wb");/*Same here, binary man...
                                                   You should read some doc one
                                                   day*/
        CatchError(out_file == NULL)
        WriteBGAD(out_file, info);
        fclose(out_file);
    }

    fclose(file);

    return 0;
}
