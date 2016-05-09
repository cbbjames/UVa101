#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<cstdlib>
using namespace std;
int n;
vector<int> p[30];
struct Block {
	int height;
	int which;
};
Block* block;
void print() {
	for (int i = 0; i < n; i++) {
		printf("%d:", i);
		for (int j = 0; j < p[i].size(); j++)
			printf(" %d", p[i][j]);
		putchar('\n');
	}
}
void to_move(int a, int b) {
	p[block[b].which].push_back(a);
	p[block[a].which].pop_back();
	block[a].height = p[block[b].which].size();
	block[a].which = block[b].which;
	//print();
}
void to_clear(int a) {
	while (p[block[a].which].size() > block[a].height) {
		int x = p[block[a].which][p[block[a].which].size() - 1];
		p[x].push_back(x);
		p[block[a].which].pop_back();
		block[x].which = x;
		block[x].height = p[block[x].which].size();
	}
	//print();
}
void to_pile(int a,int b) {
	int k = block[a].height-1;
	int w = block[a].which;
	for (int i = k; i < p[w].size(); i++) {
		p[block[b].which].push_back(p[w][i]);
		block[p[w][i]].height = p[block[b].which].size();
		block[p[w][i]].which = block[b].which;
	}
	p[w].resize(k);
	//print();
}
void initial() {
	block = (Block*)malloc(n*sizeof(Block));
	for (int i = 0; i < n; i++) {
		p[i].push_back(block[i].which = i);
		block[i].height = 1;
		//cout << p[i][0]<<endl;
	}
}
int main(){
	cin >> n;
	initial();
	//int();
	int a, b;
	string v, prep;
	while (cin >> v &&v[0] != 'q'&&cin >> a >> prep >> b) {
		if (block[a].which == block[b].which) continue;
		if (v[0] == 'm') {
			to_clear(a);
			if (prep[1] == 'n'){
				to_clear(b);
				to_move(a, b);
			}
			else if (prep[1] == 'v') 
				to_move(a, b);
		}
		else if (v[0] == 'p') {
			if (prep[1] == 'n') {
				to_clear(b);
				to_pile(a, b);
			}
			else if (prep[1] == 'v')
				to_pile(a, b);
		}
	}
	print();
	//system("PAUSE");
	return 0;
}

