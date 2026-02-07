#include <stdio.h>
#include <math.h>
#define MAX 20

void normal(float x[MAX], float y[MAX], float c[MAX][MAX], float b[MAX], int n, int m) {
    int i, j, k, l1, l2;
    
    for(j=1; j<=m; j++) {
        for(k=1; k<=m; k++) {
            c[j][k] = 0.0;
            l1 = k + j - 2;
            for(i=1; i<=n; i++) {
                c[j][k] = c[j][k] + pow(x[i], l1);
            }
        }
    }
    
    for(j=1; j<=m; j++) {
        b[j] = 0.0;
        l2 = j - 1;
        for(i=1; i<=n; i++) {
            b[j] = b[j] + y[i] * pow(x[i], l2);
        }
    }
}

void gauss(int n, float a[MAX][MAX], float b[MAX], float x[MAX]) {
    int i, j, k;
    float pivot, factor, sum;
    
    for(k=1; k<=n-1; k++) {
        pivot = a[k][k];
        for(i=k+1; i<=n; i++) {
            factor = a[i][k] / pivot;
            for(j=k+1; j<=n; j++) {
                a[i][j] = a[i][j] - factor * a[k][j];
            }
            b[i] = b[i] - factor * b[k];
        }
    }
    
    x[n] = b[n] / a[n][n];
    for(k=n-1; k>=1; k--) {
        sum = 0.0;
        for(j=k+1; j<=n; j++) {
            sum = sum + a[k][j] * x[j];
        }
        x[k] = (b[k] - sum) / a[k][k];
    }
}

int main() {
    int n, mp, m, i;
    float x[MAX], y[MAX], c[MAX][MAX], a[MAX], b_coeff[MAX];
    
    printf("\n Input number of data points: ");
    scanf("%d", &n);
    
    printf("\n Input degree of required polynomial: ");
    scanf("%d", &mp);
    
    printf("\n Input x and y values (one set on each line): ");
    for(i=1; i<=n; i++) {
        scanf("%f%f", &x[i], &y[i]);
    }
    
    m = mp + 1;
    
    normal(x, y, c, b_coeff, n, m);
    gauss(m, c, b_coeff, a);
    
    printf("\n Polynomial Coefficients:\n");
    for(i=1; i<=m; i++) {
        printf("a[%d] = %15.6f\n", i-1, a[i]);
    }
    
    printf("\n The polynomial equation is: y = ");
    for(i=m; i>=1; i--) {
        if(i == m) {
            printf("%fx^%d", a[i], i-1);
        } else if(i == 1) {
            if(a[i] >= 0) {
                printf(" + %f", a[i]);
            } else {
                printf(" - %f", -a[i]);
            }
        } else {
            if(a[i] >= 0) {
                printf(" + %fx^%d", a[i], i-1);
            } else {
                printf(" - %fx^%d", -a[i], i-1);
            }
        }
    }
    

    return 0;
}