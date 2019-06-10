import os

from conans import CMake, ConanFile, tools


class SociTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    requires = (
        # This specific version of OpenSSL required for
        # android ndk
        # "OpenSSL/1.0.2r@conan/stable",
        # "harfbuzz/2.4.0@bincrafters/stable",
        # End android deps | begin qt  override reqs
        # "freetype/2.9.1@bincrafters/stable",
        # "libpng/1.6.36@bincrafters/stable",
        "glibc_version_header/0.1@bincrafters/stable",
        "doxygen_installer/1.8.15@bincrafters/stable",
        "soci/4.0@soci/stable",
        "nameof/0.8.2@nameof/stable",
        "range-v3/0.5.0@ericniebler/stable",
        "gtest/1.8.1@bincrafters/stable",
        "qt/5.12.0@bincrafters/stable",
    )

    generators = "cmake", "txt", "qt"

    options = {
        "enable_documentation": [True, False],
        "enable_tests": [True, False],
        "fPIC": [True, False],
    }

    default_options = {
        "glibc_version_header:glibc_version": "2.27",
        "soci:shared": True,
        "soci:sqlite3": True,
        "qt:qtquickcontrols": True,
        "qt:qtquickcontrols2": True,
        "enable_documentation": False,
        "enable_tests": False,
        "soci:fPIC": True,
        "fPIC": True,
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
        self.copy("*soci*.a", dst="lib/tracker", src="lib")
        self.copy("*soci*.so*", dst="lib/tracker", src="lib")
        self.copy("*gmock*.a", dst="lib", src="lib")
        self.copy("*gtest*.a", dst="lib", src="lib")

    def test(self):
        if not tools.cross_building(self.settings):
            os.chdir("bin")
            self.run(".%smain" % os.sep)
