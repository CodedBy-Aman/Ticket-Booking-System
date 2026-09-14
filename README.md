# Movie Ticket Booking System

B.Tech CSE Semester 5 - System Design Assignment 1

## Build
```bash
cmake -S . -B build
cmake --build build
```

## Project layout
- `src/app/main.cpp` contains the runnable integration demo.
- `src/classes/` contains the individual class implementation files used as assignment references.
- `CMakeLists.txt` builds only the integration demo, keeping the standalone class files available without compiling duplicate class definitions.

Run:
```bash
./build/movie_booking
```

Windows:
```powershell
.uild\Debug\movie_booking.exe
```

## Required features
1. List movies
2. List shows
3. Display seat availability
4. Book one or more seats
5. Silver ₹150 / Gold ₹250 / Platinum ₹400
6. UPI / Card / Cash
7. Print ticket
8. Cancel booking and release seats

## OOP
Encapsulation, abstraction, inheritance, runtime polymorphism, compile-time polymorphism,
static member, this keyword, composition, aggregation and association are represented.
