def leer_archivo(nombre_archivo):
    archivo = open(nombre_archivo, encoding='utf-8')
    datos = []
    for linea in archivo:
        linea = linea.rstrip('\n')
        lista = linea.split(',')
        datos.append(lista)
    archivo.close()
    return datos

def separar(datos, indices):
    final = []
    for data in datos:
        seleccionados = []
        for i in indices:
            seleccionados.append(data[i])
        final.append(seleccionados)
    return final

def escribir_archivo(nombre_archivo, datos):
    archivo = open(nombre_archivo, 'w', encoding='utf-8')
    for linea in datos:
        archivo.write(','.join(linea) + '\n')
    archivo.close()

    #main function:

    datos_archivo = leer_archivo('Data.csv')
    indices_a_seleccionar = [3, 4, 5, 6, 7]
    datos_seleccionados = separar(datos_archivo, indices_a_seleccionar)
    escribir_archivo('datafutbol.csv', datos_seleccionados)