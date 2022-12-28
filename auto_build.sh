./set_env.sh
mkdir build
cd build
conan install --profile=../ubuntu_to_rpi .. --build=missing
conan build ..
cd ..