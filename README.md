# Movie Ticket Console

## Project Description

`Movie Ticket Console` is a console-based cinema ticket management project written in C. It simulates the core workflow of a movie ticket system in a terminal application, with separate responsibilities split across dedicated service modules.

The project is currently organized around:

- `auth` services for login and role-based access
- `movie` services for listing, searching, adding, editing, and deleting movies
- `screening` services for viewing screenings, showing seat maps, creating screenings, and canceling screenings
- `customer` services for booking tickets, canceling tickets, and viewing purchase history
- `manager` services for administrative reporting such as revenue tracking
- CSV-based data storage for movies, screenings, tickets, and users

This structure makes the codebase easier to extend and maintain while keeping the application modular and straightforward to build with CMake.

## Course Information
- Course name: `IT1.103.3 - Advanced Programming`
- Assignment title: `Course Project`
- Instructor: `M.Sc.Tran Thi Dung`
- Institution: `University of Transport and Communications Campus in Ho Chi Minh City`

## Requirements
- Language: `C17`
- Compiler: `GCC`
- Build system: `CMake`
- Build generator: `Ninja`
- IDE: `VS Code` is highly recommended)

## Build and Run on Windows

1. Clone the repository:

```powershell
git clone https://github.com/CQ-66-CNTT-Unknown/movie-ticket-console.git
cd movie-ticket-console
```

2. Run the PowerShell build script:
- Normal build
```powershell
./build.ps1
```
- Clean build
```powershell
./build.ps1 -Clean
```
- Build then Run
```powershell
./build.ps1 -Run
```

3. After the build completes, open the project in your IDE or run the generated executable from the build folder.


## Authors

- [`Tran Trong Nguyen` ](https://github.com/TTNguyen2505)- Student ID: `6651071099`
- [`Le Phan Trung Dong`](https://github.com/trungdong158) - Student ID: `6651071016`
- [`Nguyen Le Quy Trong`](https://github.com/pahmnguyen) - Student ID: `6651071084`
- [`Nguyen Phuc Khai Tam`](https://github.com/NgpkTam0910) - Student ID: `6651071065`
