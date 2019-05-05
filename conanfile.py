import os

from conans import CMake, ConanFile, tools


class SociTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = (
        "soci/4.0@soci/stable",
        "doxygen_installer/1.8.15@bincrafters/stable",
        "nameof/0.8.2@nameof/stable",
        "range-v3/0.5.0@ericniebler/stable",
        "gtest/1.8.1@bincrafters/stable",
    )

    generators = "cmake"

    options = {
        "enable_documentation": [True, False],
        "enable_tests": [True, False]
    }

    default_options = {
        "soci:sqlite3": True,
        "enable_documentation": False,
        "enable_tests": False,
    }

    def build(self):
        cmake = CMake(self)
        # Current dir is "test_package/build/<build_id>" and CMakeLists.txt is
        # in "test_package"
        cmake.configure(
            defs={
                "ENABLE_DOCUMENTATION": self.options.enable_documentation,
                "ENABLE_TESTS": self.options.enable_tests,
            })

        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")
        self.copy("*.a", dst="bin", src="lib")

    def test(self):
        if not tools.cross_building(self.settings):
            os.chdir("bin")
            self.run(".%smain" % os.sep)
