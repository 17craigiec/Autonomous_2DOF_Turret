#Executable Outputs
auto_aim.exe: auto_aim.o Stepper.o Turret.o
	g++ auto_aim.o Stepper.o Turret.o ../pixy2/build/libpixyusb2/libpixy2.a -o auto_aim.exe -lwiringPi -lusb-1.0 -std=c++11 -pthread

#Mains
auto_aim.o: ../auto_aim.cpp
	g++ -c ../auto_aim.cpp

#Supporting classes
Stepper.o: ../private/Stepper.cpp ../public/Stepper.h ../public/Timer.h
	g++ -c ../private/Stepper.cpp -lwiringPi

Turret.o: ../private/Turret.cpp ../public/Turret.h
	g++ -c ../private/Turret.cpp -lwiringPi

clean:
	rm *.o *.exe
