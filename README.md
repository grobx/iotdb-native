# IoTDB Native

[![Build Status (roberti42)](https://travis-ci.com/roberti42/iotdb-native.svg?branch=dev)](https://travis-ci.com/roberti42/iotdb-native)
[![Build Status (giorgiozoppi](https://travis-ci.com/giorgiozoppi/iotdb-native.svg?branch=dev)](https://travis-ci.com/giorgiozoppi/iotdb-native)

IoTDB Native is a specialized database management system for time series data generated by a network of IoT devices with low computational power. 
It targets a workload that has high-frequency data write, large-volume data storage, and complex analytical queries. 
IoTDB supports queries that are common in monitoring and collecting metrics in IoT devices, namely filtering by predicates, query by time range, group aggregation, and data sample. Data in IoTDB is stored in TsFile, a file format designed for accessing, compressing, and storing time series data. Its storage is organized in LSM based structure catering to write throughput.

This repository is the on stage port of Apache IoTDB https://iotdb.apache.org to a native platform.

## Roadmap

The stages of the port will be:

1. [TsFile](https://iotdb.apache.org/SystemDesign/1-TsFile/1-TsFile.html)
2. Server Interface.
3. [QueryEngine](https://iotdb.apache.org/SystemDesign/2-QueryEngine/1-QueryEngine.html)
4. [SchemaManager](https://iotdb.apache.org/SystemDesign/3-SchemaManager/1-SchemaManager.html)
5. [StorageEngine](https://iotdb.apache.org/SystemDesign/4-StorageEngine/1-StorageEngine.html)

At the moment we have just started the first stage.

## Development Guidelines

The master branch should always be stable (all automated test passed in CI, code
reviewed).  Every feature is developed on a branch starting from the *dev* branch (starting from the HEAD, not from a specific tag/commit). After creating the branch, a new PR in draft mode (for merging the branch against dev) is immediately created to allow tracking and discussing it.
When the feature is complete we switch the PR from Draft to Ready and we assign a reviewer. The reviewer should have a clear vision of the goal of the PR if any changes/compromises were made along the way.
When the PR is approved, the PR should be merged unless other important tasks have higher priority.
Every PR is opened versus the dev branch. Each PR after the first release should have associated a github ticket.

### Release

Monthly we do a release process. We freeze dev and we do testing for a week than we tag a release and merge the master with the dev after all fixes are tested and applied.

### How to Commit Code into the Repository

- Choose a repository where you shall develop, for example rocket-s3, and clone it. You must start adding from branch dev, otherwise the continuous integration system will not work.

`$ git clone https://github.com/giorgiozoppi/iotdb-native`

`$ git checkout dev`

- Create a new branch, possibly specifying the GitHub ticket where the necessity of the added feature/fix was originated:

`$ git checkout -b IOTDB-tsfile-encoder`
- Add and/or modify files, committing them to the local branch when time arises:

`$ git commit -a -m "Added encoder file support"`
- Then push modifications upstream:

`$ git push --set-upstream origin IOTDB-tsfile-encoder`

A new branch will be visible in the GitHub web application from the branches tab of the repository. The invitation to open a pull request will be available aside.

