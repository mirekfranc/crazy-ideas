import os
from setuptools import setup

def read(fname):
    try:
        return open(os.path.join(os.path.dirname(__file__), fname)).read()
    except:
        return "Zebra's world"

setup(
    name='zebras-world',
    version='0.1',
    description="Zebra's world",
    author='Miroslav Franc',
    author_email='mfranc@gmx.com',
    url='https://github.com/mirekfranc/crazy-ideas/zebras-world',
    packages=['zebras-world'],
    package_dir={'zebras-world': 'zebras-world'},
    scripts=['zebras-world/zebras-world'],
    long_description=read('README'),
    classifiers=[
        "License :: OSI Approved :: GNU Library or Lesser General Public License (LGPL)",
        "Programming Language :: Python :: 2.6",
        "Programming Language :: Python :: 2.7",
        "Development Status :: 3 - Alpha",
        "Intended Audience :: End Users/Desktop",
        "Topic :: Games/Entertainment :: Simulation",
        "Topic :: Games/Entertainment",
        "Operating System :: POSIX"
    ],
    keywords='game simulation',
    license='LGPL',
    setup_requires=['setuptools']
    )
