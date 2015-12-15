    #include <cstdio>
    #include <cstring>
    int n;
    int c[42][42], f[42][42], p[42], q[42];
    bool v[42];
    bool busca(int s, int t) {
        int h = 0, i, j, tl = 0;
        memset(v, 0, n);
        q[tl++] = s;
        v[s] = 1;
        p[s] = -1;
        while(!v[t] && h != tl) {
            i = q[h++];
            for(j = 0; j < n; j++) {
                if(!v[j] && c[i][j] - f[i][j] > 0) {
                    q[tl++] = j;
                    v[j] = 1;
                    p[j] = i;
                }
            }
        }
        return v[t];
    }
    int maxfluxo(int s, int t) {
        int i, fluxo = 0;
        memset(f, 0, sizeof(f));
        while(busca(s, t)) {
            int cf = 1<<10;
            for(i = t; p[i] >= 0; i = p[i]){
                int temp = c[p[i]][i] - f[p[i]][i];
                if(temp < cf) cf = temp;
            }
            for(i = t; p[i] >= 0; i = p[i]) {
                f[p[i]][i] += cf;
                f[i][p[i]] -= cf;
            }
            fluxo += cf;
        }
        return fluxo;
    }
    int pts[42], m[42][42], ml[42];
    const char *resp[2] = {"N","Y"};
    int main(void){
        int a, b, G, M, N;
        char r;
        bool flag;
        while(scanf("%d %d %d",&N, &M, &G) && N){
            n = N + 2;
            int partida = (N - 1) * M;
            int fonte = n - 1;
            int destino = n - 2;
            flag = 0;
            for(int i = 0; i < n; ++i){
                pts[i] = 0;
                ml[i] = partida;
                for(int j = 0; j < n; ++j)
                    c[i][j] = m[i][j] = 0;
            }
            for(int i = 0; i < G; ++i){
                scanf("%d %c %d", &a, &r, &b);
                if(r == '<') pts[b] += 2;
                else ++pts[a], ++pts[b];
                --ml[a], --ml[b];
                m[a][b] = m[b][a] = m[a][b] + 1;
            }
            for(int i = 1; i < N; ++i){
                int x = M - m[0][i];
                pts[0] += (x << 1);
                G += x;
                ml[i] -= x;
                m[0][i] = m[i][0] = 0;
            }
            for(int i = 1; i < N; ++i){
                int s = 0;
                for(int j = i + 1; j < N; ++j){
                    int x = (M - m[i][j]) << 1;
                    s += x;
                    c[i][j] = x;
                }
                c[fonte][i] = s;
                int a = pts[0] - pts[i] - 1;
                int b = ml[i] << 1;
                if(a < 0){ flag = 1; break; }
                if(a < b) c[i][destino] = a;
                else c[i][destino] = b;
            }
            if(!flag){
                int fluxo = maxfluxo(fonte, destino);
                int desloc = partida* N - 2 * G;
                puts(resp[fluxo == desloc]);
            } else printf("N\n");
        }
        return 0;
    }
