# A Python and C++ inline REST Exchange APM agent

[![Build Status](https://travis-ci.org/gatkinso/challenge.svg?branch=master)](https://travis-ci.org/gatkinso/challenge) [![codecov.io](https://codecov.io/gh/gatkinso/challenge/coverage.svg?branch=master)](https://codecov.io/gh/gatkinso/challenge?branch=master) [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Detailed test and test coverage information is located at:
https://my.cdash.org/index.php?project=Challenge

# Overview
This project is an unsolicited entry for an employment code challenge I found online.  While I am not applying for the job (yet), the challenge looked interesting enough just to do in order to learn something new... in this case actually learning how to implement a REST API, Flask, and integrate it with other programming languages.  Also, learn how to integrate with Travis-CI, codecov.io, and CDash.

Most of these things I did not know before starting this project!  I'm a C++ man.  This other stuff... all new to me.

# Agent
This project is an Application Performance Monitoring (APM) middleware library for Python.  It will preprocess both the request and response side of a REST API exchange, and create various telemetry about the exchange.  This data will be stored in a CSV file, but that will be extended pretty quickly.

# Architecture
The agent is implemented in C++, with a Python interface for a simple Flask application.  It uses CMake as the build system, and Google Protocol Buffers for the IPC serialization.  Usually serializing to JSON, we can flip to the protocol buffer binary format trivially.

I was initially thinking this would be a Flask Extension... however I am not sure that is the best way to go.  Perhaps it would be more accurate to say the "only way to go."  You can see vestiges of this in the code base, especially the flask-exagent submodule.  My inner muse thinks that a bevy of thin front ends for Flask, Django, (or what have you), interfacing with the high performance C++ back end is the way to go. The front end need not be Python:  C, C++, Ruby... there are many possibilities for agent shims which allow us to keep our IPC and processing back end stable.  A big plus for the C++ backend is power efficiency... mobile anyone?

It is imagined that this software will primarily be run in a Linux container.  Much of the C++ code is based on or inspired by cross platform C++ projects that I have implemented in the past, however I have really only targeted Linux in the CMake files.  It would be fairly easy to extend this code base to Mac and Windows.

Actual deployment will probably never happen, however I have included a couple of Dockerfiles that start down that road.  I am going to leverage what I learn here for another project I amn writing called Skywire that will indeed be deployed to a cloud provider.

# Dependencies
| Dependency              | Version | URL                                         |
|-------------------------|---------|---------------------------------------------|
| CMake                   | 3.8     | https://github.com/Kitware/CMake            |
| Google Protocol Buffers | 3.7.1   | https://github.com/protocolbuffers/protobuf |
| Google Test             | 1.8.1   | https://github.com/google/googletest        |

For more detail on dependencies you can always refer to the .travis.yml for Dockerfiles.

# Building
Building is easy.

## Development

```
> git checkout https://github.com/gatkinso/challenge.git
> cd challenge
> mkdir build && cd build
> cmake ..
> cmake --build .
```

Voilà!

## Coverage

```
> git checkout https://github.com/gatkinso/challenge.git
> cd challenge
> mkdir build && cd build
> cmake -DGENERATE_COV:BOOL=TRUE ..
> cmake --build . --target gcov
```

HTML formatted unit test coverage information should be generated in the <topsrc>/build/code_coverage directory.

## Unit tests
In your build directory, do this...

```
> ctest .
```

This should invoke both the C++ and Python unit tests.

## Building Docker image
This is easy too.

The image build is a two stage pipeline:  
1. Build the base image with all dependencies
2. Build the development image with the built source

Currently, a test and deployment stage do not exist.  :-)

To build the base image, in your top source directory type:
```
> docker build . -f Dockerfile.base -t challenge_base
```

To build the development image, in your top source directory type:
```
> docker build . -f Dockerfile.dev -t challenge_dev
```
# Open Questions...
* The Transport.proto file.  My C++centic view of the universe has it living in the c++/ branch of the source.  I probably should not live there since the Python code is using it as well.  I just lazily plopped the Python generation there because it was convienient and I knew that it would work.
* The mixed Python/C++ unit testing is clunky.  It just is.
* I am not sure that the coverage metrics are being generated correctly.  Certainly what is being reported to CDash is incorrect.  The cocecov.io metrics look better, but are not including Python coverage.

# Summary
I cannot reveal the company this challenge is for - they ask that their name not be used lest other candidates find a submitted solution and draw inspiration from it (if not outright plagiarize it).

However the conditions of this challenge are pretty cool.  The code remains the property of the applicant and they encourage it's inclusion into the applicant's portfolio... even to use to it present to other prospective employers!

This is pretty progressive thinking.  It stands in stark contrast to some other parasitic creatures at unethical organizations that essentially are using code challenges as a source of free labor.

I encourage you to check it out and see if it has anything to offer you.  It is released under the GPLv3.  The Flask extension under the simplified BSD license.



