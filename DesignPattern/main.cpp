#include "Singleton.h"
#include <stdio.h>
#include <stdlib.h>

class A :public Singleton<A>
{
	SINGLETON_INIT_FUNC(A)
	{
		printf("A Init()\n");
	}

	SINGLETON_DESTROY_FUNC(A)
	{
		printf("delete data %d\n", data--);
	}
public:
	void Print()
	{
		printf("A Print()\n");
	}
	void Add() { printf("%d\n", data++); }
private:
	int data;
};

template<typename T>
class Singletion
{
	friend T;
private:
	Singletion() {}
	virtual ~Singletion() {}

	static T* pObject;

	//���ô������������ͷŵ���ʵ���ڴ�  
	class CCarbageCollector
	{
	public:
		~CCarbageCollector()
		{
			printf("~CCarbageCollector");
			if (Singletion<T>::pObject != NULL)
			{
				delete Singletion<T>::pObject;
				printf("Object delete");
			}
		}
	};

protected:

	//�ṩ��������ĳ�ʼ���ӿ�  
	virtual void Init() = 0;

public:
	//��ȡ����  
	inline static T* GetSingleton()
	{
		//����ϵͳ�˳�ʱ�ͷŵ���ʵ�����ڴ�  
		static Singletion<T>::CCarbageCollector CarCo;

		pObject == NULL && (pObject = new T);
		return pObject;
	}

};

template<typename T>
T* Singletion<T>::pObject = NULL;

#define SINGLETON_INIT(ClassType)  friend ClassType* Singletion<ClassType>::GetSingleton(); friend Singletion<ClassType>::CCarbageCollector; \
	private:\
	ClassType() { Init(); }\
	virtual ~ClassType() {}\
	virtual void Init()

	//����  
class B : public Singletion<B>
{
	SINGLETON_INIT(B)
	{
		data = 0;
		printf("Singleton Init\n");
	}
public:
	void Add() { printf("%d\n", data++); }
private:
	int data;
};

int main()
{
	B *b = B::GetSingleton();
	b->Add();
	B* c = B::GetSingleton();
	c->Add();
	b->Add();
	A* a = A::Get_Instance();
	A* d = A::Get_Instance();
	system("pause");
	return 0;
}