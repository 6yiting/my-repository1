#include<iostream>
#include"workerManager.h"
#include"worker.h"
using namespace std;
int main()
{
	//ʵ�������������
	WorkerManager wm;
	int choice = 0;//�����洢�û���ѡ��
	while (true)
	{
		//����չʾ�˵�����
		wm.ShowMenu();
		cout << "����������ѡ��" << endl;
		cin >> choice;//�����û���ѡ��
		switch (choice)
		{
		case 0://�˳�ϵͳ
			wm.exitSystem();
			break;
		case 1://����ְ��
			wm.AddEmp();
			break;
		case 2://��ʾְ��
			wm.ShowEmp();
			break;
		case 3://ɾ��ְ��
			wm.DelEmp();
			break;
		case 4://�޸�ְ��
			wm.ModEmp();
			break;
		case 5://����ְ��
			wm.FindEmp();
			break;
		case 6://����ְ��
			wm.SortEmp();
			break;
		case 7://����ĵ�
			wm.CleanFile();
			break;
		default:
			system("cls");//����
			break;
		}
	}
	system("pause");//�����������
	return 0;
}