# A Python and C++ inline REST Exchange APM agent

[![Build Status](https://travis-ci.org/gatkinso/challenge.svg?branch=master)](https://travis-ci.org/gatkinso/challenge) [![codecov.io](https://codecov.io/gh/gatkinso/challenge/coverage.svg?branch=master)](https://codecov.io/gh/gatkinso/challenge?branch=master) [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Detailed test and test coverage information is located at:
https://my.cdash.org/index.php?project=Challenge

# Overview
This project is an unsolicited entry for an employment code challenge I found online.  While I am not applying for the job (yet), the challenge looked interesting enough just to do in order to learn something new.... in this case actually learning how to implement a REST API using Flask, and integrate it with other programming languages.  Also, learn how to integrate with Travis-CI, codecov.io, and CDash.

# Agent
This project is an Application Performance Monitoring (APM) middleware library for Python.  It will preprocess both the request and response side of a REST API exchange, and create various telemetry about the exchange.

# Architecture
The agent is implemented in C++, with a Python Flask interface.  It used CMake as the
build system.  It uses Google Protocol Buffers for the IPC serialization.  Usually
serializing to JSON, we can flip to the binary format trivially.

(I was initially thinking this would be a Flask Extension... however I am not sure that is the best way to go.  You can see vestiges of this in the code base, especially the flask-exagent submodule.)

It is imagined that this software will primarily be run on Linux.  Much of the C++ code is based on or inspired by cross platform C++ projects that I have implemented in the past, however I have really only targeted Linux in the CMake files.  It would be fairly trivial to extend this code base to Mac and Windows.

My inner muse thinks that a bevy of thin front ends like Flask, Django, or what have you, interfacing with the high performance C++ backend is the way to go. The front end need not be Python:  C, C++, Ruby... there are many possibilities for agent shims which allow us to keep our IPC and backend stable.  A big plus for the C++ backend is power efficiency...

Mobile anyone?

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

HTML formatted code should be generated in the <workspace>/build/code_coverage directory.

## Unit tests
In your build directory, do this...

```
> ctest .
```

This should invoke both the C++ and Python unit tests.

# Summary
I cannot reveal the company this challenge is for - they ask that their name not be used lest other candidates find a submitted solution and draw inspiration from it (if not outright plagiarize it).

However the conditions of this challenge are pretty cool.  The code remains the property of the applicant and they encourage it's inclusion into the applicant's portfolio... even to use to it present to other prospective employers!

This is pretty progressive thinking.  It stands in stark contrast to some other parasitic creatures at unethical organizations that essentially are using code challenges as a source of free labor.

I encourage you to check it out and see if it has anything to offer you.  It is released under the GPLv3.  The Flask extension under the simplified BSD license.



