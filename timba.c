#include <stdio.h>

int main() { 

double p, a, imc;

printf("Digite seu peso em kg: ");
scanf("%lf", &p);

printf("Digite sua altura em metros: ");
scanf("%lf", &a);

imc = p / (a * a);

printf("Seu IMC é: %.2lf\n", imc);

if (imc < 18.5){
    printf("Você está abaixo do peso");
}
else if (imc < 24.9) {
    printf("Você está com o peso normal");
}
else if (imc < 29.9){
    printf("Você está acima do peso");
}
else if (imc > 30){
    printf("Você é obeso");
}
return 0;
}