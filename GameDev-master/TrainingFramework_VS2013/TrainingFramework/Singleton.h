#pragma once
template <typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		if (!s_Instance)
			s_Instance = new T();
		return s_Instance;
	}

protected:
	Singleton()
	{}
	virtual ~Singleton()
	{}
	static T* s_Instance;
};

template<typename T >
T* Singleton<T>::s_Instance = NULL;