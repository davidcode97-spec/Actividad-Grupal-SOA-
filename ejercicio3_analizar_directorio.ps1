# Ejercicio 3 - Analizar contenido de un directorio (pasado como parámetro)
param(
    [Parameter(Mandatory=$true)]
    [string]$Directorio
)

if (-not (Test-Path -Path $Directorio -PathType Container)) {
    Write-Host "Error: '$Directorio' no es un directorio válido o no existe." -ForegroundColor Red
    exit 1
}

$archivosEstandar = 0
$subdirectorios   = 0
$ejecutables      = 0

$items = Get-ChildItem -Path $Directorio -Force

foreach ($item in $items) {
    if ($item.PSIsContainer) {
        $subdirectorios++
    } elseif ($item.PSObject.TypeNames -contains "System.IO.FileInfo") {
        $archivosEstandar++
        # Comprobar si el archivo es ejecutable (extensiones comunes en Windows)
        $extensionesEjecutables = @(".exe", ".bat", ".cmd", ".ps1", ".sh", ".msi", ".com")
        if ($extensionesEjecutables -contains $item.Extension.ToLower()) {
            $ejecutables++
        }
    }
}

Write-Host ""
Write-Host "Análisis del directorio: $Directorio" -ForegroundColor Cyan
Write-Host "-------------------------------------------"
Write-Host "Archivos estándar : $archivosEstandar" -ForegroundColor White
Write-Host "Subdirectorios    : $subdirectorios"   -ForegroundColor Yellow
Write-Host "Archivos ejecutables: $ejecutables"    -ForegroundColor Green
Write-Host "-------------------------------------------"
