
#Not working
CreateBuild:
	rm -fr build
	mkdir build
	cd build
	conan install ..
	cmake ..



BuildProject:
	cd build
	make all

Deploy:
	scp ./build/bin/Quadrocopter_Central_run dronpi@192.168.0.191:~/bin/Quadrocopter_Central_run

SSH_IN:
	ssh dronpi@192.168.0.191

RunProject:
	./build/src/Quadrocopter_Central_run

RunTest:
	./build/tests/Quadrocopter_Central_tst
