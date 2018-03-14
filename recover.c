#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

typedef uint8_t  BYTE;
int main(int argc,char* argv[])
{
    BYTE byte[512];
    char str[8];
    int num=0,c;
    if(argc!=2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    char* image=argv[1];
    FILE* file=fopen(image,"r");
    if(file==NULL)
    {
        fprintf(stderr, "Could not open %s.\n", image);
        return 2;
    }
    FILE *fp=NULL;
    while(!feof(file))
    {
        c=fread(&byte,sizeof(byte),1,file);
        if(byte[0]==0xff && byte[1]==0xd8 && byte[2]==0xff && byte[3]>=0xe0 && byte[3]<=0xef)
        {
            sprintf(str,"%.3d.jpg",num);
            if(num>0)
            fclose(fp);
            fp=fopen(str,"w");
            fwrite(&byte,sizeof(byte),1,fp);
            num++;
        }
        else if(num==0)
        continue;
        else if(c==1)
        fwrite(&byte,sizeof(byte),1,fp);
    }
    fclose(file);
    return 0;
}
