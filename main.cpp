#include<iostream>
#include<string>
#include<fstream>

using namespace std;
typedef struct ListItem
{
	ListItem* next;
	ListItem* prev;
	char info;
	int position;
}Item;

typedef struct List
{
	Item* top = nullptr;
	Item* bot = nullptr;

	void CreateList(string filename)
	{
		ifstream File(filename);
		int filelines = 0;
		string line;
		while (!File.eof())
		{
			getline(File, line);
			filelines++;
		}
		File.close();
		File.open(filename);

		for (int i = 0; i < filelines; i++)
		{
			Item* newItem = new Item();

			cout << sizeof(char) << " байт памяти выделено\tадресс: " << newItem;
			File >> newItem->info;
			newItem->position = i;
			cout << "\tданные: { элемент: " << newItem->info << "\tпозиция: " << newItem->position << " }" << endl;


#pragma region Linking

			newItem->prev = top;

			if (top != nullptr) top->next = newItem; // set prev item field <nextItem> equals newItem
			newItem->next = bot;

			if (bot == nullptr) bot = newItem;

			top = newItem;
#pragma endregion

		}
		bot->prev = top;
		cout << "Descriptor: botAddress: " << bot << "\ttopAddress: " << top << endl;
		File.close();
	}
	void PrintList()
	{
		cout << "\n_____________________Вывод___________________" << endl;
		if (bot != nullptr && top != nullptr)
		{
			cout << "*Список от: " << bot << " до " << top << "*" << endl;

			Item* currentItem = bot;

			while (true)
			{
				if (currentItem != nullptr)
				{
					cout << "{ " << currentItem->info << "} ";
					if (currentItem->next == bot) break;
				}
				currentItem = currentItem->next;

			}
		}
		else
		{
			cout << "Список пуст\n" << endl;
		}
		cout << "\n_____________________________________________" << endl;
	}

	void FindMax()
	{
		Item* Max = bot;
		if (bot != nullptr && top != nullptr)
		{
			Item* currentItem = bot;

			while (currentItem->next != bot)
			{
				if (currentItem->info > Max->info)
				{
					Max = currentItem;
				}
				currentItem = currentItem->next;
			}

			currentItem = bot;
			while (currentItem->next != bot)
			{
				if (currentItem->info == Max->info)
				{
					cout << "\nМаксимальное значение: " << currentItem->info << "\tпозиция: " << currentItem->position << "\tадресс: " << currentItem;
				}
				currentItem = currentItem->next;
			}
		}
		else
		{
			cout << "Список пуст\n";
		}
	}
	void addToBack(char info)
	{
		Item* currentItem = new Item;

	}

	void DeleteFirst()
	{
		if (bot != nullptr && top != nullptr)
		{
			Item* first = bot;
			bot = bot->next;
			top->next = bot;
			delete first;

			Item* currentItem = bot;
			while (currentItem->next != bot)
			{
				currentItem->position--;
				currentItem = currentItem->next;
			}
		}
		else
		{
			cout << "Список пуст\n";
		}
	}
	void ClearList()
	{
		if (bot != nullptr && top != nullptr)
		{
			Item* currentItem = bot;
			Item* nextitem;

			while (true)
			{
				nextitem = currentItem->next;
				delete currentItem;
				if (nextitem == bot) break;
				currentItem = nextitem;
			}
			bot = nullptr;
			top = nullptr;
			cout << "Список очищен" << endl;
		}
		else
		{
			cout << "Список уже пуст";
		}
	}
};
int main()
{
	setlocale(LC_ALL, "rus");
	List list;

	// TASK 1
	list.CreateList("text.txt");

	// TASK 2
	list.PrintList();

	list.FindMax();

	list.DeleteFirst();
	list.DeleteFirst();
	list.PrintList();

	list.addToBack('r');
	list.PrintList();

	list.ClearList();
	system("pause ");
	return 0;
}
