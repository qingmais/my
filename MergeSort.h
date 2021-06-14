#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <vector>
using namespace std;
class MergeSort{
public:
    void sort(){
        int file_count=memory_sort();//将文件内容分块在内存中排序，并分别写入临时文件
        merge_sort(file_count);//归并临时文件内容到输出文件
    }
    MergeSort(const char* input_file,const char* out_file,int count){
        m_count=count;
        m_in_file=new char[strlen(input_file)+1];
        strcpy(m_in_file,input_file);
        m_out_file=new char[strlen(out_file)+1];
        strcpy(m_out_file,out_file);
    }
    virtual ~MergeSort(){
        delete[] m_in_file;
        delete[] m_out_file;
    }
private:
    int m_count;//每次在内存中排序的整数个数
    char *m_in_file;
    char *m_out_file;
protected:
    int read_data(FILE* f,int a[],int n){
        int i=0;
        while(i<n && (fscanf(f,"%d",&a[i])!=EOF))//为每个临时文件按行读取m_count个整数
            i++;
        printf("read: %d integer\n",i);//输出所读取的整数个数
        return i;//返回临时文件中应该存放的整数个数
    }
    char* temp_filename(int index){
        char *tempfile=new char[100];//最多为100个临时文件
        sprintf(tempfile,"temp%d.txt",index);
        return tempfile;
    }
    void write_data(FILE* f,vector<int> a,int n){
        for(int i=0;i<n;++i){
            fprintf(f,"%d\n",a[i]);//向临时文件中写入排好序的整数
        }
    }
    int memory_sort(){//分块进行堆排序，并写入临时文件
        FILE* fin=fopen(m_in_file,"rt");
        int n=0,file_count=0;
        int *array=new int[m_count];
        while((n=read_data(fin,array,m_count))>0){
              vector<int> ivec(array,array+m_count);//一个vector向量存放m_count个整数
              make_heap(ivec.begin(),ivec.end());//建堆，默认构造大顶堆
              sort_heap(ivec.begin(),ivec.end());//堆排序，得到一个非降序列，第一个数即为最小数
              char *fileName=temp_filename(file_count++);
              FILE *tempFile=fopen(fileName,"w");//创建临时文件
              free(fileName);
              write_data(tempFile,ivec,n);
              fclose(tempFile);
        }
        delete[] array;
        fclose(fin);
        return file_count;
    }
    void merge_sort(int file_count){//多路归并
        if(file_count<=0)return;
        FILE *fout=fopen(m_out_file,"wt");//建立输出文件
        FILE* *farray=new FILE*[file_count];//索引每个临时文件，先申请内存
        int i;
        for(i=0;i<file_count;++i){
            char* fileName=temp_filename(i);
            farray[i]=fopen(fileName,"rt");//索引每个临时文件
            free(fileName);
        }
        int *data=new int[file_count];//存放每个临时文件的第一个数，即最小数
        bool *hasNext=new bool[file_count];//标记临时文件是否读完（每次只读一个数，即当前文件的最小数）
        memset(data,0,sizeof(int)*file_count);
        memset(hasNext,1,sizeof(bool)*file_count);
        for(i=0;i<file_count;++i){
            if(fscanf(farray[i],"%d",&data[i])==EOF)//读每个文件的第一个数到data数组
                hasNext[i]=false;
        }
        while(true){
            //求data数组中的最小数，并记录对应文件的索引
            int min=data[0];
            int j=0;
            for(i=0;i<file_count;++i){
                if(hasNext[i] && min>data[i]){
                    min=data[i];
                    j=i;
                }
            }
            if(j==0 && !hasNext[0]) break;
            if(fscanf(farray[j],"%d",&data[j])==EOF){//读取该文件的下一个最小数到原来最小数的位置
                hasNext[j]=false;
            }
            fprintf(fout,"%d\n",min);//把最小数写入最终输出文件
        }
        delete[] hasNext;
        delete[] data;
        for(i=0;i<file_count;++i){
            fclose(farray[i]);
        }
        delete[] farray;
        fclose(fout);
    }
};

#endif // MERGESORT_H_INCLUDED
