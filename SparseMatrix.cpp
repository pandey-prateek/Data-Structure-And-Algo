#include <algorithm>
#include <iostream>
using namespace std;

template <typename T>
class Index
{
public:
	int r;
	int c;
	T val;
};
template <typename T>
bool comp(Index<T> i1, Index<T> i2)
{
	if (i1.r < i2.r || i1.r == i2.r && i1.c < i2.c)
	{
		return true;
	}
	return false;
}

template <typename T>
class Matrix
{
public:
	int N;
	int M;
	Index<T> *mat;

	int size = 0;

	void fillMatrix()
	{

		cin >> N >> M;
		if(N<1||M<1){
			cout<<"Not a valid dimension for Matrix"<<endl;
			return;
		}

		mat = new Index<T>[N * M];
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				int k;
				cin >> k;
				if (k)
				{
					mat[size].r = i;
					mat[size].c = j;
					mat[size].val = k;
					size++;
				}
			}
		}
	}
	void transpose()
	{

		int t = N;
		N = M;
		M = t;

		for (int i = 0; i <= size; i++)
		{
			int t = mat[i].r;
			mat[i].r = mat[i].c;
			mat[i].c = t;
		}
		sort(mat, mat + size, comp<T>);
	}
	void print()
	{

		int ret = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (mat[ret].r == i && mat[ret].c == j)
				{
					cout << mat[ret].val << " ";
					ret++;
				}
				else
				{
					cout << 0 << " ";
				}
			}
			cout << endl;
		}
	}
	static void add(Matrix m1, Matrix m2)
	{
		if (m1.N != m2.N || m1.M != m2.M)
		{
			cout << "Matrices not compatible";
			return;
		}
		int j1 = 0, j2 = 0;
		Index<T> mat3[m1.size + m2.size];
		int i3 = 0;
		int size = 0;
		while (j1 < m1.size && j2 < m2.size)
		{
			if (m1.mat[j1].r < m2.mat[j2].r)
			{
				mat3[i3++] = m1.mat[j1++];
			}
			else if (m1.mat[j1].r > m2.mat[j2].r)
			{
				mat3[i3++] = m2.mat[j2++];
			}
			else
			{
				if (m1.mat[j1].c < m2.mat[j2].c)
				{
					mat3[i3++] = m1.mat[j1++];
				}
				else if (m1.mat[j1].c > m2.mat[j2].c)
				{
					mat3[i3++] = m2.mat[j2++];
				}
				else
				{
					if (m1.mat[j1].val + m1.mat[j2].val)
					{
						mat3[i3] = m1.mat[j1];
						mat3[i3].val = m1.mat[j1].val + m1.mat[j2].val;
						i3++;
					}
					j1++;
					j2++;
				}
			}
		}
		while (j1 < m1.size)
		{

			mat3[i3++] = m1.mat[j1++];
		}
		while (j2 < m2.size)
		{

			mat3[i3++] = m2.mat[j2++];
		}
		int ret = 0;
		for (int i = 0; i < m1.N; i++)
		{
			for (int j = 0; j < m1.M; j++)
			{
				if (mat3[ret].r == i && mat3[ret].c == j)
				{
					cout << mat3[ret].val << " ";
					ret++;
				}
				else
				{
					cout << 0 << " ";
				}
			}
			cout << endl;
		}
	}
	static void multiply(Matrix m1, Matrix m2)
	{
		m2.transpose();
		if (m1.M != m2.M)
		{
			cout << "Matrices not compatible";
			return;
		}
		Matrix m;
		m.N = m1.N;
		m.M = m2.N;
		m.mat = new Index<T>[m.N * m.M];
		Index<T> indx[m1.size * m2.size];

		int z = 0;
		for (int i = 0; i < m1.size; i++)
		{
			for (int j = 0; j < m2.size; j++)
			{
				if (m1.mat[i].c == m2.mat[j].c)
				{

					indx[z].r = m1.mat[i].r;
					indx[z].c = m2.mat[j].r;
					indx[z].val = m1.mat[i].val * m2.mat[j].val;
					z++;
				}
			}
		}
		sort(indx, indx + z, comp<T>);
		Index<T> prev = indx[0];
		int size = 0;
		
		for (int i = 1; i < z; i++)
		{
			if (prev.r == indx[i].r && prev.c == indx[i].c)
			{
				prev.val += indx[i].val;
				
			}
			else
			{	
				m.mat[size++] = prev;
				prev = indx[i];
				
			}
		}
		m.mat[size++] = prev;

		m.size = size;
		m.print();
	}
};
template <typename T>
struct LIndex
{
	int r;
	int c;
	T val;
	LIndex *next;
	LIndex(int i, int j, T value)
	{
		r = i;
		c = j;
		val = value;
		next = NULL;
	}
};
template <class T>
LIndex<T> *merge(LIndex<T> *temp1, LIndex<T> *temp2)
{
	LIndex<T> *h = NULL;
	LIndex<T> *temp3 = NULL;
	while (temp1 && temp2)
	{
		if (temp1->r < temp2->r)
		{
			LIndex<T> *temp = temp1;
			temp1 = temp1->next;
			temp->next = NULL;
			if (h)
			{
				temp3->next = temp;
				temp3 = temp;
			}
			else
			{
				h = temp;
				temp3 = temp;
			}
		}
		else if (temp1->r > temp2->r)
		{
			LIndex<T> *temp = temp2;
			temp2 = temp2->next;
			temp->next = NULL;
			if (h)
			{
				temp3->next = temp;
				temp3 = temp;
			}
			else
			{
				h = temp;
				temp3 = temp;
			}
		}
		else
		{
			if (temp1->c < temp2->c)
			{
				LIndex<T> *temp = temp1;
				temp1 = temp1->next;
				temp->next = NULL;
				if (h)
				{
					temp3->next = temp;
					temp3 = temp;
				}
				else
				{
					h = temp;
					temp3 = temp;
				}
			}
			else if (temp1->c > temp2->c)
			{
				LIndex<T> *temp = temp2;
				temp2 = temp2->next;
				temp->next = NULL;
				if (h)
				{
					temp3->next = temp;
					temp3 = temp;
				}
				else
				{
					h = temp;
					temp3 = temp;
				}
			}
			else
			{
				LIndex<T> *temp = temp2;
				temp2 = temp2->next;
				temp->next = NULL;
				if (h)
				{
					temp3->next = temp;
					temp3 = temp;
				}
				else
				{
					h = temp;
					temp3 = temp;
				}
			}
		}
	}
	if (temp1)
	{

		if (h)
		{
			temp3->next = temp1;
		}
		else
		{
			h = temp1;
		}
	}
	if (temp2)
	{

		if (h)
		{
			temp3->next = temp2;
		}
		else
		{
			h = temp2;
		}
	}
	return h;
}
template <typename T>
void sortlist(LIndex<T> **head)
{
	if ((*head == NULL) || ((*head)->next == NULL))
	{
		return;
	}
	LIndex<T> *h1 = *head;
	LIndex<T> *h2;
	LIndex<T> *fast = (*head)->next;
	LIndex<T> *slow = *head;
	while (fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	h2 = slow->next;
	slow->next = NULL;
	sortlist(&h1);
	sortlist(&h2);
	*head = merge(h1, h2);
}
template <class T>
class LinkedMatrix
{
public:
	int N;
	int M;
	struct LIndex<T> *mat = NULL;

	int size = 0;

	void fillMatrix()
	{

		cin >> N >> M;
		if(N<1||M<1){
			cout<<"Not a valid dimension for Matrix";
			return;
		}
		LIndex<T> *temp = NULL;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				int k;
				cin >> k;
				if (k)
				{
					LIndex<T> *node = new LIndex(i, j, k);
					if (mat)
					{
						temp->next = node;
						temp = temp->next;
					}
					else
					{
						mat = node;
						temp = node;
					}
					size++;
				}
			}
		}
	}
	void transpose()
	{

		int t = N;
		N = M;
		M = t;

		LIndex<T> *node = mat;
		while (node)
		{
			int t = node->c;
			node->c = node->r;
			node->r = t;
			node = node->next;
		}
		sortlist(&mat);
	}
	void print()
	{

		LIndex<T> *temp = mat;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (temp && temp->r == i && temp->c == j)
				{
					cout << temp->val << " ";
					temp = temp->next;
				}
				else
				{
					cout << 0 << " ";
				}
			}
			cout << endl;
		}
	}
	static void add(LinkedMatrix *m1, LinkedMatrix *m2)
	{
		if (m1->N != m2->N || m1->M != m2->M)
		{
			cout << "Matrices not compatible";
			return;
		}
		LinkedMatrix m3;
		m3.N = m2->N;
		m3.M = m1->M;
		m3.mat = NULL;
		LIndex<T> *temp1 = m1->mat;
		LIndex<T> *temp2 = m2->mat;
		LIndex<T> *temp3 = m3.mat;
		int size = 0;
		while (temp1 && temp2)
		{
			if (temp1->r < temp2->r)
			{
				LIndex<T> *temp = temp1;
				temp1 = temp1->next;
				temp->next = NULL;
				if (m3.mat)
				{
					temp3->next = temp;
					temp3 = temp;
				}
				else
				{
					m3.mat = temp;
					temp3 = temp;
				}
			}
			else if (temp1->r > temp2->r)
			{
				LIndex<T> *temp = temp2;
				temp2 = temp2->next;
				temp->next = NULL;
				if (m3.mat)
				{
					temp3->next = temp;
					temp3 = temp;
				}
				else
				{
					m3.mat = temp;
					temp3 = temp;
				}
			}
			else
			{
				if (temp1->c < temp2->c)
				{
					LIndex<T> *temp = temp1;
					temp1 = temp1->next;
					temp->next = NULL;
					if (m3.mat)
					{
						temp3->next = temp;
						temp3 = temp;
					}
					else
					{
						m3.mat = temp;
						temp3 = temp;
					}
				}
				else if (temp1->c > temp2->c)
				{
					LIndex<T> *temp = temp2;
					temp2 = temp2->next;
					temp->next = NULL;
					if (m3.mat)
					{
						temp3->next = temp;
						temp3 = temp;
					}
					else
					{
						m3.mat = temp;
						temp3 = temp;
					}
				}
				else
				{
					LIndex<T> *t2 = temp2;
					LIndex<T> *t1 = temp1;
					temp2 = temp2->next;
					temp1 = temp1->next;
					t1->next = NULL;
					t2->next = NULL;
					LIndex<T> *temp = new LIndex(t1->r, t1->c, t1->val + t2->val);
					free(t1);
					free(t2);
					if (m3.mat)
					{
						temp3->next = temp;
						temp3 = temp;
					}
					else
					{
						m3.mat = temp;
						temp3 = temp;
					}
				}
			}
		}
	if (temp1)
		{

			
			if (m3.mat)
			{
				temp3->next = temp1;
				
			}
			else
			{
				m3.mat = temp1;
				
			}
		}
		if (temp2)
		{

			if (m3.mat)
			{
				temp3->next = temp2;
				
			}
			else
			{
				m3.mat = temp2;
				
			}
		}
		m3.print();
	}
	static void multiply(LinkedMatrix m1, LinkedMatrix m2)
	{
		m2.transpose();
		if (m1.M != m2.M)
		{
			cout << "Matrices not compatible";
			return;
		}
		LinkedMatrix m;
		m.N = m1.N;
		m.M = m2.N;
		m.mat = NULL;
		LIndex<T> *indx = NULL;
		LIndex<T> *temp1 = m1.mat;
		LIndex<T> *temp2 = m2.mat;
		LIndex<T> *temp3 = NULL;

		int z = 0;
		while (temp1)
		{
			LIndex<T> *temp2 = m2.mat;
			while (temp2)
			{
				if (temp1->c == temp2->c)
				{
					LIndex<T> *temp = new LIndex(temp1->r, temp2->r, temp1->val * temp2->val);
					if (!indx)
					{
						indx = temp;
						temp3 = temp;
					}
					else
					{
						temp3->next = temp;
						temp3 = temp;
					}
				}
				temp2 = temp2->next;
			}
			temp1 = temp1->next;
		}
		sortlist(&indx);
		LIndex<T> *prev = indx;
		LIndex<T> *curr = indx->next;
		int size = 0;
		while (curr)
		{
			if (prev->r == curr->r && prev->c == curr->c)
			{
				LIndex<T> *temp = curr;
				prev->val = prev->val + curr->val;
				curr = curr->next;
				prev->next = curr;
				temp->next = NULL;
				free(temp);
				size++;
			}
			else
			{
				prev = curr;
				curr = curr->next;
			}
		}

		m.mat = indx;

		m.size = size;
		m.print();
	}
};
int main()
{
	int q;

	while (true)
	{
		cout << "1.Array \n2.Linked List\n";
		cin >> q;
		if (q == 1)
		{
			int k;
			cout << "1.Addition \n2.Transpose\n3.Multiplication\n";
			cin >> k;
			if (k == 1)
			{
				Matrix<int> m1;
				Matrix<int> m2;
				m1.fillMatrix();
				m2.fillMatrix();
				Matrix<int>::add(m1, m2);
			}
			else if (k == 2)
			{
				Matrix<int> m1;
				m1.fillMatrix();
				m1.transpose();
				m1.print();
			}
			else if (k == 3)
			{
				Matrix<int> m1;
				Matrix<int> m2;
				m1.fillMatrix();
				m2.fillMatrix();
				Matrix<int>::multiply(m1, m2);
			}
			else
			{
				cout << "Wrong choice\n";
			}
		}
		else if (q == 2)
		{
			int k;
			cout << "1.Addition \n 2.Transpose\n 3.Multiplication\n";
			cin >> k;
			if (k == 1)
			{
				LinkedMatrix<int> m1;
				LinkedMatrix<int> m2;
				m1.fillMatrix();
				m2.fillMatrix();
				LinkedMatrix<int>::add(&m1, &m2);
			}
			else if (k == 2)
			{
				LinkedMatrix<int> m1;
				m1.fillMatrix();
				m1.transpose();
				m1.print();
			}
			else if (k == 3)
			{
				LinkedMatrix<int> m1;
				LinkedMatrix<int> m2;
				m1.fillMatrix();
				m2.fillMatrix();
				LinkedMatrix<int>::multiply(m1, m2);
			}
			else
			{
				cout << "Wrong choice\n";
			}
		}
		else
		{
			cout << "Wrong choice\n";
		}
	}

	return 0;
}
