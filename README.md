
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=sakcakoca_RawBufferProject&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=sakcakoca_RawBufferProject)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=sakcakoca_RawBufferProject&metric=bugs)](https://sonarcloud.io/summary/new_code?id=sakcakoca_RawBufferProject)
[![Vulnerabilities](https://sonarcloud.io/api/project_badges/measure?project=sakcakoca_RawBufferProject&metric=vulnerabilities)](https://sonarcloud.io/summary/new_code?id=sakcakoca_RawBufferProject)
[![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=sakcakoca_RawBufferProject&metric=reliability_rating)](https://sonarcloud.io/summary/new_code?id=sakcakoca_RawBufferProject)
[![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=sakcakoca_RawBufferProject&metric=sqale_rating)](https://sonarcloud.io/summary/new_code?id=sakcakoca_RawBufferProject)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/832fd9eab7d644e9bc3e80ed8408631f)](https://www.codacy.com/gh/sakcakoca/RawBufferProject/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=sakcakoca/RawBufferProject&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/gh/sakcakoca/RawBufferProject/branch/master/graph/badge.svg?token=X4W14HNP37)](https://codecov.io/gh/sakcakoca/RawBufferProject)
<a href="https://scan.coverity.com/projects/sakcakoca-rawbufferproject">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/23025/badge.svg"/>
</a>

<!-- Sonar Cloud setup is done with https://sonarcloud.io/projects/create link. It is free for public repos. -->

Platform | CI Status
---------|:---------
Build and Test on Ubuntu, MacOS, Windows | [![CMake on multiple platforms](https://github.com/sakcakoca/RawBufferProject/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/sakcakoca/RawBufferProject/actions/workflows/cmake-multi-platform.yml)
Windows on Appveyor  | [![Windows Build status](https://ci.appveyor.com/api/projects/status/github/sakcakoca/RawBufferProject?branch=master&svg=true)](https://ci.appveyor.com/project/sakcakoca/rawbufferproject)
<!-- OSX      | [![OSX Build Status](http://badges.herokuapp.com/travis/sakcakoca/RawBufferProject?env=BADGE=OSX&label=build&branch=master)](https://travis-ci.org/sakcakoca/RawBufferProject) -->
<!-- Linux    | [![Linux Build Status](http://badges.herokuapp.com/travis/sakcakoca/RawBufferProject?env=BADGE=Ubuntu_18.04&label=build&branch=master)](https://travis-ci.org/sakcakoca/RawBufferProject) -->


# RawBufferProject

RawBufferProject is a header-only C++ library for managing raw byte data buffers.
General purpose buffer to store data read from TCP, UDP, SerialChannel, CAN, 1553, etc.

## Usage

### Installation

Since this is a header-only library, you only need to include the `RawBuffer.h` header file in your project.

### Getting Started

1. Include the `RawBuffer.h` header file in your project:

```cpp
#include "RawBuffer.h"
```

2. Use the RawBuffer class to manage raw byte data:

```cpp
// Example usage
RawBuffer buffer;

// Add single byte
buffer.push_back(0xAB);

// Add multiple bytes from a container
std::vector<unsigned char> data = {0x01, 0x02, 0x03};
buffer += data;

// Add bytes from a C-style array
unsigned char rawArray[] = {0xAA, 0xBB, 0xCC};
buffer += rawArray;

// Print buffer content
std::cout << buffer;
```

## Features

* Easily manage raw byte data buffers.
* Supports adding single bytes, containers, and C-style arrays.
* Iterators for traversal and manipulation of buffer contents.
