#pragma once

template <class T>
class CList final
{
private:
	// *** Структура узла односвязного списка
	struct SNode final
	{
	public:
		// Указатель на следующий узел
		SNode* Next;

		// Содержимое узла
		T Source;

	public:
		explicit SNode(const T& Element) : Source{ Element }, Next{}
		{
		}
	};

private:
	// *** Класс итератора односвязного списка
	class CIterator final
	{
	public:
		explicit CIterator(SNode* Element) : Node{ Element }
		{
		}

		bool operator==(const CIterator& Other) const 
		{
			return Node == Other.Node;
		}

		bool operator!=(const CIterator& Other) const
		{
			return !operator==(Other);
		}

		// *** Получить значение текущего узла
		T operator*() const 
		{
			if (Node) 
			{
				return Node->Source;
			}
			
			throw std::runtime_error("Node == nullptr!");
		}

		// *** Перейти к следующему узлу
		void operator++() 
		{
			if (Node) 
			{
				Node = Node->Next;
			}
			else
			{
				throw std::runtime_error("Current element > elements count!");
			}
		}

	private:
		// Указатель на активный узел
		SNode* Node;
	};

private:
	// Первый (головной) узел списка
	SNode* First;

public:
	CList() : First{}
	{
	}

	~CList()
	{
		clear();
	}

public:
	// *** Определить наличие элементов в списке
	bool empty() const
	{
		return !First;
	}

	// *** Добавить элемент в начало списка
	void push_front(const T& Element) noexcept
	{
		// Выделяем память под узел
		SNode* Node = new SNode(Element);

		// Если в контейнере уже есть элементы - связываем
		// первый элемент к новому узлу
		if (!empty())
		{
			Node->Next = First;
		}

		// Первым элементом становится новосозданный узел
		First = Node;
	}

	// *** Удалить элемент из начала списка
	void pop_front()
	{
		if (!empty())
		{
			// Записываем указатель на второй узел
			SNode* Buffer = First->Next;

			// Освобождаем память, занятую первым узлом
			delete First;

			// Второй узел становится первым
			First = Buffer;
		}
		else
		{
			throw std::runtime_error("List already empty!");
		}
	}

	T& operator[](size_t Index)
	{
		// Не выходим за пределы листа
		if (empty() || Index > size())
			throw std::runtime_error("Index > size()");

		SNode* Node = First;

		for (size_t Pos = 0; Pos < Index; ++Pos)
		{
			Node = Node->Next;

			if (!Node)
				throw std::runtime_error("Index > size()");
		}

		return Node->Source;
	}

	// *** Получить итератор начала списка
	CIterator begin() const
	{
		return CIterator(First);
	}

	// *** Получить итератор конца списка
	CIterator end() const
	{
		return CIterator(nullptr);
	}

	// *** Получить размер списка
	size_t size() const
	{
		size_t Result = 0;

		for (CIterator It = begin(); It != end(); ++It) 
		{
			++Result;
		}

		return Result;
	}

	// *** Получить итератор на элемент в списке
	CIterator find(const T& Element)
	{
		for (CIterator It = begin(); It != end(); ++It)
		{
			// Сравниваем значения
			if (*It == Element)
				return It;
		}

		return end();
	}

	// *** Очистка списка
	void clear()
	{
		while (!empty())
		{
			pop_front();
		}
	}
};