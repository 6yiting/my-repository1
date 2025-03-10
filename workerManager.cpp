#include"workerManager.h"
WorkerManager::WorkerManager()
{
	//初始化属性
	//但如果文件中已经有了数据，就不能把它直接置空

	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2、文件存在且数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())//文件为空
	{
		//cout << "文件为空" << endl;
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3、文件存在并保存职工数据
	int num = this->getEmpNum();
	//cout << "职工人数为： " << num << endl;
	this->m_EmpNum = num;
	//先开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据存到数组中
	this->initEmp();
}
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			if(this->m_EmpArray[i]!=NULL)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
		}
		delete[]this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
//展示菜单函数
void WorkerManager::ShowMenu()
{
	cout << "**********************************" << endl;
	cout << "*****欢迎使用职工管理系统！*******" << endl;
	cout << "*********0、退出管理程序**********" << endl;
	cout << "*********1、增加职工信息**********" << endl;
	cout << "*********2、显示职工信息**********" << endl;
	cout << "*********3、删除离职职工**********" << endl;
	cout << "*********4、修改职工信息**********" << endl;
	cout << "*********5、查找职工信息**********" << endl;
	cout << "*********6、按照编号排序**********" << endl;
	cout << "*********7、清空所有文档**********" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}
//退出系统
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}
//增加职工信息
void WorkerManager::AddEmp()
{
	cout << "请输入添加职工数量： " << endl;
	int addNum = 0;//保存用户的输入数量
	cin >> addNum;
	if (addNum > 0)
	{
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;//新人数=原来记录人数+新增人数
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];
		//将原来空间下的数据拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//批量添加新数据
		for (int i = 0;i < addNum;i++)
		{
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择
			cout << "请输入第 " << i + 1 << "个新职工编号： " << endl;
			start:cin >> id;
			int re=this->IsExit(id);
			if (re != -1)//说明已经有了该编号
			{
				cout << "已有编号为" << id << "的职工,请重新输入职工编号：" << endl;
				goto start;
			}
			cout << "请输入第 " << i + 1 << "个新职工姓名： " << endl;
			cin >> name;
			cout << "请选择该职工岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建的职工指针保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原有空间
		delete[] this->m_EmpArray;
		//更改新空间指向
		this->m_EmpArray = newSpace;
		//更新新的职工人数
		this->m_EmpNum = newSize;
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;
		//更新职工不为空的标志
		this->m_FileIsEmpty = false;
		//保存数据到文件中
		this->save();
	}
	else
	{
		cout << "输入数据有误" << endl;
	}
	//按任意键后清屏 回到上级目录
	system("pause");
	system("cls");
}
//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//写文件
	//将每个人的数据写入到文件中
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID<< endl;
	}
	//关闭文件
	ofs.close();
}
//统计文件中人数
int WorkerManager::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件 读文件
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	return num;
}
//初始化员工
void WorkerManager::initEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)//普通职工
		{
			worker = new Employee(id,name,dId);
		}
		else if (dId == 2)//经理
		{
			worker = new Manager(id, name, dId);
		}
		else //老板
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();
}
//显示职工
void WorkerManager::ShowEmp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}
//删除职工
void WorkerManager::DelEmp()
{
	//判断文件是否存在
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		//按照职工编号进行删除职工
		cout << "请输入需要删除职工的编号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExit(id);
		if (index != -1)//说明职工存在，并且想要删除index位置上的职工
		{
			for (int i = index;i < this->m_EmpNum - 1;i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录人员个数
			//同步更新到文件中
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "未找到该职工，删除失败" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//判断职工是否存在，若存在，返回职工所在数组中的位置；若不存在，返回-1
int WorkerManager::IsExit(int id)
{
	int index = -1;
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		if (this->m_EmpArray[i]->m_ID == id)
		{
			//找到职工
			index = i;
			break;
		}
	}
	return index;
}
//修改职工
void WorkerManager::ModEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号： " << endl;
		int id;
		cin >> id;
		int re=this->IsExit(id);
		if (re != -1)
		{
			//找到要修改职工了
			delete this->m_EmpArray[re];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "查到" << id << "号职工，请输入新职工号： " << endl;
			start:cin >> newId;
			int re = this->IsExit(newId);
			if (re != -1)
			{
				//说明已有该编号职工
				cout << "已有编号为" << newId << "的职工，请重新输入新职工号：" << endl;
				goto start;
			}
			cout << "请输入新姓名： " << endl;
			cin >> newName;
			cout << "请输入新岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			//更新数据到数组中
			this->m_EmpArray[re] = worker;
			cout << "修改成功" << endl;
			//将数据保存到文件中
			this->save();
		}
		else
		{
			cout << "查无此人，修改失败" << endl;
		}
	}
	system("pause");
	system("cls");
}
//查找职工
void WorkerManager::FindEmp()
{
	//判断文件
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式： " << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)//按编号查
		{
			int id;
			cout << "请输入查找职工的编号：" << endl;
			cin >> id;
			int re = this->IsExit(id);
			if (re != -1)
			{
				//找到职工
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[re]->showInfo();
			}
			else
			{
				cout << "查无此人，查找失败！" << endl;
			}
		}
		else if (select == 2)//按姓名查
		{
			string name;
			cout << "请输入查找职工的姓名： " << endl;
			cin >> name;
			//判断是否查到的标志
			bool flag = false;//默认未找到
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					flag = true;
					cout << "查找成功，该职工编号为：" << this->m_EmpArray[i]->m_ID << "  该职工信息如下：" << endl;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "查无此人，查找失败！" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}
//按照职工编号排序
void WorkerManager::SortEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			int minormax = i;//最小值或最大值下标
			for(int j=i+1;j<this->m_EmpNum;j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[j]->m_ID < this->m_EmpArray[minormax]->m_ID)
					{
						minormax = j;
					}
				}
				else//降序
				{
					if (this->m_EmpArray[j]->m_ID > this->m_EmpArray[minormax]->m_ID)
					{
						minormax = j;
					}
				}
			}
			//判断一开始认定的最大值或最小值是不是真的最大值或最小值
			if (minormax != i)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minormax];
				this->m_EmpArray[minormax] = temp;
			}
		}
		cout << "排序成功！排序后的结果为：" << endl;
		this->save();
		this->ShowEmp();
	}
}
//清空文件
void WorkerManager::CleanFile()
{
	cout << "确定清空吗？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME,ios::trunc);//删除文件后重新创建
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}