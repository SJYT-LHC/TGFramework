#ifndef _SIMP_SHM_20100810_H
#define _SIMP_SHM_20100810_H

#include    <stdio.h>
#include    <unistd.h>
#include    <errno.h>
#include    <string.h>
#include    <sys/types.h>
#include    <sys/ipc.h>
#include    <sys/shm.h>
#include    <sys/sem.h>

// ����һ������ڴ�
// pShmRoot:ָ������,������/�ҽ�һ�鹲���ڴ�ɹ�ʱ,������ʼ��ַ
// tShmKey:�����ڴ�Key
// iShmSize:�����ڴ��С
// bCreate:true �������ڴ治�������Զ����� false�ҽӵ����е�һ���ڴ���
// bNew:�������ڴ�Ϊ�½���bNew����true
// ����ֵ:
// < 0  fail
// >=0  Shm-ID
int AttachShm(void **ppShmRoot,key_t tShmKey,int iShmSize,bool bCreate,bool &bNew);

// ����������ڴ������,pShmRootָ�����ڴ��׵�ַ
int DetachShm(void **ppShmRoot);

char* GetShm(int iKey, int iSize, int iFlag);
int GetShm2(void **pstShm, int iShmID, int iSize, int iFlag);
int GetShm3(void **pstShm, int iShmID, int iSize, int iFlag);


#endif

