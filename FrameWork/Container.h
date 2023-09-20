#ifndef _CONTAINER_H_
#define _CONTAINER_H_
#include "Monster.h"

// �Լ� �������� ���ø� Ŭ���� �Ǵ� �Լ���°� �˷���� �Ѵ�.

template <typename T> // Ŭ���� �������� ���ø�ȭ �Ѵٰ� �������ش�.
class Container
{
	T* arr; // ��ü
	int length; // �ִ� ����
	int itemIndex = 0; // ���� �ε���

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


template <typename T> // �Լ� �������� ��� ���ش�.
Container<T>::Container(int len) : itemIndex(0)
{
	if (len <= 0 || 10 < len) // �ִ� 10��
		len = 10;

	length = len;
	arr = new T[length]; // ����
}

template <typename T> // �Լ� �������� ��� ���ش�.
void Container<T>::Insert(T data) {
	if (itemIndex == length)
	{
		//cout << "�뷮�� �ʰ��Ǿ����ϴ�." << endl; // ������ �ʰ�
		return;
	}
	arr[itemIndex++] = data;
}

template <typename T> // �Լ� �������� ��� ���ش�.
void Container<T>::Reset() {
	while(itemIndex != 0){ // ������ ����� ������ ����		
		Remove(itemIndex - 1); // ������ ��ü ��� ����
	}
}

template <typename T> // �Լ� �������� ��� ���ش�.
T Container<T>::Remove(int idx)
{
	if (idx < 0 || idx >= itemIndex)
	{		
		return NULL; // �ش� ��� ������ ��ȯ
	}

	T del = arr[idx];
	for (int i = idx; i < itemIndex - 1; i++)
		arr[i] = arr[i + 1]; // ��ü ��ü

	itemIndex--;

	return del;
}

template <typename T> // �Լ� �������� ��� ���ش�.
T Container<T>::GetItem(int idx)
{
	if (idx < 0 || idx >= itemIndex) {
		//cout << "�ش� ��Ұ� �����ϴ�." << endl;
		return NULL;
	}
	return arr[idx];
}
#endif // !_CONTAINER_H_