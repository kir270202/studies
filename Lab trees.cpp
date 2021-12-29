#include<iostream>
#include<queue>
#include<stack>
using namespace std;

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};
Node* newNode(int val) {
	Node* temp = new Node();
	temp->data = val;
	temp->right = NULL;
	temp->left = NULL;
	return temp;
}
Node* insert(Node* root, int val) {
	if (root == NULL) {
		root = newNode(val);
	}
	else if (val < root->data)
		root->left = insert(root->left, val);
	else
		root->right = insert(root->right, val);
	return root;
}
void display(Node* root) {
	if (root != NULL) {
		display(root->left);
		cout << root->data << " -> ";
		display(root->right);
	}
}

void postorder(Node* node) { //Обратный обход
	if (node != NULL) {
		postorder(node->left);
		postorder(node->right);
		cout << node->data << " ";
	}
}
void inorder(Node* node) { //Симметричный обход
	if (node != NULL) {
		postorder(node->left);
		cout << node->data << " ";
		postorder(node->right);
	}
}

bool search(Node* root, int item) {
	if (root == NULL)
		return false;
	if (item == root->data) {
		return true;
	}
	else if (item < root->data) {
		search(root->left, item);
	}
	else if (item > root->data) {
		search(root->right, item);
	}
	else
		return false;
}

void printPostorder(struct Node* node)
{
	if (node == NULL)
		return;

	printPostorder(node->left);
	printPostorder(node->right);
	cout << node->data << " ";
}

void printInorder(struct Node* node)
{
	if (node == NULL)
		return;

	printInorder(node->left);
	cout << node->data << " ";
	printInorder(node->right);
}
void printPreorder(struct Node* node)
{
	if (node == NULL)
		return;

	cout << node->data << " ";
	printPreorder(node->left);
	printPreorder(node->right);
}


// Функция, печатающая общие элементы двух деревьев
void printCommon(Node* root1, Node* root2)
{
	// Создаем два стека для двух inorder обходов
	stack<Node*> stack1, s1, s2;

	while (1)
	{
		// помещаем узлы второго дерева в стек s1
		if (root1)
		{
			s1.push(root1);
			root1 = root1->left;
		}

		// помещаем узлы второго дерева в стек s2
		else if (root2)
		{
			s2.push(root2);
			root2 = root2->left;
		}

		//root1 и root2 здесь NULL
		else if (!s1.empty() && !s2.empty())
		{
			root1 = s1.top();
			root2 = s2.top();

			// Если текущие data в двух деревьях одинаковы
			if (root1->data == root2->data)
			{
				cout << root1->data << " ";
				s1.pop();
				s2.pop();

				// переход к inorder преемнику
				root1 = root1->right;
				root2 = root2->right;
			}

			else if (root1->data < root2->data)
			{
				// Если узел первого дерева меньше, чем узел второго дерево, тогда очевидно, что inorder наследники текущего узла могут иметь значения как у второго узла дерева. Таким образом, мы делаем pop() из s2
				s1.pop();
				root1 = root1->right;

				// root2 установлен в NULL, потому что нам нужны новые узлы дерева 1
				root2 = NULL;
			}
			else if (root1->data > root2->data)
			{
				s2.pop();
				root2 = root2->right;
				root1 = NULL;
			}
		}

		// Оба корня и стека пусты
		else {
			/*display(root1);
			cout << endl;*/
			/*display(root2);
			cout << endl;*/
			break;
		}
	}
}
int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Введите количество элементов"<<endl;
	int n, n2, n3, item;
	Node* root = NULL;
	Node* root2 = NULL;
	Node* root3 = NULL;
	cin >> n>>n2>>n3;
	cout << "Введите значения для вставки в дерево A"<<endl;
	for (int i = 0; i < n; i++) {
		cin >> item;
		root = insert(root, item); //сохраняет возвращаемые значения в самом корне каждый раз, когда это необходимо
	}

	cout << "Дерево A сформировано" << endl;
	display(root);
	cout << endl;
	cout << "Введите значения для вставки в дерево B" << endl;
	for (int i = 0; i < n2; i++) {
		cin >> item;
		root2 = insert(root2, item); //сохраняет возвращаемые значения в самом корне каждый раз, когда это необходимо
	}
	cout << "Дерево B сформировано"<<endl;
	display(root2);
	cout << endl;

	cout << "Введите значения для вставки в дерево C" << endl;
	for (int i = 0; i < n3; i++) {
		cin >> item;
		root3 = insert(root3, item); //сохраняет возвращаемые значения в самом корне каждый раз, когда это необходимо
	}
	cout << "Дерево C сформировано" << endl;
	display(root3);
	cout << endl;

	printPostorder(root);
	cout << endl;
	printInorder(root2);
	cout << endl;
	printPreorder(root3);
	cout << endl;
	/*cout << "Обратный обход дерева A: ";
	postorder(root);
	cout << endl;
	cout << "Симметричный обход дерева B: ";
	inorder(root2);
	cout << endl;*/
	cout << "Исключаем из A узлы, отсутствующие в B" << endl;;
	printCommon(root, root2);
	cout << endl;
	
	//Поиск элемента в дереве..
	cout << "Введите элемент для поиска (введите -1 для выхода из поиска)" << endl;
	do {
		cin >> item;
		if (search(root, item))
			cout << "Найдено.."<<endl;
		else
			cout << "Не найдено!"<<endl;
	} while (item != -1);
	return 0;
}