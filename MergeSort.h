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
        int file_count=memory_sort();//���ļ����ݷֿ����ڴ������򣬲��ֱ�д����ʱ�ļ�
        merge_sort(file_count);//�鲢��ʱ�ļ����ݵ�����ļ�
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
    int m_count;//ÿ�����ڴ����������������
    char *m_in_file;
    char *m_out_file;
protected:
    int read_data(FILE* f,int a[],int n){
        int i=0;
        while(i<n && (fscanf(f,"%d",&a[i])!=EOF))//Ϊÿ����ʱ�ļ����ж�ȡm_count������
            i++;
        printf("read: %d integer\n",i);//�������ȡ����������
        return i;//������ʱ�ļ���Ӧ�ô�ŵ���������
    }
    char* temp_filename(int index){
        char *tempfile=new char[100];//���Ϊ100����ʱ�ļ�
        sprintf(tempfile,"temp%d.txt",index);
        return tempfile;
    }
    void write_data(FILE* f,vector<int> a,int n){
        for(int i=0;i<n;++i){
            fprintf(f,"%d\n",a[i]);//����ʱ�ļ���д���ź��������
        }
    }
    int memory_sort(){//�ֿ���ж����򣬲�д����ʱ�ļ�
        FILE* fin=fopen(m_in_file,"rt");
        int n=0,file_count=0;
        int *array=new int[m_count];
        while((n=read_data(fin,array,m_count))>0){
              vector<int> ivec(array,array+m_count);//һ��vector�������m_count������
              make_heap(ivec.begin(),ivec.end());//���ѣ�Ĭ�Ϲ���󶥶�
              sort_heap(ivec.begin(),ivec.end());//�����򣬵õ�һ���ǽ����У���һ������Ϊ��С��
              char *fileName=temp_filename(file_count++);
              FILE *tempFile=fopen(fileName,"w");//������ʱ�ļ�
              free(fileName);
              write_data(tempFile,ivec,n);
              fclose(tempFile);
        }
        delete[] array;
        fclose(fin);
        return file_count;
    }
    void merge_sort(int file_count){//��·�鲢
        if(file_count<=0)return;
        FILE *fout=fopen(m_out_file,"wt");//��������ļ�
        FILE* *farray=new FILE*[file_count];//����ÿ����ʱ�ļ����������ڴ�
        int i;
        for(i=0;i<file_count;++i){
            char* fileName=temp_filename(i);
            farray[i]=fopen(fileName,"rt");//����ÿ����ʱ�ļ�
            free(fileName);
        }
        int *data=new int[file_count];//���ÿ����ʱ�ļ��ĵ�һ����������С��
        bool *hasNext=new bool[file_count];//�����ʱ�ļ��Ƿ���꣨ÿ��ֻ��һ����������ǰ�ļ�����С����
        memset(data,0,sizeof(int)*file_count);
        memset(hasNext,1,sizeof(bool)*file_count);
        for(i=0;i<file_count;++i){
            if(fscanf(farray[i],"%d",&data[i])==EOF)//��ÿ���ļ��ĵ�һ������data����
                hasNext[i]=false;
        }
        while(true){
            //��data�����е���С��������¼��Ӧ�ļ�������
            int min=data[0];
            int j=0;
            for(i=0;i<file_count;++i){
                if(hasNext[i] && min>data[i]){
                    min=data[i];
                    j=i;
                }
            }
            if(j==0 && !hasNext[0]) break;
            if(fscanf(farray[j],"%d",&data[j])==EOF){//��ȡ���ļ�����һ����С����ԭ����С����λ��
                hasNext[j]=false;
            }
            fprintf(fout,"%d\n",min);//����С��д����������ļ�
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
