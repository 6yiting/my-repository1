#pragma once//��ֹͷ�ļ��ظ�����
#include<iostream>//�������������ͷ�ļ�
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
using namespace std;//ʹ�ñ�׼�����ռ�
#define FILENAME "empFile.txt"
class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();
	//չʾ�˵�����
	void ShowMenu();
	//�˳�ϵͳ
	void exitSystem();
	//����ְ����Ϣ
	void AddEmp();
	//�����ļ�
	void save();
	//ͳ���ļ�������
	int getEmpNum();
	//��ʼ��Ա��
	void initEmp();
	
	//��ʾְ��
	void ShowEmp();

	//ɾ��ְ��
	void DelEmp();

	//�ж�ְ���Ƿ���ڣ������ڣ�����ְ�����������е�λ�ã��������ڣ�����-1
	int IsExit(int id);

	//�޸�ְ��
	void ModEmp();

	//����ְ��
	void FindEmp();

	//����ְ���������
	void SortEmp();

	//����ļ�
	void CleanFile();

	//����
	//��¼ְ������
	int m_EmpNum;
	//ְ������ָ��
	Worker** m_EmpArray;
	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
};
