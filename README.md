# quadrocopter_central


Quadrocopter central is a quadrocopter project for a raspberry pi.
 
To Setup:

# Run:
"sudo apt-get install build-essential cmake" 

# Wiring pi:
sudo apt-get install git-core
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
./build

https://learnembeddedsystems.co.uk/wiringpi-on-the-raspberry-pi-zero-2-w



sudo apt-get install -y python-smbus
sudo apt-get install -y i2c-tools


sudo raspi-config

https://github.com/sarfata/pi-blaster
https://ozzmaker.com/software-pwm-on-a-raspberry-pi/
RPI 0 Need to be added.


# Conan:
conan create ../conanfile.py --profile=../ubuntu_to_rpi --build=wiringpi --build=QuadrocopterCore


ssh cdron bash << 'EOF'
    sudo mkdir -p /usr/local/lib/arm-linux-gnueabihf
    sudo mv libstdc++.so.6.0.30 $_
    sudo ldconfig
EOF

cat >> ~/.ssh/config << 'EOF'
Host cdron
    HostName dronpi@192.168.0.191
    User dronpi
EOF

source set_env.sh 
source ~/.profile


Debugg: gdb-multiarch ./Quadrocopter_Central_run