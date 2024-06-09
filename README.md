# Manual para Configurar Claves SSH en Windows 11 y Enviarlas para Agregar a GitHub

## Paso 1: Abrir PowerShell

1. **Abrir PowerShell**:
   - En el menú de inicio de Windows 11, busquen "PowerShell" y abran la aplicación.

## Paso 2: Generar una Clave SSH

1. **Generar una nueva clave SSH**:
   - En la ventana de PowerShell, ejecuten el siguiente comando:


ssh-keygen -t rsa -b 4096 -C "su-email@example.com"

   - Cuando se les pregunte dónde guardar la clave, presionen `Enter` para aceptar la ubicación predeterminada (`C:\Users\su-usuario\.ssh\id_rsa`).
   - Luego, se les pedirá que ingresen una frase de contraseña. Pueden dejarlo vacío si no desean usar una frase de contraseña, aunque se recomienda por seguridad.

## Paso 3: Agregar la Clave SSH al ssh-agent

1. **Iniciar el ssh-agent en segundo plano**:
   - Ejecuten el siguiente comando en PowerShell:


Start-Service ssh-agent


2. **Añadir la clave SSH al ssh-agent**:
   - Ejecuten el siguiente comando en PowerShell:

sh ssh-add C:\Users\su-usuario.ssh\id_rsa


## Paso 4: Copiar la Clave SSH Pública

1. **Copiar la clave pública al portapapeles**:
   - Ejecuten el siguiente comando en PowerShell:

sh Get-Content C:\Users\su-usuario.ssh\id_rsa.pub | Set-Clipboard


## Notas Adicionales modofokas

- **Seguridad**: No compartan su clave privada (`id_rsa`). Solo deben compartir la clave pública (`id_rsa.pub`).
- **Acceso**: Una vez que la clave pública sea agregada a GitHub, podrán clonar el repositorio y hacer `push` usando SSH.
