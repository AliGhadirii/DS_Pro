#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#include<vector>
#include<algorithm>

using namespace std;
int MAXLVL = 6;

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
	vector<stackNode*> stack_heads1;
	vector<stackNode*> stack_heads2;
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
			}
			else
			{
				addend_person(&temp, pass_id);
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
			stack_heads1.push_back(head_temp_stack);
		}
		search_result->head_person = temp;
	}
	/*cout<<"Number of stations of SECOND train in which passengers transfer : ";
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
			}
			else
			{
				addend_person(&head_person_temp, pass_id);
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

	}*/
	//------------------------------------------------------------------------------------ghatar 1 test----------------------------------------------------------------------
	mainlst.print_persons();
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
	return 0;
}
