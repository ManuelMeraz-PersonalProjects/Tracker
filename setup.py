#!/usr/bin/env python

import os
import setuptools

DIR = os.path.dirname(__file__)
REQUIREMENTS = os.path.join(DIR, "requirements.txt")

with open(REQUIREMENTS) as f:
    reqs = f.read()

setuptools.setup(
    name="tracker",
    version="0.0.0",
    description="Macronutrient and Exercise tracking",
    url="https://github.com/ManuelMeraz/Tracker",
    author="Manuel Meraz",
    license="MIT",
    packages=setuptools.find_packages(),
    install_requires=reqs.strip().split("\n"),
    entry_points={"console_scripts": ["pytext = pytext.main:main"]},
)
