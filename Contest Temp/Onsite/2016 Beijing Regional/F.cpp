#include <bits/stdc++.h>

using namespace std;
struct Node{
	char tone;
	int cnt;
}tongji[5];
char raw[105][105];
map<char ,int > mp;
void init(){
	tongji[0]={'C',0};
	tongji[1]={'D',0};
	tongji[2]={'E',0};
	tongji[3]={'G',0};
	tongji[4]={'A',0};
	mp.clear();
}

bool cmp(Node&a,Node&b){
	if(a.cnt==b.cnt) return a.tone<b.tone;
	return a.cnt>b.cnt;
}

int main(){
	int N,M;
	while((cin >> N >> M) && N && M){
		mp.clear();
		for(int i=0;i<N;++i){
			for(int j=0;j<M;++j)
				cin >> raw[i][j], mp[raw[i][j]]+=1;
		}
		tongji[0]={'C',mp['C']};
		tongji[1]={'D',mp['D']};
		tongji[2]={'E',mp['E']};
		tongji[3]={'G',mp['G']};
		tongji[4]={'A',mp['A']};
		sort(tongji,tongji+5,cmp);
		for(int i=0;i<5;++i)
		{
			if (tongji[i].cnt==0)break;
			if(i)cout << ' ';
			cout << tongji[i].tone << ' ' << tongji[i].cnt;
		}
		cout << endl;
	}
	return 0;
}