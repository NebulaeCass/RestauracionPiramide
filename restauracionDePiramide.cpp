#include <bits/stdc++.h>  
#define ll long long
using namespace std; 

template<typename T> void mostrarArreglo(vector<T> &v, int l, int r){
    for(int i=l; i<=r; i++){
        cout<<v[i]<<" "; 
    }
    cout<<"\n"; 
} 

bool validar(vector<int> &fijos, vector<ll> &alturas, int k){

    for(int i=1; i<=k; i++){
        if(alturas[fijos[i]] - alturas[fijos[i-1]] < fijos[i] - fijos[i-1]) return false;
    }

    return true; 
}

void descartar(vector<ll> &alturas, vector<int> &fijos, vector<bool> &esFijo, int n){
    int l = 0, r = 1;

    for(int i=1; i<=n+1; i++){
        if(!esFijo[i]){
            if(alturas[i] - alturas[fijos[l]] < i - fijos[l] || alturas[fijos[r]] - alturas[i] < fijos[r] - i){
                alturas[i] = -1;         
            }
        }
        else{
            l++, r++;
        }
    }
}

int crearSubsecuencia(vector<ll> &alturas, int n, vector<int> &posSubsecuencia){
    vector<int> dp(n+1); 
    dp[0] = 0; 

    for(int i=1; i<=n; i++){
        if(alturas[i] != -1){
            dp[i] = 1; 
            posSubsecuencia[i] = 0; 

            for(int j=1; j<i; j++){
                if(alturas[j] != -1 && alturas[i] - alturas[j] >= i - j && dp[j] + 1 > dp[i]){
                    dp[i] = dp[j] + 1; 
                    posSubsecuencia[i] = j; 
                }
            }
        }
    }

    

    return max_element(dp.begin(), dp.end()) - dp.begin(); 
}

void modificarEscalera(vector<ll> &alturas, vector<bool> &esFijo, int n){
    int i = 0;
    while(i <= n){
        if(!esFijo[i]) alturas[i] = alturas[i-1] + 1; 
        i++; 
    }
}

void mostrarEscalera(vector<ll> &alturas, int n){
    for(int i=1; i<=n; i++){
        cout<<alturas[i]<<" "; 
    }
}


int main(){
    ios_base::sync_with_stdio(false); 
    int i, n, k; 

    cin>>n>>k; 

    vector<ll> alturas(n+2);
    vector<int> fijos(k+2), posSubsecuencia(n+1); 
    vector<bool> esFijo(n+2, false); 

    alturas[0] = -1; 
    fijos[0] = 0; 
    esFijo[0] = true; 

    for(i=1; i<=n; i++){
        cin>>alturas[i]; 
    }

    for(i=1; i<=k; i++){
        cin>>fijos[i]; 
        esFijo[fijos[i]] = true; 
    }

    alturas[n+1] = 1e11; 
    fijos[k+1] = n+1;
    esFijo[n+1] = true; 

    sort(fijos.begin(), fijos.end());


    if(validar(fijos, alturas, k)){
        descartar(alturas, fijos, esFijo, n); 
        
        i = crearSubsecuencia(alturas, n, posSubsecuencia); 

        while(i > 0){
            esFijo[i] = true; 
            i = posSubsecuencia[i]; 
        }

        modificarEscalera(alturas, esFijo, n); 

        mostrarEscalera(alturas, n); 
    }
    else{
        cout<<-1; 
    }

    return 0;
}