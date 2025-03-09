#include <iostream>
#include <string> 
#include <regex>

using namespace std;

int validIntegerInput(string message) {
	string input;
	regex valid("[1-7]");
	do {
		cout << message;
		getline(cin, input);
	} while (!regex_match(input, valid));
	return stoi(input);
}


struct DynamicLinkedList{
	string data;
	DynamicLinkedList *next, *prev;
} *HEAD;

void init() {
	HEAD = new DynamicLinkedList();
	HEAD->data = "HEAD";
	HEAD->next = HEAD;
	HEAD->prev = HEAD;
}


bool isEmpty() {
	return HEAD->next == HEAD;
}


int getSize() {
	int size = 0;
	DynamicLinkedList* current = HEAD->next;
	while (current != HEAD) {
		size++;
		current = current->next;
	}
	return size;
}

void printList(bool isForward) {
	if (isEmpty()) {
		cout << "Список пустой!" << endl;
		return;
	}
	int pos;
	if (isForward) {
		DynamicLinkedList* current = HEAD->next;
		pos = 1;
		while (current != HEAD) {
			cout << pos++<<") " << current->data << endl;
			current = current->next;
		}
		cout << endl;
	}
	else {
		pos = getSize();
		DynamicLinkedList* current = HEAD->prev;
		while (current != HEAD) {
			cout << pos-- << ") " << current->data << endl;
			current = current->prev;
		}
		cout << endl;
	}
	cout << endl;
}


void push(string value, string targetValue, bool after) {

	DynamicLinkedList* temp = new DynamicLinkedList;
	DynamicLinkedList* current = HEAD;

	temp->data = value;

	if (isEmpty()) {
		
		temp->next = HEAD;
		temp->prev = HEAD;
		HEAD->next = temp;
		HEAD->prev = temp;
	}
	else {

		while (current->next != HEAD && current->data != targetValue)
			current = current->next;
	
		if (current -> data != targetValue) {
			cout << "Элемента " << targetValue << " нет в списке!" << endl;
			return;
		}

		if (after) {
			temp->next = current->next;
			temp->prev = current;
			current->next->prev = temp;
			current->next = temp;
		}
		else {
			temp->next = current;
			temp->prev = current->prev;
			current->prev->next = temp;
			current->prev = temp;
		}
	}
}

void pop(string targetValue) {
	if (isEmpty()) {
		cout << "Список пустой!" << endl;
		return;
	}
	DynamicLinkedList* current = HEAD->next;
	while (current != HEAD && current->data != targetValue)
		current = current->next;
	if (current == HEAD) {
		cout << "Элемента " << targetValue << " нет в списке!" << endl;
		return;
	}	
	current->prev->next = current->next;
	current->next->prev = current->prev;
	delete current;
	cout << "Элемент удален" << endl;
}

void clear() {
	if (isEmpty()) {
		cout << "Список и так пустой!" << endl;
		return;
	}

	DynamicLinkedList* current = HEAD->next;
	while (current != HEAD) {
		HEAD->next = current->next;
		delete current;
		current = HEAD->next;
	}
	HEAD->next = HEAD;
	HEAD->prev = HEAD;
	cout << "Список очищен" << endl;
} 

int find(string value, bool isForwardSerch) {

	if (isEmpty()) {
		cout << "Список пустой!" << endl;
		return -1;
	}

	DynamicLinkedList* current;
	int pos;

	if (isForwardSerch) {
		pos = 1;
		current = HEAD->prev;
		while (current != HEAD && (current->data != value)){
			current = current->next;
			pos++;
		}
	}
	else {
		pos = getSize();
		current = HEAD->prev;
		while (current != HEAD && (current->data != value)){
			current = current->prev;
			pos--;
		}
	}
	return (current != HEAD) ? pos : -1;
}

void menu(bool& exit) {
	cout << endl << "Меню:" << endl;
	cout << "1. Добавить элемент в список" << endl;
	cout << "2. Удалить элемент из списка" << endl;

	cout << "3. Проверка пустой ли список" << endl;

	cout << "4. Вывести список" << endl;
	cout << "5. Поиск элемента в списке" << endl;
	cout << "6. Очистить список" << endl;
	cout << "7. Выход" << endl;

	int choice = validIntegerInput("");

	switch (choice) {
		case 1: {
			string value, targetValue;
			bool after = true;
				
			cout << "Введите значение нового элемента: ";
			getline(cin, value);
			
			if (!isEmpty()) {
				cout << "Добавить элемент после? (1 - да, 0 - нет): ";
				cin >> after;
				cin.ignore();

				cout << "Введите значение элемента, " << (after ? "после" : "до") << " которого нужно добавить новый элемент: ";
				getline(cin, targetValue);

				
			}
			push(value, targetValue, after);
			break;
		}
		case 2: {
			string targetValue;
			cout << "Введите значение элемента, который нужно удалить: ";
			getline(cin, targetValue);
			pop(targetValue);
			break;
		}
		case 3: {
			cout << "Список " << (isEmpty() ? "пустой" : "не пустой") << endl;
			break;
		}
		case 4: {
			bool isForward = true;
			cout << "Вывести список в прямом порядке? (1 - да, 0 - нет): ";
			cin >> isForward;
			printList(isForward);
			break;
		}
		case 5: {
			if (!isEmpty()) {
				string value;
				bool isForwardSerch = true;
				cout << "Введите значение элемента, который нужно найти: ";
				getline(cin, value);
				cout << "Искать элемент в прямом порядке? (1 - да, 0 - нет): ";
				cin >> isForwardSerch;
				int pos = find(value, isForwardSerch);
				if (pos != -1) cout << "Элемент найден на позиции " << pos << endl;
				else cout << "Элемент не найден!" << endl;
				break;
			}
			else cout << "Список пустой!" << endl;
			break;
		}
		case 6: {
			clear();
			break;
		}
		case 7: {
			exit = true;
			break;
		}

	}
}


int main(){
	setlocale(LC_ALL, "Russian");
	init();
	bool exit = false;
	while (!exit)menu(exit);
	clear();
	return 0;
}
