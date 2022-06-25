
#Not working
CreateBuild:
	mkdir build
	cd build
	cmake ..

BuildProject:
	cd build
	make all


RunProject:
	./build/src/Quadrocopter_Central_run

RunTest:
	./build/tests/Quadrocopter_Central_tst
