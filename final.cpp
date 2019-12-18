#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#include<vector>
#include<algorithm>

using namespace std;
int MAXLVL = 6;
class Queue {
	int front, rear, capacity;
	int size = 0;
	int* queue;
public:
	Queue(int c)
	{
		front = rear = 0;
		capacity = c;
		queue = new int;
	}

	~Queue() { delete[] queue; } 
	void insert_queue(int data)
	{
		if (capacity == rear) {
			cout<<"\nQueue is full\n";
			return;
		}
		else {
			queue[rear] = data;
			size++;
			rear++;
		}
		return;
	}
	void pop_queue()
	{
		
		if (front == rear) {
			cout<<"\nQueue is  empty\n";
			return;
		}
		else {
			for (int i = 0; i < rear - 1; i++) {
				queue[i] = queue[i + 1];
			}
			rear--;
			size--;
		}
		return;
	} 
	void print()
	{
		int i;
		if (front == rear) {
			cout<<"\nQueue is Empty\n";
			return;
		}
		for (i = front; i < rear; i++) {
			cout<< queue[i]<<' ';
		}
		cout << endl;
		return;
	}

	void get_front()
	{
		if (front == rear) {
			cout<<"\nQueue is Empty\n";
			return;
		}
		cout<<"\nFront Element is: "<<queue[front];
		return;
	}
	int get_size()
	{
		return size;
	}
};
struct stackNode 
{
    int data;
    stackNode * next;
};
void push_stack(stackNode** head_stack, int x)
{
	stackNode* newnode;
	newnode = new stackNode;
	newnode->data = x;
	if ((*head_stack) == NULL)
	{
		*head_stack = newnode;
		newnode->next = NULL;

	}
	else {
		newnode->next = *head_stack;
		*head_stack = newnode;
	}

	cout << "Datas pushed to stack" << endl;
}
int get_top(stackNode* head_stack)
{
	return head_stack->data;
}
void find_print_stack(vector<stackNode*> vectoserach,int key)
{
	for (int i = 0; i < vectoserach.size(); i++)
	{
		if (get_top(vectoserach[i]) == key)
		{
			stackNode* temp = vectoserach[i]->next;
			while (temp->next != NULL)
			{
				cout << temp->data << ' ';
			}
			cout << temp->data << endl;

		}
	}
}

struct person
{
	int id;
	struct person* next;
};
struct node
{
	int n;
	struct person* head_person;
	struct node* next;
}*head_node;

void addfirst(node ** head_node, int n,person * head_person)
{
	node* new_node = new node;
	new_node->n = n;
	new_node->next = NULL;
	new_node->head_person = head_person;
	new_node->next = (*head_node);
	(*head_node) = new_node;
}
void addfirst_person(person** head_node, int id)
{
	person* new_node = new person;
	new_node->id = id;
	new_node->next = NULL;
	new_node->next = (*head_node);
	(*head_node) = new_node;
}
void addend(node** head_node, int n,person* head_person)
{
	node* new_node = new node;
	new_node->n = n;
	new_node->head_person = head_person;
	new_node->next = NULL;
	if (*head_node == NULL)
	{
		*head_node = new_node;
		return;
	}
	node* temp = (*head_node);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return;
}
void addend_person(person** head_node, int id)
{
	person* new_node = new person;
	new_node->id = id;
	new_node->next = NULL;
	if (*head_node == NULL)
	{
		*head_node = new_node;
		return;
	}
	person* temp = (*head_node);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return;
}
class SkipListNode
{
public:
	int key;
	struct person* head_person;
	SkipListNode** forward;
	SkipListNode(int, int, struct person*);
};

SkipListNode::SkipListNode(int key, int level, struct person* head_person)
{
	this->key = key;
	this->head_person = head_person;
	forward = new SkipListNode * [level + 1];
	memset(forward, 0, sizeof(SkipListNode*) * (level + 1));
};

class SkipList
{

	int MAXLVL;
	float P;
	int level;
	SkipListNode* header;
public:
	SkipList(int, float);
	int randomLevel();
	SkipListNode* get_header();
	SkipListNode* createNode(int, int);
	SkipListNode* searchElement(int);
	void insertElement(int);
	void displayList();
	void print_persons();
};

SkipList::SkipList(int MAXLVL, float P)
{
	this->MAXLVL = MAXLVL;
	this->P = P;
	level = 0;

	header = new SkipListNode(-1, MAXLVL, NULL);
};

SkipListNode* SkipList::searchElement(int key)
{
	SkipListNode* current = header;

	for (int i = level; i >= 0; i--)
	{
		while (current->forward[i] &&
			current->forward[i]->key < key)
			current = current->forward[i];

	}

	current = current->forward[0];
	if (current and current->key == key)
	{
		cout << "Found key: " << key << "\n";
		return current;
	}


	else
	{
		cout << "Not Found\n";
		return NULL;
	}

};

int SkipList::randomLevel()
{
	float r = (float)rand() / RAND_MAX;
	int lvl = 0;
	while (r < P && lvl < MAXLVL)
	{
		lvl++;
		r = (float)rand() / RAND_MAX;
	}
	return lvl;
}
SkipListNode* SkipList::get_header()
{
	return this->header;
}
;

SkipListNode* SkipList::createNode(int key, int level)
{
	SkipListNode* n = new SkipListNode(key, level, NULL);
	return n;
};

void SkipList::insertElement(int key)
{
	SkipListNode* current = header;

	SkipListNode* update[7];
	memset(update, 0, sizeof(SkipListNode*) * (MAXLVL + 1));

	/*
		az bishtarin level shoro mikonim mirim jelo ta vaghti ke key mon bozorgtare key e node e badimon beshe vagarna badeesh ye level mirim payin
		o az aval dobare search mikonam
	*/
	for (int i = level; i >= 0; i--)
	{
		while (current->forward[i] != NULL &&
			current->forward[i]->key < key)
			current = current->forward[i];
		update[i] = current;
	}


	current = current->forward[0];
	if (current == NULL || current->key != key)
	{

		int rlevel = randomLevel();

		if (rlevel > level)
		{
			for (int i = level + 1; i < rlevel + 1; i++)
				update[i] = header;

			level = rlevel;
		}


		SkipListNode* n = createNode(key, rlevel);

		for (int i = 0; i <= rlevel; i++)
		{
			n->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = n;
		}
		cout << "Successfully Inserted key " << key << "\n";
	}
}
void SkipList::print_persons()
{
	SkipListNode* current = header->forward[0];
	while (current != NULL)
	{
		if (current->head_person != NULL)
		{
			person* temp2 = current->head_person;
			while (temp2->next != NULL)
			{
				cout << temp2->id << ' ';
				temp2 = temp2->next;
			}
			cout << temp2->id << ' ';
			cout << endl;
		}
		current = current->forward[0];
	}
	return ;
}
;


  

int main()
{
	int num1, station_num, num_pass, pass_id, num_foods, food_id[5], num2;
	vector<int> stations_transed(50, 0);
	vector<stackNode*> stack_heads1;
	vector<stackNode*> stack_heads2;
	
	cout << "please enter number of passengers of train1 and train2 : ";
	int n, m; cin >> n >> m;
	Queue train1_ids(n);
	Queue train2_ids(m);
	struct node* head_node2 = NULL;
	SkipList mainlst(6, 0.5);
	for (int i = 1; i <= 50; i++)
	{
		mainlst.insertElement(i);
	}
	vector<int> random_nums;
	while (random_nums.size() != 50)
	{
		int temp = (rand() % 50) + 1;
		while (find(random_nums.begin(), random_nums.end(), temp) != random_nums.end())
		{
			temp = (rand() % 50) + 1;
		}
		random_nums.push_back(temp);

	}
	for (int i = 0; i < 50; i++)
	{
		if (i == 0)
		{
			addfirst(&head_node2, random_nums[i], NULL);
		}
		else
		{
			addend(&head_node2, random_nums[i], NULL);
		}
	}
	system("cls");
	cout<<"Number of stations of FIRST train in which passengers transfer : ";
	cin>>num1;
	for (int i = 0; i < num1; i++)
	{
		cout << "Station number : ";
		cin >> station_num;
		cout << "Number of passengers transfered in this staion : ";
		cin >> num_pass;
		SkipListNode* search_result = mainlst.searchElement(station_num);
		person* temp = NULL;
		for (int j = 0; j < num_pass; j++)
		{
			cout << "Id of passenger " << j + 1 << " : ";
			cin >> pass_id;
			if (temp == NULL)
			{
				addfirst_person(&temp, pass_id);
				stations_transed[station_num - 1]++;
			}
			else
			{
				addend_person(&temp, pass_id);
				stations_transed[station_num - 1]++;
			}
			cout << "Number of foods of passgenger " << j + 1 << " : ";
			cin >> num_foods;
			stackNode* head_temp_stack = NULL;
			for (int q = 0; q < num_foods; q++)
			{
				cout << "Now enter the food id : " << q + 1 << " : ";
				cin >> food_id[q];
				push_stack(&head_temp_stack, food_id[q]);
			}
			push_stack(&head_temp_stack, pass_id);
			train1_ids.insert_queue(pass_id);
			stack_heads1.push_back(head_temp_stack);
		}
		search_result->head_person = temp;
	}
	system("cls");
	cout<<"Number of stations of SECOND train in which passengers transfer : ";
	cin>>num2;
	for(int i = 0; i < num2; i++)
	{
		cout<<"Station number : ";
		cin>>station_num;
		cout<<"Number of passengers transfered in this staion : ";
		cin>>num_pass;
		person* head_person_temp = NULL;
		for(int j = 0; j < num_pass; j++)
		{
			cout<<"Id of passenger "<< j + 1<<" : ";
			cin>>pass_id;
			if (head_person_temp == NULL)
			{
				addfirst_person(&head_person_temp, pass_id);
				stations_transed[station_num - 1]++;
			}
			else
			{
				addend_person(&head_person_temp, pass_id);
				stations_transed[station_num - 1]++;
			}
			cout<<"Number of foods of passgenger "<< j + 1<<" : ";
			cin>>num_foods;	
			stackNode* head_temp_stack = NULL;
			for(int q = 0; q < num_foods; q++)
			{
				cout<<"Now enter the food id : "<< q + 1<<" : ";
				cin>>food_id[q];
				push_stack(&head_temp_stack,food_id[q]);
			}
			push_stack(&head_temp_stack,pass_id);
			train2_ids.insert_queue(pass_id);
			stack_heads2.push_back(head_temp_stack);
		}
		node* temp = head_node2;
		while (temp->next != NULL)
		{
			if (temp->n == station_num)
			{
				temp->head_person = head_person_temp;
			}
			temp = temp->next;
		}

	}
	system("cls");
	cout << " passengers transfered in stations" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << i + 1 << ' : ' << stations_transed[i] << ' ';
	}
	cout << "\npassengers ramained in train1's last station: " << n - train1_ids.get_size();
	cout << "\npassengers ramained in train2's last station: " << m - train2_ids.get_size();
	cout << "\ntrain1's queue: "; 
	train1_ids.print();
	cout << "\ntrain2's queue: ";
	train2_ids.print();

	//------------------------------------------------------------------------------------ghatar 1 test----------------------------------------------------------------------
	//mainlst.print_persons();
	//------------------------------------------------------------------------------------ghatar 2 test-----------------------------------------------------------------------
	/*node* tempp = head_node2;
	while (tempp->next != NULL)
	{
		if (tempp->head_person != NULL)
		{
			person* temp2 = tempp->head_person;
			while (temp2->next != NULL)
			{
				cout << temp2->id << ' ';
				temp2 = temp2->next;
			}
			cout << temp2->id << ' ';
			cout << endl;
		}
		tempp = tempp->next;
	}
	for (int i = 0; i < stack_heads2.size(); i++)
	{
		stackNode* temp = stack_heads2[i];
		while (temp->next != NULL)
		{
			cout << temp->data << ' ';
			temp = temp->next;
		}
		cout << temp->data << ' ';
		cout << endl;
	}*/
	system("cls");
	cout<<"List of food codes ordered in the FIRST train :\n";
	cout<<"\n*********************************************\n";

	for(int q=0; q < train1_ids.get_size(); q++)
	{	
		cout<<"\n-------------------\n";
		while(stack_heads1[q]->next != NULL)
		{
			cout<<stack_heads1[q]->next->data<<endl;
			stack_heads1[q] = stack_heads1[q]->next;
		}
	}
	cout<<"List of food codes ordered in the SECOND train :\n";
	cout<<"\n*********************************************\n";

	for(int q=0; q < train2_ids.get_size(); q++)
	{	
		cout<<"\n-------------------\n";
		while(stack_heads2[q]->next != NULL)
		{
			cout<<stack_heads2[q]->next->data<<endl;
			stack_heads2[q] = stack_heads2[q]->next;
		}
	}

	
	return 0;
}
