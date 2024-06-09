def leer_archivo(nombre_archivo):
    try:
        with open(nombre_archivo, encoding='utf-8') as archivo:
            datos = []
            for linea in archivo:
                linea = linea.rstrip('\n')
                lista = linea.split(',')
                datos.append(lista)
        return datos
    except Exception as e:
        print(f"Error al leer el archivo: {e}")
        return []

def separar(datos, indices):
    final = []
    for data in datos:
        seleccionados = []
        for i in indices:
            seleccionados.append(data[i])
        final.append(seleccionados)
    return final

def escribir_archivo(nombre_archivo, datos):
    try:
        with open(nombre_archivo, 'w', encoding='utf-8') as archivo:
            for linea in datos:
                archivo.write(','.join(linea) + '\n')
        print(f"Archivo '{nombre_archivo}' procesado correctamente.")
    except Exception as e:
        print(f"Error al escribir el archivo: {e}")

# Función principal
if __name__ == "__main__":
    datos_archivo = leer_archivo('./datafutbol.csv')
    if datos_archivo:
        indices_a_seleccionar = [3, 4, 5, 6, 7]
        datos_seleccionados = separar(datos_archivo, indices_a_seleccionar)
        escribir_archivo('./cmake-build-debug/datafutbol_process.csv', datos_seleccionados)
#hola cecilio