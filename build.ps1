param(
    [switch]$Clean,
    [switch]$Run,
    [switch]$Export
)

# Optionally remove the build directory
if ($Clean) {
    if (Test-Path build) {
        Write-Host "Cleaning build directory..."
        Remove-Item -Recurse -Force build
    } else {
        Write-Host "No existing build directory to clean."
    }
}

# Configure the project
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=gcc

if ($LASTEXITCODE -ne 0) {
    Write-Error "CMake configuration failed."
    exit $LASTEXITCODE
}

# Build the project
cmake --build build

if ($LASTEXITCODE -ne 0) {
    Write-Error "Build failed."
    exit $LASTEXITCODE
}

Write-Host "Build completed successfully."

# Optionally run the executable
if ($Run) {
    $exePath = "build\movie_ticket_console.exe"

    if (Test-Path $exePath) {
        Write-Host "Running movie_ticket_console.exe..."
        & $exePath
    } else {
        Write-Warning "Executable not found at $exePath"
    }
}

# Optionally export the build
if ($Export) {
    $distDir = "dist"
    Write-Host "Exporting production files to $distDir..."
    if (Test-Path $distDir) { Remove-Item -Recurse -Force $distDir }
    New-Item -ItemType Directory -Path "$distDir\data"

    Copy-Item "build\movie-ticket-console.exe" -Destination "$distDir"
    Copy-Item "data\*.csv" -Destination "$distDir\data\"

    Write-Host "Export complete!"
}