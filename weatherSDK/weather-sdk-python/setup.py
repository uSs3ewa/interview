from setuptools import find_packages, setup

setup(
    name="weather-sdk",
    version="1.0.0",
    packages=find_packages(),
    install_requires=["requests"],
    entry_points={
        "console_scripts": [
            "weather-sdk = demo:main",
        ]
    },
)
