#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<array>
#include<string>
#include<stack>
#include<queue>
using namespace std;
struct node {
	int data;
	node *left, *right;
};
ifstream file("tree.txt");

class BiTree
{
public:
	node * root = nullptr;

	BiTree();
	BiTree(string S);
	BiTree(const char *S);
	BiTree(const BiTree &B);
	~BiTree();//¤Þ¤À
	void Preorder(node * T = nullptr);
	void Preorder_nonrecurrance();
	void Inorder(node * T = nullptr);
	void Levelorder();
	int Height();
	bool isExist(int ch);
	bool isBST();
	void InsertBST(int ch);
	void DeleteBST(int ch);
private:
	int height = 0;
	node *pre = nullptr;//JudgeBST()
	node *last;//DeleteBST
	node *target;//find
	void CreatBiTree(node * &T, string &S = string(""));//Construction use
	void CreatBiTree(node *&T, queue<int> &Q);
	void pre_copy(node *& R, const node *const &T);//Copy constrution use
	void pre_find(node * R, int ch, bool &F);
	void get_Height(node * R, int level);
	//void printsubtree(node *R, string mark);
	bool JudgeBST(node *R);
	void BST_find(node * R, int ch, bool &F);
};

BiTree::BiTree()
{
	queue<int> Q;
	int tmp;
	while (!file.eof())
		if (file >> tmp)
			Q.push(tmp);
	CreatBiTree(root, Q);
	//get_Height(root, 1);
}

BiTree::BiTree(string S)
{
	CreatBiTree(root, S);
	//get_Height(root, 1);
}

BiTree::BiTree(const char * S)
{
	CreatBiTree(root, string(S));
	//get_Height(root, 1);
}

BiTree::BiTree(const BiTree & B)
{
	pre_copy(root, B.root);
	//this->height = B.height;
}

BiTree::~BiTree()
{
}

void BiTree::CreatBiTree(node * &T, string &S)
{
	char ch;
	if (S == "")
	{
		cin >> ch;
		if (ch == '#')
			T = nullptr;
		else
		{
			T = new node;
			T->data = ch;
			CreatBiTree(T->left);
			CreatBiTree(T->right);
		}
	}
	else
	{
		ch = S[0];
		S.erase(S.begin());

		if (ch == '#')
			T = nullptr;
		else
		{
			T = new node;
			T->data = ch;
			CreatBiTree(T->left, S);
			CreatBiTree(T->right, S);
		}

	}
}

void BiTree::CreatBiTree(node * &T, queue<int>& Q)
{
	if (Q.empty())
	{
		perror("Input Error!");
		exit(0);
	}
	int tmp = Q.front();
	Q.pop();
	if (tmp == -1)
		T = nullptr;
	else
	{
		T = new node;
		T->data = tmp;
		CreatBiTree(T->left, Q);
		CreatBiTree(T->right, Q);
	}
}

void BiTree::pre_copy(node *& R, const node *const &T)
{
	if (T == nullptr)
		R = nullptr;
	else
	{
		R = new node;
		R->data = T->data;
		pre_copy(R->left, T->left);
		pre_copy(R->right, T->right);
	}
}

void BiTree::pre_find(node * R, int ch, bool &F)
{
	if (R&&F == false)
		if (R->data == ch)
		{
			F = true;
			target = R;
		}
		else
		{
			pre_find(R->left, ch, F);
			pre_find(R->right, ch, F);
		}
}

void BiTree::get_Height(node * R, int level)
{
	if (R)
	{
		if (height < level)
			height = level;
		get_Height(R->left, level + 1);
		get_Height(R->right, level + 1);
	}
}

bool BiTree::JudgeBST(node * R)
{
	if (R->left)
		if (!JudgeBST(R->left))
			return false;
	if (pre == nullptr)
		pre = R;
	else
	{
		if (pre->data>R->data)
			return false;
	}
	if (R->right)
		if (!JudgeBST(R->right))
			return false;
	return true;
}

void BiTree::BST_find(node * R, int ch, bool &F)
{
	if (F == false)
	{
		target = R;
		if (R->data == ch)
			F = true;
		else
		{
			if (R->data > ch)
			{
				if (R->left)
				{
					last = R;
					BST_find(R->left, ch, F);
				}
			}
			else
				if (R->right)
				{
					last = R;
					BST_find(R->right, ch, F);
				}
		}
	}
}

void BiTree::Preorder(node * T)
{
	if (!T)
		T = root;
	cout << T->data << ' ';
	if (T->left)
		Preorder(T->left);
	if (T->right)
		Preorder(T->right);
}

void BiTree::Preorder_nonrecurrance()
{
	node *T = root;
	stack<node *> s;
	s.push(nullptr);
	while (T)
	{
		cout << T->data << ' ';
		if (T->right)
			s.push(T->right);
		if (T->left)
			T = T->left;
		else
		{
			T = s.top();
			s.pop();
		}
	}
}

void BiTree::Inorder(node * T)
{
	if (T == nullptr)
		T = root;
	if (T->left)
		Inorder(T->left);
	cout << T->data << ' ';
	if (T->right)
		Inorder(T->right);
}

void BiTree::Levelorder()
{
	cout << "Levelorder" << endl;
	queue<node *> Q;
	Q.push(root);
	while (!Q.empty())
	{
		node *x = Q.front();
		cout << x->data << ' ';
		if (x->left)
			Q.push(x->left);
		if (x->right)
			Q.push(x->right);
		Q.pop();
	}
	cout << endl;
}

int BiTree::Height()
{
	get_Height(root, 1);
	return height;
}

bool BiTree::isExist(int ch)
{
	bool F = false;
	if (!isBST())
	{
		pre_find(root, ch, F);
		return F;
	}
	else
	{
		BST_find(root, ch, F);
		return F;
	}
}

bool BiTree::isBST()
{
	return JudgeBST(root);
}

void BiTree::InsertBST(int ch)
{
	node *tmp = new node;
	tmp->data = ch;
	tmp->left = nullptr;
	tmp->right = nullptr;

	if (root == nullptr)
		root = tmp;
	else
	{
		if (isExist(ch))
			puts("Key exists.");
		else
		{
			if (target->data > ch)
				target->left = tmp;
			else
				target->right = tmp;
		}
	}
	target = last = nullptr;
}

void BiTree::DeleteBST(int ch)
{
	node *tmp;
	if (root->data == ch)
	{
		tmp = root;
		if (root->left&&root->right)
			goto both;
		else if (root->left)
			root = root->left;
		else if (root->right)
			root = root->right;
		else
			root = nullptr;
		delete tmp;
	}
	else
	{
	both:	if (!isExist(ch))
			puts("No such node");
		else
		{
			tmp = target;
			if (target->left&&target->right)
			{
				tmp = tmp->right;
				node *q = target;
				while (tmp->left)
				{
					q = tmp;
					tmp = tmp->left;
				}
				if (q != target)
					q->left = tmp->right;
				else
					q->right = tmp->right;
				target->data = tmp->data;
			}
			else if (target->left)
			{
				if (last->left == target)
					last->left = target->left;
				else
					last->right = target->left;
			}
			else /*if (target->right)*/
			{
				if (last->left == target)
					last->left = target->right;
				else
					last->right = target->right;
			}
			delete tmp;
		}
	}
}

int main()
{
	BiTree B;
	BiTree A = B;
	A.DeleteBST(5);
	A.Levelorder();
	cout << "height: " << A.Height() << endl;
	//cout << (A.isExist(28) ? "true" : "false") << endl;
}