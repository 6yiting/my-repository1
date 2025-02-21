#include"workerManager.h"
WorkerManager::WorkerManager()
{
	//��ʼ������
	//������ļ����Ѿ��������ݣ��Ͳ��ܰ���ֱ���ÿ�

	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2���ļ�����������Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())//�ļ�Ϊ��
	{
		//cout << "�ļ�Ϊ��" << endl;
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3���ļ����ڲ�����ְ������
	int num = this->getEmpNum();
	//cout << "ְ������Ϊ�� " << num << endl;
	this->m_EmpNum = num;
	//�ȿ��ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݴ浽������
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
//չʾ�˵�����
void WorkerManager::ShowMenu()
{
	cout << "**********************************" << endl;
	cout << "*****��ӭʹ��ְ������ϵͳ��*******" << endl;
	cout << "*********0���˳��������**********" << endl;
	cout << "*********1������ְ����Ϣ**********" << endl;
	cout << "*********2����ʾְ����Ϣ**********" << endl;
	cout << "*********3��ɾ����ְְ��**********" << endl;
	cout << "*********4���޸�ְ����Ϣ**********" << endl;
	cout << "*********5������ְ����Ϣ**********" << endl;
	cout << "*********6�����ձ������**********" << endl;
	cout << "*********7����������ĵ�**********" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}
//�˳�ϵͳ
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}
//����ְ����Ϣ
void WorkerManager::AddEmp()
{
	cout << "���������ְ�������� " << endl;
	int addNum = 0;//�����û�����������
	cin >> addNum;
	if (addNum > 0)
	{
		//��������¿ռ��С
		int newSize = this->m_EmpNum + addNum;//������=ԭ����¼����+��������
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];
		//��ԭ���ռ��µ����ݿ������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//�������������
		for (int i = 0;i < addNum;i++)
		{
			int id;//ְ�����
			string name;//ְ������
			int dSelect;//����ѡ��
			cout << "������� " << i + 1 << "����ְ����ţ� " << endl;
			start:cin >> id;
			int re=this->IsExit(id);
			if (re != -1)//˵���Ѿ����˸ñ��
			{
				cout << "���б��Ϊ" << id << "��ְ��,����������ְ����ţ�" << endl;
				goto start;
			}
			cout << "������� " << i + 1 << "����ְ�������� " << endl;
			cin >> name;
			cout << "��ѡ���ְ����λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			//��������ְ��ָ�뱣�浽������
			newSpace[this->m_EmpNum + i] = worker;
		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;
		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;
		//�����µ�ְ������
		this->m_EmpNum = newSize;
		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
		//����ְ����Ϊ�յı�־
		this->m_FileIsEmpty = false;
		//�������ݵ��ļ���
		this->save();
	}
	else
	{
		cout << "������������" << endl;
	}
	//������������� �ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}
//�����ļ�
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//д�ļ�
	//��ÿ���˵�����д�뵽�ļ���
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID<< endl;
	}
	//�ر��ļ�
	ofs.close();
}
//ͳ���ļ�������
int WorkerManager::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ� ���ļ�
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
//��ʼ��Ա��
void WorkerManager::initEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)//��ְͨ��
		{
			worker = new Employee(id,name,dId);
		}
		else if (dId == 2)//����
		{
			worker = new Manager(id, name, dId);
		}
		else //�ϰ�
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//�ر��ļ�
	ifs.close();
}
//��ʾְ��
void WorkerManager::ShowEmp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	//�������������
	system("pause");
	system("cls");
}
//ɾ��ְ��
void WorkerManager::DelEmp()
{
	//�ж��ļ��Ƿ����
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		//����ְ����Ž���ɾ��ְ��
		cout << "��������Ҫɾ��ְ���ı�ţ�" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExit(id);
		if (index != -1)//˵��ְ�����ڣ�������Ҫɾ��indexλ���ϵ�ְ��
		{
			for (int i = index;i < this->m_EmpNum - 1;i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//���������м�¼��Ա����
			//ͬ�����µ��ļ���
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "δ�ҵ���ְ����ɾ��ʧ��" << endl;
		}
	}
	//�����������
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ���ڣ������ڣ�����ְ�����������е�λ�ã��������ڣ�����-1
int WorkerManager::IsExit(int id)
{
	int index = -1;
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		if (this->m_EmpArray[i]->m_ID == id)
		{
			//�ҵ�ְ��
			index = i;
			break;
		}
	}
	return index;
}
//�޸�ְ��
void WorkerManager::ModEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı�ţ� " << endl;
		int id;
		cin >> id;
		int re=this->IsExit(id);
		if (re != -1)
		{
			//�ҵ�Ҫ�޸�ְ����
			delete this->m_EmpArray[re];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "�鵽" << id << "��ְ������������ְ���ţ� " << endl;
			start:cin >> newId;
			int re = this->IsExit(newId);
			if (re != -1)
			{
				//˵�����иñ��ְ��
				cout << "���б��Ϊ" << newId << "��ְ����������������ְ���ţ�" << endl;
				goto start;
			}
			cout << "�������������� " << endl;
			cin >> newName;
			cout << "�������¸�λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			//�������ݵ�������
			this->m_EmpArray[re] = worker;
			cout << "�޸ĳɹ�" << endl;
			//�����ݱ��浽�ļ���
			this->save();
		}
		else
		{
			cout << "���޴��ˣ��޸�ʧ��" << endl;
		}
	}
	system("pause");
	system("cls");
}
//����ְ��
void WorkerManager::FindEmp()
{
	//�ж��ļ�
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ�� " << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2����ְ����������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)//����Ų�
		{
			int id;
			cout << "���������ְ���ı�ţ�" << endl;
			cin >> id;
			int re = this->IsExit(id);
			if (re != -1)
			{
				//�ҵ�ְ��
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[re]->showInfo();
			}
			else
			{
				cout << "���޴��ˣ�����ʧ�ܣ�" << endl;
			}
		}
		else if (select == 2)//��������
		{
			string name;
			cout << "���������ְ���������� " << endl;
			cin >> name;
			//�ж��Ƿ�鵽�ı�־
			bool flag = false;//Ĭ��δ�ҵ�
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					flag = true;
					cout << "���ҳɹ�����ְ�����Ϊ��" << this->m_EmpArray[i]->m_ID << "  ��ְ����Ϣ���£�" << endl;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "���޴��ˣ�����ʧ�ܣ�" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}
//����ְ���������
void WorkerManager::SortEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			int minormax = i;//��Сֵ�����ֵ�±�
			for(int j=i+1;j<this->m_EmpNum;j++)
			{
				if (select == 1)//����
				{
					if (this->m_EmpArray[j]->m_ID < this->m_EmpArray[minormax]->m_ID)
					{
						minormax = j;
					}
				}
				else//����
				{
					if (this->m_EmpArray[j]->m_ID > this->m_EmpArray[minormax]->m_ID)
					{
						minormax = j;
					}
				}
			}
			//�ж�һ��ʼ�϶������ֵ����Сֵ�ǲ���������ֵ����Сֵ
			if (minormax != i)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minormax];
				this->m_EmpArray[minormax] = temp;
			}
		}
		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->save();
		this->ShowEmp();
	}
}
//����ļ�
void WorkerManager::CleanFile()
{
	cout << "ȷ�������" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME,ios::trunc);//ɾ���ļ������´���
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}