#include <bits/stdc++.h>

using namespace std;

typedef struct {
    int x,w,y,h;
} rectangle;

typedef pair<int,int> ii;
#define INF 112345678
#define MAXN 1123
vector<ii> adjList[MAXN];

rectangle rect[MAXN];
int N;
int xi,yi,xf,yf;
int dist[MAXN];

int dijkstra(int s, int t, int n, int dist[]) {
	for(int i = 0; i <= n; i++) dist[i] = INF;
	set<ii> pq;
	dist[s] = 0;
	pq.insert(ii(0, s));
	while(!pq.empty()) {
		int u = pq.begin()->second;
		pq.erase(pq.begin());
		for(int i=0; i<(int)adjList[u].size(); i++) {
			int v = adjList[u][i].second;
			int w = adjList[u][i].first;
			if (dist[v] > dist[u] + w) {
				pq.erase(ii(dist[v], v));
				dist[v] = dist[u] + w;
				pq.insert(ii(dist[v], v));
			}
		}
	}
	return dist[t];
}

int calculateDistance(int p1, int s1, int p2, int s2) {
    if (p1+s1 < p2) {
        return p2-(p1+s1);
    }
    if (p1 > p2+s2) {
        return p1-(p2+s2);
    }
    return 0;
}

void fillDistances() {
    int d;
    for (int i=0; i<N; ++i) {
        for (int j=i; j<N; ++j) {
            d = calculateDistance(rect[i].x,rect[i].w,rect[j].x,rect[j].w);
            d += calculateDistance(rect[i].y,rect[i].h,rect[j].y,rect[j].h);
            adjList[i].push_back(ii(d,j));
            adjList[j].push_back(ii(d,i));
        }
    }
}

int main() {
    int x1,y1,x2,y2;

    cin >> xi >> yi >> xf >> yf;
    cin >> N;

    for (int i=0; i < N; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        rect[i].x=min(x1,x2);
        rect[i].y=min(y1,y2);
        rect[i].w=abs(x1-x2);
        rect[i].h=abs(y1-y2);
    }

    N+=2;
    rect[N-2].x = xi;
    rect[N-2].y = yi;
    rect[N-2].w = rect[N-2].h = 0;

    rect[N-1].x = xf;
    rect[N-1].y = yf;
    rect[N-1].w = rect[N-1].h = 0;

    fillDistances();

    cout << dijkstra(N-2,N-1,N,dist) << endl;

    return 0;
}
