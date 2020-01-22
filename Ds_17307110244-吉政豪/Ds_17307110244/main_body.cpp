#include"guild_code.h"

void MainPage();
void Page_1();
void Page_2();
void Page_3();
void ReturnPage(int sw);

void ShortesPath(int u,int v);
void AllPath(int u, int v);
void DFS(int u, int v, vector<int> s, int visited[]);
void EAdd();
void EDel();
void EModify();
void VAdd();
void VDel();

int main() {
	ReadCostAndPlace();
	cout << "welcome to Fudan University!\n" <<
		"Here is the Guild system for you.\n" <<
		"Please wait for seconds.\n" <<
		"Verison 1.00 author: Zhenghao Ji\n"<<endl;
	MainPage();
}
void MainPage() {
	cout << "Please enter a number\n" <<
		"1:查询景点相关信息.\n" <<
		"2:查询景点间路径.\n" <<
		"3:修改景点信息.\n" <<
		"q:关闭本系统.\n" <<endl;
	char sw = 0;
	cin >> sw;
	switch (sw){
		case '1':
			Page_1();
			break;
		case '2':
			Page_2();
			break;
		case '3':
			Page_3(); 
			break;
		case 'q':
			return;
			break;
		default:
			cout << "Please enter a legal num." << endl;
			MainPage();
			break;
	}
	return;
}
void Page_1() {
	int sw;
	for (size_t i = 0; i < NV; i++)
	{
		cout << i << ':' << place[i] << endl;
	}
	cin >> sw;
	if (sw<NV)
	{
		cout << place[sw]<<" : " << note[sw] << endl;
	}
	else
	{
		cout << "Please enter a legal num.\n";
		Page_1();
	}
	ReturnPage(1);
	return;
}
void Page_2() { 
	cout << "Page2." << endl;
	int start, end;
	cout << "Please enter the start and end place.\n";
	cin >> start >> end;
	int allorShortest = 1;
	cout << "Please enter 1 for the shortest path and 0 for all paths.\n";
	cin >> allorShortest;
	if (allorShortest==0)
	{
		AllPath(start, end);
	}
	else if(allorShortest==1)
	{
		ShortesPath(start, end);
	}
	ReturnPage(2);
	return;
}
void Page_3() {
	cout << "Page3." << endl;
	int sw;
	cout << "Please enter a number\n" <<
		"1:增加路径.\n" <<
		"2:删除路径.\n" <<
		"3:更新路径.\n" <<
		"4:增加景点.\n" <<
		"5:删除景点.\n" << endl;
	cin >> sw;
	switch (sw) {
	case 1:
		EAdd();
		break;
	case 2:
		EDel();
		break;
	case 3:
		EModify();
		break;
	case 4:
		VAdd();
		break;
	case 5:
		VDel();
		break;
	default:
		cout << "Please enter a legal num." << endl;
		break;
	}
	ReturnPage(3);
	return;
}
void ReturnPage(int sw){
	cout << "r:返回主页面\nq:退出本系统\n任意键继续查询." << endl;
	char isreturn;
	cin >> isreturn;
	if (isreturn == 'r')
	{
		MainPage();
		return;
	}
	else if(isreturn=='q')
	{
		return;
	}
	switch (sw)
	{
	case 1:
		Page_1();
		break;
	case 2:
		Page_2();
		break;
	case 3:
		Page_3();
		break;
	default:
		break;
	}
	return;
}

void ShortesPath(int u, int v) {
	bool S[MaxV];    // 判断是否已存入该点到S集合中
	int Dist[MaxV];
	int Pre[MaxV];
	int	n = NV;
	int i, j, k;
	float Min;
	for (i = 0; i < n; i++)
	{ //Dist、Pre和S数组初始化
		Dist[i] = cost[u][i];  //邻接矩阵第v行复制到Dist中
		S[i] = 0;
		if (Dist[i] < Maxint)
			Pre[i] = u;
		else Pre[i] = -1;
	}
	S[u] = 1;  //顶点v加入S集合中
	Pre[u] = 0;
	for (i = 0; i < n; i++)
	{  //从顶点v确定n-1条路径
		Min = Maxint;
		k = -1;
		for (j = 0; j < n; j++)
			if (S[j] == 0) {
				if (Dist[j] != 0 && Dist[j] < Min)
				{
					Min = Dist[j];
					k = j;
				}
			}
		if (k == -1) {
			break;
		}
		S[k] = 1;
		for (j = 0; j < n; j++)
			if (S[j] == 0 && cost[k][j] < Maxint)  //修改
				if (Dist[k] + cost[k][j] < Dist[j])
				{
					Dist[j] = Dist[k] + cost[k][j];
					Pre[j] = k;
				}
	}

	stack<int> st;
	int sum = 0;
	if (Dist[v]==Maxint)
	{
		cout << "There is no way between " << place[u] << " and " << place[v] << endl;
		return;
	}
	int end = v;
	while (u != v)
	{
		sum += cost[Pre[v]][v];
		v = Pre[v];
		st.push(v);
	}
	int tmp;
	while (!st.empty())
	{
		tmp = st.top();
		cout << place[tmp]<< "->";
		st.pop();
	}
	cout << place[end]<<endl;
	cout <<"All sum distance: " << sum << endl;
	return;
}

void AllPath(int u, int v){
	vector<int> st;
	int vis[MaxV];
	for (int i = 0; i < NV; i++)
	{
		vis[i] = 0;
	}
	DFS(u, v, st, vis);
}
void DFS(int u, int v, vector<int> s,int visited[]) {
	s.push_back(u);
	visited[u] = 1;
	if (u==v)
	{
		int sum = 0;
		for (int i = 0; i < s.size()-1; i++)
		{
			cout << s[i] << "->";
			sum += cost[s[i]][s[i + 1]];
		}
		cout << s[s.size() - 1];
		cout << " Sum is " << sum << endl;
		s.pop_back();
		return;
	}
	for (int i = 0; i < NV; i++)
	{
		if (visited[i]==0&&cost[u][i]<Maxint)
		{
			DFS(i, v, s, visited);
			visited[i] = 0;
		}
	}
	s.pop_back();
	return;
}
void EAdd(){
	int start, end,costij;
	cout << "Please enter the start,end and the cost.\n";
	cin >> start >> end >> costij;
	if (cost[start][end]<Maxint)
	{
		cout << "The path existed.\n";
	}
	else
	{
		cost[start][end] = costij;
		cost[end][start] = costij;
		cout << "The path has been added.\n";
	}
	return;
}
void EDel(){
	int start, end;
	cout << "Please enter the start,end.\n";
	cin >> start >> end;
	if (cost[start][end] == Maxint)
	{
		cout << "The path doesn`t exist.\n";
	}
	else
	{
		cost[start][end] = Maxint;
		cost[end][start] = Maxint;
		cout << "The path has been deled.\n";
	}
	return;
}
void EModify(){
	int start, end, costij;
	cout << "Please enter the start,end and the new cost.\n";
	cin >> start >> end >> costij;
	if (cost[start][end] < Maxint)
	{
		cost[start][end] = costij;
		cost[end][start] = costij;
		cout << "The path has been Modified.\n";
	}
	else
	{
		cout << "The path doesn`t exist.\n";
	}
	return;
}
void VAdd() {
	if (NV==MaxV)
	{
		cout << "OverRange.\nYou can`t add more Ver.\n";
		return;
	}
	string name;
	string str;
	cout << "Please enter the name and the note.\n";
	cin >> name>>str;
	place.push_back(name);
	note.push_back(str);
	for (int i = 0; i < NV; i++)
	{
		cost[NV][i] = Maxint;
	}
	NV++;
	return;
}
void VDel() {
	if (NV ==0)
	{
		cout << "OverRange.\nYou can`t del Ver.\n";
		return;
	}
	int s;
	cout << "Please enter the num.\n";
	cin >> s;
	place.erase(place.begin() + s);
	note.erase(note.begin() + s);
	//行变换
	for (int i = NV-1; i >s; i--)
	{
		for (int j = 0; j < NV; j++)
		{
			cost[i-1][j] = cost[i][j];
		}
	}
	//列修改
	for (int i = NV - 2; i > 0; i--)
	{
		for (int j = NV-1; j>s; j--)
		{
			cost[i][j-1] = cost[i][j];
		}
	}
	NV--;
	return;
}