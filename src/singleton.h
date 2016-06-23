/***************************************************
* @filename	singleton.h
* @auther	yangenliang
* @email	2499899214@qq.com
* @data		2016-06-22 23:26:35.
***************************************************/

#ifndef _SINGLETON_H_ 
#define _SINGLETON_H_ 

template<class T>
class Singleton
{
protected:
	Singleton(){}
	~Singleton(){}
	
private:
	Singleton(const Singleton&);
	const Singleton& operator=(const Singleton&);

public:
	static inline T& get_instance(){
		static T t;
		return t;
	}

	static inline T* get_instance_ptr(){
		return &get_instance();
	}
};

#endif // _SINGLETON_H_ 
