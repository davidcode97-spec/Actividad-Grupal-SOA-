# Ejercicio 2 - Menu gestion de usuarios

function Get-NombreUsuario {
    $usuario = Read-Host "Introduce el nombre de usuario"
    return $usuario
}

function Test-UsuarioExiste {
    param([string]$usuario)
    $existe = (Get-LocalUser -Name $usuario -ErrorAction SilentlyContinue) -ne $null
    return $existe
}

function Get-UIDUsuario {
    param([string]$usuario)
    $obj = Get-LocalUser -Name $usuario -ErrorAction SilentlyContinue
    if ($obj) {
        return $obj.SID
    }
    return $null
}

do {
    Write-Host ""
    Write-Host "============================" -ForegroundColor Cyan
    Write-Host "  MENU DE GESTION DE USUARIOS" -ForegroundColor Cyan
    Write-Host "============================" -ForegroundColor Cyan
    Write-Host "1. Verificar la existencia de un usuario"
    Write-Host "2. Conocer el UID (SID) de un usuario"
    Write-Host "3. Salir"
    Write-Host ""
    $opcion = Read-Host "Selecciona una opcion (1-3)"

    switch ($opcion) {
        "1" {
            $usuario = Get-NombreUsuario
            if (Test-UsuarioExiste -usuario $usuario) {
                Write-Host "El usuario '$usuario' SI existe en el sistema." -ForegroundColor Green
            } else {
                Write-Host "El usuario '$usuario' NO existe en el sistema." -ForegroundColor Red
            }
        }
        "2" {
            $usuario = Get-NombreUsuario
            $uid = Get-UIDUsuario -usuario $usuario
            if ($uid) {
                Write-Host "El UID (SID) del usuario '$usuario' es: $uid" -ForegroundColor Green
            } else {
                Write-Host "El usuario '$usuario' no existe. No se puede obtener el UID." -ForegroundColor Red
            }
        }
        "3" {
            Write-Host "Saliendo..." -ForegroundColor Yellow
        }
        default {
            Write-Host "Opcion no valida. Introduce 1, 2 o 3." -ForegroundColor Magenta
        }
    }
} while ($opcion -ne "3")
