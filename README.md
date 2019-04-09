# A Python and C++ inline REST Exchange APM agent

[![Build Status](https://travis-ci.org/gatkinso/challenge.svg?branch=master)](https://travis-ci.org/gatkinso/challenge) [![codecov.io](https://codecov.io/gh/gatkinso/challenge/coverage.svg?branch=master)](https://codecov.io/gh/gatkinso/challenge?branch=master) [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Detailed test and test coverage information is located at:
https://my.cdash.org/index.php?project=Challenge

# Overview
This project is an unsolicited entry for an employment code challenge I found online.  While I am not applying for the job (yet), the challenge looked interesting enough to do simply to learn something new... in this case actually learning how to implement a REST API, Flask, and integrate it with other programming languages.  Also, learn how to integrate with Travis-CI, codecov.io, and CDash.

Most of these things I did not know before starting this project!  I'm a C++ man.  This other stuff... all new to me.

# Agent
This project is an Application Performance Monitoring (APM) middleware library for Python.  It will preprocess both the request and response side of a REST API exchange, and create various telemetry about the exchange.  This data will be stored in a CSV file.

# Architecture
The agent is implemented in C++, with a Python interface for a simple Flask application.  It uses CMake as the build system, and Google Protocol Buffers for the IPC serialization.  Usually serializing to JSON, we can flip to the protocol buffer binary serialization format easily.

I was initially thinking this would be a Flask Extension... however I am not sure that is the best way to go.  You can see vestiges of this in the code base, especially the flask-exagent submodule.  My inner muse thinks that a bevy of thin front ends for Flask, Django, (or what have you), interfacing with the high performance C++ back end is the way to go. The front end need not even be Python:  C, C++, Ruby... there are many possibilities for agent shims which allow us to keep our IPC and processing back end stable.  A big plus for the C++ backend is power efficiency... mobile anyone?

It is imagined that this software will primarily be run in a Linux container.  Much of the C++ code is based on or inspired by cross platform C++ projects that I have implemented in the past, however I have really only targeted Linux in the CMake files.  It would be fairly easy to extend this code base to Mac and Windows.

Actual deployment will probably never happen, however I have included a couple of Dockerfiles that start down that road.  I am going to leverage what I learn here for another project I am writing called Skywire that will indeed be deployed to a cloud provider.

Because of that I am holding back some of my cooler "Stupid Protocol Buffer Tricks."  You just get this watered down version.  Trust me when it comes to protobuf, I am the master.

# Dependencies
| Dependency              | Version | URL                                         |
|-------------------------|---------|---------------------------------------------|
| CMake                   | 3.8     | https://github.com/Kitware/CMake            |
| Google Protocol Buffers | 3.7.1   | https://github.com/protocolbuffers/protobuf |
| Google Test             | 1.8.1   | https://github.com/google/googletest        |

For more detail on dependencies you can always refer to the .travis.yml or Dockerfiles.

## A Note on Google Protocol Buffers
Google.  Why must you vex us so?  When building Protocol Buffers for use with this project, be sure to specify that the CMAKE_POSITION_INDEPENDENT_CODE option is set to ON (this sets the gcc compile flag -fPIC).  The agent will not link correctly if this is not set.
```
cmake -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON ../cmake
```

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
  
Your build artifacts should be in the  <topsrc>/build/staging directory.

## Unit tests
To run the unit tests, in your build directory, do this...

```
> ctest .
```

This should invoke both the C++ and Python unit tests.

# Testing
In the flask-exagent submodule, I included a little example Flask application (app.py) that I found in the blogosphere which I instrumented.

Perform the following steps to setup your environment...

1. Build the agent
2. In the agent build/staging dir, create a Python3 virtual environment (Python 2 was not tested.)
3. pip install protobuf
4. Set your PYTHONPATH as needed
5. Run: python app.py
6. In your browser, paste in this URL and hit Enter:  http://127.0.0.1:5000/todo/api/v1.0/tasks/2

You should see a file named agent_output.txt in your working directory.

# Using the agent

In your Flask application, do this:
````
from flask_exagent import FlaskExagent        # add this import

app = Flask(__name__, static_url_path = "")   # keep this

agent = FlaskExagent(app)                     # replace 'App' with 'Flask'
````

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

# Issues...
This code works.  However there are always warts...

* The Transport.proto file.  My C++-centic view of the universe has it living in the c++/ branch of the source.  It probably should not live there since the Python code is using it as well.  I just lazily plopped the Python code generation there because it was convienient and I knew that it would work.
* The mixed Python/C++ unit testing is clunky.  It just is.
* I am not sure that the coverage metrics are being generated correctly.  Certainly what is being reported to CDash is incorrect.  The codecov.io metrics look better, but are not including Python coverage.
* Additionally, the way the coverage files are being and staged is a bit hamfisted.  It doesn't even rise to the level of roast beef.  (What???)
* Something is broken in the coverage report generation.  It is pulling in system file headers.  Will I fix it?  Perhaps.
* In the C++ code there are many copy operations that could easily be eliminated.
* I am not bothering to increment/decrement instance counters in the C(++) extension.
* A dearth of error checking, logging, or exception handling.
* I am using CMake to build the libagent extension.  I have strong reasons for not replying on Python for this.

# Summary
I cannot reveal the company this challenge is for - they ask that their name not be used lest other candidates find a submitted solution and draw inspiration from it (if not outright plagiarize it).

However the conditions of this challenge are pretty cool.  The code remains the property of the applicant and they encourage it's inclusion into the applicant's portfolio... even to use to it present to other prospective employers!

This is pretty progressive thinking.  It stands in stark contrast to some other parasitic creatures at unethical organizations that essentially are using code challenges as a source of free labor.

I encourage you to check it out and see if it has anything to offer you.  It is released under the GPLv3.  The Flask extension under the simplified BSD license.



