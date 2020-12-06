#Executable Outputs
auto_aim.exe: auto_aim.o Stepper.o
	g++ auto_aim.o Stepper.o ../pixy2/build/libpixyusb2/libpixy2.a -o auto_aim.exe -lwiringPi -lusb-1.0

#Mains
auto_aim.o: ../auto_aim.cpp
	g++ -c ../auto_aim.cpp

#Supporting classes
Stepper.o: ../private/Stepper.cpp ../public/Stepper.h ../public/Timer.h
	g++ -c ../private/Stepper.cpp -lwiringPi

clean:
	rm *.o *.exe
