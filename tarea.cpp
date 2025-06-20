#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

struct Producto{
	int codg;
	char nombre [30];
	float price;
	int stock;
	string categoria;
	string activo;
};

vector<Producto> productos;

void ingProducto(){
	Producto nuevo;
	
	cout<<"Ingrese codigo del producto:"<<endl;
	cin>>nuevo.codg;
	cout<<"Ingrese el nombre del producto:"<<endl;
	cin.ignore();
	cin.getline(nuevo.nombre,30);
	cout<<"Ingrese el precio del producto:"<<endl;
	cin>>nuevo.price;
	cout<<"Ingrese la cantidad del producto disponible: "<<endl;
	cin>>nuevo.stock;
	cout<<"Ingrese la categoria a la que pertenece el producto: "<<endl;
	cin>>nuevo.categoria;
	cout<<"El producto esta activo o eliminado? A/E"<<endl;
	cin>>nuevo.activo;
	
	productos.push_back(nuevo);
}

void mostrarProductosActivos() {
    if (productos.empty()) {
        cout << "No hay productos en stock" << endl;
        return;
    }

    cout << "Lista de productos activos: " << endl;
    for (const auto& producto : productos) {
        if (producto.activo == "A" || producto.activo == "a") {
            cout <<"* "<< producto.nombre << endl;
        }
    }
}

void mostrarProductosCatg(){
	if(productos.empty()){
		cout<<"No hay productos en stock"<<endl;
		return;
	}
	cout<<"Lista de categorias: ";
	for(size_t i=0;i < productos.size();i++){
		cout<<endl<<"---"<<i+1<<"---"<<endl<<productos[i].categoria<<" ---> "<<productos[i].nombre<<endl;
	}
	
}


void busCodigo() {
    int code;
    
    if (productos.empty()) {
        cout << "No hay productos en stock" << endl;
        return;
    }
    cout << "Ingrese el codigo del producto: ";
    cin >> code;
    for (size_t i = 0; i < productos.size(); i++) {
        if (code == productos[i].codg) {
            cout << "Producto encontrado: "<<endl<<"* "<<productos[i].nombre<<endl<<"* "<<productos[i].price<<endl<<"* "<<productos[i].stock<<endl<<"* "<<productos[i].categoria<<endl<<"producto Activo o Eliminado? A/E"<<endl<<"- "<<productos[i].activo<<endl;
        }
    }
}
void guardarEnArchivoBin(const string& nombreArchivo) {
	
    ofstream archivo(nombreArchivo, ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo para guardar datos.\n";
        return;
    }
    size_t cantidad = productos.size();
    archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));
    for (const auto& producto : productos) {
        archivo.write(reinterpret_cast<const char*>(&producto.codg), sizeof(producto.codg));
        archivo.write(producto.nombre, sizeof(producto.nombre));
        archivo.write(reinterpret_cast<const char*>(&producto.price), sizeof(producto.price));
        archivo.write(reinterpret_cast<const char*>(&producto.stock), sizeof(producto.stock));
        size_t categoriaSize = producto.categoria.size();
        archivo.write(reinterpret_cast<const char*>(&categoriaSize), sizeof(categoriaSize));
        archivo.write(producto.categoria.c_str(), categoriaSize);
        size_t activoSize = producto.activo.size();
        archivo.write(reinterpret_cast<const char*>(&activoSize), sizeof(activoSize));
        archivo.write(producto.activo.c_str(), activoSize);
    }
    archivo.close();
    cout << "Datos guardados en " << nombreArchivo << " exitosamente.\n";
}

void cargarDesdeArchivoBin(const string& nombreArchivo) {
	
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo para cargar datos.\n";
        return;
    }
    size_t cantidad;
    archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));
    productos.resize(cantidad);
    for (auto& producto : productos) {
        archivo.read(reinterpret_cast<char*>(&producto.codg), sizeof(producto.codg));
        archivo.read(producto.nombre, sizeof(producto.nombre));
        archivo.read(reinterpret_cast<char*>(&producto.price), sizeof(producto.price));
        archivo.read(reinterpret_cast<char*>(&producto.stock), sizeof(producto.stock));
        size_t categoriaSize;
        archivo.read(reinterpret_cast<char*>(&categoriaSize), sizeof(categoriaSize));
        producto.categoria.resize(categoriaSize);
        archivo.read(&producto.categoria[0], categoriaSize);
        size_t activoSize;
        archivo.read(reinterpret_cast<char*>(&activoSize), sizeof(activoSize));
        producto.activo.resize(activoSize);
        archivo.read(&producto.activo[0], activoSize);
    }
    archivo.close();
    cout << "Datos cargados desde " << nombreArchivo << " exitosamente.\n";
}


void eliminarProducto(int codigo) {
    for (auto& producto : productos) {
        if (producto.codg == codigo) {
            producto.activo = "E";
            cout << "Producto marcado como inactivo exitosamente.\n";
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}


int main(){
	int option;
	string nombreArchivo = "Inventario.bin";
	
	do{
		cout<<"-------Menu-------"<<endl;
		cout<<"1. Agregar un producto nuevo "<<endl;
		cout<<"2. Mostrar todos los productos activos "<<endl;
		cout<<"3. Mostrar productor por categoria "<<endl;
		cout<<"4. Buscar un producto por codigo "<<endl;
		cout<<"5. Modificar un producto "<<endl;
		cout<<"6. Eliminar un producto "<<endl;
		cout<<"7. Cargar datos desde el archivo binario "<<endl;
		cout<<"8. Guardar datos en el archivo binario "<<endl;
		cout<<"9. Salir"<<endl;
		cout<<" Ingrese su opcion: ";
		cin>>option;
		
		switch(option){
			case 1:
				ingProducto();
				break;
			case 2:
				mostrarProductosActivos();
				break;
			case 3:
				mostrarProductosCatg();
				break;
			case 4:
				busCodigo();
				break;
			case 5:{
                int codigo;
                float nuevoPrecio;
                int nuevoStock;
                string nuevaCategoria;

                cout << "Ingrese el codigo del producto a modificar: ";
                cin >> codigo;
                cout << "Ingrese el nuevo precio: ";
                cin >> nuevoPrecio;
                cout << "Ingrese el nuevo stock: ";
                cin >> nuevoStock;
                cout << "Ingrese la nueva categoria: ";
                cin.ignore();
                getline(cin, nuevaCategoria);

                for (auto& producto : productos) {
                    if (producto.codg == codigo) {
                        producto.price = nuevoPrecio;
                        producto.stock = nuevoStock;
                        producto.categoria = nuevaCategoria;
                        cout << "Producto modificado exitosamente.\n";
                        break;
                    }
                }
                break;
            }

			case 6:
				 {
                int codigo;
                cout << "Ingrese el codigo del producto a eliminar: ";
                cin >> codigo;
                eliminarProducto(codigo);
                break;
            }

				break;
			case 7:
				cargarDesdeArchivoBin(nombreArchivo);
				break;
			case 8:
				guardarEnArchivoBin(nombreArchivo);
				break;
			case 9:
				cout<<"Saliendo del programa"<<endl;
				break;
			default:
				cout<<"Ingrese una opcion valida"<<endl;
				break;
		}
	}while(option!=9);
	return 0;
}
