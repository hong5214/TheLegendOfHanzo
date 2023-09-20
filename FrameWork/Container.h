#ifndef _CONTAINER_H_
#define _CONTAINER_H_
#include "Monster.h"

// 함수 구현마다 템플릿 클래스 또는 함수라는걸 알려줘야 한다.

template <typename T> // 클래스 선언전에 템플릿화 한다고 선언해준다.
class Container
{
	T* arr; // 객체
	int length; // 최대 개수
	int itemIndex = 0; // 현재 인덱스

public:
	Container(int len = 10);
	~Container() { delete[] arr; }
	void Insert(T data);
	void Reset();
	T Remove(int idx);

	T GetItem(int idx);
	int GetLength() { return length; }
	int GetItemCount() { return itemIndex; }
};


template <typename T> // 함수 구현마다 계속 해준다.
Container<T>::Container(int len) : itemIndex(0)
{
	if (len <= 0 || 10 < len) // 최대 10개
		len = 10;

	length = len;
	arr = new T[length]; // 생성
}

template <typename T> // 함수 구현마다 계속 해준다.
void Container<T>::Insert(T data) {
	if (itemIndex == length)
	{
		//cout << "용량이 초과되었습니다." << endl; // 데이터 초과
		return;
	}
	arr[itemIndex++] = data;
}

template <typename T> // 함수 구현마다 계속 해준다.
void Container<T>::Reset() {
	while(itemIndex != 0){ // 제거할 대상이 없으면 리턴		
		Remove(itemIndex - 1); // 마지막 객체 계속 제거
	}
}

template <typename T> // 함수 구현마다 계속 해준다.
T Container<T>::Remove(int idx)
{
	if (idx < 0 || idx >= itemIndex)
	{		
		return NULL; // 해당 요소 없으면 반환
	}

	T del = arr[idx];
	for (int i = idx; i < itemIndex - 1; i++)
		arr[i] = arr[i + 1]; // 객체 교체

	itemIndex--;

	return del;
}

template <typename T> // 함수 구현마다 계속 해준다.
T Container<T>::GetItem(int idx)
{
	if (idx < 0 || idx >= itemIndex) {
		//cout << "해당 요소가 없습니다." << endl;
		return NULL;
	}
	return arr[idx];
}
#endif // !_CONTAINER_H_