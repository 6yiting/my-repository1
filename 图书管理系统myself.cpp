#include<iostream>
#include<string>
#define MAX 1000//后面修改限定人数时更方便
using namespace std;
//联系人结构体
struct Person {
	string m_Name;
	string m_Sex;
	int m_Age;
	string m_Phone;
	string m_Address;
};
//通讯录结构体
struct Addressbooks {
	Person personbooks[MAX];
	int num;//记录当前联系人个数
};
//1、添加联系人
void addPerson(Addressbooks* abs)
{
	if (abs->num == 1000)//退出，不做操作
	{
		cout << "联系人已满，无法再添加" << endl;
	}
	else
	{
		//姓名
		cout << "姓名：" << endl;
		cin >> abs->personbooks[abs->num].m_Name;
		//性别
		cout << "性别：" << endl;
		cin >> abs->personbooks[abs->num].m_Sex;
		//年龄
		cout << "年龄：" << endl;
		cin >> abs->personbooks[abs->num].m_Age;
		//电话
		cout << "电话：" << endl;
		cin >> abs->personbooks[abs->num].m_Phone;
		//地址
		cout << "地址：" << endl;
		cin >> abs->personbooks[abs->num].m_Address;
		abs->num++;//更新通讯录中当前联系人个数
		system("pause");//按任意键继续
		system("cls");//清空界面作用
	}
}
//2、显示联系人
void showPerson(Addressbooks* abs)
{
	if (abs->num != 0)
	{
		for (int i = 0;i < abs->num;i++)
		{
			cout << "姓名： " << abs->personbooks[i].m_Name << '\t';
			cout << "性别： " << abs->personbooks[i].m_Sex << '\t';
			cout << "年龄： " << abs->personbooks[i].m_Age << '\t';
			cout << "电话： " << abs->personbooks[i].m_Phone << '\t';
			cout << "地址： " << abs->personbooks[i].m_Address << endl;
		}
	}
	else cout << "通讯录为空" << endl;
	system("pause");
	system("cls");
}
//检验是否存在该联系人
int isExist(Addressbooks* abs, string name)
{
	for (int i = 0;i < abs->num;i++)
	{
		if (abs->personbooks[i].m_Name == name)return i;
	}
	return -1;//没有该联系人
}
//3、删除联系人
void deletePerson(Addressbooks* abs)
{
	cout << "请输入您要删除的联系人" << endl;
	string name;
	cin >> name;
	int re = isExist(abs, name);
	if (re != -1)//存在该联系人
	{
		for (int i = re;i < abs->num-1;i++)
		{
			abs->personbooks[i] = abs->personbooks[i + 1];
		}
		cout << "删除成功" << endl;
		abs->num--;//更新通讯录中联系人个数
	}
	else cout << "查无此人" << endl;
	system("pause");
	system("cls");
}
//4、查找联系人
void findPerson(Addressbooks* abs)
{
	cout << "请输入您要查询的联系人" << endl;
	string name;
	cin >> name;
	int re = isExist(abs, name);
	if (re != -1)
	{
		cout << "姓名： " << abs->personbooks[re].m_Name << '\t';
		cout << "性别： " << abs->personbooks[re].m_Sex << '\t';
		cout << "年龄： " << abs->personbooks[re].m_Age << '\t';
		cout << "电话： " << abs->personbooks[re].m_Phone << '\t';
		cout << "地址： " << abs->personbooks[re].m_Address << endl;
	}
	else cout << "查无此人" << endl;
	system("pause");
	system("cls");
}
//5、修改联系人
void modifyPerson(Addressbooks* abs)
{
	cout << "请输入您要修改的联系人" << endl;
	string name;
	cin >> name;
	int re = isExist(abs, name);
	if (re != -1)
	{
		//姓名
		cout << "姓名：" << endl;
		cin >> abs->personbooks[re].m_Name;
		//性别
		cout << "性别：" << endl;
		cin >> abs->personbooks[re].m_Sex;
		//年龄
		cout << "年龄：" << endl;
		cin >> abs->personbooks[re].m_Age;
		//电话
		cout << "电话：" << endl;
		cin >> abs->personbooks[re].m_Phone;
		//地址
		cout << "地址：" << endl;
		cin >> abs->personbooks[re].m_Address;
		cout << "修改成功" << endl;
	}
	else cout << "查无此人" << endl;
	system("pause");
	system("cls");
}
//6、清空联系人
void cleanPerson(Addressbooks* abs)
{
	abs->num = 0;
	cout << "清空成功" << endl;
	system("pause");
	system("cls");
}
//显示功能界面
void showFunction()
{
	cout << "***************************" << endl;
	cout << "*****  1、添加联系人  *****" << endl;
	cout << "*****  2、显示联系人  *****" << endl;
	cout << "*****  3、删除联系人  *****" << endl;
	cout << "*****  4、查找联系人  *****" << endl;
	cout << "*****  5、修改联系人  *****" << endl;
	cout << "*****  6、清空联系人  *****" << endl;
	cout << "*****  0、退出通讯录  *****" << endl;
	cout << "***************************" << endl;
}
int main()
{
	Addressbooks abs;
	abs.num = 0;//初始化为0
	int select;
	while (1)
	{
		showFunction();
		cin >> select;
		switch (select)
		{
		case 1://1、添加联系人
			addPerson(&abs);
			break;
		case 2://2、显示联系人
			showPerson(&abs);
			break;
		case 3://3、删除联系人
			deletePerson(&abs);
			break;
		case 4://4、查找联系人
			findPerson(&abs);
			break;
		case 5://5、修改联系人
			modifyPerson(&abs);
			break;
		case 6://6、清空联系人
			cleanPerson(&abs);
			break;
		case 0://0、退出通讯录
			cout << "欢迎下次使用" << endl;
			return 0;
		default:
		{
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");
		}
			break;
		}

	}
	return 0;
}