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
		cout << "������ ������!" << endl;
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
			cout << "�������� " << targetValue << " ��� � ������!" << endl;
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
		cout << "������ ������!" << endl;
		return;
	}
	DynamicLinkedList* current = HEAD->next;
	while (current != HEAD && current->data != targetValue)
		current = current->next;
	if (current == HEAD) {
		cout << "�������� " << targetValue << " ��� � ������!" << endl;
		return;
	}	
	current->prev->next = current->next;
	current->next->prev = current->prev;
	delete current;
	cout << "������� ������" << endl;
}

void clear() {
	if (isEmpty()) {
		cout << "������ � ��� ������!" << endl;
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
	cout << "������ ������" << endl;
} 

int find(string value, bool isForwardSerch) {

	if (isEmpty()) {
		cout << "������ ������!" << endl;
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
	cout << endl << "����:" << endl;
	cout << "1. �������� ������� � ������" << endl;
	cout << "2. ������� ������� �� ������" << endl;

	cout << "3. �������� ������ �� ������" << endl;

	cout << "4. ������� ������" << endl;
	cout << "5. ����� �������� � ������" << endl;
	cout << "6. �������� ������" << endl;
	cout << "7. �����" << endl;

	int choice = validIntegerInput("");

	switch (choice) {
		case 1: {
			string value, targetValue;
			bool after = true;
				
			cout << "������� �������� ������ ��������: ";
			getline(cin, value);
			
			if (!isEmpty()) {
				cout << "�������� ������� �����? (1 - ��, 0 - ���): ";
				cin >> after;
				cin.ignore();

				cout << "������� �������� ��������, " << (after ? "�����" : "��") << " �������� ����� �������� ����� �������: ";
				getline(cin, targetValue);

				
			}
			push(value, targetValue, after);
			break;
		}
		case 2: {
			string targetValue;
			cout << "������� �������� ��������, ������� ����� �������: ";
			getline(cin, targetValue);
			pop(targetValue);
			break;
		}
		case 3: {
			cout << "������ " << (isEmpty() ? "������" : "�� ������") << endl;
			break;
		}
		case 4: {
			bool isForward = true;
			cout << "������� ������ � ������ �������? (1 - ��, 0 - ���): ";
			cin >> isForward;
			printList(isForward);
			break;
		}
		case 5: {
			if (!isEmpty()) {
				string value;
				bool isForwardSerch = true;
				cout << "������� �������� ��������, ������� ����� �����: ";
				getline(cin, value);
				cout << "������ ������� � ������ �������? (1 - ��, 0 - ���): ";
				cin >> isForwardSerch;
				int pos = find(value, isForwardSerch);
				if (pos != -1) cout << "������� ������ �� ������� " << pos << endl;
				else cout << "������� �� ������!" << endl;
				break;
			}
			else cout << "������ ������!" << endl;
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
