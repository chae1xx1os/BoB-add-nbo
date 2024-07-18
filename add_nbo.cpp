#include <stdio.h>
#include <stdint.h>

uint32_t my_convert(uint32_t x) {
    uint32_t result = (x & 0xff)<<24;
    result |= ((x>>8)&0xff)<<16;
    result |= ((x>>16)&0xff)<<8;
    result |= (x>>24);
    return result;
}

int main(int argc, char **argv) {
    FILE *fp1, *fp2;
    uint32_t num1, num2;

    if(argc < 3) {
        printf("add-nbo <file1> <file2>\n");
        return -1;
    }

    fp1 = fopen(argv[1], "rb");    
    fp2 = fopen(argv[2], "rb");

    if(!fp1 || !fp2) {
        perror("fopen");
        return -1;
    }

    if(fread(&num1, sizeof(num1), 1, fp1) != 1 || fread(&num2, sizeof(num2), 1, fp2) != 1) {
        perror("fread");
        return -1;
    }

    num1 = my_convert(num1);
    num2 = my_convert(num2);
    
    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, num1+num2, num1+num2);

    fclose(fp1);
    fclose(fp2);

    return 0;
}
