from conans import ConanFile, CMake
   
class QuadrocopterCore(ConanFile):
    name = "QuadrocopterCore"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "virtualenv", "virtualrunenv", "cmake_find_package", "cmake"

    def requirements(self):
        self.requires("wiringpi/cci.20210727")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        pass
    def package_info(self):
        pass