#pragma once//防止头文件重复包含
#include<iostream>//包含输入输出流头文件
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
using namespace std;//使用标准命名空间
#define FILENAME "empFile.txt"
class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();
	//展示菜单函数
	void ShowMenu();
	//退出系统
	void exitSystem();
	//增加职工信息
	void AddEmp();
	//保存文件
	void save();
	//统计文件中人数
	int getEmpNum();
	//初始化员工
	void initEmp();
	
	//显示职工
	void ShowEmp();

	//删除职工
	void DelEmp();

	//判断职工是否存在，若存在，返回职工所在数组中的位置；若不存在，返回-1
	int IsExit(int id);

	//修改职工
	void ModEmp();

	//查找职工
	void FindEmp();

	//按照职工编号排序
	void SortEmp();

	//清空文件
	void CleanFile();

	//属性
	//记录职工人数
	int m_EmpNum;
	//职工数组指针
	Worker** m_EmpArray;
	//判断文件是否为空
	bool m_FileIsEmpty;
};
