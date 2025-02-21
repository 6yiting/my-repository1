#include<iostream>
#include"workerManager.h"
#include"worker.h"
using namespace std;
int main()
{
	//实例化管理类对象
	WorkerManager wm;
	int choice = 0;//用来存储用户的选项
	while (true)
	{
		//调用展示菜单函数
		wm.ShowMenu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;//接受用户的选项
		switch (choice)
		{
		case 0://退出系统
			wm.exitSystem();
			break;
		case 1://增加职工
			wm.AddEmp();
			break;
		case 2://显示职工
			wm.ShowEmp();
			break;
		case 3://删除职工
			wm.DelEmp();
			break;
		case 4://修改职工
			wm.ModEmp();
			break;
		case 5://查找职工
			wm.FindEmp();
			break;
		case 6://排序职工
			wm.SortEmp();
			break;
		case 7://清空文档
			wm.CleanFile();
			break;
		default:
			system("cls");//清屏
			break;
		}
	}
	system("pause");//按任意键继续
	return 0;
}