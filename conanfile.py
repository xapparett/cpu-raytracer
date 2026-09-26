from conan import ConanFile

from conan.tools.cmake import CMake
from conan.tools.cmake import CMakeToolchain
from conan.tools.cmake import CMakeDeps

class CPURaytracer(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    
    def requirements(self):
        self.requires("stb/cci.20240531")
    
    def build_requirements(self):
        self.tool_requires("cmake/[>=3.25]")
    
    def generate(self):
        tc = CMakeToolchain(self)
        tc.generator = "MinGW Makefiles"
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()
    
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()