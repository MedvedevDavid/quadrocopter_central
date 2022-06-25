CreateBuild:
	mkdir build
	cd build
	cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"

BuildProject:
	mkdir build
	cd build
	make all


RunProject:
	./build/src/Quadrocopter_Central

RunTest:
	./build/tests/Quadrocopter_Central
