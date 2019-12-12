#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#include<vector>
#include<algorithm>

using namespace std;
int MAXLVL = 3;
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

void addmiddle(node* prev_node, int n,person * head_person)
{
	if (prev_node == NULL)
	{
		cout << "the given previous node cannot be NULL";
		return;
	}

	node* new_node = new node;
	new_node->n = n;
	new_node->next = NULL;
	new_node->head_person = head_person;
	new_node->next = prev_node->next;
	prev_node->next = new_node;
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


class SkipListNode 
{ 
public: 
    int key; 
    SkipListNode **forward; 
    SkipListNode(int, int); 
}; 
  
SkipListNode::SkipListNode(int key, int level) 
{ 
    this->key = key; 
    forward = new SkipListNode*[level+1]; 
    memset(forward, 0, sizeof(SkipListNode*)*(level+1)); 
}; 
  
class SkipList 
{ 

    int MAXLVL; 
    float P; 
    int level; 
    SkipListNode *header; 
public: 
    SkipList(int, float); 
    int randomLevel(); 
    SkipListNode* createNode(int, int); 
	SkipListNode* searchElement(int);
    void insertElement(int); 
    void displayList(); 
}; 
  
SkipListNode* SkipList::searchElement(int key)
{ 
    SkipListNode *current = header; 
  
    for(int i = level; i >= 0; i--) 
    { 
        while(current->forward[i] && 
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
  
SkipList::SkipList(int MAXLVL, float P) 
{ 
    this->MAXLVL = MAXLVL; 
    this->P = P; 
    level = 0; 

    header = new SkipListNode(-1, MAXLVL); 
}; 
  
int SkipList::randomLevel() 
{ 
    float r = (float)rand()/RAND_MAX; 
    int lvl = 0; 
    while (r < P && lvl < MAXLVL) 
    { 
        lvl++; 
        r = (float)rand()/RAND_MAX; 
    } 
    return lvl; 
}; 
  
SkipListNode* SkipList::createNode(int key, int level) 
{ 
    SkipListNode *n = new SkipListNode(key, level); 
    return n; 
}; 

void SkipList::insertElement(int key) 
{ 
    SkipListNode *current = header; 
  
    SkipListNode *update[4]; 
    memset(update, 0, sizeof(SkipListNode*)*(MAXLVL+1)); 
 
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
            for (int i=level+1;i<rlevel+1;i++) 
                update[i] = header; 
                
            level = rlevel; 
        } 
  

        SkipListNode* n = createNode(key, rlevel); 

        for (int i=0;i<=rlevel;i++) 
        { 
            n->forward[i] = update[i]->forward[i]; 
            update[i]->forward[i] = n; 
        } 
        cout << "Successfully Inserted key " << key << "\n"; 
    } 
}; 
  
  
  SkipList convert_queue_to_skiplist(struct node* head_node)
{
	//creating a skiplist with maxlevel of 3 and p = 0.5
	SkipList lst(3, 0.5);
	node *temp = head_node;
	while(temp != NULL)
	{
		lst.insertElement(temp->n);
		temp = temp->next;
	}
	
	return lst;
}

  void SkipList::displayList()
  {
	  cout << "\n*****Skip List*****" << "\n";
	  for (int i = 0; i <= level; i++)
	  {
		  SkipListNode* node = header->forward[i];
		  cout << "Level " << i << ": ";
		  while (node != NULL)
		  {
			  cout << node->key << " ";
			  node = node->forward[i];
		  }
		  cout << "\n";
	  }
  };
  


int main()
{
	
	struct node* head_node1 = NULL;
	struct node* head_node2 = NULL;
	for (int i = 1; i <= 50; i++)
	{
		if (i == 1)
		{
			addfirst(&head_node1, i, NULL);

		}
		else
		{
			addend(&head_node1, i, NULL);
		}
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

	/*struct node* temp = head_node1;
	while (temp->next != NULL)
	{
		cout << temp->n << ' ';
		temp = temp->next;
	}
	cout << temp->n << '\n';
	temp = head_node2;
	while (temp->next != NULL)
	{
		cout << temp->n << ' ';
		temp = temp->next;
	}
	cout << temp->n;*/
	return 0;
}
