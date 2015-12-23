#include <iostream>
#include <list>
#include <queue>

using namespace std;

template<typename T>
class ObjectPool
{
public:
	ObjectPool(int chunkSize = defaultChunk) : chunkSize_(chunkSize)
	{
		if (chunkSize <= 0) {
			std::cout << "chunkSize <= 0" << endl;
		}
		else {
			allocChunk(defaultSize);
		}
	}
	
	~ObjectPool()
	{
		deleteAllAllocList();
	}
	
	// 获取一个对象，不要释放该对象，其由对象池类管理
	T &acquireObject()
	{
		if (freeQueue_.empty()) {
			allocChunk(chunkSize_);
		}
		T *obj = freeQueue_.front();
		freeQueue_.pop();
		return *obj;
	}
	
	// 释放一个对象到对象池
	void releaseObject(T &object)
	{
		freeQueue_.push(&object);
	}

private:
	// Not allow
	ObjectPool(const ObjectPool<T> &rhs);
	ObjectPool<T> &operator=(const ObjectPool<T> &rhs);
	
	void allocChunk(int size)
	{
		T *p = new T[size];
		
		for (int i = 0; i < size; i++) {
			freeQueue_.push(&p[i]);
		}
		// 注意：申请内存是按块申请的，所以释放时也要按照块来释放
		allAllocList_.push_back(p);
	}
	
	void deleteAllAllocList()
	{
		for (int i = 0; i < allAllocList_.size(); i++) {
			delete []allAllocList_[i];
		}
	}
	
	// 默认对象池大小为100
	static const int defaultSize = 100;
	// 默认块大小，即每次分配内存时的增量
	static const int defaultChunk = 10;
	
	int chunkSize_;
	// 空闲队列
	std::queue<T*> freeQueue_;
	// 已分配的内存
	std::vector<T*> allAllocList_;
};

int main(int argc, char **args)
{
	ObjectPool<int> pool;
	
	int &a = pool.acquireObject();
	pool.releaseObject(a);
	
	return 0;
}