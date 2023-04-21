#include<iostream>
using namespace std;
const char *nombre_archivo = "notas.dat";
struct Estudiante{
	int codigo;
	char nombre[100];
	int nota[4];
	int promedio;
	string resultado;
};
void crear();
void leer();
void actualizar();
void borrar();

int main(){
	crear();
	char res1;
	cout<<"desea actualizar el archivo (s/n)"<<endl;
	cin>>res1;
	if(res1=='s'||res1=='S'){
		void actualizar();
	}
	char res2;
	cout<<"desea actualizar el archivo (s/n)"<<endl;
	cin>>res2;
	if(res2=='s'||res2=='S'){
		void borrar();	
	}
	
	system("pause");
}

void crear(){
	FILE* archivo = fopen(nombre_archivo, "a+b");
	char res;
	Estudiante estudiante;
	
	do{
		fflush(stdin);
		
		cout<<"ingrese Codigo"<<endl;
		cin>>estudiante.codigo;
		cin.ignore();
		
		cout<<"ingrese el nombre"<<endl;
		cin.getline(estudiante.nombre,50);
		
		for(int i=0; i<4; i++){
			cout<<"ingrese la nota "<<i<<endl;
			cin>>estudiante.nota[i];
		}
		estudiante.promedio = (estudiante.nota[0] + estudiante.nota[1] + estudiante.nota[2] + estudiante.nota[3]) / 4;
		
		cout<<"el promedio es de "<<estudiante.promedio<<endl;
		estudiante.promedio >= 60 ? estudiante.resultado = "aprobado" : estudiante.resultado = "reprobado";
		
		fwrite(&estudiante,sizeof(estudiante),1,archivo);
		cout<<"desea ingresar un nuevo estudiante(s/n)"<<endl;
		cin>>res;
	}while(res=='s'||res=='S');
	
	fclose(archivo);
	leer();
}
void leer(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo, "rb");
	if(!archivo){
		archivo = fopen(nombre_archivo,"w+b");
	}
	Estudiante estudiante;
	int id=0;
	fread(&estudiante,sizeof(estudiante),1,archivo);
	cout<<"____________________________________________"<<endl;
	cout<<"ID | Codigo | Nombres completos "<<endl;
	do{
		cout<<"ID"<<"|"<<estudiante.codigo<<"|"<<estudiante.nombre<<"|"<<endl;
		for(int i=0; i<4; i++){
			cout<<"nota "<<i<<" "<<estudiante.nota[i]<<" || ";
		}
		cout<<estudiante.promedio<<"||"<<estudiante.resultado<<endl;
		fread(&estudiante,sizeof(estudiante),1,archivo);
		id+=1;
	}while(feof(archivo)==0);
	fclose(archivo);
}
void actualizar(){
	FILE* archivo = fopen(nombre_archivo, "r+b");
	Estudiante estudiante;
	int id =0;
	cout<<"ingrese el ID de la persona que quiere modificar"<<endl;
	cin>>id;
	fseek(archivo,id * sizeof(estudiante),SEEK_SET);
		
		cout<<"ingrese Codigo"<<endl;
		cin>>estudiante.codigo;
		cin.ignore();
		
		cout<<"ingrese el nombre"<<endl;
		cin.getline(estudiante.nombre,50);
		
		cout<<"ingrese el apellido"<<endl;
		cin.getline(estudiante.nombre,50);
		
		fwrite(&estudiante,sizeof(estudiante),1,archivo);
		
	fclose(archivo);
	leer();
}
void borrar(){
	const char *nombre_archivoAux = "archivoAux.dat";
	FILE* archivo = fopen(nombre_archivo, "rb");
	FILE* archivoAux = fopen(nombre_archivoAux, "w+b");
	Estudiante estudiante;
	int id, id_n=0;
	
	cout<<"que elemento desea elimminar"<<endl;
	cin>>id;
	
	while(fread(&estudiante,sizeof(estudiante),1,archivo)){
		if (id_n != id){
			fread(&estudiante,sizeof(estudiante),1,archivoAux);
		}
		id_n++;
	}
	
	fclose(archivo);
	fclose(archivoAux);
	
	archivo = fopen(nombre_archivo, "rb");
	archivoAux = fopen(nombre_archivoAux, "wb");
	
	while(fread(&estudiante,sizeof(estudiante),1,archivoAux)){
		if (id_n != id){
			fread(&estudiante,sizeof(estudiante),1,archivo);
		}
		id_n++;
	}
	fclose(archivo);
	fclose(archivoAux);
	leer();
}
