#include <stdio.h>
#include <string.h>
struct clientes
{
	char nombre[30];
	char dir[30];
	int numed;
	float saldo;
}cli[100];
FILE *fich;
float Pagar_cuenta(int);
int menu_user(int *, int);
int menu_maq(int *);
int menu_admin(int *);
int menu_admin2(int *);
int registros();
void escribir_estructs(int);
int main()
{
	fich=fopen("clientes.txt","a+b");
	int i, band=0, clave, o, q;
	int admin, a, e, x;
	int band2, f;
	x=registros();
	do{
		menu_admin(&a);
		switch(a){
		case 1:{
			printf("Dame tu clave\n");
			scanf("%d",&admin);
			if(admin==5090){
				do{
				menu_admin2(&e);
				if(e==1){
					band2=0;
					f=0;
					printf("Dame la clave de recibo\n");
					scanf("%d",&clave);
					do{
 					if (clave==cli[f].numed){
						printf("El usuario ya existe\n");
						band2=1;}
 						else {
							band2=0;
							f++;
						}
					}while(band2==0&&f<x);
					if(band2==0){
					cli[x].numed=clave;
					printf("Dame el nombre\n");
					//scanf("%['\n]",cli[x].nombre);					
					//scanf("%s",cli[x].nombre);
					//gets(cli[x].nombre);
					printf("Dame la dirección\n");
					//scanf("%['\n]",cli[x].dir);
					//scanf("%s",cli[x].dir);
					//gets(cli[x].dir);
					printf("Dame la deuda del cliente\n");
					scanf("%f",&cli[x].saldo);
					x++;
					}
				}
				}while(e!=2);
			}
			else printf("No eres administrador\n");
			break;}
		case 2:{
			if(x==1) printf("No hay usuarios que mostrar\n");
			else{
			i=0;
			menu_maq(&q);
			do{
			if (q==cli[i].numed){
				do{
				menu_user(&o, i);
				switch(o){
				case 1: printf("---------------------");
					printf("Nombre:%s\n", cli[i].nombre);
					printf("Direccion:%s\n",cli[i].dir);
					printf("Clave de recibo:%d\n",cli[i].numed);
					printf("----------------------");
					break;
				case 2: printf("----------------------");
					printf("Tu adeudo es:%.2f\n",cli[i].saldo);
					printf("---------------------");
					break;
				case 3: printf("Deuda:%.2f\n",cli[i].saldo);
					Pagar_cuenta(i);
					break;
				}
				}while(o!=4);
				printf("Gracias por utilizar nuestros servicios\n");
				printf("Que tenga un excelente dia");
				band=1;
			}
			else{band=0; i++;}
			}while(band==0&&i<x);
			if (band==0) printf("Clave no existente\n");
			}
			break;}
		case 3: {fich=fopen("clientes.txt","wb");
			if (fich==NULL) printf("Error en la escritura del fichero");
			else{
				escribir_estructs(x);
				fclose(fich);
			}
			break;}
		}
	}while(a!=3);
	fclose(fich);
}
float Pagar_cuenta(int a)
{
	float cambio, x;
	if (cli[a].saldo!=0){
	do{
	printf("Dame la cantidad\n");
	scanf("%f",&x);
	if (x < cli[a].saldo){
		cli[a].saldo-=x;
		printf("Te falta:$%.2f\n",cli[a].saldo);}
		else if (x>= cli[a].saldo){
		cambio=cli[a].saldo-x;	
		if (cambio==0){
	 		printf("--------------------------------\n");
			printf("¡Tu adeudo esta¡ PAGADO!!!\n");
			printf("--------------------------------\n");
			cli[a].saldo=0;}
			else{
			printf("--------------------------------\n");
			printf("Tu cambio es:$%.2f\n",-(cambio));
			printf("--------------------------------\n");
			printf("******PAGADO*******\n");
			cli[a].saldo=0;}	
		}
	}while(cli[a].saldo!=0);
	printf("--------------------------------\n");
	printf("Gracias por tu pago\n");
	printf("********************************\n");
	}
	else printf("Tu adeudo esta¡ *****PAGADO****\n");
}
int menu_user(int *opc, int i)
{
	printf("--------------------------------\n");
	printf("Â¿Que le gustarÃ­a hacer?\n");
	printf("--------------------------------\n");
	printf("1.-Consultar datos de cuenta\n2.-Verificar saldo\n");
	if (cli[i].saldo!=0)
	printf("3.-Pagar.\n");
	printf("4.-Salir de usuario\n");
	scanf("%d",opc);
}
int menu_maq(int *clave)
{
	printf("--------------------------------\n");
	printf("Bienvenido a CFEmÃ¡tico\n");
	printf("Dame la clave de tu recibo\n");
	scanf("%d",clave);
}
//Primera funcion en usar administrador
int menu_admin(int *cla)
{
	printf("CFEm@tico\n1.Administrador\n2.-Cliente\n3.-Salir\n");
	scanf("%d",cla);
}
//Primera funcion en usar, segundo menu del admin
int menu_admin2(int *clave)
{
	printf("¿Qué deseas hacer?\n");
	printf("1.-Alta de cliente\n");
	printf("2.-Salir al menu\n");
	scanf("%d",clave);
}
int registros()
{

	int i=1;
	fich=fopen("clientes.txt","rb");
	if (fich==NULL) printf("Error en la apertura del fichero");
	else{
		fread(&cli[i],sizeof(struct clientes),1,fich);
		while(!feof(fich)){
			fread(&cli[i],sizeof(struct clientes),1,fich);
			i++;
		}
		fclose(fich);
		return (i);
	}
}
void escribir_estructs(int i)
{
	int j;
	for(j=0;j<i;j++){
	fwrite(&cli[j], sizeof(struct clientes), 1, fich);
	}
}
