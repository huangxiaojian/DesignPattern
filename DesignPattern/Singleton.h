#pragma once
template <class T>
class Singleton
{
	friend T;
public:
	inline static T* Get_Instance()
	{
		static T instance;
		return &instance;
	}
protected:
	virtual void Init() = 0;
private:
	Singleton() = default;
	virtual ~Singleton() = default;
};

#define SINGLETON_INIT_FUNC(T)		friend T* Singleton<T>::Get_Instance(); \
									private:								\
									T() { Init(); }							\
									virtual void Init()
#define SINGLETON_DESTROY_FUNC(T)	public:\
									virtual ~T()