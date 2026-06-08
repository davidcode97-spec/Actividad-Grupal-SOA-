# Ejercicio 1 - Clasificación de notas
$nota = Read-Host "Introduce tu nota (0-20)"
$nota = [double]$nota

if ($nota -ge 16 -and $nota -le 20) {
    Write-Host "Muy bueno" -ForegroundColor Green
} elseif ($nota -ge 14 -and $nota -le 15.99) {
    Write-Host "Bueno" -ForegroundColor Cyan
} elseif ($nota -ge 12 -and $nota -le 13.99) {
    Write-Host "Lo suficientemente bueno" -ForegroundColor Yellow
} elseif ($nota -ge 10 -and $nota -le 11.99) {
    Write-Host "Medio" -ForegroundColor DarkYellow
} elseif ($nota -lt 10) {
    Write-Host "Insuficiente" -ForegroundColor Red
} else {
    Write-Host "Nota fuera de rango (debe ser entre 0 y 20)" -ForegroundColor Magenta
}
